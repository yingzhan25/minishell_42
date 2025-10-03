/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:22:00 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 12:18:09 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchr_g(const char *str, int c);
size_t	ft_strlen_g(const char *str);
char	*ft_strdup_g(const char *str);
char	*ft_substr_g(char const *str, unsigned int start, size_t len);
char	*ft_strjoin_g(char const *s1, char const *s2);

#endif