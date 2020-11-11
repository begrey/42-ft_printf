/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:34:08 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/11 11:13:54 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_w_and_free(char *substr)
{
	int		result;

	result = ft_atoi(substr);
	free(substr);
	return (result);
}

void		prec_wildcard(char *str, char *ptr, t_flag *f, va_list ap)
{
	int		wild;
	int		flag;
	char	*w;

	flag = 0;
	w = ft_strchr(str, '*');
	if (w < ptr)
	{
		wild = va_arg(ap, int);
		f->width = wild;
		flag = 1;
		f->prec = get_w_and_free(ft_substr(ptr + 1, 0, ft_strlen(ptr)));
	}
	if ((ft_strchr(ptr, '*')))
	{
		f->prec = va_arg(ap, int);
		if (flag != 1)
		{
			f->width = get_w_and_free(
			ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr)));
		}
	}
	else
		f->prec = get_w_and_free(ft_substr(ptr + 1, 0, ft_strlen(ptr)));
}

void		check_prec(t_flag *f, char *ptr, char *str, va_list ap)
{
	char	*w;
	int		flag;

	flag = 0;
	f->prec_zero = TRUE;
	if ((w = ft_strchr(str, '*')))
		prec_wildcard(str, ptr, f, ap);
	else
	{
		f->prec = ft_atoi(ft_substr(ptr + 1, 0, ft_strlen(ptr)));
		f->width = ft_atoi(ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr)));
	}
	if (f->prec >= 0)
		f->zero = FALSE;
}

void		check_width(va_list ap, char *str, t_flag *f)
{
	int		wild;

	wild = 0;
	f->prec_zero = FALSE;
	if ((ft_strchr(str, '*')))
	{
		wild = va_arg(ap, int);
		f->width = wild;
	}
	else
		f->width = ft_atoi(ft_substr(str, 0, ft_strlen(str)));
	f->prec = 0;
}

void		get_flag(char *str, va_list ap, t_flag *f)
{
	char	*ptr;

	f->left = str[0] == '-' ? TRUE : FALSE;
	f->zero = str[0] == '0' ? TRUE : FALSE;
	if (f->zero == TRUE || f->left == TRUE)
		str = ft_substr(str, 1, ft_strlen(str));
	if ((ptr = ft_strchr(str, '.')))
		check_prec(f, ptr, str, ap);
	else
		check_width(ap, str, f);
	if (f->width < 0)
	{
		f->left = TRUE;
		f->zero = FALSE;
		f->width *= -1;
	}
}
