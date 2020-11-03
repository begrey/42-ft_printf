/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:26:58 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/03 16:35:34 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"

int	ft_printf(const char *str, ...);
typedef enum _boolean {
    FALSE,
    TRUE
} boolean;

typedef	struct			flag_list
{
	boolean				zero;
	boolean				left;
	boolean				prec_zero;
	int					prec;
	int					width;	
}						f_list;

#endif
