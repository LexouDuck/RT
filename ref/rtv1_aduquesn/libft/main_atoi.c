#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define RED		"\x1b[31m"
#define GREEN	"\x1b[32m"
#define RESET	"\x1b[0m"

//#include "main_util.c"
#include "ft_strrev.c"
#include "ft_strlen.c"
#include "ft_isdigit.c"
#include "ft_isspace.c"

#include "ft_atoi.c"
#include "ft_atoi_base.c"
#include "ft_itoa.c"
#include "ft_itoa_base.c"



int	equals(char const *str1, char const *str2)
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

char *str_to_escape(char *str)
{
	unsigned char HI_nibble;
	unsigned char LO_nibble;
	char *result;
	int i = 0;
	int j = 0;

	if (!(result = (char *)malloc(strlen(str) * 4)))
		return (NULL);
	while (str[i])
	{
		if (!isprint(str[i]))
		{
			result[j++] = '\\';
			switch (str[i])
			{
				case 0x07: result[j++] =  'a'; break; // Alert (Beep, Bell) (added in C89)[1]
				case 0x08: result[j++] =  'b'; break; // Backspace
				case 0x0C: result[j++] =  'f'; break; // Formfeed
				case 0x0A: result[j++] =  'n'; break; // Newline (Line Feed); see notes below
				case 0x0D: result[j++] =  'r'; break; // Carriage Return
				case 0x09: result[j++] =  't'; break; // Horizontal Tab
				case 0x0B: result[j++] =  'v'; break; // Vertical Tab
				case 0x5C: result[j++] = '\\'; break; // Backslash
				case 0x27: result[j++] = '\''; break; // Single quotation mark
				case 0x22: result[j++] = '\"'; break; // Double quotation mark
				case 0x3F: result[j++] =  '?'; break; // Question mark (used to avoid trigraphs)
				default: result[j++] = 'x'; // Hexadecimal char notation: \xFF
					HI_nibble = (str[i] >> 4) & 0x0F;
					LO_nibble = (str[i] & 0x0F);
					result[j++] = (HI_nibble <= 9) ? (HI_nibble + '0') : (HI_nibble - 10 + 'A');
					result[j++] = (LO_nibble <= 9) ? (LO_nibble + '0') : (LO_nibble - 10 + 'A');
				break;
			}
		}
		else result[j++] = str[i];
		++i;
	}
	result[j] = '\0';
	return (result);
}









void test_atoi()
{
	char	*tests[] = {
		"0",
		"1",
		"42",
		"-42",
		"",
		"-5435",
		"--9999999",
		"-2147483648",
		"2147483647",
		"   8543",
		"\f3541",
		"\n5643",
		"\r397+",
		"\t8513",
		"- 45678978748f",
		"swag123",
		"(-(123",
		"[12]123",
		"45_",
		"\v9876-",
		"65435+--+",
		"def58453",
		"5486helllo",
		"\f-3541",
		"\n-5643",
		"-\r-397+",
		"---84648-+",
		"&%64",
		"125\n12",
		"  -2",
		"  2",
		"!789",
		"#45",
		"$786",
		"&789",
		"*4456",
		".1234",
		"/1234",
		"%1234",
		",7",
		",,789",
		"456,78",
		".456",
		"  +5896df",
		"  + 563",
		"++4653",
		" + 45631dsf-+",
		"\200 456",
		"\255\2543",
		"\0 456",
		"\255 5",
		"\\//\v/789",
		"0x123",
		"0b1101",
		"\15124578",
		"\33124578",
		"[124578",
		"=0124578",
		"_456",
		"##4567",
		"\124578",
		"\\256",
		"\\256\\",
		"25627165465413",
		"\\25627165465413",
		"\2568",
		"30000f",
		"-500000000000",
		"-6513212312310531",
		"2147483648",
		"-2147483649",
		"3000000000",
		"-3000000000",
		"9999999999999999999999999999999999999",
		"-9999999999999999999999999999999999999",
		"9223372036854775807",
		"-9223372036854775808",
		"9223372036854775808",
		"-9223372036854775809",
	};
	int		i;
	int		length;
	int 	error;

	int		result;
	int		expect;
	char	*str;

	i = 0;
	length = (int)SIZE(tests);
	while (i < length)
	{
		result = ft_atoi(tests[i]);
		expect =    atoi(tests[i]);
		error = (result != expect);
		if (error)	printf(RED"ERROR"RESET);
		else		printf(GREEN"OK!"RESET);
		str = print_test(tests[i]);
		printf(" -> Test: {%s} -> {%d}\n", str, result);
		free(str);
		if (error)
		{
			printf(RED">ft_atoi:{%d}\n>   atoi:{%d}\n"RESET, result, expect);
		}
		i++;
	}
}

