/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:13:04 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/11 11:13:06 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_percent(char *str, va_list ap, t_flag *f)
{
	int		len;

	len = 1;
	get_flag(str, ap, f);
	if (str[0] == '0' && f->left == FALSE)
		f->zero = TRUE;
	if (f->zero == TRUE)
		return (zero_flag(f, 0, "%"));
	f->width -= 1;
	if (f->width < 1)
		f->width = 0;
	if (f->left == FALSE)
		len = print_flag(f->width, len, " ");
	write(1, "%%", 1);
	if (f->left == TRUE)
		len = print_flag(f->width, len, " ");
	return (len);
}
