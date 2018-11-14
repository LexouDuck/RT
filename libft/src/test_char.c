
#include "test.h"

int		test_char(void)
{

printf("\n");

	printf("       .--------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_char   }===---\n");
	printf("       '--------------------------'       \n");

//	int		ft_isalpha(int c);
//	int		ft_isdigit(int c);
//	int		ft_isalnum(int c);
//	int		ft_isascii(int c);
//	int		ft_isprint(int c);
//	int		ft_toupper(int c);
//	int		ft_tolower(int c);
	printf("\n==> "C_BLUE"The following tests are done by comparing your 'ft_' functions to the ctype.h standard functions."RESET);
	printf("\n==> "C_BLUE"All of these char function tests should silently succeed (except after 255, thats undefined behavior)."RESET);
	printf("\n==> "C_BLUE"(In any case, errors will be displayed if there are any, important or not)."RESET"\n");

printf("\n");
	int charmax = 260;
	int error = 0;
	for (int i = 0; i < charmax; i++)
	{
		if (!bool_equals(ft_isalpha(i), isalpha(i))) { ++error; printf(C_RED"ERROR - ft_isalpha(%d) = %d\n"RESET, i, ft_isalpha(i)); }
		if (!bool_equals(ft_isupper(i), isupper(i))) { ++error; printf(C_RED"ERROR - ft_isupper(%d) = %d\n"RESET, i, ft_isupper(i)); }
		if (!bool_equals(ft_islower(i), islower(i))) { ++error; printf(C_RED"ERROR - ft_islower(%d) = %d\n"RESET, i, ft_islower(i)); }
		if (!bool_equals(ft_isalnum(i), isalnum(i))) { ++error; printf(C_RED"ERROR - ft_isalnum(%d) = %d\n"RESET, i, ft_isalnum(i)); }
		if (!bool_equals(ft_isdigit(i), isdigit(i))) { ++error; printf(C_RED"ERROR - ft_isdigit(%d) = %d\n"RESET, i, ft_isdigit(i)); }
		if (!bool_equals(ft_isspace(i), isspace(i))) { ++error; printf(C_RED"ERROR - ft_isspace(%d) = %d\n"RESET, i, ft_isspace(i)); }
		if (!bool_equals(ft_ispunct(i), ispunct(i))) { ++error; printf(C_RED"ERROR - ft_ispunct(%d) = %d\n"RESET, i, ft_ispunct(i)); }
		if (!bool_equals(ft_isprint(i), isprint(i))) { ++error; printf(C_RED"ERROR - ft_isprint(%d) = %d\n"RESET, i, ft_isprint(i)); }
		if (!bool_equals(ft_isascii(i), isascii(i))) { ++error; printf(C_RED"ERROR - ft_isascii(%d) = %d\n"RESET, i, ft_isascii(i)); }

		if (!bool_equals(ft_toupper(i), toupper(i))) { ++error; printf(C_RED"ERROR - ft_toupper(%d) = %d\n"RESET, i, ft_toupper(i)); }
		if (!bool_equals(ft_tolower(i), tolower(i))) { ++error; printf(C_RED"ERROR - ft_tolower(%d) = %d\n"RESET, i, ft_tolower(i)); }
	}
	if (error)
		printf("\nA total of "C_RED"%d"RESET" errors found, testing every char up to %d", error, charmax);

	printf("\n");
	return (OK);
}
