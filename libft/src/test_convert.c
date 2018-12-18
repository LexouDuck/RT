
#include "test.h"



/*
**	char*	ft_s8_to_str(t_s8 n);
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
#ifdef __TEST_OVERFLOW
	print_test_s8_to_str("s8_to_str (n > max)     ",	FALSE,    "128", 128  );
	print_test_s8_to_str("s8_to_str (n < min)     ",	FALSE,   "-129",-129  );
	print_test_s8_to_str("s8_to_str (n > maxdigit)",	FALSE,  "99999", 99999);
	print_test_s8_to_str("s8_to_str (n < maxdigit)",	FALSE, "-99999",-99999);
#endif
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
#ifdef __TEST_OVERFLOW
	print_test_s16_to_str("s16_to_str (n > max)     ",	FALSE,    "32768", 32768  );
	print_test_s16_to_str("s16_to_str (n < min)     ",	FALSE,   "-32769",-32769  );
	print_test_s16_to_str("s16_to_str (n > maxdigit)",	FALSE,  "9999999", 9999999);
	print_test_s16_to_str("s16_to_str (n < maxdigit)",	FALSE, "-9999999",-9999999);
#endif
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
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "1", 1           );
	print_test_s32_to_str("s32_to_str               ",	FALSE,            "42", 42          );
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "0", 0           );
	print_test_s32_to_str("s32_to_str               ",	FALSE,           "777", 777         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,          "-666",-666         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,        "-10000",-10000       );
	print_test_s32_to_str("s32_to_str               ",	FALSE,     "123456789", 123456789   );
	print_test_s32_to_str("s32_to_str (n = max)     ",	FALSE,    "2147483647", 2147483647  );
	print_test_s32_to_str("s32_to_str (n = min)     ",	FALSE,   "-2147483648",-2147483648  );
#ifdef __TEST_OVERFLOW
	print_test_s32_to_str("s32_to_str (n > max)     ",	FALSE,    "2147483648", 2147483648  );
	print_test_s32_to_str("s32_to_str (n < min)     ",	FALSE,   "-2147483649",-2147483649  );
	print_test_s32_to_str("s32_to_str (n > maxdigit)",	FALSE,  "999999999999", 999999999999);
	print_test_s32_to_str("s32_to_str (n < maxdigit)",	FALSE, "-999999999999",-999999999999);
#endif
}



/*
**	char*	ft_s64_to_str(t_s64 n);
*/
void	print_test_s64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s64_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s64_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s64_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_s64_to_str("s64_to_str               ",	FALSE,                      "1", 1                     );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                     "42", 42                    );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                      "0", 0                     );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                    "777", 777                   );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                   "-666",-666                   );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                 "-10000",-10000                 );
	print_test_s64_to_str("s64_to_str               ",	FALSE,              "123456789", 123456789             );
	print_test_s64_to_str("s64_to_str               ",	FALSE,             "2147483648", 2147483648            );
	print_test_s64_to_str("s64_to_str               ",	FALSE,            "-2147483649",-2147483649            );
	print_test_s64_to_str("s64_to_str               ",	FALSE,           "999999999999", 999999999999          );
	print_test_s64_to_str("s64_to_str               ",	FALSE,          "-999999999999",-999999999999          );
	print_test_s64_to_str("s64_to_str (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807LL );
	print_test_s64_to_str("s64_to_str (n = min)     ",	FALSE,   "-9223372036854775807",-9223372036854775807LL );
#ifdef __TEST_OVERFLOW
	print_test_s64_to_str("s64_to_str (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808LL  );
	print_test_s64_to_str("s64_to_str (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809LL  );
	print_test_s64_to_str("s64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999LL);
	print_test_s64_to_str("s64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999LL);
#endif
}



/*
**	char*	ft_u8_to_str(t_s8 n);
*/
void	print_test_u8_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u8_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u8_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u8_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_u8_to_str("u8_to_str               ",	FALSE,      "1", 1    );
	print_test_u8_to_str("u8_to_str               ",	FALSE,     "42", 42   );
	print_test_u8_to_str("u8_to_str               ",	FALSE,    "111", 111  );
	print_test_u8_to_str("u8_to_str (n = max)     ",	FALSE,    "255", 255  );
	print_test_u8_to_str("u8_to_str (n = min)     ",	FALSE,      "0", 0    );
#ifdef __TEST_OVERFLOW
	print_test_u8_to_str("u8_to_str (n > max)     ",	FALSE,    "256", 256  );
	print_test_u8_to_str("u8_to_str (n < min)     ",	FALSE,     "-1", -1   );
	print_test_u8_to_str("u8_to_str (n > maxdigit)",	FALSE,  "99999", 99999);
	print_test_u8_to_str("u8_to_str (n < maxdigit)",	FALSE, "-99999",-99999);
#endif
}



/*
**	char*	ft_u16_to_str(t_s16 n);
*/
void	print_test_u16_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u16_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u16_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u16_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_u16_to_str("u16_to_str               ",	FALSE,        "1", 1      );
	print_test_u16_to_str("u16_to_str               ",	FALSE,       "42", 42     );
	print_test_u16_to_str("u16_to_str               ",	FALSE,      "777", 777    );
	print_test_u16_to_str("u16_to_str               ",	FALSE,    "10000", 10000  );
	print_test_u16_to_str("u16_to_str (n = max)     ",	FALSE,    "65535", 65535  );
	print_test_u16_to_str("u16_to_str (n = min)     ",	FALSE,        "0", 0      );
#ifdef __TEST_OVERFLOW
	print_test_u16_to_str("u16_to_str (n > max)     ",	FALSE,    "65536", 65536  );
	print_test_u16_to_str("u16_to_str (n < min)     ",	FALSE,       "-1", -1     );
	print_test_u16_to_str("u16_to_str (n > maxdigit)",	FALSE,  "9999999", 9999999);
	print_test_u16_to_str("u16_to_str (n < maxdigit)",	FALSE, "-9999999",-9999999);
#endif
}



/*
**	char*	ft_u32_to_str(t_s32 n);
*/
void	print_test_u32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u32_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u32_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u32_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS */
	print_test_u32_to_str("u32_to_str               ",	FALSE,             "1", 1           );
	print_test_u32_to_str("u32_to_str               ",	FALSE,            "42", 42          );
	print_test_u32_to_str("u32_to_str               ",	FALSE,             "0", 0           );
	print_test_u32_to_str("u32_to_str               ",	FALSE,           "777", 777         );
	print_test_u32_to_str("u32_to_str               ",	FALSE,         "10000", 10000       );
	print_test_u32_to_str("u32_to_str               ",	FALSE,     "123456789", 123456789   );
	print_test_u32_to_str("u32_to_str (n = max)     ",	FALSE,    "4294967295", 4294967295  );
	print_test_u32_to_str("u32_to_str (n = min)     ",	FALSE,             "0", 0           );
#ifdef __TEST_OVERFLOW
	print_test_u32_to_str("u32_to_str (n > max)     ",	FALSE,    "4294967296", 4294967296  );
	print_test_u32_to_str("u32_to_str (n < min)     ",	FALSE,            "-1", -1          );
	print_test_u32_to_str("u32_to_str (n > maxdigit)",	FALSE,  "999999999999", 999999999999);
	print_test_u32_to_str("u32_to_str (n < maxdigit)",	FALSE, "-999999999999",-999999999999);
#endif
}



/*
**	char*	ft_u64_to_str(t_s64 n);
*/
void	print_test_u64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u64_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u64_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u64_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_u64_to_str("u64_to_str               ",	FALSE,                      "1", 1                     );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                     "42", 42                    );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                    "777", 777                   );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                  "10000", 10000                 );
	print_test_u64_to_str("u64_to_str               ",	FALSE,              "123456789", 123456789             );
	print_test_u64_to_str("u64_to_str               ",	FALSE,           "999999999999", 999999999999          );
	print_test_u64_to_str("u64_to_str (n = max)     ",	FALSE,   "18446744073709551615", 18446744073709551615UL);
	print_test_u64_to_str("u64_to_str (n = min)     ",	FALSE,                      "0", 0                     );
