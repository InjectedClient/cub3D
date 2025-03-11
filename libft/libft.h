/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:55:02 by nlambert          #+#    #+#             */
/*   Updated: 2025/03/11 11:43:35 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE_GNL
#  define BUFFER_SIZE_GNL 42
# endif

// Random functions
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *src);
char	*ft_itoa(int n);

// Get Next Line Functions
char	*ft_read(int fd, char *stash);
char	*ft_line(char *stash);
char	*ft_rab(char *stash);
char	*get_next_line(int fd);

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);


#endif
