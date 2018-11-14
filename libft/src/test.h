
#ifndef LIBFT_TEST_H
# define LIBFT_TEST_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

// for the standard functions, to compare
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
// for segfault handling
# include <setjmp.h>
# include <signal.h>
// for speed testing
# include <time.h>

# include "../libft.h"
# include "../libft_memory.h"
# include "../libft_string.h"
# include "../libft_char.h"
# include "../libft_convert.h"
# include "../libft_math.h"
# include "../libft_list.h"
# include "../libft_io.h"

/*
** ************************************************************************** *|
**                              Segfault handling                             *|
** ************************************************************************** *|
*/

extern char* nullstr;
extern char* segstr;
struct sigaction sig;
int			segfault;
jmp_buf 	restore;

void		segfault_handler(int sig, siginfo_t *info, void *ptr);

/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/
typedef struct timespec t_time;

typedef struct	s_timer
{
    t_time	start1;
    t_time	start2;
    t_time	end1;
    t_time	end2;
    t_time	time1;
    t_time	time2;
}				t_timer;

void	timer_clock(t_time* t);
t_time	timer_getdiff(t_time start, t_time end);
int		timer_compare(t_time a, t_time b);
void	print_timer_result(t_timer* timer, int compare);

/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

extern char const* test1; extern size_t const test1_len; 
extern char const* test2; extern size_t const test2_len; 
extern char const* test3; extern size_t const test3_len; 

void	print_nonstd(void);

int		test_memory(void);
int		test_string(void);
int		test_char(void);
int		test_convert(void);
int		test_math(void);
int		test_list(void);
int		test_io(void);

/*
** ************************************************************************** *|
**                              Utility Functions                             *|
** ************************************************************************** *|
*/

int		bool_equals(int a, int b);

int		str_equals(char const *str1, char const *str2);

char	*print_memory(void const *ptr, size_t length);

char	*int_to_string(int number);

char	*str_padleft(char const *str, char c, size_t length);



void	print_test_int(
		char const *test_name,
		char const *function,
		t_u32 result,
		t_u32 expect,
		int can_segfault);

void	print_test_str(
		char const *test_name,
		char const *function,
		char const *result,
		char const *expect,
		int can_segfault);

void	print_test_mem(
		char const *test_name,
		char const *function,
		void const *result,
		void const *expect,
		size_t length,
		int can_segfault);

void	print_test_strls(
		char const *test_name,
		char const *function,
		char const **result,
		char const **expect,
		int can_segfault);

void	print_test_lst(
		char const *test_name,
		char const *function,
		t_list const *result,
		char const *expect[],
		int can_segfault);

#endif