#ifdef __TEST_OVERFLOW
	print_test_u64_to_str("u64_to_str (n > max)     ",	FALSE,   "18446744073709551616", 18446744073709551616UL);
	print_test_u64_to_str("u64_to_str (n < min)     ",	FALSE,                     "-1", -1                    );
	print_test_u64_to_str("u64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999UL);
	print_test_u64_to_str("u64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999UL);
#endif
}



/*
**	char*	ft_f32_to_str(t_s32 n);
*/
void	print_test_f32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_f32 number,
		t_u8 precision)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_f32_to_str(number, precision); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_f32_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_f32_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_f32_to_str("f32_to_str               ",	FALSE,                      "1", 1                    , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                     "42", 42                   , 0);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                   "42.0", 42                   , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "42.00", 42                   , 2);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                      "0", 0                    , 0);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                    "0.0", 0                    , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "0.000", 0                    , 3);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                     "-1", -1                   , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                    "0.5", 0.5                  , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "0.001", 0.001                , 3);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                "0.33333", 0.33333333           , 5);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                 "-777.1", -777.1               , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,               "3.141592", 3.141592             , 6);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "10000", 10000                , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,              "10000.000", 10000                , 3);
	print_test_f32_to_str("f32_to_str               ",	FALSE,     "10000.000000000000", 10000                , 12);
	print_test_f32_to_str("f32_to_str               ",	FALSE,              "123456789", 123456789            , 1);
/* TODO make it so these tests are ok, they arent because the float conversion functions use a u64 tmp variable
	print_test_f32_to_str("f32_to_str (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807  , 1);
	print_test_f32_to_str("f32_to_str (n = min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808  , 1);
	print_test_f32_to_str("f32_to_str (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808  , 1);
	print_test_f32_to_str("f32_to_str (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809  , 1);
	print_test_f32_to_str("f32_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999, 1);
	print_test_f32_to_str("f32_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999, 1);
*/
}



/*
**	char*	ft_f64_to_str(t_s32 n);
*/
void	print_test_f64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_f32 number,
		t_u8 precision)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_f64_to_str(number, precision); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_f64_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_f64_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_f64_to_str("f64_to_str               ",	FALSE,                      "1", 1                    , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                     "42", 42                   , 0);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                   "42.0", 42                   , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "42.00", 42                   , 2);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                      "0", 0                    , 0);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                    "0.0", 0                    , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "0.000", 0                    , 3);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                     "-1", -1                   , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                    "0.5", 0.5                  , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "0.001", 0.001                , 3);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                "0.33333", 0.33333333           , 5);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                 "-777.1", -777.1               , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,               "3.141592", 3.141592             , 6);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "10000", 10000                , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,              "10000.000", 10000                , 3);
	print_test_f64_to_str("f64_to_str               ",	FALSE,     "10000.000000000000", 10000                , 12);
	print_test_f64_to_str("f64_to_str               ",	FALSE,              "123456789", 123456789            , 1);
/* TODO make it so these tests are ok, they arent because the float conversion functions use a u64 tmp variable
	print_test_f64_to_str("f64_to_str (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807  , 1);
	print_test_f64_to_str("f64_to_str (n = min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808  , 1);
	print_test_f64_to_str("f64_to_str (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808  , 1);
	print_test_f64_to_str("f64_to_str (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809  , 1);
	print_test_f64_to_str("f64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999, 1);
	print_test_f64_to_str("f64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999, 1);
*/
}



