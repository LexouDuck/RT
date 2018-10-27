/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:51:47 by tduquesn          #+#    #+#             */
/*   Updated: 2018/04/18 21:26:57 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_fd(int fd, const char *format, ...)
{
	va_list		args;
	int			status;

	va_start(args, format);
	status = ft_vprintf_fd(fd, format, args);
	va_end(args);
	return (status);
}

int				ft_printf(const char *format, ...)
{
	va_list		args;
	int			status;

	va_start(args, format);
	status = ft_vprintf_fd(1, format, args);
	va_end(args);
	return (status);
}

int				ft_vprintf_fd(int fd, const char *format, va_list args)
{
	char	*str;
	int		status;

	status = ft_vasprintf(&str, format, args);
	if (status >= 0)
	{
		if (write(fd, str, status) == -1)
			return (-1);
		ft_strdel(&str);
	}
	return (status);
}

int				ft_asprintf(char **res, const char *format, ...)
{
	va_list		args;
	int			status;

	va_start(args, format);
	status = ft_vasprintf(res, format, args);
	va_end(args);
	return (status);
}

int				ft_vasprintf(char **res, const char *format, va_list args)
{
	char	**fmt_strls;
	t_list	*res_lststr;
	int		i;
	t_str	tmp_res;

	if (!format || !(fmt_strls = format_to_strls(format)))
		return (-1);
	res_lststr = NULL;
	i = -1;
	while (fmt_strls[++i])
		if (convert_str(fmt_strls[i], &res_lststr, args) == ERROR)
		{
			*res = NULL;
			ft_strlsdel(&fmt_strls);
			ft_lstdel(&res_lststr, del_t_str);
			return (-1);
		}
	tmp_res = to_single_t_str(res_lststr);
	*res = tmp_res.data;
	ft_strlsdel(&fmt_strls);
	ft_lstdel(&res_lststr, del_t_str);
	return (tmp_res.len);
}
