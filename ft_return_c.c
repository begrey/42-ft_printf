/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:57:38 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 17:38:49 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_c(char *str, va_list ap, t_flag *f)
{
	char	c;
	int		len;

	len = 1;
	get_flag(str, ap, f);
	c = va_arg(ap, int);
	f->width -= 1;
	if (f->width < 1)
		f->width = 0;
	if (f->left == FALSE)
		len = print_flag(f->width, len, " ");
	write(1, &c, 1);
	if (f->left == TRUE)
		len = print_flag(f->width, len, " ");
	return (len);
}
