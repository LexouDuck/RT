
#include "test.h"

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

printf("\n");
/*
//	t_list	*ft_lstnew(void const *content, size_t content_size);
	lst_0 = ft_lstnew("Omae", 5);
	lst_1 = ft_lstnew(" wa ", 5);
	lst_2 = ft_lstnew("mou ", 5);
	lst_3 = ft_lstnew("shindeiru.", 11);
	print_test_int("lstnew", "_lstnew->content_size", lst_0->content_size,    5, FALSE);
	print_test_str(NULL,     "_lstnew->content",      lst_0->content, expect[0], FALSE);
	print_test_int(NULL,     "_lstnew->content_size", lst_1->content_size,    5, FALSE);
	print_test_str(NULL,     "_lstnew->content",      lst_1->content, expect[1], FALSE);
	print_test_int(NULL,     "_lstnew->content_size", lst_2->content_size,    5, FALSE);
	print_test_str(NULL,     "_lstnew->content",      lst_2->content, expect[2], FALSE);
	print_test_int(NULL,     "_lstnew->content_size", lst_3->content_size,   11, FALSE);
	print_test_str(NULL,     "_lstnew->content",      lst_3->content, expect[3], FALSE);

	segfault = setjmp(restore); if (!segfault) lst_4 = ft_lstnew(NULL, 5); else lst_4->content = segstr;
	print_test_str("lstnew (null ptr)", "_lstnew->content", lst_4->content, segstr, TRUE);

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
	return (OK);
}
