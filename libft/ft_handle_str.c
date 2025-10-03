/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:08:05 by yingzhan          #+#    #+#             */
/*   Updated: 2025/05/29 15:02:11 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_str(char *str, int len, size_t *n)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_putchar_fd(str[i], 1);
		(*n)++;
		i++;
	}
}

void	ft_handle_str(va_list ap, t_format *fmt, size_t *n)
{
	char	*str;
	int		len;

	str = va_arg(ap, char *);
	if (str == NULL)
	{
		if (fmt->prec > 5 || fmt->prec < 0)
		{
			len = 6;
			str = "(null)";
		}
		else
			len = 0;
	}
	else
		len = ft_strlen(str);
	if (fmt->prec >= 0 && fmt->prec < len)
		len = fmt->prec;
	if (!fmt->minus && fmt->width > len)
		ft_padding(fmt->width - len, ' ', n);
	ft_print_str(str, len, n);
	if (fmt->minus && fmt->width > len)
		ft_padding(fmt->width - len, ' ', n);
}
