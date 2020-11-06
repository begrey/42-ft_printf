/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:23:50 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/06 19:23:12 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char get_option(char *str)
{
	char option;
	char *init;

	option = 'a';
	init = str;
	if (ft_strchr(str, 'c') && (str = init))
		option = 'c';
	else if (ft_strchr(str, 'd') && (str = init))
		option = 'd';
	else if (ft_strchr(str, 'i') && (str = init))
		option = 'i';
	else if (ft_strchr(str, 'p') && (str = init))
		option = 'p';
	else if (ft_strchr(str, 's') && (str = init))
		option = 's';
	else if (ft_strchr(str, 'u') && (str = init))
		option = 'u';
	else if (ft_strchr(str, 'x') && (str = init))
		option = 'x';
	else if (ft_strchr(str, 'X') && (str = init))
		option = 'X';
	else
		option = '%';
	return (option);
}

void			reset_flag(t_flag *f)
{
	f->zero = FALSE;
	f->left = FALSE;
	f->prec_zero = FALSE;
	f->prec = 0;
	f->width = 0;
}

int	ft_printf(const char *str, ...)
{
	va_list ap;
	int		len;
	int		i;
	char	*ptr;
	char	*s;
	char	*init;
	t_flag	f;

	i = 0;
	len = 0;
	reset_flag(&f);
	va_start(ap, str);
	init = (char *)str;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if ((ptr = ft_strchr(str, 'd'))) //서식 지정자들 골라내기
			{
				s = ft_substr(str, 0, ptr - str);
				len += get_d(s, ap, &f);
				str = ptr + 1;
			}
			else if ((ptr = ft_strchr(str, 'c')))
			{
				s = ft_substr(str, 0, ptr - str);
				len += get_c(s, ap, &f);
				str = ptr + 1;
			}
			else if ((ptr = ft_strchr(str, 's')))
			{
				s = ft_substr(str, 0, ptr - str);
				len += get_s(s, ap, &f);
				str = ptr + 1;
			}
			else //%만 출력할 때
			{
				len++;
				write(1, "%%", 1);
				str++;
			}
		}
		else
		{
			write(1, &(*str++), 1);
			len++;
		}
	}
	va_end(ap);
	return (len);
}

// int main()
// {
// 	int a = printf("-->|%-16.*s|<--\n", -4, "abc"); //출력값은 결국 인자 길이 + 플래그를 통한 여백이나 0
// 	int b = ft_printf("-->|%-16.*s|<--\n", -4, "abc");
// 	printf("%d %d\n", a, b);
// 	return 0;
// } 