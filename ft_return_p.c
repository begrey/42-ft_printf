/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:49:25 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 19:36:11 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_base_p(long value, int base, char c)
{
	char	*ans;
	int		len;
	long	num;

	len = 3;
	num = value;
	while (num >= base && len++ > 0)
		num /= base;
	ans = (char *)malloc(sizeof(char) * (len));
	ans[len] = '\0';
	num = value;
	while (num > 0)
	{
		if ((num % base) >= 10)
			ans[--len] = c + (num % base) % 10;
		else
			ans[--len] = (num % base) + '0';
		num /= base;
	}
	ans[0] = '0';
	ans[1] = 'x';
	return (ans);
}

int			get_p(char *str, va_list ap, t_flag *f)
{
	long	num;
	char	*s;
	int		len;
	int		w;

	len = 0;
	get_flag(str, ap, f);
	num = va_arg(ap, long);
	if (f->prec == 0 && num == 0 && f->prec_zero == FALSE)
		s = ft_strdup("0x0");
	else
		s = ft_itoa_base_p(num, 16, 'a');
	w = set_prev_and_width(s, f, num);
	if (f->left == FALSE)
		len = print_flag(w, len, " ");
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	if (f->left == TRUE)
		len = print_flag(f->width - (int)ft_strlen(s), len, " ");
	free(s);
	return (len);
}
