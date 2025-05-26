/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:55:02 by nlambert          #+#    #+#             */
/*   Updated: 2025/05/15 12:41:41 by nlambert         ###   ########.fr       */
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
void	*ft_memset(void *b, int c, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strtok(char *str, const char *delim);
int		ft_strcmp(const char *s1, const char *s2);

// Get Next Line Functions
char	*ft_read(int fd, char *stash);
char	*ft_line(char *stash);
char	*ft_rab(char *stash);
char	*get_next_line(int fd);

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif
