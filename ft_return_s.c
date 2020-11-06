/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:04:54 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/06 19:04:48 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_s_left(char *s, t_flag *f)
{
	int result;
	
	if (f->zero == TRUE)
		result = print_flag(f->width - (int)ft_strlen(s), 0, "0");
	else
		result = print_flag(f->width - (int)ft_strlen(s), 0, " ");
	return (result);
}

int	get_s(char *str, va_list ap, t_flag *f)
{
	char	*s;
	int		len;
	int		i;

	len = 0;
	i = 0;
	get_flag(str, ap, f);
	s = va_arg(ap, char *);
	if (!s)
		s = "(null)";
	if ((int)ft_strlen(s) < f->prec || (f->prec == 0 && f->prec_zero == FALSE)) //정밀도가 인자 길이보다 같거나 크면 의미없으니 음수로 설정, 애초에 음수 정밀도는 무시당함
		f->prec = -1;
	if (f->prec > 0 && f->prec < (int)ft_strlen(s)) //정밀도가 인자 길이보다 작으면 정밀도 만큼만 문자열 자르기
			s = ft_substr(s, 0, f->prec);
	if (f->prec == 0) //0이면 빈문자열
			s = "";
	if (f->left == FALSE) //오른쪽 정렬일 때
		len = check_s_left(s, f);
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	if (f->left == TRUE) //왼쪽 정렬일 때
		len = print_flag(f->width - (int)ft_strlen(s), len, " ");
	return (len);
}