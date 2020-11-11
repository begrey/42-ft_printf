/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:08:32 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 19:35:34 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_flag(int w, int len, char *s)
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

int			zero_flag(t_flag *f, long num, char *s)
{
	int		len;
	int		i;
	int		index;

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

int			set_prev_and_width(char *s, t_flag *f, long num)
{
	int		minus;
	int		w;

	minus = 0;
	w = 0;
	if (s && s[0] == '-')
		minus = -1;
	if (f->prec <= (int)ft_strlen(s) + minus)
		f->prec = 0;
	if (f->width <= (int)ft_strlen(s) + minus || f->width <= f->prec)
		f->width = 0;
	if (f->prec <= 0)
		w = f->width - ft_strlen(s) <= 0 ? 0 : f->width - ft_strlen(s);
	else
	{
		w = f->width - (f->prec) <= 0 ? 0 : f->width - (f->prec);
		if (num < 0)
			w -= 1;
	}
	return (w);
}

int			get_d_two(int len, char *s, int num, t_flag *f)
{
	char	*str;

	if (num < 0)
	{
		write(1, "-", 1);
		len++;
		str = ft_substr(s, 1, ft_strlen(s));
	}
	else
		str = s;
	len = print_flag(f->prec - ft_strlen(str) <= 0 ? 0 :
	f->prec - ft_strlen(str), len, "0");
	write(1, str, ft_strlen(str));
	len += (int)ft_strlen(str);
	if (num < 0)
		free(str);
	return (len);
}

int			get_d(char *str, va_list ap, t_flag *f)
{
	char	*s;
	int		w;
	int		num;
	int		len;

	get_flag(str, ap, f);
	len = 0;
	num = va_arg(ap, int);
	if (f->prec == 0 && num == 0 && f->prec_zero == TRUE)
		s = ft_strdup("");
	else
		s = ft_itoa(num);
	if (f->zero == TRUE && f->prec <= 0)
		return (zero_flag(f, num, s));
	w = set_prev_and_width(s, f, num);
	if (f->left == FALSE)
		len = print_flag(w, len, " ");
	len = get_d_two(len, s, num, f);
	if (f->left == TRUE)
		len = print_flag(w, len, " ");
	free(s);
	return (len);
}
