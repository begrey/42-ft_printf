/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:18:08 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 20:20:12 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_base(long value, int base, char c)
{
	char	*ans;
	int		len;
	long	num;

	len = 1;
	num = value;
	while (num >= base && len++ > 0)
		num /= base;
	ans = (char *)malloc(sizeof(char) * (len + 1));
	ans[len] = '\0';
	num = value;
	while (num >= base)
	{
		if ((num % base) >= 10)
			ans[--len] = c + (num % base) % 10;
		else
			ans[--len] = (num % base) + '0';
		num /= base;
	}
	if (num >= 10)
		ans[0] = c + num % 10;
	else
		ans[0] = num + '0';
	return (ans);
}

int			get_x(char *str, va_list ap, t_flag *f, char c)
{
	long	num;
	char	*s;
	int		len;
	int		w;

	len = 0;
	get_flag(str, ap, f);
	num = va_arg(ap, unsigned int);
	if (f->prec == 0 && num == 0 && f->prec_zero == TRUE)
		s = ft_strdup("");
	else
		s = ft_itoa_base(num, 16, c);
	if (f->zero == TRUE && f->prec <= 0)
		return (zero_flag(f, num, s));
	w = set_prev_and_width(s, f, num);
	if (f->left == FALSE)
		len = print_flag(w, len, " ");
	len = print_flag(f->prec - ft_strlen(s) <= 0 ? 0 :
	f->prec - ft_strlen(s), len, "0");
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	if (f->left == TRUE)
		len = print_flag(set_prev_and_width(s, f, num), len, " ");
	free(s);
	return (len);
}
