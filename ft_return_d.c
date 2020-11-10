/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:08:32 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 12:32:33 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int print_flag(int w, int len, char *s)
{
	int		i;
	
	i = 0;
	while (i++ < w)
	{
		write(1, s, 1);
		len++;
	}
	return (len);
}

int	zero_flag(t_flag *f, long num, char *s)
{
	int len;
	int i;
	int index;

	i = 0;
	len = 0;
	index = f->width - (int)ft_strlen(s) <= 0 ?
	0 : f->width - (int)ft_strlen(s);
	if (num < 0)
	{
		s++;
		write(1, "-", 1);
		len++;
	}
	while (i++ < index)
	{
		write(1, "0", 1);
		len++;
	}
	write(1, s, ft_strlen(s));
	return (len + (int)ft_strlen(s));
}

int set_prev_and_width(char *s, t_flag *f, long num)
{
	int		minus;
	int		w;
	
	minus = 0;
	w = 0;
	if (s && s[0] == '-')
		minus = -1;
	if (f->prec <= (int)ft_strlen(s) + minus) //인자 길이보다 작으면 정밀도 무시 여기서 음수-가 들어있어서 길이가 +1 되는 경우는 예외처리 필요
		f->prec = 0;
	if (f->width <= (int)ft_strlen(s) + minus || f->width <= f->prec)
		f->width = 0;
	if (f->prec <= 0)
		w = f->width - ft_strlen(s) <= 0 ? 0 : f->width - ft_strlen(s);// 정밀도가 무시당할 때는, -가 포함된 길이로 폭을 구함
	else
	{
		w = f->width - (f->prec) <= 0 ? 0 : f->width - (f->prec); //but 정밀도가 유의미한 경우 폭을 구할 때 인자가 -인 경우는 따로 처리해줘야함
		if (num < 0) w -= 1;
	}
	return w;
}

int get_d(char *str, va_list ap, t_flag *f)
{
	char	*s;
	int		w;
	int		num;
	int		len;
	
	get_flag(str, ap, f);
	len = 0;
	num = va_arg(ap, int);
	s = ft_itoa(num);
	if (f->prec == 0 && num == 0 && f->prec_zero == TRUE) //정밀도에 기본값 0이 들어있을 때, value가 0이면 null처리로 0 대신 빈 문자열이 출력되어야 함
		s = "";
	if (f->zero == TRUE && f->prec <= 0) //정밀도가 없거나 음수여야 0플래그가 유효함
		return (zero_flag(f, num, s));
	w = set_prev_and_width(s, f, num);
	if (f->left == FALSE) //오른쪽 정렬일 때
		len = print_flag(w, len, " ");
	if (num < 0)
	{
		write(1, "-", 1); //-00001234같은 경우를 위해 미리 - 출력
		len++;
		s = ft_substr(s, 1, ft_strlen(s));
	}
	len = print_flag(f->prec - ft_strlen(s) <= 0 ? 0 : f->prec - ft_strlen(s), len, "0");
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	if (f->left == TRUE) //왼쪽 정렬일 때
		len = print_flag(w, len, " ");
	return (len);
}
