
#include "test.h"

/*
**	char*	ft_strnew(size_t size);
*/
void	print_test_strnew(char const* test_name, int can_segfault,
		size_t n)
{
	char* result;
	int error = FALSE;
	segfault = setjmp(restore); if (!segfault) result = ft_strnew(n); else result = segstr;
	printf("\n%s -> ", test_name);
	if (result == NULL)
	{
		error = TRUE;
		printf(C_RED"\nERROR - The call to ft_strnew returned NULL."RESET);
	}
	for (size_t i = 0; i < n; ++i)
	{
		if (result[i])
		{
			error = TRUE;
			printf(C_RED"\nERROR - Every char should be '\\0', but '%c' was read at index %d."RESET, result[i], i);
		}
	}
	if (!error) printf(C_GREEN"OK!"RESET);
	if (result) free(result);
}
void	test_strnew(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME      |CAN SEGV|TEST ARGS */
	print_test_strnew("strnew",        	FALSE,	12);
	print_test_strnew("strnew (n = 0)",	FALSE,	0);
}



/*
**	void	ft_strset(char *str, char c);
*/
void	print_test_strset(char const* test_name, int can_segfault,
		char const* expecting,
		char* dest_libft,
		char* dest_libc,
		char c)
{
	segfault = setjmp(restore); if (!segfault) ft_strset(dest_libft, c); else dest_libft = segstr;
//	segfault = setjmp(restore); if (!segfault)    strset(dest_libc,  c); else dest_libc  = segstr;
	print_test_str(test_name, "strset arg", dest_libft, expecting, can_segfault);
}
void	test_strset(void)
{
	char str1[32];
	char str2[32];
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strset("strset",           	FALSE,	"aaaa", str1, str2, 'a');
	print_test_strset("strset (null ptr)",	TRUE, 	segstr, NULL, NULL, 'a');
}



/*
**	void	ft_strclr(char *str);
*/
void	print_test_strclr(char const* test_name, int can_segfault,
		char const* expecting,
		char* dest_libft,
		char* dest_libc)
{
	segfault = setjmp(restore); if (!segfault) ft_strclr(dest_libft); else dest_libft = segstr;
//	segfault = setjmp(restore); if (!segfault)    strclr(dest_libc);  else dest_libc  = segstr;
	print_test_str(test_name, "strclr arg", dest_libft, expecting, can_segfault);
}
void	test_strclr(void)
{
	char str1[32];
	char str2[32];
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strclr("strclr",           	FALSE,	"\0",   str1, str2);
	print_test_strclr("strclr (null ptr)",	TRUE, 	segstr, NULL, NULL);
}



/*
**	void	ft_strdel(char** ptr);
*/
void	print_test_strdel(char const* test_name, int can_segfault,
		char const* expecting,
		char** dest_libft,
		char** dest_libc)
{
	segfault = setjmp(restore); if (!segfault) ft_strdel(dest_libft); else *dest_libft = segstr;
//	segfault = setjmp(restore); if (!segfault)    strdel(dest_libc);  else *dest_libc  = segstr;
	print_test_str(test_name, "strdel arg", *dest_libft, expecting, can_segfault);
}
void	test_strdel(void)
{
	char* str1; if (!(str1 = malloc(32))) return;
	char* str2; if (!(str2 = malloc(32))) return;
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strdel("strdel",           	FALSE,	NULL, &str1, &str2);
	print_test_strdel("strdel (null ptr)",	TRUE, 	NULL, NULL,  NULL);
}



/*
**	char*	ft_strdup(char const* str);
*/
void	print_test_strdup(char const* test_name, int can_segfault,
		char const* src)
{
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) result_libft = ft_strdup(src); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  =    strdup(src); else result_libc  = segstr;
	print_test_str(test_name, "strdup return", result_libft, result_libc, can_segfault);
	if (result_libft) free(result_libft);
	if (result_libc)  free(result_libc);
}
void	test_strdup(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strdup("strdup",            	FALSE,	test1);
	print_test_strdup("strdup (empty str)",	FALSE,	"\0");
//	print_test_strdup("strdup (null str) ",	TRUE, 	NULL);
}



/*
**	char*	ft_strcpy(char* dest, char const* src);
*/
void	print_test_strcpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src)
{
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) result_libft = ft_strcpy(dest_libft, src); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  =    strcpy(dest_libc,  src); else result_libc  = segstr;
	print_test_str(test_name, "strcpy 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strcpy return",     result_libft, result_libc, can_segfault);
}
void	test_strcpy(void)
{
	char str1[test2_len];
	char str2[test2_len];
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strcpy("strcpy",            	FALSE,	str1, str2, test2);
	print_test_strcpy("strcpy (n = 0)",    	FALSE,	str1, str2, test2);
	print_test_strcpy("strcpy (null dest)",	TRUE, 	NULL, NULL, test2);
	print_test_strcpy("strcpy (null src) ",	TRUE, 	str1, str2, NULL);
	print_test_strcpy("strcpy (both null)",	TRUE, 	NULL, NULL, NULL);
}



/*
**	char*	ft_strncpy(char* dest, char const* src, size_t n);
*/
void	print_test_strncpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t n)
{
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) result_libft = ft_strncpy(dest_libft, src, n); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  =    strncpy(dest_libc,  src, n); else result_libc  = segstr;
	print_test_str(test_name, "strncpy 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strncpy return",     result_libft, result_libc, can_segfault);
}
void	test_strncpy(void)
{
	char str1[32];
	char str2[32];
printf("\n");
/*	| TEST FUNCTION   | TEST NAME               | CAN SEGV | TEST ARGS */
	print_test_strncpy("strncpy",                 	FALSE,	str1, str2, test1,     test1_len);
	print_test_strncpy("strncpy (n = 0)",         	FALSE,	str1, str2, test1,             0);
	print_test_strncpy("strncpy (n < src_len)",   	FALSE,	str1, str2, test1, test1_len - 5);
	print_test_strncpy("strncpy (n > src_len)",   	FALSE,	str1, str2, test2, test2_len + 5);
	print_test_strncpy("strncpy (several '\\0's)",	FALSE,	str1, str2, "Swag\0\0\0",      7);
	print_test_strncpy("strncpy (null dest)",     	TRUE, 	NULL, NULL, test1,             5);
	print_test_strncpy("strncpy (null src) ",     	TRUE, 	str1, str2, NULL,              5);
	print_test_strncpy("strncpy (both null)",     	TRUE, 	NULL, NULL, NULL,              5);
}



/*
**	size_t	ft_strlcat(char* dest, char const* src, size_t size);
*/
void	print_test_strlcpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t size)
{
	const int has_segfault = 0x7FFFFFFF;
	size_t	return_libft = 0;
	size_t	return_libc  = 0;
	char*	result_libft;
	char*	result_libc;
	segfault = setjmp(restore); if (!segfault) return_libft = ft_strlcpy(dest_libft, src, size); else return_libft = has_segfault;
	segfault = setjmp(restore); if (!segfault) return_libc  =    strlcpy(dest_libc,  src, size); else return_libc  = has_segfault;
	result_libft = (return_libft == has_segfault) ? NULL : int_to_string(return_libft);
	result_libc  = (return_libc  == has_segfault) ? NULL : int_to_string(return_libc);
	print_test_str(test_name, "strlcpy 'dest' arg", dest_libft, dest_libc, can_segfault);
	print_test_str(NULL,      "strlcpy return",
		(result_libft) ? segstr : result_libft,
		(result_libc)  ? segstr : result_libc,
		can_segfault);
}
void	test_strlcpy(void)
{
	char str1[32];
	char str2[32];
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS */
	print_test_strlcpy("strlcpy          ",  	FALSE,	str1, str2, " shindeiru", 5);
	print_test_strlcpy("strlcpy (n = 0)  ",  	FALSE,	str1, str2, " shindeiru", 0);
	print_test_strlcpy("strlcpy (n < len)",  	FALSE,	str1, str2, " shindeiru", 15);
	print_test_strlcpy("strlcpy (n > len)",  	FALSE,	str1, str2, " shindeiru", 50);
	print_test_strlcpy("strlcpy (null dest)",	TRUE,	NULL, NULL, " shindeiru", 5);
	print_test_strlcpy("strlcpy (null src) ",	TRUE,	str1, str2, NULL,         5);
	print_test_strlcpy("strlcpy (both null)",	TRUE,	NULL, NULL, NULL,         5);
}



/*
**	char*	ft_strcat(char* dest, char const* src);
*/
void	print_test_strcat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src)
{
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) result_libft = ft_strcat(dest_libft, src); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  =    strcat(dest_libc,  src); else result_libc  = segstr;
	print_test_str(test_name, "strcat 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strcat return",     result_libft, result_libc, can_segfault);
}
void	test_strcat(void)
{
	char str1[32];
	char str2[32];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strcat("strcat",            	FALSE,	str1, str2, "Bob\0");
	print_test_strcat("strcat (null dest)",	TRUE,	NULL, NULL, "Bob\0");
	print_test_strcat("strcat (null src) ",	TRUE,	str1, str2, NULL);
	print_test_strcat("strcat (both null)",	TRUE,	NULL, NULL, NULL);
}



/*
**	char*	ft_strncat(char* dest, char const* src, size_t n);
*/
void	print_test_strncat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t n)
{
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) result_libft = ft_strncat(dest_libft, src, n); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  =    strncat(dest_libc,  src, n); else result_libc  = segstr;
	print_test_str(test_name, "strncat 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strncat return",     result_libft, result_libc, can_segfault);
}
void	test_strncat(void)
{
	char str1[32];
	char str2[32];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS */
	print_test_strncat("strncat          ",  	FALSE,	str1, str2, "Bob\0",    3);
	print_test_strncat("strncat (n = 0)  ",  	FALSE,	str1, str2, "Bobensen", 0);
	print_test_strncat("strncat (n < len)",  	FALSE,	str1, str2, "Bobensen", 3);
	print_test_strncat("strncat (n > len)",  	FALSE,	str1, str2, "Bob\0",    7);
	print_test_strncat("strncat (null dest)",	TRUE,	NULL, NULL, "Bob\0",    5);
	print_test_strncat("strncat (null src) ",	TRUE,	str1, str2, NULL,       5);
	print_test_strncat("strncat (both null)",	TRUE,	NULL, NULL, NULL,       5);
}



/*
**	size_t	ft_strlcat(char* dest, char const* src, size_t size);
*/
void	print_test_strlcat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t size)
{
	const int has_segfault = 0x7FFFFFFF;
	size_t	return_libft = 0;
	size_t	return_libc  = 0;
	char*	result_libft;
	char*	result_libc;
	segfault = setjmp(restore); if (!segfault) return_libft = ft_strlcat(dest_libft, src, size); else return_libft = has_segfault;
	segfault = setjmp(restore); if (!segfault) return_libc  =    strlcat(dest_libc,  src, size); else return_libc  = has_segfault;
	result_libft = (return_libft == has_segfault) ? NULL : int_to_string(return_libft);
	result_libc  = (return_libc  == has_segfault) ? NULL : int_to_string(return_libc);
	print_test_str(test_name, "strlcat 'dest' arg", dest_libft,   dest_libc, can_segfault);
	print_test_str(NULL,      "strlcat return",
		(result_libft) ? segstr : result_libft,
		(result_libc)  ? segstr : result_libc,
		can_segfault);
}
void	test_strlcat(void)
{
	char str1[32];
	char str2[32];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS */
	print_test_strlcat("strlcat          ",  	FALSE,	str1, str2, " shindeiru", 5);
	print_test_strlcat("strlcat (n = 0)  ",  	FALSE,	str1, str2, " shindeiru", 0);
	print_test_strlcat("strlcat (n < len)",  	FALSE,	str1, str2, " shindeiru", 15);
	print_test_strlcat("strlcat (n > len)",  	FALSE,	str1, str2, " shindeiru", 50);
	print_test_strlcat("strlcat (null dest)",	TRUE,	NULL, NULL, " shindeiru", 5);
	print_test_strlcat("strlcat (null src) ",	TRUE,	str1, str2, NULL,         5);
	print_test_strlcat("strlcat (both null)",	TRUE,	NULL, NULL, NULL,         5);
}



/*
**
*/
/*
void	print_test_strsplit(char const* test_name, int can_segfault,
		char const* *expect,
		char const* str,
		char separator)
{
	char* *result;
	segfault = setjmp(restore); if (!segfault) result = ft_strsplit(str, separator);
	else { result = (char**)malloc(sizeof(char*)); *result = segstr; }
	print_test_strls(test_name, "strsplit", (char const* *)result, expect, can_segfault);
}
*/



int		test_string(void)
{
	char*	str1;
	char*	str2;
	char const test1[] = "Omae wa mou shindeiru.";		size_t test1_len = strlen(test1) + 1;
	char const test2[] = "Nani???";						size_t test2_len = strlen(test2) + 1;
	char const test3[] = "Un ange mange de la fange.";	size_t test3_len = strlen(test3) + 1;
	char**	strls;

printf("\n");

	printf("       .----------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_string   }===---\n");
	printf("       '----------------------------'       \n");

	test_strnew();
	test_strdup();
	test_strcpy();
	test_strncpy();
	test_strlcpy();
	test_strcat();
	test_strncat();
	test_strlcat();

	print_nonstd();

	test_strset();
	test_strclr();
//	test_strdel();

printf("\n");
/*
//	char*	ft_strchr(char const* str, int c);
	sra = ft_strchr(test1, 'm');
	srb =    strchr(test1, 'm');
	print_test_str("strchr", "strchr return", sra, srb, FALSE);

	sra = ft_strchr(test1, '_');
	srb =    strchr(test1, '_');
	print_test_str("strchr", "strchr return", sra, srb, FALSE);

	sra = ft_strchr(test3, '\0');
	srb =    strchr(test3, '\0');
	print_test_str("strchr (\\0)", "strchr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strchr(NULL, '_'); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strchr(NULL, '_'); else srb = segstr;
	print_test_str("strchr (null ptr)", "strchr return", sra, srb, TRUE);

printf("\n");

//	char*	ft_strrchr(char const* str, int c);
	sra = ft_strrchr(test1, 'm');
	srb =    strrchr(test1, 'm');
	print_test_str("strrchr", "strrchr return", sra, srb, FALSE);

	sra = ft_strrchr(test1, '_');
	srb =    strrchr(test1, '_');
	print_test_str("strrchr", "strrchr return", sra, srb, FALSE);

	sra = ft_strrchr(test3, '\0');
	srb =    strrchr(test3, '\0');
	print_test_str("strrchr (\\0)", "strrchr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strrchr(NULL, 'm'); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strrchr(NULL, 'm'); else srb = segstr;
	print_test_str("strrchr (null ptr)", "strrchr return", sra, srb, TRUE);

printf("\n");

//	char*	ft_strstr(char const* str, char const* query);
	sra = ft_strstr(test1, "mou ");
	srb =    strstr(test1, "mou ");
	print_test_str("strstr", "strstr return", sra, srb, FALSE);

	sra = ft_strstr(test2, "??");
	srb =    strstr(test2, "??");
	print_test_str("strstr", "strstr return", sra, srb, FALSE);

	sra = ft_strstr(test2, "???");
	srb =    strstr(test2, "???");
	print_test_str("strstr", "strstr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strstr(NULL, "mou "); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strstr(NULL, "mou "); else srb = segstr;
	print_test_str("strstr (null str)  ", "strstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strstr(test1, NULL); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strstr(test1, NULL); else srb = segstr;
	print_test_str("strstr (null query)", "strstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strstr(NULL, NULL); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strstr(NULL, NULL); else srb = segstr;
	print_test_str("strstr (both null) ", "strstr return", sra, srb, TRUE);

printf("\n");

//	char*	ft_strnstr(char const* str, char const* query, size_t n);
	sra = ft_strnstr(test1, "ou ", test1_len);
	srb =    strnstr(test1, "ou ", test1_len);
	print_test_str("strnstr", "strnstr return", sra, srb, FALSE);

	sra = ft_strnstr(test1, "ou ", 0);
	srb =    strnstr(test1, "ou ", 0);
	print_test_str("strnstr (n = 0)", "strnstr return", sra, srb, FALSE);

	sra = ft_strnstr(test1, "ou ", 3);
	srb =    strnstr(test1, "ou ", 3);
	print_test_str("strnstr (n < match)", "strnstr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strnstr(NULL, "ou ", test1_len); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strnstr(NULL, "ou ", test1_len); else srb = segstr;
	print_test_str("strnstr (null str)  ", "strnstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strnstr(test1, NULL, test1_len); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strnstr(test1, NULL, test1_len); else srb = segstr;
	print_test_str("strnstr (null query)", "strnstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strnstr(NULL, NULL, 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strnstr(NULL, NULL, 5); else srb = segstr;
	print_test_str("strnstr (both null) ", "strnstr return", sra, srb, TRUE);

printf("\n");

//	int		ft_strcmp(char const* str1, char const* str2);
	na = ft_strcmp(test3, test2);
	nb =    strcmp(test3, test2);
	test_int("strcmp", "strcmp return", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strcmp(NULL, test2); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strcmp(NULL, test2); else nb = 0xFFFFFFFF;
	print_test_str("strcmp (null str1)", "strcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strcmp(test3, NULL); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strcmp(test3, NULL); else nb = 0xFFFFFFFF;
	print_test_str("strcmp (null str2)", "strcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strcmp(NULL, NULL); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strcmp(NULL, NULL); else nb = 0xFFFFFFFF;
	print_test_str("strcmp (both null)", "strcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

printf("\n");

//	int		ft_strncmp(char const* str1, char const* str2, size_t n);
	na = ft_strncmp(test1, test3, 7);
	nb =    strncmp(test1, test3, 7);
	test_int("strncmp", "strncmp return", na, nb, FALSE);

	na = ft_strncmp("abc", "abcdef", 3);
	nb =    strncmp("abc", "abcdef", 3);
	test_int("strncmp", "strncmp return", na, nb, FALSE);

	na = ft_strncmp(test2 + 1, test3 + 3, 2);
	nb =    strncmp(test2 + 1, test3 + 3, 2);
	test_int("strncmp", "strncmp return", na, nb, FALSE);

	na = ft_strncmp(test2, test3, 0);
	nb =    strncmp(test2, test3, 0);
	test_int("strncmp (n = 0)", "strncmp return", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strncmp(NULL, test3, 7); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strncmp(NULL, test3, 7); else nb = 0xFFFFFFFF;
	print_test_str("strncmp (null str1)", "strncmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strncmp(test1, NULL, 7); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strncmp(test1, NULL, 7); else nb = 0xFFFFFFFF;
	print_test_str("strncmp (null str2)", "strncmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strncmp(NULL, NULL, 7); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strncmp(NULL, NULL, 7); else nb = 0xFFFFFFFF;
	print_test_str("strncmp (both null)", "strncmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

printf("\n");

//	char*	ft_strrev(char const* str);
	str1 = ft_strrev(test1);
	str2 = ".uriednihs uom aw eamO";
	print_test_str("strrev (even len)", "_strrev", str1, str2, FALSE);

	str1 = ft_strrev(test2);
	str2 = "???inaN";
	print_test_str("strrev (odd len) ", "_strrev", str1, str2, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strrev(NULL); else sra = segstr;
//	segfault = setjmp(restore); if (!segfault) srb =    strrev(NULL); else srb = segstr;
	print_test_str("strrev (null ptr)", "_strrev", sra, segstr, TRUE);

printf("\n");

//	int		ft_strequ(char const* str1, char const* str2);
	na = ft_strequ(test1, test2);
	nb =   (strcmp(test1, test2) == 0);
	test_int("strequ", "_strequ", na, nb, FALSE);

	na = ft_strequ(str1, test1);
	nb =   (strcmp(str1, test1) == 0);
	test_int("strequ", "_strequ", na, nb, FALSE);

	na = ft_strequ(str1, "");
	nb =   (strcmp(str1, "") == 0);
	test_int("strequ (empty str)", "_strequ", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strequ(NULL, test2); else na = 0xFFFFFFFF;
	print_test_str("strequ (null str1)", "_strequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strequ(test1, NULL); else na = 0xFFFFFFFF;
	print_test_str("strequ (null str2)", "_strequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strequ(NULL, NULL); else na = 0xFFFFFFFF;
	print_test_str("strequ (both null)", "_strequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

printf("\n");

//	int		ft_strnequ(char const* str1, char const* str2, size_t n)
	na = ft_strnequ(test1, test2, 5);
	nb =   (strncmp(test1, test2, 5) == 0);
	test_int("strnequ", "_strnequ", na, nb, FALSE);

	na = ft_strnequ(str1, test1, 5);
	nb =   (strncmp(str1, test1, 5) == 0);
	test_int("strnequ", "_strnequ", na, nb, FALSE);

	na = ft_strnequ(str1, test1, 50);
	nb =   (strncmp(str1, test1, 50) == 0);
	test_int("strnequ (n > len)", "_strnequ", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strnequ(NULL, test1, 5); else na = 0xFFFFFFFF;
	print_test_str("strnequ (null str1)", "_strnequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strnequ(test1, NULL, 5); else na = 0xFFFFFFFF;
	print_test_str("strnequ (null str2)", "_strnequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strnequ(NULL, NULL, 5); else na = 0xFFFFFFFF;
	print_test_str("strnequ (both null)", "_strnequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

printf("\n");

//	char*	ft_strsub(char const* str, size_t start, size_t length);
	sra = ft_strsub(test1, 5, 5);
	srb = "wa mo";
	print_test_str("strsub", "_strsub", sra, srb, FALSE);
//	free(sra);

	sra = ft_strsub(test1, 0, 0);
	print_test_str("strsub (len = 0)", "_strsub", sra, "", FALSE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strsub(test1, 5, 100); else sra = segstr;
	print_test_str("strsub (len > str)", "_strsub", sra, NULL, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strsub(test1, 100, 5); else sra = segstr;
	print_test_str("strsub (offset > str)", "_strsub", sra, NULL, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strsub(NULL, 5, 5); else sra = segstr;
	print_test_str("strsub (null ptr)", "_strsub", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

printf("\n");

//	char*	ft_strjoin(char const* str1, char const* str2);
	sra = ft_strjoin(test1, test2);
	srb = "Omae wa mou shindeiru.Nani???";
	print_test_str("strjoin", "_strjoin", sra, srb, FALSE);
//	free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strjoin(NULL, test2); else sra = segstr;
	print_test_str("strjoin (null str1)", "_strjoin", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strjoin(test1, NULL); else sra = segstr;
	print_test_str("strjoin (null str2)", "_strjoin", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strjoin(test1, NULL); else sra = segstr;
	print_test_str("strjoin (both null)", "_strjoin", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

printf("\n");

//	char*	ft_strtrim(char const* str);
	sra = ft_strtrim("\t\n    FOR THE\tHORDE ! 	 \t \n ");
	srb = "FOR THE\tHORDE !";
	print_test_str("strtrim", "_strtrim", sra, srb, FALSE);
//	free(sra);

	sra = ft_strtrim("   swag");
	srb = "swag";
	print_test_str("strtrim", "_strtrim", sra, srb, FALSE);
//	free(sra);

	sra = ft_strtrim("do u even trim bruh\n\n\n\n\t");
	srb = "do u even trim bruh";
	print_test_str("strtrim", "_strtrim", sra, srb, FALSE);
//	free(sra);

	sra = ft_strtrim("\n   \n\t ");
	print_test_str("strtrim (only whitespace)", "_strtrim", sra, "", FALSE);
//	free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strtrim(""); else sra = segstr;
	print_test_str("strtrim (empty string)", "_strtrim", sra, "", FALSE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strtrim(NULL); else sra = segstr;
	print_test_str("strtrim (null ptr)", "_strtrim", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

printf("\n");

//	char*	*ft_strsplit(char const* str, char c);

	printf("\nstrsplit\n");
	strls = ft_strsplit(test1, ' ');
	printf("ft_strsplit: [");
	for (int i = 0; strls[i]; i++)
		printf("%s%s", strls[i], strls[i + 1] ? ", " : "]\n");
	printf("   Expected: [Omae, wa, mou, shindeiru.]");

	char const* split_1[] = { "Omae", "wa", "mou", "shindeiru." };
	test_strsplit("strsplit", FALSE, split_1, test1, ' ');

	char const* split_2[] = { "Un ", "nge m", "nge de l", " f", "nge." };
	test_strsplit("strsplit", FALSE, split_2, test3, 'a');

	segfault = setjmp(restore); if (!segfault) strls = ft_strsplit(NULL, ' '); else strls = (char* *)segstr;
	print_test_str("strsplit (null ptr)", "_strsplit", strls, segstr, TRUE);

printf("\n");

//	void	ft_striter(char* str, void (*f))
	strcpy(str1, "omAe wA mOu ShINDeIRu.");
	ft_striter(str1, ptrtolower);
	print_test_str("striter", "_striter", str1, "omae wa mou shindeiru.", FALSE);

	strcpy(str1, "omAe wA mOu ShINDeIRu.");
	segfault = setjmp(restore); if (!segfault) ft_striter(sra, NULL); else sra = segstr;
	print_test_str("striter (null f)   ", "_striter", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striter(NULL, ptrtolower); sra = NULL; } else sra = segstr;
	print_test_str("striter (null str) ", "_striter", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striter(NULL, NULL); sra = NULL; } else sra = segstr;
	print_test_str("striter (both null)", "_striter", sra, segstr, TRUE);

printf("\n");

//	void	ft_striteri(char* str, void (*f)(unsigned int, char* ));
	strcpy(str1, "OMAE WA MOU SHINDEIRU.");
	ft_striteri(str1, ptrtolower_1on2);
	print_test_str("striteri", "_striteri", str1, "oMaE Wa mOu sHiNdEiRu.", FALSE);

	strcpy(str1, "OMAE WA MOU SHINDEIRU.");
	segfault = setjmp(restore); if (!segfault) ft_striteri(sra, NULL); else sra = segstr;
	print_test_str("striteri (null f)   ", "_striteri", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striteri(NULL, ptrtolower_1on2); sra = NULL; } else sra = segstr;
	print_test_str("striteri (null str) ", "_striteri", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striteri(NULL, NULL); sra = NULL; } else sra = segstr;
	print_test_str("striteri (both null)", "_striteri", sra, segstr, TRUE);

printf("\n");

//	char*	ft_strmap(char const* str, char (*f)(char));
	str1 = ft_strmap("omAe wA mOu ShINDeIRu.", toupper_chr);
	print_test_str("strmap", "_strmap", str1, "OMAE WA MOU SHINDEIRU.", FALSE);

	segfault = setjmp(restore); if (!segfault) str1 = ft_strmap("omAe wA mOu ShINDeIRu.", NULL); else str1 = segstr;
	print_test_str("strmap (null f)   ", "_strmap", str1, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) str1 = ft_strmap(NULL, toupper_chr); else str1 = segstr;
	print_test_str("strmap (null str) ", "_strmap", str1, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) str1 = ft_strmap(NULL, NULL); else str1 = segstr;
	print_test_str("strmap (both null)", "_strmap", str1, segstr, TRUE);

printf("\n");

//	char*	ft_strmapi(char const* str, char (*f)(unsigned int, char));
	str1 = ft_strmapi("omae wa mou shindeiru.", toupper_1on2);
	print_test_str("strmapi", "_strmapi", str1, "oMaE Wa mOu sHiNdEiRu.", FALSE);

	segfault = setjmp(restore); if (!segfault) str1 = ft_strmapi("omAe wA mOu ShINDeIRu.", NULL); else str1 = segstr;
	print_test_str("strmapi (null f)   ", "_strmapi", str1, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) str1 = ft_strmapi(NULL, toupper_1on2); else str1 = segstr;
	print_test_str("strmapi (null str) ", "_strmapi", str1, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) str1 = ft_strmapi(NULL, NULL); else str1 = segstr;
	print_test_str("strmapi (both null)", "_strmapi", str1, segstr, TRUE);
*/
	return (0);
}
