/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:04:54 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 19:22:56 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_s_left(char *s, t_flag *f)
{
	int		result;

	if (f->zero == TRUE)
		result = print_flag(f->width - (int)ft_strlen(s), 0, "0");
	else
		result = print_flag(f->width - (int)ft_strlen(s), 0, " ");
	return (result);
}

int			get_s(char *str, va_list ap, t_flag *f)
{
	char	*s;
	int		len;

	len = 0;
	get_flag(str, ap, f);
	s = va_arg(ap, char *);
	if (!s)
		s = "(null)";
	if (s[0] == '\0')
		s = "";
	if ((int)ft_strlen(s) < f->prec || (f->prec == 0 && f->prec_zero == FALSE))
		f->prec = -1;
	if (f->prec == 0)
		s = "";
	if (f->prec > 0 && f->prec < (int)ft_strlen(s))
		s = ft_substr(s, 0, f->prec);
	if (f->left == FALSE)
		len = check_s_left(s, f);
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	if (f->left == TRUE)
		len = print_flag(f->width - (int)ft_strlen(s), len, " ");
	if (f->prec > 0 && f->prec < (int)ft_strlen(s))
		free(s);
	return (len);
}
