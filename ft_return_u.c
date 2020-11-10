/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:30:55 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/09 13:40:11 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int get_u(char *str, va_list ap, t_flag *f)
{
	char	*s;
	int		w;
	long	num;
	int		len;
	
	get_flag(str, ap, f);
	len = 0;
	num = va_arg(ap, int);
	if (num < 0)
		num += 4294967296;
	s = ft_itoa(num);
	if (f->prec == 0 && num == 0 && f->prec_zero == TRUE) //정밀도에 기본값 0이 들어있을 때, value가 0이면 null처리로 0 대신 빈 문자열이 출력되어야 함
		s = "";
	if (f->zero == TRUE && f->prec <= 0) //정밀도가 없거나 음수여야 0플래그가 유효함
		return (zero_flag(f, num, s));
	w = set_prev_and_width(s, f, num);
	if (f->left == FALSE) //오른쪽 정렬일 때
		len = print_flag(w, len, " ");
	len = print_flag(f->prec - ft_strlen(s) <= 0 ? 0 : f->prec - ft_strlen(s), len, "0");
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	if (f->left == TRUE) //왼쪽 정렬일 때
		len = print_flag(w, len, " ");
	return (len);
}