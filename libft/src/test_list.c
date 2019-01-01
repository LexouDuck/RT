
#include "test.h"



/*
**	t_list	*ft_lstnew(void const *item, size_t item_size);
*/
void	print_test_lstnew(char const* test_name, int can_segfault,
		char const* expecting,
		void const* item,
		size_t item_size)
{
	t_timer t = {0};
	size_t expect_size = expecting ? strlen(expecting) + 1 : 0;
	t_list* result;
	segfault = setjmp(restore); if (!segfault) result = ft_lstnew(item, item_size); else can_segfault |= (1 << 1);
	print_test_size(test_name, "_lstnew->item_size", result->item_size, expect_size, can_segfault);
	print_test_str(NULL,       "_lstnew->item",      result->item,      expecting,   can_segfault);
	print_timer_result(&t, FALSE);
	if (result) free(result);
}
void	test_lstnew(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME         |CAN SEGV| EXPECTING   | TEST ARGS */
	print_test_lstnew("lstnew            ",	FALSE,  "Omae",       "Omae",        5);
	print_test_lstnew("lstnew            ",	FALSE,  " wa ",       " wa ",        5);
	print_test_lstnew("lstnew            ",	FALSE,  "mou ",       "mou ",        5);
	print_test_lstnew("lstnew            ",	FALSE,  "shindeiru.", "shindeiru.", 11);
	print_test_lstnew("lstnew (empty str)",	FALSE,  "",           "",            1);
	print_test_lstnew("lstnew (null  ptr)",	TRUE,   NULL,         NULL,          5);
}



/*
**	char	*ft_lst_(char const* str);
*/
void	print_test_lst_(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_lst_(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



int		test_list(void)
{
	t_list **a_lst;
	t_list *lst_0;
	t_list *lst_1;
	t_list *lst_2;
	t_list *lst_3;
	t_list *lst_4;
	char const *expect[]       = { "Omae", " wa ", "mou ", "shindeiru.", NULL };
	char const *expect_upper[] = { "OMAE", " WA ", "MOU ", "SHINDEIRU.", NULL };
	char const *expect_lower[] = { "omae", " wa ", "mou ", "shindeiru.", NULL };

printf("\n");

	printf("       .--------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_list   }===---\n");
	printf("       '--------------------------'       \n");

	print_nonstd();

	test_lstnew();

printf("\n");
/*

printf("\n");

//	void	ft_lstadd(t_list **alst, t_list *new_elem);
	a_lst = &lst_3;
	ft_lstadd(a_lst, lst_2);
	ft_lstadd(a_lst, lst_1);
	ft_lstadd(a_lst, lst_0);
	print_test_lst("lstadd", "lstadd", lst_0, expect, FALSE);

printf("\n");

//	t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = ft_lstmap(*a_lst, ft_lstmap_toupper); else *a_lst = NULL;
	print_test_lst("lstmap", "lstmap", *a_lst, expect_upper, FALSE);

printf("\n");

//	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
	ft_lstiter(*a_lst, ft_lstiter_tolower);
	print_test_lst("lstiter", "lstiter", a_lst, expect_lower, FALSE);

printf("\n");

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

		if (*a_ilst) // || *a_ilst || (*a_ilst)->item)
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

		if (*mixed_list) // || *mixed_list || (*mixed_list)->item)
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
		if (*a_ilst) // || *a_ilst || (*a_ilst)->item)
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
		if (*a_slst || tmp) // || *a_slst || (*a_ilst)->item || tmp->item)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
	}
*/
	return (OK);
}
