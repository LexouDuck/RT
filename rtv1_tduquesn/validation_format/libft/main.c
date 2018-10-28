#include "main_util.c"

int segfault;
struct sigaction sig;
char const segstr[] = "(segfault)";



void	test_bzero(char const *test_name, int can_segfault,
		char *dest_libft,
		char *dest_libc,
		size_t length)
{
	segfault = setjmp(restore); if (!segfault) ft_bzero(dest_libft, length); else dest_libft = segstr;
	segfault = setjmp(restore); if (!segfault)    bzero(dest_libc,  length); else dest_libc  = segstr;
	test_str(test_name, "bzero",                    dest_libft,          dest_libc,          can_segfault);
	test_str(NULL,      "bzero (after the '\\0's)", dest_libft + length, dest_libc + length, can_segfault);
}

void	test_memset(char const *test_name, int can_segfault,
		char *dest_libft,
		char *dest_libc,
		int byte,
		size_t length)
{
	char *result_libft;
	char *result_libc;
	segfault = setjmp(restore); if (!segfault) result_libft = (char*)ft_memset(dest_libft, byte, length); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  = (char*)   memset(dest_libc,  byte, length); else result_libc  = segstr;
	test_mem(test_name, "memset arg",      dest_libft,   dest_libc, length, can_segfault);
	test_mem(NULL,      "memset return", result_libft, result_libc, length, can_segfault);
}

void	test_memcpy(char const *test_name, int can_segfault,
		char *dest_libft,
		char *dest_libc,
		char const *src,
		size_t src_len)
{
	char *result_libft;
	char *result_libc;
	segfault = setjmp(restore); if (!segfault) result_libft = (char*)ft_memcpy(dest_libft, src, src_len); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  = (char*)   memcpy(dest_libc,  src, src_len); else result_libc  = segstr;
	test_str(test_name, "memcpy arg",      dest_libft,   dest_libc, can_segfault);
	test_str(NULL,      "memcpy return", result_libft, result_libc, can_segfault);
}

void	test_memccpy(char const *test_name, int can_segfault,
		char *dest_libft,
		char *dest_libc,
		char const *src,
		char c,
		size_t src_len)
{
	char *result_libft;
	char *result_libc;
	segfault = setjmp(restore); if (!segfault) result_libft = (char*)ft_memccpy(dest_libft, src, c, src_len); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  = (char*)   memccpy(dest_libc,  src, c, src_len); else result_libc  = segstr;
	test_str(test_name, "memccpy arg",      dest_libft,   dest_libc, can_segfault); if (c !='\0')
	test_str(NULL,      "memccpy return", result_libft, result_libc, can_segfault);
}

void	test_strcpy(char const *test_name, int can_segfault,
		char *dest_libft,
		char *dest_libc,
		char const *src)
{
	char *result_libft;
	char *result_libc;
	segfault = setjmp(restore); if (!segfault) result_libft = (char*)ft_strcpy(dest_libft, src); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  = (char*)   strcpy(dest_libc,  src); else result_libc  = segstr;
	test_str(test_name, "strcpy arg",      dest_libft,   dest_libc, can_segfault);
	test_str(NULL,      "strcpy return", result_libft, result_libc, can_segfault);
}

void	test_strncpy(char const *test_name, int can_segfault,
		char *dest_libft,
		char *dest_libc,
		char const *src,
		size_t length)
{
	char *result_libft;
	char *result_libc;
	segfault = setjmp(restore); if (!segfault) result_libft = (char*)ft_strncpy(dest_libft, src, length); else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) result_libc  = (char*)   strncpy(dest_libc,  src, length); else result_libc  = segstr;
	test_str(test_name, "strcpy arg",      dest_libft,   dest_libc, can_segfault);
	test_str(NULL,      "strcpy return", result_libft, result_libc, can_segfault);
}

void	test_memalloc(char const *test_name, int can_segfault,
		char *result_1,
		char *result_2,
		size_t length)
{
	int error;
	segfault = setjmp(restore); if (!segfault) result_1 = (char *)ft_memalloc(MALLOC_LEN); else result_1 = segstr;
	segfault = setjmp(restore); if (!segfault) result_2 = (char *)ft_memalloc(MALLOC_LEN); else result_2 = segstr;
	printf("\n%s -> ", test_name);
	if (result_1 == NULL) { error = TRUE; printf(C_RED"\nERROR - The 1st call returned NULL."RESET); }
	if (result_2 == NULL) { error = TRUE; printf(C_RED"\nERROR - The 2nd call returned NULL."RESET); }
	for (size_t i = 0; i < MALLOC_LEN; ++i)
	{
		if (result_1[i] || result_2[i])
		{
			error = TRUE;
			printf(C_RED"\nERROR - Every char should be '\\0'."RESET);
		}
	}
	if (!error) printf(C_GREEN"OK!"RESET);
}
void	test_strnew(char const *test_name, int can_segfault,
		char *result_1,
		char *result_2,
		size_t length)
{
	int error;
	segfault = setjmp(restore); if (!segfault) result_1 = (char *)ft_strnew(MALLOC_LEN); else result_1 = segstr;
	segfault = setjmp(restore); if (!segfault) result_2 = (char *)ft_strnew(MALLOC_LEN); else result_2 = segstr;
	printf("\n%s -> ", test_name);
	if (result_1 == NULL) { error = TRUE; printf(C_RED"\nERROR - The 1st call returned NULL."RESET); }
	if (result_2 == NULL) { error = TRUE; printf(C_RED"\nERROR - The 2nd call returned NULL."RESET); }
	for (size_t i = 0; i < MALLOC_LEN; ++i)
	{
		if (result_1[i] || result_2[i])
		{
			error = TRUE;
			printf(C_RED"\nERROR - Every char should be '\\0'."RESET);
		}
	}
	if (!error) printf(C_GREEN"OK!"RESET);
}



void	test_strsplit(char const *test_name, int can_segfault,
		char const **expect,
		char const *str,
		char separator)
{
	char **result;
	segfault = setjmp(restore);
	if (!segfault) result = ft_strsplit(str, separator);
	else { result = (char **)malloc(sizeof(char *)); *result = segstr; }
	test_strarray(test_name, "strsplit", (char const **)result, expect, can_segfault);
}












int		main(void)
{
	memset(&sig, 0, sizeof(sigaction));
	sigemptyset(&sig.sa_mask);
	sig.sa_flags     = SA_NODEFER;
	sig.sa_sigaction = segfault_handler;
	sigaction(SIGSEGV, &sig, NULL);



	int num = 1;
	if (*(char *)&num == 1)
	{
		printf(C_GREEN"\n/!\\ Processor is Little-Endian (all tests should work fine)\n"RESET);
	}
	else
	{
		printf(C_RED"\n/!\\ Processor is Big-Endian (errors may arise in certain tests: notably memcmp, and various lst tests)\n"RESET);
	}
	printf(C_YELLOW"\nAll the tests with written in yellow 'can segfault' are NULL pointer tests.\n"RESET);



	t_u32	n = 0xFFFFAAAA;
	t_u32	na;
	t_u32	nb;
	t_u32	*nra;	
	t_u32	*nrb;
	t_u64	la;
	t_u64	lb;
	char 	*sa;
	char 	*sb;
	char	*sra;
	char	*srb;
	char const s1[] = "Omae wa mou shindeiru.";		size_t s1_len = strlen(s1) + 1;
	char const s2[] = "Nani???";					size_t s2_len = strlen(s2) + 1;
	char const s3[] = "Un ange mange de la fange.";	size_t s3_len = strlen(s3) + 1;
	char	**strls;



//	void	*ft_memalloc(size_t size);
	test_memalloc("memalloc", FALSE, sa, sb, MALLOC_LEN);

printf("\n");

//	char	*ft_strnew(size_t size);
	test_strnew("strnew", FALSE, sra, srb, MALLOC_LEN);

printf("\n");

//	void	*ft_memcpy(void *dest, const void *src, size_t n);
	nra = (t_u32*)ft_memcpy(&na, &n, 4);
	nrb = (t_u32*)   memcpy(&nb, &n, 4);
	test_int("memcpy (uint) ", "memcpy arg",    na,   nb,   FALSE);
	test_int(NULL,             "memcpy return", *nra, *nrb, FALSE);

	test_memcpy("memcpy (str)  ",     FALSE, sa,   sb,   s1,   s1_len);
	test_memcpy("memcpy (n = 0)",     FALSE, sa,   sb,   s1,   0);
	test_memcpy("memcpy (null dest)", TRUE,  NULL, NULL, s1,   s1_len);
	test_memcpy("memcpy (null src) ", TRUE,  sa,   sb,   NULL, s1_len);
	test_memcpy("memcpy (both null)", TRUE,  NULL, NULL, NULL, s1_len);

printf("\n");

//	void	*ft_memccpy(void *dest, const void *src, int byte, size_t n);
/*
	sra = ft_memccpy(&na, &n, 0xAA, 10);
	srb =    memccpy(&nb, &n, 0xAA, 10);
	test_int("memccpy (uint)", "memccpy arg", na, nb, FALSE);
	test_int(NULL, "memccpy return pointer difference",
		(t_u32)(sra - (char *)&na),
		(t_u32)(srb - (char *)&nb), FALSE);
*/
	test_memccpy("memccpy (str) ",           FALSE,  sa,   sb,  s3,   'e', s3_len);
	test_memccpy("memccpy (str, c = '\\0')", FALSE,  sa,   sb,  s3,  '\0', s3_len);
	test_memccpy("memccpy (null dest)",      TRUE,  NULL, NULL, s3,   'e', s3_len);
	test_memccpy("memccpy (null src) ",      TRUE,   sa,   sb,  NULL, 'e', 5);
	test_memccpy("memccpy (both null)",      TRUE,  NULL, NULL, NULL, 'e', 5);

printf("\n");

//	char	*ft_strcpy(char *dest, const char *src);
	test_strcpy("strcpy",             FALSE, sa,   sb,   s2);
	test_strcpy("strcpy (n = 0)",     FALSE, sa,   sb,   s2);
	test_strcpy("strcpy (null dest)", TRUE,  NULL, NULL, s2);
	test_strcpy("strcpy (null src) ", TRUE,  sa,   sb,   NULL);
	test_strcpy("strcpy (both null)", TRUE,  NULL, NULL, NULL);

printf("\n");

//	char	*ft_strncpy(char *dest, const char *src, size_t n);
	test_strncpy("strncpy",                  FALSE, sa,   sb,   s1,  s1_len);
	test_strncpy("strncpy (n = 0)",          FALSE, sa,   sb,   s1,  0);
	test_strncpy("strncpy (n > src_len)",    FALSE, sa,   sb,   s2,  s2_len + 5);
	test_strncpy("strncpy (n < src_len)",    FALSE, sa,   sb,   s1,  s1_len - 5);
	test_strncpy("strncpy (several '\\0's)", FALSE, sa,   sb,   "Swag\0\0\0", 7);
	test_strncpy("strncpy (null dest)",      TRUE,  NULL, NULL, s1,   5);
	test_strncpy("strncpy (null src) ",      TRUE,  sa,   sb,   NULL, 5);
	test_strncpy("strncpy (both null)",      TRUE,  NULL, NULL, NULL, 5);

printf("\n");

//	void	*ft_memset(void *ptr, int byte, size_t n);
	test_memset("memset (str)",      FALSE,  sa,  sb,  'a', 7);
	test_memset("memset (uint)",     FALSE, &na, &nb,  0xDDCCBBAA, 4);
	test_memset("memset (n = 0)",    FALSE,  sa,  sb, '\0', 0);
	test_memset("memset (null ptr)", TRUE,   sa,  sb,  '_', 5);

printf("\n");

//	void	ft_bzero(void *ptr, size_t n);
	test_bzero("bzero",            FALSE, sa, sb, 2);
	test_bzero("bzero (n = 0)",    FALSE, sa, sb, 0);
	test_bzero("bzero (null ptr)", TRUE,  sa, sb, 2);

printf("\n");

//	void	*ft_memmove(void *dest, const void *src, size_t n);
/*	
	n = 0xDDAA3333;
	nra = ft_memmove(&na, &n, 4);
	nrb =    memmove(&nb, &n, 4);
	test_int("memmove (uint) ", "memmove arg",    na,   nb,   FALSE);
	test_int(NULL,              "memmove return", *nra, *nrb, FALSE);

	sra = ft_memmove(sa, s2, s2_len);
	srb =    memmove(sb, s2, s2_len);
	test_str("memmove (str)  ", "memmove arg",    sa,  sb,  FALSE);
	test_str(NULL,              "memmove return", sra, srb, FALSE);

	sra = ft_memmove(sa, s1, 0);
	srb =    memmove(sb, s1, 0);
	test_str("memmove (n = 0)", "memmove arg",    sa,  sb,  FALSE);
	test_str(NULL,              "memmove return", sra, srb, FALSE);

	sra = ft_memmove(sa + 3, sa, s1_len - 5);
	srb =    memmove(sb + 3, sb, s1_len - 5);
	test_str("memmove (overlapping)", "memmove arg",    sa,  sb,  FALSE);
	test_str(NULL,                    "memmove return", sra, srb, FALSE);
*/
	segfault = setjmp(restore); if (!segfault) sra = ft_memmove(NULL, s1, 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    memmove(NULL, s1, 5); else srb = segstr;
	test_str("memmove (null dest)", "memmove return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_memmove(sa, NULL, 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    memmove(sb, NULL, 5); else srb = segstr;
	test_str("memmove (null src) ", "memmove arg",    sa,  sb,  TRUE);
	test_str(NULL,                  "memmove return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_memmove(NULL, NULL, 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    memmove(NULL, NULL, 5); else srb = segstr;
	test_str("memmove (both null)", "memmove return", sra, srb, TRUE);

printf("\n");

//	char	*ft_strdup(const char *str);
	sra = ft_strdup(s1);
	srb =    strdup(s1);
	test_str("strdup", "strdup return", sa, sb, FALSE);
/*
	segfault = setjmp(restore); if (!segfault) sra = ft_strdup(NULL); else sa = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strdup(NULL); else sb = segstr;
	test_str("strdup (null ptr)", "strdup return", sa, sb, TRUE);
*/
printf("\n");

//	void	ft_strdel(char **ptr);
	ft_strdel(&sra);
//	   strdel(&srb);
	test_str("strdel", "strdel", sra ? C_RED"ERROR"RESET : C_GREEN"OK!"RESET, "(n/a)", FALSE);

	segfault = setjmp(restore); if (!segfault) { ft_strdel(NULL); sra = C_GREEN"OK!"RESET; } else sra = segstr;
//	segfault = setjmp(restore); if (!segfault) {    strdel(NULL); srb = C_GREEN"OK!"RESET; } else srb = segstr;
	test_str("strdel (null ptr)", "strdel", sra, "(n/a)", TRUE);

printf("\n");

//	char	*ft_strchr(char const *str, int c);
	sra = ft_strchr(s1, 'm');
	srb =    strchr(s1, 'm');
	test_str("strchr", "strchr return", sra, srb, FALSE);

	sra = ft_strchr(s1, '_');
	srb =    strchr(s1, '_');
	test_str("strchr", "strchr return", sra, srb, FALSE);

	sra = ft_strchr(s3, '\0');
	srb =    strchr(s3, '\0');
	test_str("strchr (\\0)", "strchr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strchr(NULL, '_'); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strchr(NULL, '_'); else srb = segstr;
	test_str("strchr (null ptr)", "strchr return", sra, srb, TRUE);

printf("\n");

//	char	*ft_strrchr(char const *str, int c);
	sra = ft_strrchr(s1, 'm');
	srb =    strrchr(s1, 'm');
	test_str("strrchr", "strrchr return", sra, srb, FALSE);

	sra = ft_strrchr(s1, '_');
	srb =    strrchr(s1, '_');
	test_str("strrchr", "strrchr return", sra, srb, FALSE);

	sra = ft_strrchr(s3, '\0');
	srb =    strrchr(s3, '\0');
	test_str("strrchr (\\0)", "strrchr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strrchr(NULL, 'm'); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strrchr(NULL, 'm'); else srb = segstr;
	test_str("strrchr (null ptr)", "strrchr return", sra, srb, TRUE);

printf("\n");

//	void	*ft_memchr(const void *ptr, int byte, size_t n);
	na = 0xFFAABBCC; nra = ft_memchr(&na, 0xBB, 4);
	nb = 0xFFAABBCC; nrb =    memchr(&nb, 0xBB, 4);
	test_int("memchr (uint)", "memchr return", *((t_u16*)nra), *((t_u16*)nrb), FALSE);

	sra = ft_memchr(s1, 'u', s1_len);
	srb =    memchr(s1, 'u', s1_len);
	test_str("memchr (str) ", "memchr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_memchr(NULL, 'c', 4); else sa = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    memchr(NULL, 'c', 4); else sb = segstr;
	test_str("memchr (null ptr)", "memchr return", sra, srb, TRUE);

printf("\n");

//	char	*ft_strstr(const char *str, const char *query);
	sra = ft_strstr(s1, "mou ");
	srb =    strstr(s1, "mou ");
	test_str("strstr", "strstr return", sra, srb, FALSE);

	sra = ft_strstr(s2, "??");
	srb =    strstr(s2, "??");
	test_str("strstr", "strstr return", sra, srb, FALSE);

	sra = ft_strstr(s2, "???");
	srb =    strstr(s2, "???");
	test_str("strstr", "strstr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strstr(NULL, "mou "); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strstr(NULL, "mou "); else srb = segstr;
	test_str("strstr (null str)  ", "strstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strstr(s1, NULL); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strstr(s1, NULL); else srb = segstr;
	test_str("strstr (null query)", "strstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strstr(NULL, NULL); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strstr(NULL, NULL); else srb = segstr;
	test_str("strstr (both null) ", "strstr return", sra, srb, TRUE);

printf("\n");

//	char	*ft_strnstr(const char *str, const char *query, size_t n);
	sra = ft_strnstr(s1, "ou ", s1_len);
	srb =    strnstr(s1, "ou ", s1_len);
	test_str("strnstr", "strnstr return", sra, srb, FALSE);

	sra = ft_strnstr(s1, "ou ", 0);
	srb =    strnstr(s1, "ou ", 0);
	test_str("strnstr (n = 0)", "strnstr return", sra, srb, FALSE);

	sra = ft_strnstr(s1, "ou ", 3);
	srb =    strnstr(s1, "ou ", 3);
	test_str("strnstr (n < match)", "strnstr return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strnstr(NULL, "ou ", s1_len); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strnstr(NULL, "ou ", s1_len); else srb = segstr;
	test_str("strnstr (null str)  ", "strnstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strnstr(s1, NULL, s1_len); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strnstr(s1, NULL, s1_len); else srb = segstr;
	test_str("strnstr (null query)", "strnstr return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strnstr(NULL, NULL, 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    strnstr(NULL, NULL, 5); else srb = segstr;
	test_str("strnstr (both null) ", "strnstr return", sra, srb, TRUE);

printf("\n");

//	int		ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
/*
	na = -0x554433; //little endian in mem as CD BB AA FF
	nb = -0x554F33; //little endian in mem as CD B0 AA FF
	printf("na in mem: {%s}\nnb in mem: {%s}\n", ft_memhex(&na, 4), ft_memhex(&nb, 4));
*/
	nra = &na;
	nrb = &nb;
	n = ft_memcmp(nra, nrb, 4);
	num =  memcmp(nra, nrb, 4);
	test_int("memcmp (uint)", "memcmp return", n, num, FALSE);
	//note that some implementations of memcmp can know the type of argument in input,
	//so they return *(int*)nra - *(int*)nrb -> not just analyzing memory as bytes like is said in the man. 

	na = ft_memcmp(s2, s3, s3_len);
	nb =    memcmp(s2, s3, s3_len);
	test_int("memcmp (str) ", "memcmp return", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_memcmp(NULL, s3, s3_len); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    memcmp(NULL, s3, s3_len); else nb = 0xFFFFFFFF;
	test_str("memcmp (null str1)", "memcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_memcmp(s2, NULL, s3_len); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    memcmp(s2, NULL, s3_len); else nb = 0xFFFFFFFF;
	test_str("memcmp (null str2)", "memcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_memcmp(NULL, NULL, s3_len); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    memcmp(NULL, NULL, s3_len); else nb = 0xFFFFFFFF;
	test_str("memcmp (both null)", "memcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

printf("\n");

//	int		ft_strcmp(const char *str1, const char *str2);
	na = ft_strcmp(s3, s2);
	nb =    strcmp(s3, s2);
	test_int("strcmp", "strcmp return", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strcmp(NULL, s2); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strcmp(NULL, s2); else nb = 0xFFFFFFFF;
	test_str("strcmp (null str1)", "strcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strcmp(s3, NULL); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strcmp(s3, NULL); else nb = 0xFFFFFFFF;
	test_str("strcmp (null str2)", "strcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strcmp(NULL, NULL); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strcmp(NULL, NULL); else nb = 0xFFFFFFFF;
	test_str("strcmp (both null)", "strcmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

printf("\n");

//	int		ft_strncmp(const char *str1, const char *str2, size_t n);
	na = ft_strncmp(s1, s3, 7);
	nb =    strncmp(s1, s3, 7);
	test_int("strncmp", "strncmp return", na, nb, FALSE);

	na = ft_strncmp("abc", "abcdef", 3);
	nb =    strncmp("abc", "abcdef", 3);
	test_int("strncmp", "strncmp return", na, nb, FALSE);

	na = ft_strncmp(s2 + 1, s3 + 3, 2);
	nb =    strncmp(s2 + 1, s3 + 3, 2);
	test_int("strncmp", "strncmp return", na, nb, FALSE);

	na = ft_strncmp(s2, s3, 0);
	nb =    strncmp(s2, s3, 0);
	test_int("strncmp (n = 0)", "strncmp return", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strncmp(NULL, s3, 7); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strncmp(NULL, s3, 7); else nb = 0xFFFFFFFF;
	test_str("strncmp (null str1)", "strncmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strncmp(s1, NULL, 7); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strncmp(s1, NULL, 7); else nb = 0xFFFFFFFF;
	test_str("strncmp (null str2)", "strncmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strncmp(NULL, NULL, 7); else na = 0xFFFFFFFF;
	segfault = setjmp(restore); if (!segfault) nb =    strncmp(NULL, NULL, 7); else nb = 0xFFFFFFFF;
	test_str("strncmp (both null)", "strncmp return",
		(na == 0xFFFFFFFF) ? segstr : ft_itoa(na),
		(nb == 0xFFFFFFFF) ? segstr : ft_itoa(nb), TRUE);

printf("\n");

//	char	*ft_strcat(char *dest, const char *src);
	sa = (char *)malloc(MALLOC_LEN);
	sb = (char *)malloc(MALLOC_LEN);
	ft_strcpy(sa, "Sponge\0"); sra = ft_strcat(sa, "Bob\0");
	ft_strcpy(sb, "Sponge\0"); srb =    strcat(sb, "Bob\0");
	test_str("strcat", "strcat return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) { ft_strcpy(sa, "Sponge\0"); sra = ft_strcat(NULL, "Bob\0"); } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { ft_strcpy(sb, "Sponge\0"); srb =    strcat(NULL, "Bob\0"); } else srb = segstr;
	test_str("strcat (null dest)", "strcat return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_strcpy(sa, "Sponge\0"); sra = ft_strcat(sa, NULL); } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { ft_strcpy(sb, "Sponge\0"); srb =    strcat(sb, NULL); } else srb = segstr;
	test_str("strcat (null src) ", "strcat return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_strcpy(sa, "Sponge\0"); sra = ft_strcat(sa, NULL); } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { ft_strcpy(sb, "Sponge\0"); srb =    strcat(sb, NULL); } else srb = segstr;
	test_str("strcat (both null)", "strcat return", sra, srb, TRUE);

printf("\n");

//	char	*ft_strncat(char *dest, const char *src, size_t n);
	strcpy(sa, "Sponge\0"); sra = ft_strncat(sa, "Bob", 3);
	strcpy(sb, "Sponge\0"); srb = ft_strncat(sb, "Bob", 3);
	test_str("strncat", "strncat return", sra, srb, FALSE);

	strcpy(sa, "Sponge\0"); sra = ft_strncat(sa, "Bobensen", 0);
	strcpy(sb, "Sponge\0"); srb = ft_strncat(sb, "Bobensen", 0);
	test_str("strncat (n = 0)", "strncat return", sra, srb, FALSE);

	strcpy(sa, "Sponge\0"); sra = ft_strncat(sa, "Bob", 7);
	strcpy(sb, "Sponge\0"); srb = ft_strncat(sb, "Bob", 7);
	test_str("strncat (n > str)", "strncat return", sra, srb, FALSE);

	strcpy(sa, "Sponge\0"); sra = ft_strncat(sa, "Bobensen", 3);
	strcpy(sb, "Sponge\0"); srb = ft_strncat(sb, "Bobensen", 3);
	test_str("strncat (n < str)", "strncat return", sra, srb, FALSE);

	segfault = setjmp(restore); if (!segfault) { strcpy(sa, "Sponge\0"); sra = ft_strncat(NULL, "Bobensen", 3); } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { strcpy(sb, "Sponge\0"); srb = ft_strncat(NULL, "Bobensen", 3); } else srb = segstr;
	test_str("strncat (null dest)", "strncat return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) { strcpy(sa, "Sponge\0"); sra = ft_strncat(sa, NULL, 3); } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { strcpy(sb, "Sponge\0"); srb = ft_strncat(sb, NULL, 3); } else srb = segstr;
	test_str("strncat (null src) ", "strncat return", sra, srb, TRUE);

	segfault = setjmp(restore); if (!segfault) { sra = ft_strncat(NULL, NULL, 3); } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { srb = ft_strncat(NULL, NULL, 3); } else srb = segstr;
	test_str("strncat (both null)", "strncat return", sra, srb, TRUE);

printf("\n");

//	size_t	ft_strlcat(char *dest, const char *src, size_t size);
	sa = (char *)ft_memalloc(64);
	sb = (char *)ft_memalloc(64);

    strcpy(sa, "Omae wa mou"); la = ft_strlcat(sa, " shindeiru", 5);
    strcpy(sb, "Omae wa mou"); lb =    strlcat(sb, " shindeiru", 5);
	test_int("strlcat", "strlcat return", (t_u32)la, (t_u32)lb, FALSE);
	test_str(NULL,      "strlcat arg",           sa,        sb, FALSE);

    strcpy(sa, "Omae wa mou"); la = ft_strlcat(sa, " shindeiru", 15);
    strcpy(sb, "Omae wa mou"); lb =    strlcat(sb, " shindeiru", 15);
	test_int("strlcat (n < str)", "strlcat return", (t_u32)la, (t_u32)lb, FALSE);
	test_str(NULL,                "strlcat arg",           sa,        sb, FALSE);

    strcpy(sa, "Omae wa mou"); la = ft_strlcat(sa, " shindeiru", 50);
    strcpy(sb, "Omae wa mou"); lb =    strlcat(sb, " shindeiru", 50);
	test_int("strlcat (n > str)", "strlcat return", (t_u32)la, (t_u32)lb, FALSE);
	test_str(NULL,                "strlcat arg",           sa,        sb, FALSE);

    strcpy(sa, "Omae wa mou"); la = ft_strlcat(sa, " shindeiru", 0);
    strcpy(sb, "Omae wa mou"); lb =    strlcat(sb, " shindeiru", 0);
	test_int("strlcat (n = 0)", "strlcat return", (t_u32)la, (t_u32)lb, FALSE);
	test_str(NULL,              "strlcat arg",           sa,        sb, FALSE);

	segfault = setjmp(restore); if (!segfault) { strcpy(sa, "Omae wa mou"); la = ft_strlcat(NULL, " shin", 5); sra = sa; } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { strcpy(sb, "Omae wa mou"); lb =    strlcat(NULL, " shin", 5); srb = sb; } else srb = segstr;
	test_int("strlcat (null dest)", "strlcat return", (t_u32)la, (t_u32)lb, TRUE);
	test_str(NULL,                  "strlcat arg",           sa,        sb, TRUE);

	segfault = setjmp(restore); if (!segfault) { strcpy(sa, "Omae wa mou"); la = ft_strlcat(sa, NULL, 5); sra = sa; } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { strcpy(sb, "Omae wa mou"); lb =    strlcat(sb, NULL, 5); srb = sb; } else srb = segstr;
	test_int("strlcat (null src) ", "strlcat return", (t_u32)la, (t_u32)lb, TRUE);
	test_str(NULL,                  "strlcat arg",           sa,        sb, TRUE);

	segfault = setjmp(restore); if (!segfault) { strcpy(sa, "Omae wa mou"); la = ft_strlcat(NULL, NULL, 15); sra = sa; } else sra = segstr;
	segfault = setjmp(restore); if (!segfault) { strcpy(sb, "Omae wa mou"); lb =    strlcat(NULL, NULL, 15); srb = sb; } else srb = segstr;
	test_int("strlcat (both null)", "strlcat return", (t_u32)la, (t_u32)lb, TRUE);
	test_str(NULL,                  "strlcat arg",           sa,        sb, TRUE);

printf("\n");

//	int		ft_isalpha(int c);
//	int		ft_isdigit(int c);
//	int		ft_isalnum(int c);
//	int		ft_isascii(int c);
//	int		ft_isprint(int c);
//	int		ft_toupper(int c);
//	int		ft_tolower(int c);
	printf(C_BLUE"\nChar functions - all these tests should return '1'.\n");
	printf("(Except after 255, those numbers are undefined behavior).\n");
	printf("(Errors will be displayed if there are any).\n"RESET);
	for (int i = 0; i < 258; i++)
	{
		if (!bool_equals(ft_isalpha(i), isalpha(i))) printf(C_RED"ERROR - ft_isalpha(%d) = %d\n"RESET, i, ft_isalpha(i));
		if (!bool_equals(ft_isdigit(i), isdigit(i))) printf(C_RED"ERROR - ft_isdigit(%d) = %d\n"RESET, i, ft_isdigit(i));
		if (!bool_equals(ft_isalnum(i), isalnum(i))) printf(C_RED"ERROR - ft_isalnum(%d) = %d\n"RESET, i, ft_isalnum(i));
		if (!bool_equals(ft_isascii(i), isascii(i))) printf(C_RED"ERROR - ft_isascii(%d) = %d\n"RESET, i, ft_isascii(i));
		if (!bool_equals(ft_isprint(i), isprint(i))) printf(C_RED"ERROR - ft_isprint(%d) = %d\n"RESET, i, ft_isprint(i));
		if (!bool_equals(ft_toupper(i), toupper(i))) printf(C_RED"ERROR - ft_toupper(%d) = %d\n"RESET, i, ft_toupper(i));
		if (!bool_equals(ft_tolower(i), tolower(i))) printf(C_RED"ERROR - ft_tolower(%d) = %d\n"RESET, i, ft_tolower(i));
	}

printf("\n");

printf(C_BLUE"The following tests are functions not present in the standard C library.\n");
printf("You may decide to protect them against segfaults or not, just stay consistent."RESET);

printf("\n");

//	void	ft_strclr(char *str);
/*
	printf("strclr -> "C_GREEN"OK ?"RESET);
	na = ft_strlen(sa);
	ft_strclr(sa);
	for (unsigned int i = 0; i < na; i++)
	{
		if (sa[i]) printf(C_RED"\nERROR - Every char should be '\\0' after calling 'ft_strclr'."RESET);
	}
	sa = (char *)malloc(MALLOC_LEN);
	sb = (char *)malloc(MALLOC_LEN);
	strcpy(sa, s1);
*/
printf("\n");

//	char	*ft_strrev(const char *str);
	sa = ft_strrev(s1);
	sb = ".uriednihs uom aw eamO";
	test_str("strrev (even len)", "_strrev", sa, sb, FALSE);

	sa = ft_strrev(s2);
	sb = "???inaN";
	test_str("strrev (odd len) ", "_strrev", sa, sb, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strrev(NULL); else sra = segstr;
//	segfault = setjmp(restore); if (!segfault) srb =    strrev(NULL); else srb = segstr;
	test_str("strrev (null ptr)", "_strrev", sra, segstr, TRUE);

printf("\n");

//	int		ft_strequ(const char *str1, const char *str2);
	na = ft_strequ(s1, s2);
	nb =   (strcmp(s1, s2) == 0);
	test_int("strequ", "_strequ", na, nb, FALSE);

	na = ft_strequ(sa, s1);
	nb =   (strcmp(sa, s1) == 0);
	test_int("strequ", "_strequ", na, nb, FALSE);

	na = ft_strequ(sa, "");
	nb =   (strcmp(sa, "") == 0);
	test_int("strequ (empty str)", "_strequ", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strequ(NULL, s2); else na = 0xFFFFFFFF;
	test_str("strequ (null str1)", "_strequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strequ(s1, NULL); else na = 0xFFFFFFFF;
	test_str("strequ (null str2)", "_strequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strequ(NULL, NULL); else na = 0xFFFFFFFF;
	test_str("strequ (both null)", "_strequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

printf("\n");

//	int		ft_strnequ(const char *str1, const char *str2, size_t n)
	na = ft_strnequ(s1, s2, 5);
	nb =   (strncmp(s1, s2, 5) == 0);
	test_int("strnequ", "_strnequ", na, nb, FALSE);

	na = ft_strnequ(sa, s1, 5);
	nb =   (strncmp(sa, s1, 5) == 0);
	test_int("strnequ", "_strnequ", na, nb, FALSE);

	na = ft_strnequ(sa, s1, 50);
	nb =   (strncmp(sa, s1, 50) == 0);
	test_int("strnequ (n > len)", "_strnequ", na, nb, FALSE);

	segfault = setjmp(restore); if (!segfault) na = ft_strnequ(NULL, s1, 5); else na = 0xFFFFFFFF;
	test_str("strnequ (null str1)", "_strnequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strnequ(s1, NULL, 5); else na = 0xFFFFFFFF;
	test_str("strnequ (null str2)", "_strnequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) na = ft_strnequ(NULL, NULL, 5); else na = 0xFFFFFFFF;
	test_str("strnequ (both null)", "_strnequ", (na == 0xFFFFFFFF) ? segstr : ft_itoa(na), segstr, TRUE);

printf("\n");

//	char	*ft_strsub(const char *str, size_t start, size_t length);
	sra = ft_strsub(s1, 5, 5);
	srb = "wa mo";
	test_str("strsub", "_strsub", sra, srb, FALSE);
//	free(sra);

	sra = ft_strsub(s1, 0, 0);
	test_str("strsub (len = 0)", "_strsub", sra, "", FALSE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strsub(s1, 5, 100); else sra = segstr;
	test_str("strsub (len > str)", "_strsub", sra, NULL, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strsub(s1, 100, 5); else sra = segstr;
	test_str("strsub (offset > str)", "_strsub", sra, NULL, FALSE);

	segfault = setjmp(restore); if (!segfault) sra = ft_strsub(NULL, 5, 5); else sra = segstr;
	test_str("strsub (null ptr)", "_strsub", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

printf("\n");

//	char	*ft_strjoin(const char *str1, const char *str2);
	sra = ft_strjoin(s1, s2);
	srb = "Omae wa mou shindeiru.Nani???";
	test_str("strjoin", "_strjoin", sra, srb, FALSE);
//	free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strjoin(NULL, s2); else sra = segstr;
	test_str("strjoin (null str1)", "_strjoin", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strjoin(s1, NULL); else sra = segstr;
	test_str("strjoin (null str2)", "_strjoin", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strjoin(s1, NULL); else sra = segstr;
	test_str("strjoin (both null)", "_strjoin", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

printf("\n");

//	char	*ft_strtrim(const char *str);
	sra = ft_strtrim("\t\n    FOR THE\tHORDE ! 	 \t \n ");
	srb = "FOR THE\tHORDE !";
	test_str("strtrim", "_strtrim", sra, srb, FALSE);
//	free(sra);

	sra = ft_strtrim("   swag");
	srb = "swag";
	test_str("strtrim", "_strtrim", sra, srb, FALSE);
//	free(sra);

	sra = ft_strtrim("do u even trim bruh\n\n\n\n\t");
	srb = "do u even trim bruh";
	test_str("strtrim", "_strtrim", sra, srb, FALSE);
//	free(sra);

	sra = ft_strtrim("\n   \n\t ");
	test_str("strtrim (only whitespace)", "_strtrim", sra, "", FALSE);
//	free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strtrim(""); else sra = segstr;
	test_str("strtrim (empty string)", "_strtrim", sra, "", FALSE);
//	if (sra && sra != segstr) free(sra);

	segfault = setjmp(restore); if (!segfault) sra = ft_strtrim(NULL); else sra = segstr;
	test_str("strtrim (null ptr)", "_strtrim", sra, segstr, TRUE);
//	if (sra && sra != segstr) free(sra);

printf("\n");

//	char	**ft_strsplit(const char *str, char c);
/*
	printf("\nstrsplit\n");
	strls = ft_strsplit(s1, ' ');
	printf("ft_strsplit: [");
	for (int i = 0; strls[i]; i++)
		printf("%s%s", strls[i], strls[i + 1] ? ", " : "]\n");
	printf("   Expected: [Omae, wa, mou, shindeiru.]");
*/
	char const *split_1[] = { "Omae", "wa", "mou", "shindeiru." };
	test_strsplit("strsplit", FALSE, split_1, s1, ' ');

	char const *split_2[] = { "Un ", "nge m", "nge de l", " f", "nge." };
	test_strsplit("strsplit", FALSE, split_2, s3, 'a');

	segfault = setjmp(restore); if (!segfault) strls = ft_strsplit(NULL, ' '); else strls = (char **)segstr;
	test_str("strsplit (null ptr)", "_strsplit", (char *)strls, segstr, TRUE);

printf("\n");

//	void	ft_striter(char *str, void (*f)(char *))
	strcpy(sa, "omAe wA mOu ShINDeIRu.");
	ft_striter(sa, ptrtolower);
	test_str("striter", "_striter", sa, "omae wa mou shindeiru.", FALSE);

	strcpy(sa, "omAe wA mOu ShINDeIRu.");
	segfault = setjmp(restore); if (!segfault) ft_striter(sra, NULL); else sra = segstr;
	test_str("striter (null f)   ", "_striter", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striter(NULL, ptrtolower); sra = NULL; } else sra = segstr;
	test_str("striter (null str) ", "_striter", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striter(NULL, NULL); sra = NULL; } else sra = segstr;
	test_str("striter (both null)", "_striter", sra, segstr, TRUE);

printf("\n");

//	void	ft_striteri(char *str, void (*f)(unsigned int, char *));
	strcpy(sa, "OMAE WA MOU SHINDEIRU.");
	ft_striteri(sa, ptrtolower_1on2);
	test_str("striteri", "_striteri", sa, "oMaE Wa mOu sHiNdEiRu.", FALSE);

	strcpy(sa, "OMAE WA MOU SHINDEIRU.");
	segfault = setjmp(restore); if (!segfault) ft_striteri(sra, NULL); else sra = segstr;
	test_str("striteri (null f)   ", "_striteri", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striteri(NULL, ptrtolower_1on2); sra = NULL; } else sra = segstr;
	test_str("striteri (null str) ", "_striteri", sra, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) { ft_striteri(NULL, NULL); sra = NULL; } else sra = segstr;
	test_str("striteri (both null)", "_striteri", sra, segstr, TRUE);

printf("\n");

//	char	*ft_strmap(const char *str, char (*f)(char));
	sa = ft_strmap("omAe wA mOu ShINDeIRu.", toupper_chr);
	test_str("strmap", "_strmap", sa, "OMAE WA MOU SHINDEIRU.", FALSE);

	segfault = setjmp(restore); if (!segfault) sa = ft_strmap("omAe wA mOu ShINDeIRu.", NULL); else sa = segstr;
	test_str("strmap (null f)   ", "_strmap", sa, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) sa = ft_strmap(NULL, toupper_chr); else sa = segstr;
	test_str("strmap (null str) ", "_strmap", sa, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) sa = ft_strmap(NULL, NULL); else sa = segstr;
	test_str("strmap (both null)", "_strmap", sa, segstr, TRUE);

printf("\n");

//	char	*ft_strmapi(const char *str, char (*f)(unsigned int, char));
	sa = ft_strmapi("omae wa mou shindeiru.", toupper_1on2);
	test_str("strmapi", "_strmapi", sa, "oMaE Wa mOu sHiNdEiRu.", FALSE);

	segfault = setjmp(restore); if (!segfault) sa = ft_strmapi("omAe wA mOu ShINDeIRu.", NULL); else sa = segstr;
	test_str("strmapi (null f)   ", "_strmapi", sa, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) sa = ft_strmapi(NULL, toupper_1on2); else sa = segstr;
	test_str("strmapi (null str) ", "_strmapi", sa, segstr, TRUE);

	segfault = setjmp(restore); if (!segfault) sa = ft_strmapi(NULL, NULL); else sa = segstr;
	test_str("strmapi (both null)", "_strmapi", sa, segstr, TRUE);

printf("\n");

/*============== List functions ===============*/
/*
	t_list **a_lst;
	t_list *lst_0;
	t_list *lst_1;
	t_list *lst_2;
	t_list *lst_3;
	t_list *lst_4;
	char const *expect[]       = { "Omae", " wa ", "mou ", "shindeiru.", NULL };
	char const *expect_upper[] = { "OMAE", " WA ", "MOU ", "SHINDEIRU.", NULL };
	char const *expect_lower[] = { "omae", " wa ", "mou ", "shindeiru.", NULL };

//	t_list	*ft_lstnew(void const *content, size_t content_size);
	lst_0 = ft_lstnew("Omae", 5);
	lst_1 = ft_lstnew(" wa ", 5);
	lst_2 = ft_lstnew("mou ", 5);
	lst_3 = ft_lstnew("shindeiru.", 11);
	test_int("lstnew", "_lstnew->content_size", lst_0->content_size,    5, FALSE);
	test_str(NULL,     "_lstnew->content",      lst_0->content, expect[0], FALSE);
	test_int(NULL,     "_lstnew->content_size", lst_1->content_size,    5, FALSE);
	test_str(NULL,     "_lstnew->content",      lst_1->content, expect[1], FALSE);
	test_int(NULL,     "_lstnew->content_size", lst_2->content_size,    5, FALSE);
	test_str(NULL,     "_lstnew->content",      lst_2->content, expect[2], FALSE);
	test_int(NULL,     "_lstnew->content_size", lst_3->content_size,   11, FALSE);
	test_str(NULL,     "_lstnew->content",      lst_3->content, expect[3], FALSE);

	segfault = setjmp(restore); if (!segfault) lst_4 = ft_lstnew(NULL, 5); else lst_4->content = segstr;
	test_str("lstnew (null ptr)", "_lstnew->content", lst_4->content, segstr, TRUE);

printf("\n");

//	void	ft_lstadd(t_list **alst, t_list *new_elem);
	a_lst = &lst_3;
	ft_lstadd(a_lst, lst_2);
	ft_lstadd(a_lst, lst_1);
	ft_lstadd(a_lst, lst_0);
	test_lst("lstadd", "lstadd", lst_0, expect, FALSE);

printf("\n");

//	t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = ft_lstmap(*a_lst, ft_lstmap_toupper); else *a_lst = NULL;
	test_lst("lstmap", "lstmap", *a_lst, expect_upper, FALSE);

printf("\n");

//	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
	//ft_lstiter(*a_lst, ft_lstiter_tolower);
	//test_lst("lstiter", "lstiter", a_lst, expect_lower, FALSE);

printf("\n");

	if (LIBFT_EXTRA_TD)
	{

	//ft_strlcpy(char *dest, char *src, size_t size);
		printf(C_BLUE"\nstrlcpy\n"RESET);
		sa[0] = '\0';
		printf("ft_strlcpy return:%lu\n   strlcpy return: %d\n", (t_u64)ft_strlcpy(sa, "Omae wa mou shindeiru", 15), 21);
		printf("ft_strlcpy arg:%s\n   strlcpy arg:%s\n", sa, "Omae wa mou sh"); //faut pas oublier \0


	//ft_digits(int n); ft_digits_base(int n, int base);
		printf("\nft_digits: %d | Expected: %d\n", ft_digits(-2147483648), 10);
		printf("\nft_digits: %d | Expected: %d\n", ft_digits_base(-2147483648, 2), 32);

	//ft_memhex(const void *s, size_t n);
		free(sa);
		n = -2147483648;
		sa = ft_memhex(&n, 4);
		printf("\nft_memhex : {%s}\nExpected : 00000080 (little endian)\n", sa);

	//ft_strhex(const char *s)
		free(sa);
		sa = ft_strhex("abcdefgh");
		printf("\nft_strhex : {%s}\nExpected : 6162636465666768\n", sa);

	//ft_split(char *str, char *sep_chars);		void	ft_putstrls(const char **strls); void	ft_putstrls_fd(const char **strls, int fd);
		ft_del_strls(strls);
		strls = ft_split("\nOmae\t  \nwa   mou@@shindeiru.  !!@@", " \n\t@!");
		ft_putstr("\nft_split:\n");
		ft_putstrls(strls);
		ft_putstr("\nExpected:\nOmae\nwa\nmou\nshindeiru.\n");

	//ft_strls_join(char ** strls, char* sep)
		free(sa);
		sa = ft_strlsjoin(strls, "---KWEEEN---");
		ft_putstr("\nft_strlsjoin: ");
		ft_putstr(sa);
		ft_putstr("\nExpected: Omae---KWEEEN---wa---KWEEEN---mou---KWEEEN---shindeiru.\n");

	//ft_strdivide(char *str, size_t n);
		ft_del_strls(strls);
		strls = ft_strdivide(sa, 10);
		ft_putstr("\nft_strdivide:\n");
		ft_putstrls(strls);
		ft_putstr("\nExpected:\nOmae---KWE\nEEN---wa--\n-KWEEEN---\nmou---KWEE\nEN---shind\neiru.\n");

	//	void	ft_lstappend(t_list **alst, t_list *new_elem);
		t_list	**mixed_list;
		mixed_list = a_slst;
		ft_putstr("\nft_lstappend (mind the little endianness and the fact that lst was listiter(abs)) :\n");
		ft_lstappend(mixed_list, *a_ilst);
		ft_lstiter(*mixed_list, ft_puthex_llstelem);
		ft_putstr("\nExpected:\n4F 6D 61 65 00\n20 77 61 20 00\n6D 6F 75 20 00\n73 68 69 6E 64 65 69 72 75 2E 00\n00 00 00 00\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");

	//	int		ft_lstsize(t_list *lst);
		ft_putstr("\nft_lstsize : ");
		ft_putnbr(ft_lstsize(*mixed_list));
		ft_putstr("\nExpected : 9\n");

	//	void	*ft_lstfold(t_list *lst, void *acc, void *(*f)(void *, void *));
		ft_putstr("\nft_lstfold : ");
		n = 0;
		ft_lstfold(*a_ilst, &n, ft_add);
		ft_putnbr(n);
		ft_putstr("\nExpected : 1488\n");

	//	void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
		ft_putstr("\nft_lstdelone :\n");
		t_list *tmp = (*a_ilst)->next;
		ft_lstdelone(a_ilst, ft_delete);
		//alternative fix without lstget => (*mixed_list)->next->next->next->next = 0;
		ft_lstget(*mixed_list, 3)->next = 0;
		ft_lstappend(mixed_list, tmp);
		ft_lstiter(*mixed_list, ft_puthex_llstelem);
		ft_putstr("\nExpected:\n4F 6D 61 65 00\n20 77 61 20 00\n6D 6F 75 20 00\n73 68 69 6E 64 65 69 72 75 2E 00\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");

		if (*a_ilst) // || *a_ilst || (*a_ilst)->content)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
	
	//	void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
		ft_putstr("\nft_lstdel :\n");	
		ft_lstdel(mixed_list, ft_delete);

		if (*mixed_list) // || *mixed_list || (*mixed_list)->content)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
	}
	else
	{
	//	void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
		ft_putstr("\nft_lstdelone :\n");
		t_list *tmp = (*a_ilst)->next;
		ft_lstdelone(a_ilst, ft_delete);
		ft_lstiter(tmp, ft_puthex_llstelem);
		ft_putstr("\nExpected:\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");
		if (*a_ilst) // || *a_ilst || (*a_ilst)->content)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
	
	//	void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
		ft_putstr("\nft_lstdel :\n");	
		ft_lstdel(&tmp, ft_delete);
		ft_lstdel(a_slst, ft_delete);
		if (*a_slst || tmp) // || *a_slst || (*a_ilst)->content || tmp->content)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
	}
*/
	return (0);
}
