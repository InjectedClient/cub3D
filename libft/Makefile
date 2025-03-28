NAME =	libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar crs
RM = rm -f
Lib_H = libft.h

SRCS_LIBFT =  get_next_line.c get_next_line_utils.c ft_strlen.c \
				ft_strdup.c ft_itoa.c ft_memset.c ft_memcpy.c ft_calloc.c \
					ft_strncmp.c \


OBJS_LIBFT = $(SRCS_LIBFT:%.c=%.o)


$(NAME): 		$(OBJS_LIBFT)
				$(AR) $@ $^

all:			$(NAME)
    
.c.o: $(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
				$(RM) $(OBJS_LIBFT)
    
fclean: 		clean
				$(RM) $(NAME) libft.a

re: 			fclean all

.PHONY: 		all clean fclean re
