/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:55:02 by nlambert          #+#    #+#             */
/*   Updated: 2025/04/09 12:52:02 by nlambert         ###   ########.fr       */
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
# include <stdint.h>

# ifndef BUFFER_SIZE_GNL
#  define BUFFER_SIZE_GNL 42
# endif

// Random functions
int		ft_strlen(char *str);
char	*ft_strdup(char *src);
char	*ft_itoa(int n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t nmemb, size_t size);

// Get Next Line Functions
char	*ft_read(int fd, char *stash);
char	*ft_line(char *stash);
char	*ft_rab(char *stash);
char	*get_next_line(int fd);

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif
