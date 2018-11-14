/*
** ************************************************************************** *|
**                              Includes & Defines                            *|
** ************************************************************************** *|
*/

#include "test.h"

/*
** ************************************************************************** *|
**                           Basic Utility Functions                          *|
** ************************************************************************** *|
*/

int	bool_equals(int a, int b)
{
	return (a == 0) ? (b == 0) : (b != 0);
}

int	str_equals(char const *str1, char const *str2)
{
	size_t i;

	if (str1 == str2)
		return (1);
	if (str1 && str2)
	{
		i = 0;
		while (str1[i] && str2[i])
		{
			if (str1[i] != str2[i])
				return (0);
			++i;
		}
		return (str1[0] == str2[0]);
	}
	return (0);
}

char *print_memory(void const *ptr, size_t length)
{
	char *result;
	t_u8 byte;
	char hi;
	char lo;

	if (ptr == NULL)
		return (NULL);
	if (str_equals((char const *)ptr, segstr))
		return (segstr);
	if (!(result = (char *)malloc(length * 3)))
		return (NULL);
	for (size_t i = 0; i < length; ++i)
	{
		byte = ((t_u8 const *)ptr)[i];
		hi = ((byte >> 4) & 0xF);
		lo = (byte & 0xF);
		result[i * 3 + 0] = hi + (hi < 10 ? '0' : 'A' - 10);
		result[i * 3 + 1] = lo + (lo < 10 ? '0' : 'A' - 10);
		result[i * 3 + 2] = (i + 1 == length) ? '\0' : ' ';
	}
	return (result);
}

char		*int_to_string(int number)
{
	char	*result;
	char	digits[12];
	size_t	length = 0;
	size_t	i;
	size_t	j;
	long	n;

	if (number == 0)
	{
		if (!(result = (char *)malloc(2)))
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		i = 0;
		n = (number < 0) ? (long)number * -1 : (long)number;
		while (n > 0)
		{
			digits[i++] = (n % 10) + '0';
			n /= 10;
		}
		if (number < 0)
			digits[i++] = '-';
		digits[i] = '\0';
		while (digits[length])
			++length;
		if (!(result = (char *)malloc(length + 1)))
			return (NULL);
		i = 0;
		j = length - 1;
		while (i < length)
		{
			result[i] = digits[j];
			++i;
			j--;
		}
		result[i] = '\0';
	}
	return (result);
}

char	*str_padleft(char const *str, char c, size_t length)
{
	char	*result;
	long	offset;
	size_t	i;

	if (!(result = (char *)malloc(length + 1)))
		return (NULL);
	offset = length - ft_strlen(str);
	i = 0;
	while (i < (size_t)offset)
	{
		result[i] = c;
		++i;
	}
	while (i < length)
	{
		result[i] = str[i - offset];
		++i;
	}
	result[length] = '\0';
	return (result);
}

/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/

/*	There are a couple of different cross-platform clock possibilities:
**	- CLOCK_REALTIME	System-wide real-time clock. This clock returns the number of seconds and nanoseconds since the Epoch.
**						This clock can be set via clock_settime but doing so requires appropriate privileges, because it's linked to the system time.
**	- CLOCK_MONOTONIC 			Represents monotonic time since some unspecified starting point. This clock cannot be set.
**	- CLOCK_PROCESS_CPUTIME_ID 	High-resolution per-process timer from the CPU.
**	- CLOCK_THREAD_CPUTIME_ID 	Thread-specific CPU-time clock. 
*/
inline void	timer_clock(t_time* result)
{
	if (clock_gettime(CLOCK_MONOTONIC, result) == -1)
	{
		perror("clock_gettime() returned -1");
		exit(EXIT_FAILURE);
	}
}
/*	Define a 10e9 macro we use for nanosecond modulo */
#define BILLION 1000000000L
inline t_time timer_getdiff(t_time start, t_time end)
{
	t_time result;
	
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_nsec = end.tv_nsec - start.tv_nsec;
    if (result.tv_nsec >= BILLION)
    {
        result.tv_nsec -= BILLION;
        result.tv_sec++;
    }
    if (result.tv_sec < 0)
    	result.tv_sec = 0;
    if (result.tv_nsec < 0)
    	result.tv_nsec = 0;
    return (result);
}

/* Returns negative if 'a' is lower than 'b', positive if 'b' > 'a' and 0 if equal. */
inline int timer_compare(t_time a, t_time b)
{
    if (a.tv_sec == b.tv_sec)
    	return (a.tv_nsec - b.tv_nsec);
    else
        return (a.tv_sec - b.tv_sec);
}

void		print_timer_result(t_timer* t, int compare)
{
	t->time1 = timer_getdiff(t->end1, t->start1);
	if (compare)
	{
		t->time2 = timer_getdiff(t->end2, t->start2);
		compare = timer_compare(t->time1, t->time2);
		printf(" [libft:");
		if (compare == 0)
			printf("%lld.%.09ld, libc:", (long long)t->time1.tv_sec, t->time1.tv_nsec);
		else if (compare < 0)
			printf(C_GREEN"%lld.%.09ld"RESET", libc:"C_RED, (long long)t->time1.tv_sec, t->time1.tv_nsec);
		else
			printf(C_RED"%lld.%.09ld"RESET", libc:"C_GREEN, (long long)t->time1.tv_sec, t->time1.tv_nsec);
		printf("%lld.%.09ld"RESET"]", (long long)t->time2.tv_sec, t->time2.tv_nsec);
	}
	else printf(" [libft:%lld.%.09ld]", (long long)t->time1.tv_sec, t->time1.tv_nsec);
}

