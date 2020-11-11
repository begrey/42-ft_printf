/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:26:58 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 18:44:58 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"

typedef enum	e_boolean {
	FALSE,
	TRUE
}				t_boolean;

typedef	struct			s_flag
{
	t_boolean			zero;
	t_boolean			left;
	t_boolean			prec_zero;
	int					prec;
	int					width;
}						t_flag;

int						ft_printf(const char *str, ...);
void					get_flag(char *str, va_list ap, t_flag *f);
int						get_d(char *str, va_list ap, t_flag *f);
int						get_c(char *str, va_list ap, t_flag *f);
int						get_s(char *str, va_list ap, t_flag *f);
int						get_x(char *str, va_list ap, t_flag *f, char c);
int						get_u(char *str, va_list ap, t_flag *f);
int						get_p(char *str, va_list ap, t_flag *f);
int						get_percent(char *str, va_list ap, t_flag *f);
int						print_flag(int w, int len, char *s);
char					*ft_itoa_base(long value, int base, char c);
int						set_prev_and_width(char *s, t_flag *f, long num);
int						zero_flag(t_flag *f, long num, char *s);

#endif
