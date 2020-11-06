/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:26:58 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/06 18:56:19 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"

typedef enum _boolean {
    FALSE,
    TRUE
} boolean;

typedef	struct			s_flag
{
	boolean				zero;
	boolean				left;
	boolean				prec_zero;
	int					prec;
	int					width;	
}						t_flag;

int		ft_printf(const char *str, ...);
void	get_flag(char *str, va_list ap, t_flag *f);
int get_d(char *str, va_list ap, t_flag *f);
int get_c(char *str, va_list ap, t_flag *f);
int	get_s(char *str, va_list ap, t_flag *f);
int print_flag(int w, int len, char *s);

#endif