/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

void	print_test_int(
		char const *test_name,
		char const *function,
		t_u32 result,
		t_u32 expect,
		int can_segfault)
{
	if (test_name)
	{
		if (can_segfault)
			 printf("\n%s - "C_YELLOW"can segfault"RESET, test_name);
		else printf("\n%s", test_name);
		printf(" -> ");
	}
	else printf(", ");
	if (result == expect)
	{
		printf(C_GREEN"OK!"RESET);
	}
	else
	{
		printf(C_RED"ERROR\n");
		if (function[0] == '_')
		{
			char *expected = str_padleft("Expected", ' ', strlen(function) + 2);
			printf("ft%s: %d\n%s: %d"RESET, function,
				result,
				expect);
			free(expected);
		}
		else printf("ft_%s: %d\n   %s: %d"RESET,
				function, result,
				function, expect);
	}
}

void	print_test_str(
		char const *test_name,
		char const *function,
		char const *result,
		char const *expect,
		int can_segfault)
{
	if (test_name)
	{
		if (can_segfault)
			 printf("\n%s - "C_YELLOW"can segfault"RESET, test_name);
		else printf("\n%s", test_name);
		printf(" -> ");
	}
	else printf(", ");
	if (str_equals(result, expect))
	{
		printf(C_GREEN"OK!"RESET);
	}
	else
	{
		if (str_equals(expect, "(n/a)"))
			 printf(C_RED"TEST COULD NOT BE PERFORMED\n"RESET);
		else printf(C_RED"ERROR\n");
		if (function[0] == '_')
		{
			char *expected = str_padleft("Expected", ' ', strlen(function) + 2);
			printf("ft%s: {%s}\n%s: {%s}"RESET, function,
				result,
				expect);
			free(expected);
		}
		else printf("ft_%s: {%s}\n   %s: {%s}"RESET,
				function, result,
				function, expect);
	}
}

void	print_test_mem(
		char const *test_name,
		char const *function,
		void const *result,
		void const *expect,
		size_t length,
		int can_segfault)
{
	int error;
	if (test_name)
	{
		if (can_segfault)
			 printf("\n%s - "C_YELLOW"can segfault"RESET, test_name);
		else printf("\n%s", test_name);
		printf(" -> ");
	}
	else printf(", ");
	error = (result && expect) ?
		(memcmp(result, expect, length) != 0) :
		(result != expect);
	if (!error)
	{
		printf(C_GREEN"OK!"RESET);
	}
	else
	{
		printf(C_RED"ERROR\n");
		if (function[0] == '_')
		{
			char *expected = str_padleft("Expected", ' ', strlen(function) + 2);
			printf("ft%s: {%s}\n%s: {%s}"RESET,
				function, print_memory(result, length),
				expected, print_memory(expect, length));
			free(expected);
		}
		else printf("ft_%s: {%s}\n   %s: {%s}"RESET,
				function, print_memory(result, length),
				function, print_memory(expect, length));
	}
}

void	print_test_strls(
		char const *test_name,
		char const *function,
		char const **result,
		char const **expect,
		int can_segfault)
{
	if (test_name)
	{
		if (can_segfault)
			 printf("\n%s - "C_YELLOW"can segfault"RESET, test_name);
		else printf("\n%s", test_name);
		printf(" -> ");
	}
	else printf(", ");
	int error = FALSE;
	for (int i = 0; result[i] && expect[i]; ++i)
	{
		if (!str_equals(result[i], expect[i]))
		{
			error = TRUE;
			break;
		}
	}
	if (!error)
	{
		printf(C_GREEN"OK!"RESET);
	}
	else
	{
		printf(C_RED"ERROR\n");
		printf("\nft_%s: [", function);
		for (int i = 0; result[i]; ++i)
			printf("%s%s", result[i], result[i + 1] ? ", " : "]");
		printf("\n   Expected: [");
		for (int i = 0; expect[i]; ++i)
			printf("%s%s", expect[i], expect[i + 1] ? ", " : "]");
	}
}

void	print_test_lst(
		char const *test_name,
		char const *function,
		t_list const *result,
		char const *expect[],
		int can_segfault)
{
	int error = FALSE;
	if (test_name)
	{
		if (can_segfault)
			 printf("\n%s - "C_YELLOW"can segfault"RESET, test_name);
		else printf("\n%s", test_name);
		printf(" -> ");
	}
	else printf(", ");
	t_list *lst = (t_list *)result;
	t_u32 i = 0;
	while (lst && expect[i])
	{
		if (!str_equals(lst->content, expect[i]))
			error = TRUE;
		lst = lst->next;
		++i;
	}
	if (lst || expect[i]) error = TRUE;
	if (!error)
	{
		printf(C_GREEN"OK!"RESET);
	}
	else
	{
		printf(C_RED"ERROR\n");
		lst = (t_list *)result;
		printf(    "ft_%s: [", function);
		while (lst)
		{
			printf("%s{%s}", (lst == result ? "" : ", "), lst->content);
			lst = lst->next;
		}
		printf("]\n");
		i = 0;
		printf(" Expected: [", function);
		while (expect[i])
		{
			printf("%s{%s}", (i == 0 ? "" : ", "), expect[i]);
			++i;
		}
		printf("]\n"RESET);
	}
}
