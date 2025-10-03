/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:23:28 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/29 14:38:27 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_handle_type(va_list ap, t_format *fmt, size_t *n)
{
	if (fmt->type == 'c')
		ft_handle_char(ap, fmt, n);
	else if (fmt->type == 's')
		ft_handle_str(ap, fmt, n);
	else if (fmt->type == 'p')
		ft_handle_ptr(ap, fmt, n);
	else if (fmt->type == 'd' || fmt->type == 'i')
		ft_handle_int(ap, fmt, n);
	else if (fmt->type == 'u')
		ft_handle_uint(ap, fmt, n);
	else if (fmt->type == 'x')
		ft_handle_hex(ap, fmt, n, 0);
	else if (fmt->type == 'X')
		ft_handle_hex(ap, fmt, n, 1);
	else if (fmt->type == '%')
		ft_handle_percent(n);
}

static void	ft_parse_prec(const char *s, t_format *fmt, size_t *i)
{
	if (ft_isdigit(s[*i]))
	{
		fmt->prec = ft_atoi(&s[*i]);
		while (ft_isdigit(s[*i]))
			(*i)++;
	}
	else
	{
		fmt->prec = 0;
	}
}

static void	ft_parse_format(const char *s, t_format *fmt, size_t *i)
{
	ft_init_format(fmt);
	while (!ft_strchr("cspdiuxX%", s[*i]) && s[*i])
	{
		if (ft_strchr("-0# +", s[*i]))
			ft_parse_sign(s[*i], fmt);
		else if (ft_isdigit(s[*i]))
		{
			fmt->width = ft_atoi(&s[*i]);
			while (ft_isdigit(s[*i]))
				(*i)++;
			continue ;
		}
		else if (s[*i] == '.')
		{
			(*i)++;
			ft_parse_prec(s, fmt, i);
			fmt->zero = 0;
			continue ;
		}
		(*i)++;
	}
	if (ft_strchr("cspdiuxX%", s[*i]))
		fmt->type = s[*i];
}

static void	ft_convert_args(const char *s, va_list ap, size_t *count)
{
	size_t		i;
	t_format	fmt;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			ft_parse_format(s, &fmt, &i);
			if (fmt.type)
				ft_handle_type(ap, &fmt, count);
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			(*count)++;
		}
		i++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	size_t		count;

	if (format == NULL)
		return (0);
	count = 0;
	va_start(ap, format);
	ft_convert_args(format, ap, &count);
	va_end(ap);
	return (count);
}
/*
#include <stdio.h>
int	main(void)
{
	int	a;
//	int	b;
	a = ft_printf("|%50.2s|", NULL);
	ft_printf("\n%d\n", a);
//	b = printf("%08.5i", 34);
//	printf("\n%d\n", b);
	return (0);
}*/