/*
**	t_s8	ft_str_to_s8(char const *str);
*/
void	print_test_str_to_s8(char const* test_name, int can_segfault,
		t_s8 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s8 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s8(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s8(test_name, "_str_to_s8", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s8()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "0"                          );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           1, "1"                          );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          42, "42"                         );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                         -42, "-42"                        );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          85, "   85"                      );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          35, "\f35"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          56, "\n56"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          39, "\r39+"                      );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                         138, "\t138"                      );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "swag123"                    );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          45, "45_"                        );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                         111, "111"                        );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                        -111, "-111"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "  + 56"                     );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "++43"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, " + 41dsf-+"                 );
	print_test_str_to_s8("str_to_s8 (n = max)     ",	FALSE,                         127, "127"                        );
	print_test_str_to_s8("str_to_s8 (n = min)     ",	FALSE,                        -128, "-128"                       );
	print_test_str_to_s8("str_to_s8 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s8("str_to_s8 (null str)    ",	TRUE | (1 << 2),                 0, NULL                         );
#ifdef __TEST_OVERFLOW
	print_test_str_to_s8("str_to_s8 (n > max)     ",	FALSE,                         128, " 128"                       );
	print_test_str_to_s8("str_to_s8 (n < min)     ",	FALSE,                        -129, "-129"                       );
	print_test_str_to_s8("str_to_s8 (n > maxdigit)",	FALSE,                       99999, " 99999"                     );
	print_test_str_to_s8("str_to_s8 (n < maxdigit)",	FALSE,                      -99999, "-99999"                     );
#endif
}



/*
**	t_s16	ft_str_to_s16(char const *str);
*/
void	print_test_str_to_s16(char const* test_name, int can_segfault,
		t_s16 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s16 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s16(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s16(test_name, "_str_to_s16", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s16()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "0"                          );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           1, "1"                          );
	print_test_str_to_s16("str_to_s16",               	FALSE,                          42, "42"                         );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                          45, "45_"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           2, "  2"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "!789"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "#45"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "$786"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "&789"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ",7"                         );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ".456"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_s16("str_to_s16 (n = max)     ",	FALSE,                       32767, " 32767"                     );
	print_test_str_to_s16("str_to_s16 (n = min)     ",	FALSE,                      -32768, "-32768"                     );
	print_test_str_to_s16("str_to_s16 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s16("str_to_s16 (null str)    ",	TRUE | (1 << 2),                 0, NULL                         );
#ifdef __TEST_OVERFLOW
	print_test_str_to_s16("str_to_s16 (n > max)     ",	FALSE,                       32768,  "32768"                     );
	print_test_str_to_s16("str_to_s16 (n < min)     ",	FALSE,                      -32769, "-32769"                     );
	print_test_str_to_s16("str_to_s16 (n > maxdigit)",	FALSE,                     9999999,  "9999999"                   );
	print_test_str_to_s16("str_to_s16 (n < maxdigit)",	FALSE,                    -9999999, "-9999999"                   );
#endif
}



