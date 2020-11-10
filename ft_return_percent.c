/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:13:04 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 12:33:50 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_percent(char *str, va_list ap, t_flag *f)
{
	int		len;

	len = 1;
	get_flag(str, ap, f);
	if (f->zero == TRUE && f->prec <= 0) //정밀도가 없거나 음수여야 0플래그가 유효함
		return (zero_flag(f, 0, "%"));
	f->width -= 1;
	if (f->width < 1)
		f->width = 0;
	if (f->left == FALSE) //오른쪽 정렬일 때
		len = print_flag(f->width, len, " ");
	len = print_flag(f->prec - ft_strlen("%") <= 0 ? 0 : f->prec - ft_strlen("%"), len, "0");
	write(1, "%%", 1);
	if (f->left == TRUE) //왼쪽 정렬일 때
		len = print_flag(f->width, len, " ");
	return (len);
}