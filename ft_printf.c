/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:23:50 by jimkwon           #+#    #+#             */
/*   Updated: 2020/11/03 17:44:03 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (!src)
		return (0);
	i = 0;
	len = ft_strlen(src);
	if ((int)size <= 0)
		return (len);
	while (i < size - 1 && *src != '\0')
	{
		*dest = *(char *)src;
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

static char	*make_itoa(char *str, int n, int len)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			str[--len] = '8';
			n /= 10;
		}
		n *= -1;
	}
	while (n > 9)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	str[--len] = (n % 10) + '0';
	return (str);
}

static	int	count_len(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			n += 8;
		n *= -1;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	int		minus;
	char	*str;
	char	*ans;

	minus = 0;
	len = 0;
	if (n < 0)
	{
		len = 1;
		minus = 1;
	}
	else if (n == 0)
	{
		ans = ft_strdup("0");
		return (ans);
	}
	len += count_len(n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (minus == 1)
		*str = '-';
	str[len] = '\0';
	ans = make_itoa(str, n, len);
	return (ans);
}

char		*ft_strchr(const char *str, int c)
{
	char	*p;

	p = (char *)str;
	while (*p != '\0')
	{
		if (*p == c)
			return (p);
		p++;
	}
	if (c == '\0')
		return (p);
	return (NULL);
}

int				ft_atoi(const char *str)
{
	long long	minus;
	long long	total;

	minus = 1;
	total = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	if (*str != '\0' && (*str >= '0' && *str <= '9'))
		total += *str++ - '0';
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		if (minus == 1 && total > 2147483647)
			return (-1);
		if (minus == -1 && total > 2147483648)
			return (0);
		total *= 10;
		total += *str++ - '0';
	}
	return ((int)(total * minus));
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	unsigned int	i;
	char			*str;

	if (!s)
		return (0);
	s_len = (int)ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i != start)
	{
		s++;
		i++;
	}
	i = 0;
	while (i < len && *s != '\0')
	{
		str[i++] = *(char *)s;
		s++;
	}
	str[i] = '\0';
	return (str);
}

f_list *get_flag(char *str, va_list ap)
{
	f_list	*p;
	char	*ptr;
	char	*w;
	int 	wild;

	p = malloc(sizeof(f_list) * 1);
	p->left = str[0] == '-' ? TRUE : FALSE;
	p->zero = str[0] == '0' ? TRUE : FALSE;
	if (p->zero == TRUE || p->left == TRUE)
		str = ft_substr(str, 1, ft_strlen(str));
	if ((ptr = ft_strchr(str, '.')))
	{
		p->prec_zero = TRUE; //prec이 있지만 값이 0인 상태와, prec이 없어서 prec값이 0인 상태와 구분하기 위해 사용
		if ((w = ft_strchr(str, '*'))) // 와일드 카드가 있을때
		{
			if (w < ptr) //폭에 와일드 카드가 있을 때
			{
				wild = va_arg(ap, int);
				p->width = wild; //음수일 경우 마지막에서 -플래그 예외처리
				p->prec = ft_atoi(ft_substr(ptr + 1, 0, ft_strlen(ptr)));
			}
			if ((ft_strchr(ptr, '*'))) //정밀도에 와일드 카드가
			{
				p->prec = va_arg(ap, int);
				if (p->width != wild) //폭에 와일드 카드 말고 따로 값이 있을 때!
					p->width = ft_atoi(ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr))); 
			}
			else
				p->prec = ft_atoi(ft_substr(ptr + 1, 0, ft_strlen(ptr))); //정밀도에 와카 없으면 따로 지정
		}
		else
		{
			p->prec = ft_atoi(ft_substr(ptr + 1, 0, ft_strlen(ptr))); //.뒤 출력 즉 정밀도값
			p->width = ft_atoi(ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr))); // 정밀도가 있으면 폭은 (-,0을 자르고 난 처음부터 .전까지)
		}
		if (p->prec >= 0) //정밀도가 음수가 아니고 존재하긴 한다면 0플래그 무시하기
			p->zero = FALSE;
	}
	else
	{
		p->prec_zero = FALSE;
		if ((ft_strchr(str, '*'))) // 폭에 와카가 음수로 들어오면 -플래그도 생각하자
		{
			wild = va_arg(ap, int);
			p->width = wild;
		}
		else
			p->width = ft_atoi(ft_substr(str, 0, ft_strlen(str)));
		p->prec = 0;
	}
	if (p->width < 0)
	{
		p->left = TRUE;
		p->zero = FALSE; // 원래 -와 0는 공존 불가하나 width의 와일드 카드 값으로 음수가 들어온 경우에는 왼쪽정렬이 우선순위
		p->width *= -1;
	}
	return (p);
}

int get_d(char *str, va_list ap)
{
	char	*s;
	int		index;
	int		w;
	int		i;
	int		num;
	int		len;
	int		minus;
	f_list	*f;
	
	f = get_flag(str, ap);
	index = 0;
	len = 0;
	minus = 0;
	//처음에 오는 플래그 -와 0이 있다면 여기서 뽑은 후 str에서 이 친구들을 잘라낸다.
	num = va_arg(ap, int);
	s = ft_itoa(num);
	if (f->prec == 0 && num == 0 && f->prec_zero == TRUE) //정밀도에 기본값 0이 들어있을 때, value가 0이면 null처리로 0 대신 빈 문자열이 출력되어야 함
		s = "";
	if (f->zero == TRUE && f->prec <= 0) //정밀도가 없거나 음수여야 0플래그가 유효함
	{
		i = 0;
		index = f->width - ft_strlen(s) <= 0 ? 0 : f->width - ft_strlen(s);
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
	i = 0;
	if (f->left == FALSE) //오른쪽 정렬일 때
		while (i++ < w)
		{
			write(1, " ", 1);
			len++;
		}
	if (num < 0)
	{
		write(1, "-", 1); //-00001234같은 경우를 위해 미리 - 출력
		len++;
		s = ft_substr(s, 1, ft_strlen(s));
	}
	i = 0;
	index = f->prec - ft_strlen(s) <= 0 ? 0 : f->prec - ft_strlen(s);
	while (i++ < index) 
	{
		write(1, "0", 1);
		len++;
	}
	write(1, s, ft_strlen(s));
	len += (int)ft_strlen(s);
	i = 0;
	if (f->left == TRUE) //왼쪽 정렬일 때
		while (i++ < w)
		{
			write(1, " ", 1);
			len++;
		}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list ap;
	int		len;
	int		i;
	char	*ptr;
	char	*s;

	i = 0;
	len = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			if ((ptr = ft_strchr(str++, 'd'))) //서식 지정자들 골라내기
			{
				s = ft_substr(str, 0, ptr - str);
				len += get_d(s, ap);
				str = ptr + 1;
			}
			else //%만 출력할 때
			{
				len++;
				write(1, "%%", 1);
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
// 	int a = printf("-->|%0*d|<--\n", -4, -12); //출력값은 결국 인자 길이 + 플래그를 통한 여백이나 0
// 	int b = ft_printf("-->|%0*d|<--\n", -4, -12);
// 	printf("%d %d\n", a, b);
// 	return 0;
// } 
