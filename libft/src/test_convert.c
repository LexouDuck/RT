
#include "test.h"



/*
**	char*	ft_s8_to_str(t_s32 n);
*/
void	print_test_s8_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s8_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s8_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s8_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_s8_to_str("s8_to_str               ",	FALSE,      "1", 1    );
	print_test_s8_to_str("s8_to_str               ",	FALSE,     "42", 42   );
	print_test_s8_to_str("s8_to_str               ",	FALSE,      "0", 0    );
	print_test_s8_to_str("s8_to_str               ",	FALSE,    "111", 111  );
	print_test_s8_to_str("s8_to_str               ",	FALSE,   "-111",-111  );
	print_test_s8_to_str("s8_to_str (n = max)     ",	FALSE,    "127", 127  );
	print_test_s8_to_str("s8_to_str (n = min)     ",	FALSE,   "-128",-128  );
	print_test_s8_to_str("s8_to_str (n > max)     ",	FALSE,    "128", 128  );
	print_test_s8_to_str("s8_to_str (n < min)     ",	FALSE,   "-129",-129  );
	print_test_s8_to_str("s8_to_str (n > maxdigit)",	FALSE,  "99999", 99999);
	print_test_s8_to_str("s8_to_str (n < maxdigit)",	FALSE, "-99999",-99999);
}



/*
**	char*	ft_s16_to_str(t_s16 n);
*/
void	print_test_s16_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s16_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s16_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s16_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_s16_to_str("s16_to_str               ",	FALSE,        "1", 1      );
	print_test_s16_to_str("s16_to_str               ",	FALSE,       "42", 42     );
	print_test_s16_to_str("s16_to_str               ",	FALSE,        "0", 0      );
	print_test_s16_to_str("s16_to_str               ",	FALSE,      "777", 777    );
	print_test_s16_to_str("s16_to_str               ",	FALSE,     "-666",-666    );
	print_test_s16_to_str("s16_to_str               ",	FALSE,    "10000", 10000  );
	print_test_s16_to_str("s16_to_str               ",	FALSE,   "-10000",-10000  );
	print_test_s16_to_str("s16_to_str (n = max)     ",	FALSE,    "32767", 32767  );
	print_test_s16_to_str("s16_to_str (n = min)     ",	FALSE,   "-32768",-32768  );
	print_test_s16_to_str("s16_to_str (n > max)     ",	FALSE,    "32768", 32768  );
	print_test_s16_to_str("s16_to_str (n < min)     ",	FALSE,   "-32769",-32769  );
	print_test_s16_to_str("s16_to_str (n > maxdigit)",	FALSE,  "9999999", 9999999);
	print_test_s16_to_str("s16_to_str (n < maxdigit)",	FALSE, "-9999999",-9999999);
}



/*
**	char*	ft_s32_to_str(t_s32 n);
*/
void	print_test_s32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s32_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s32_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s32_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS */
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "1", 1         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,            "42", 42        );
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "0", 0         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,           "777", 777       );
	print_test_s32_to_str("s32_to_str               ",	FALSE,          "-666",-666       );
	print_test_s32_to_str("s32_to_str               ",	FALSE,        "-10000",-10000     );
	print_test_s32_to_str("s32_to_str               ",	FALSE,     "123456789", 123456789 );
	print_test_s32_to_str("s32_to_str (n = max)     ",	FALSE,    "2147483647", 2147483647);
	print_test_s32_to_str("s32_to_str (n = min)     ",	FALSE,   "-2147483648",-2147483648);
	print_test_s32_to_str("s32_to_str (n > max)     ",	FALSE,    "2147483648", 2147483648);
	print_test_s32_to_str("s32_to_str (n < min)     ",	FALSE,   "-2147483649",-2147483649);
	print_test_s32_to_str("s32_to_str (n > maxdigit)",	FALSE,  "999999999999", 2147483648);
	print_test_s32_to_str("s32_to_str (n < maxdigit)",	FALSE, "-999999999999",-2147483649);
}



int		test_convert(void)
{

printf("\n");

	printf("       .---------------------------.       \n");
	printf("---==={  LIBFT TEST: libft_convert  }===---\n");
	printf("       '---------------------------'       \n");

	test_s8_to_str();
	test_s16_to_str();
	test_s32_to_str();

	print_nonstd();

printf("\n");

	return (OK);
}