/*
**	t_s32	ft_str_to_s32(char const *str);
*/
void	print_test_str_to_s32(char const* test_name, int can_segfault,
		t_s32 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s32 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s32(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s32(test_name, "_str_to_s32", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s32()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "0"                          );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           1, "1"                          );
	print_test_str_to_s32("str_to_s32",               	FALSE,                          42, "42"                         );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_s32("str_to_s32",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                          45, "45_"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "def58453"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        5486, "5486helllo"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       -3541, "\f-3541"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       -5643, "\n-5643"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "-\r-397+"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "---84648-+"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "&%64"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         125, "125\n12"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           2, "  2"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "!789"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "#45"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "$786"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "&789"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ",7"                         );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ".456"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\15124578"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\33124578"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "[124578"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "=0124578"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "_456"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "##4567"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\124578"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\\256"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\\256\\"                    );
	print_test_str_to_s32("str_to_s32 (n = max)     ",	FALSE,                  2147483647,  "2147483647"                );
	print_test_str_to_s32("str_to_s32 (n = min)     ",	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_s32("str_to_s32 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s32("str_to_s32 (null str)    ",	TRUE | (1 << 2),                 0, NULL                         );
#ifdef __TEST_OVERFLOW
	print_test_str_to_s32("str_to_s32 (n > max)     ",	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_s32("str_to_s32 (n < min)     ",	FALSE,                 -2147483649, "-2147483649"                );
	print_test_str_to_s32("str_to_s32 (n > maxdigit)",	FALSE,                999999999999,  "999999999999"              );
	print_test_str_to_s32("str_to_s32 (n < maxdigit)",	FALSE,               -999999999999, "-999999999999"              );
#endif
}



/*
**	t_s64	ft_str_to_s64(char const *str);
*/
void	print_test_str_to_s64(char const* test_name, int can_segfault,
		t_s64 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s64 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s64(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s64(test_name, "_str_to_s64", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s64()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "0"                          );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           1, "1"                          );
	print_test_str_to_s64("str_to_s64",               	FALSE,                          42, "42"                         );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                          45, "45_"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "def58453"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        5486, "5486helllo"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       -3541, "\f-3541"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       -5643, "\n-5643"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "-\r-397+"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "---84648-+"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "&%64"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         125, "125\n12"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           2, "  2"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "!789"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "#45"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "$786"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "&789"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ",7"                         );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ".456"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\15124578"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\33124578"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "[124578"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "=0124578"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "_456"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "##4567"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\124578"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\256"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\256\\"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,              25627165465413, "25627165465413"             );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\25627165465413"           );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\2568"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       30000, "30000f"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,               -500000000000, "-500000000000"              );
	print_test_str_to_s64("str_to_s64",               	FALSE,           -6513212312310531, "-6513212312310531"          );
	print_test_str_to_s64("str_to_s64",               	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                 -2147483649, "-2147483649"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                  3000000000,  "3000000000"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                 -3000000000, "-3000000000"                );
	print_test_str_to_s64("str_to_s64 (n = max)     ",	FALSE,       9223372036854775807LL,  "9223372036854775807"       );
	print_test_str_to_s64("str_to_s64 (n = min)     ",	FALSE,      -9223372036854775807LL, "-9223372036854775807"       );
	print_test_str_to_s64("str_to_s64 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s64("str_to_s64 (null str)    ",	TRUE | (1 << 2),                 0, NULL                         );
#ifdef __TEST_OVERFLOW
	print_test_str_to_s64("str_to_s64 (n > max)     ",	FALSE,       9223372036854775808LL,  "9223372036854775808"       );
	print_test_str_to_s64("str_to_s64 (n < min)     ",	FALSE,      -9223372036854775809LL, "-9223372036854775809"       );
	print_test_str_to_s64("str_to_s64 (n > maxdigit)",	FALSE,     999999999999999999999LL,  "999999999999999999999"     );
	print_test_str_to_s64("str_to_s64 (n < maxdigit)",	FALSE,    -999999999999999999999LL, "-999999999999999999999"     );
#endif
}



int		test_convert(void)
{

printf("\n");

	printf("       .---------------------------.       \n");
	printf("---==={  LIBFT TEST: libft_convert  }===---\n");
	printf("       '---------------------------'       \n");

	print_nonstd();

	test_s8_to_str();
	test_s16_to_str();
	test_s32_to_str();
	test_s64_to_str();

	test_u8_to_str();
	test_u16_to_str();
	test_u32_to_str();
	test_u64_to_str();

	test_f32_to_str();
	test_f64_to_str();

	test_str_to_s8();
	test_str_to_s16();
	test_str_to_s32();
	test_str_to_s64();

//	test_str_to_u8();
//	test_str_to_u16();
//	test_str_to_u32();
//	test_str_to_u64();

printf("\n");

	return (OK);
}
