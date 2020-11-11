/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:30:55 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 19:33:54 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_u(char *str, va_list ap, t_flag *f)
{
	char	*s;
	int		w;
	long	num;
	int		len;

	get_flag(str, ap, f);
	len = 0;
	num = va_arg(ap, unsigned int);
	if (f->prec == 0 && num == 0 && f->prec_zero == TRUE)
		s = ft_strdup("");
	else
		s = ft_itoa(num);
	if (f->zero == TRUE && f->prec <= 0)
		return (zero_flag(f, num, s));
	w = set_prev_and_width(s, f, num);
	if (f->left == FALSE)
		len = print_flag(w, len, " ");
	len = print_flag(f->prec - ft_strlen(s) <= 0
	? 0 : f->prec - ft_strlen(s), len, "0");
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	if (f->left == TRUE)
		len = print_flag(w, len, " ");
	free(s);
	return (len);
}