void test_atoi_base()
{
	char	*tests[] = {
	          "mmmm",                "m", "0",
	      "00101010",               "01", "42",
	       "momomom",              "mom", "0",
	         "rdmmd",              "mdr", "190",
	            "4+",       "01+3456789", "0",
	    "012345e123",       "0123456789", "12345",
	         "c===3",       "=cbadef389", "10007",
	       "000swag",       "0swag56789", "1234",
	          ".._.",               "_.", "13",
	          "-3e8", "0123456789abcdef", "-1000",
	        "*xurin",       "grincheux*", "987123",
	        "-0000F", "0123456789ABCDEF", "-15",
	          "+-2A", "0123456789ABCDEF", "0",
	          "++2A", "0123456789ABCDEF", "0",
	          "--2A", "0123456789ABCDEF", "0",
	          "-+2A", "0123456789ABCDEF", "0",
	            "+-", "0123456789ABCDEF", "0",
	            "++", "0123456789ABCDEF", "0",
	            "-+", "0123456789ABCDEF", "0",
	            "--", "0123456789ABCDEF", "0",
	           "2-A", "0123456789ABCDEF", "2",
	          "+2-A", "0123456789ABCDEF", "2",
	            "2a", "0123456789ABCDEF", "2",
	              "", "0123456789ABCDEF", "0",
	      "7FFFFFFF", "0123456789ABCDEF", "2147483647",
	   "-2147483648",       "0123456789", "-2147483648",
	};
	int		i;
	int		length;
	int 	error;

	int 	result;
	int 	expect;
	char	*base;
	/*ft_convert_base
		printf("\nft_convert_base :\n");
		printf("Test:%s | Expected:%s\n", ft_convert_base(        "abc", "_abcdefghi",       "0123456789"), "123");
		printf("Test:%s | Expected:%s\n", ft_convert_base(     "001234", "0123456789",       "0swag56789"), "swag");
		printf("Test:%s | Expected:%s\n", ft_convert_base(         "ac", "_abcdefghi",               "_."), ".._.");
		printf("Test:%s | Expected:%s\n", ft_convert_base(      "oioii",         "oi",       "opanstylez"), "pp");
		printf("Test:%s | Expected:%s\n", ft_convert_base(          "0",         "08",       "opanstylez"), "o");
		printf("Test:%s | Expected:%s\n", ft_convert_base( "2147483646", "0123456789", "legsandcwokuim3="), "c======3");
		printf("Test:%s | Expected:%s\n", ft_convert_base("-2147483648", "0123456789", "0123456789ABCDEF"), "-80000000");
		printf("Test:%s | Expected:%s\n", ft_convert_base(			 "", "0123456789", "0123456789ABCDEF"), "(null)");
		printf("Test:%s | Expected:%s\n", ft_convert_base("-2147483648", "0123456789", 		  "012345780"), "(null)");
		printf("Test:%s | Expected:%s\n", ft_convert_base("-2147483648", "0123456780", 		  "012345789"), "(null)");
	*/
	i = 0;
	length = (int)(SIZE(tests) / 3);
	while (i < length)
	{
		base = tests[i * 3 + 1];
		expect = atoi(tests[i * 3 + 2]);
		result = ft_atoi_base(tests[i * 3], base);
		error = (result != expect);
		if (error)	printf(RED"ERROR"RESET);
		else		printf(GREEN"OK!"RESET);
		printf(" -> Test: (base:{%s}, {%s}) -> {%d}\n", base, tests[i * 3], result);
		if (error)
		{
			printf(RED">ft_atoi_base:{%d}\n>    Expected:{%d}\n"RESET, result, expect);
		}
		++i;
	}
}

void test_itoa()
{
	char *tests[] = {
		"1",
		"42",
		"0",
		"777",
		"-666",
		"-10000",
		"123456789",
		"2147483647",
		"-2147483648",
	};
	int		i;
	int		length;
	int		error;

	char	*result;

	i = 0;
	length = (int)SIZE(tests);
	while (i < length)
	{
		result = ft_itoa(atoi(tests[i]));
		error = !equals(tests[i], result);
		if (error)	printf(RED"ERROR"RESET);
		else		printf(GREEN"OK!"RESET);
		printf(" -> Test: {%s} -> {%s}\n", tests[i], result);
		if (error)
		{
			printf(RED">ft_itoa:{%s}\n>   itoa:{%s}\n"RESET, result, tests[i]);
		}
		++i;
	}
}

void test_itoa_base()
{
	char *tests[] = {
	          "_",               "01",          NULL,
	          "0",                "m",          NULL,
	         "42",               "01",      "101010",
	          "0",              "mom",          NULL,
	        "-15", "0123456789ABCDEF",          "-F",
	        "190",              "mdr",       "rdmmd",
	     "012345",       "0123456789",       "12345",
	     "-12345",       "012345678-",          NULL,
	        "999",       "01+3456789",          NULL,
	      "10007",       "=cbadef389",       "c===3",
	       "1234",       "0swag56789",        "swag",
	         "13",               "_.",        ".._.",
	      "-1000", "0123456789abcdef",        "-3e8",
	    "+987123",       "grincheux*",      "*xurin",
	 "2147483647", "0123456789ABCDEF",    "7FFFFFFF",
	"-2147483648",       "0123456789", "-2147483648"
	};
	int		i;
	int		length;
	int		error;

	char	*result;
	char	*expect;
	char	*base;

	i = 0;
	length = (int)(SIZE(tests) / 3);
	while (i < length)
	{
		base = tests[i * 3 + 1];
		expect = tests[i * 3 + 2];
		result = ft_itoa_base(atoi(tests[i * 3]), base);
		error = !equals(result, expect);
		if (error)	printf(RED"ERROR"RESET);
		else		printf(GREEN"OK!"RESET);
		printf(" -> Test: ({%s}, base:{%s}) -> {%s}\n", tests[i * 3], base, result);
		if (error)
		{
			printf(RED">ft_itoa_base:{%s}\n>   itoa_base:{%s}\n"RESET, result, expect);
		}
		free(result);
		++i;
	}
}

int	 main(void)
{
	printf("\n\n");
	printf("atoi tests:\n");
	test_atoi();

	printf("\n\n");
	printf("atoi_base tests:\n");
	test_atoi_base();

	printf("\n\n");
	printf("itoa tests:\n");
	test_itoa();

	printf("\n\n");
	printf("itoa_base tests:\n");
	test_itoa_base();

	return (0);
}
