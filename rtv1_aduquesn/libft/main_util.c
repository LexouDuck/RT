/*================ Includes =================*/

#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <ctype.h>
#include <stdio.h>

#include "libft.h"

/*================ Definitions =================*/

#define FALSE	0
#define TRUE	1

#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define RESET     "\x1b[0m"

#define MALLOC_LEN 12

/*================ Segfault handling =================*/

jmp_buf restore;

void segfault_handler(int sig, siginfo_t *info, void *ptr)
{
    if (sig == SIGSEGV)
    {
        longjmp(restore, SIGSEGV);
    }
}

/*================ Testing functions =================*/


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



void	test_int(
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
			printf("ft%s: %d\n Expected: %d"RESET, function,
				result,
				expect);
		else printf("ft_%s: %d\n   %s: %d"RESET,
				function, result,
				function, expect);
	}
}

void	test_str(
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
			printf("ft%s: {%s}\n Expected: {%s}"RESET, function,
				result,
				expect);
		else printf("ft_%s: {%s}\n   %s: {%s}"RESET,
				function, result,
				function, expect);
	}
}

void	test_mem(
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
			printf("ft%s: {%s}\n Expected: {%s}"RESET, function,
				print_memory(result, length),
				print_memory(expect, length));
		else printf("ft_%s: {%s}\n   %s: {%s}"RESET,
				function, print_memory(result, length),
				function, print_memory(expect, length));
	}
}

void	test_strarray(
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

void	test_lst(
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



/*================ Test utility functions =================*/

void	ptrtolower(char *c)
{
	*c = ft_tolower(*c);
}

void	ptrtolower_1on2(t_u32 i, char *c)
{
	if (i % 2 == 0)
		*c = ft_tolower(*c);
}

char	toupper_chr(char c)
{
	if ('a' <= c && c <= 'z')
		return (c - 'a' + 'A');
	else return (c);
}

char	toupper_1on2(t_u32 i, char c)
{
	if (i % 2)
		c = ft_toupper(c);
	return (c);
}

/*
Returns a newly allocated lstelem (new_elem) from a lstelem containing a string in its content(elem).
The new lstelem applies f to every char in the content of elem while building new_elem.
Behavior if elem->content is not nul-terminated is undefined.*/
t_list	*ft_lstelem_strmap(t_list *elem, char (*f)(char))
{
	t_list	*new_elem;
	char	*new_str;

	if (elem == NULL || elem->content == NULL)
		return (NULL);
	if (!(new_elem = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(new_str = ft_strmap(elem->content, f)))
	{
		free(new_elem);
		return (NULL);
	}
	new_elem->content = new_str;
	new_elem->content_size = elem->content_size;
	return (new_elem);
}
void	ft_lstiter_toupper(t_list *elem)
{
	ft_lstelem_strmap(elem, toupper_chr);
}
t_list	*ft_lstmap_toupper(t_list *elem)
{
	return ft_lstelem_strmap(elem, toupper_chr);
}
