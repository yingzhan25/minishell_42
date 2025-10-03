/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:26:09 by yingzhan          #+#    #+#             */
/*   Updated: 2025/06/20 14:52:02 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

typedef struct s_format
{
	char	type;
	int		width;
	int		prec;
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
}	t_format;

int		ft_printf(const char *format, ...);
void	ft_handle_char(va_list ap, t_format *fmt, size_t *n);
void	ft_handle_str(va_list ap, t_format *fmt, size_t *n);
void	ft_handle_ptr(va_list ap, t_format *fmt, size_t *n);
void	ft_handle_int(va_list ap, t_format *fmt, size_t *n);
void	ft_handle_uint(va_list ap, t_format *fmt, size_t *n);
void	ft_handle_hex(va_list ap, t_format *fmt, size_t *n, int c);
void	ft_handle_percent(size_t *n);

void	ft_init_format(t_format *fmt);
void	ft_parse_sign(char c, t_format *fmt);
void	ft_padding(int width, char c, size_t *n);
char	ft_zero(t_format *fmt);
int		ft_uintlen(unsigned int nbr, unsigned int b);

#endif