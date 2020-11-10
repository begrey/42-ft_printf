/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:23:50 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 17:01:33 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		reset_flag(t_flag *f)
{
	f->zero = FALSE;
	f->left = FALSE;
	f->prec_zero = FALSE;
	f->prec = 0;
	f->width = 0;
}

int			find_option(char option, char *s, t_flag *f, va_list ap)
{
	char	*flag;
	int		len;

	len = 0;
	flag = ft_substr(s, 0, ft_strchr(s, option) - s);
	if (option == 'c')
		len += get_c(flag, ap, f);
	else if (option == 's')
		len += get_s(flag, ap, f);
	else if (option == 'p')
		len += get_p(flag, ap, f);
	else if (option == 'd' || option == 'i')
		len += get_d(flag, ap, f);
	else if (option == 'u')
		len += get_u(flag, ap, f);
	else if (option == 'x')
		len += get_x(flag, ap, f, 'a');
	else if (option == 'X')
		len += get_x(flag, ap, f, 'A');
	else if (option == '%')
		len += get_percent(flag, ap, f);
	free(flag);
	return (len);
}

char		*handle_percent(char *str, int *len, t_flag f, va_list ap)
{
	char	*s;
	char	*ptr;

	s = str;
	while (str++ && *str != '\0')
		if (*str == 'c' || *str == 's' || *str == 'p' || *str == 'd' ||
		*str == 'i' || *str == 'u' || *str == 'x' || *str == 'X' || *str == '%')
			break ;
	if (*str == '\0')
	{
		*len = -1;
		return (NULL);
	}
	ptr = ft_strchr(str, *str);
	*len += find_option(*str, s + 1, &f, ap);
	return (ptr);
}

int			ft_printf(const char *str, ...)
{
	va_list	ap;
	int		len;
	t_flag	f;

	len = 0;
	reset_flag(&f);
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str = handle_percent((char *)str, &len, f, ap);
			if (len == -1)
				return (0);
			str++;
		}
		else
		{
			write(1, &(*str++), 1);
			len++;
		}
	}
	va_end(ap);
	return (len);
}
