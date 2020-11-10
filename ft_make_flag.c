/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:34:08 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/10 17:03:30 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		prec_wildcard(char *str, char *ptr, t_flag *f, char *w, va_list ap)
{
	int		wild;
	int		flag;

	flag = 0;
	if (w < ptr) //폭에 와일드 카드가 있을 때
	{
		wild = va_arg(ap, int);
		f->width = wild; //음수일 경우 마지막에서 -플래그 예외처리
		flag = 1;
		f->prec = ft_atoi(ft_substr(ptr + 1, 0, ft_strlen(ptr)));
	}
	if ((ft_strchr(ptr, '*'))) //정밀도에 와일드 카드가
	{
		f->prec = va_arg(ap, int);
		if (flag != 1) //폭에 와일드 카드 말고 따로 값이 있을 때!
			f->width = ft_atoi(ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr)));
	}
	else
		f->prec = ft_atoi(ft_substr(ptr + 1, 0, ft_strlen(ptr))); //정밀도에 와카 없으면 따로 지정
}

void		check_prec(t_flag *f, char *ptr, char *str, va_list ap)
{
	char	*w;
	int		flag;

	flag = 0;
	f->prec_zero = TRUE; //prec이 있지만 값이 0인 상태와, prec이 없어서 prec값이 0인 상태와 구분하기 위해 사용
	if ((w = ft_strchr(str, '*'))) // 와일드 카드가 있을때
		prec_wildcard(str, ptr, f, w, ap);
	else
	{
		f->prec = ft_atoi(ft_substr(ptr + 1, 0, ft_strlen(ptr))); //.뒤 출력 즉 정밀도값
		f->width = ft_atoi(ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr))); // 정밀도가 있으면 폭은 (-,0을 자르고 난 처음부터 .전까지)
	}
	if (f->prec >= 0) //정밀도가 음수가 아니고 존재하긴 한다면 0플래그 무시하기
		f->zero = FALSE;
}

void		check_width(va_list ap, char *str, t_flag *f) //없을땐 substring에서 ""이니 널값으로 0이 알아서 들어옴. 즉 0은 너비가 읍다
{
	int		wild;
	
	wild = 0;
	f->prec_zero = FALSE;
	if ((ft_strchr(str, '*'))) // 폭에 와카가 음수로 들어오면 -플래그도 생각하자
	{
		wild = va_arg(ap, int);
		f->width = wild;
	}
	else
		f->width = ft_atoi(ft_substr(str, 0, ft_strlen(str)));
	f->prec = 0;
}

void		get_flag(char *str, va_list ap, t_flag *f)
{
	char	*ptr;

	f->left = str[0] == '-' ? TRUE : FALSE;
	f->zero = str[0] == '0' ? TRUE : FALSE;
	if (f->zero == TRUE || f->left == TRUE)
		str = ft_substr(str, 1, ft_strlen(str));
	if ((ptr = ft_strchr(str, '.')))
		check_prec(f, ptr, str, ap);
	else
	{
		check_width(ap, str, f);
	}
	if (f->width < 0)
	{
		f->left = TRUE;
		f->zero = FALSE; // 원래 -와 0는 공존 불가하나 width의 와일드 카드 값으로 음수가 들어온 경우에는 왼쪽정렬이 우선순위
		f->width *= -1;
	}
}