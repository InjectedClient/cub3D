NAME =	cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm
RM = rm -rf

SRCS = main.c srcs/parsing.c srcs/map_parsing.c srcs/texture_parsing.c \
      srcs/file_parsing.c srcs/perso_parsing.c srcs/utils.c srcs/player.c \
      srcs/color_parsing.c srcs/map.c


OBJS = $(SRCS:.c=.o)

YELLOW		= \033[1;33m
MAGENTA		= \033[1;35m
END			= \033[0m

TOTAL_FILES = $(words $(SRCS))

all:			$(NAME)
				@clear
				@echo "${MAGENTA}                                         ${END}";
				@echo "${MAGENTA} ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ ${END}";
				@echo "${MAGENTA}██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗${END}";
				@echo "${MAGENTA}██║     ██║   ██║██████╔╝ █████╔╝██║  ██║${END}";
				@echo "${MAGENTA}██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║${END}";
				@echo "${MAGENTA}╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝${END}";
				@echo "${MAGENTA} ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ${END}";
				@echo "${MAGENTA}                                         ${END}";


$(NAME):		$(OBJS)
				make -C libft/
				make -C minilibx-linux/
				$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(MLX_FLAGS) libft/libft.a minilibx-linux/libmlx.a

.c.o:
	@CURRENT_COUNT=$$(ls $(OBJS) 2>/dev/null | wc -l); \
	printf "\e[32mCompiling cub3D... [$$CURRENT_COUNT/$(TOTAL_FILES)]\e[0m\r"; \
	$(CC) $(CFLAGS) -c $< -o $@

clean:
				make clean -C libft/
				make clean -C minilibx-linux/
				$(RM) $(OBJS)
				@clear
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡆⠀⠀clean⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡈⠻⠇⢸⣷⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡿⠿⠟⠛⠋⣉⣤⣴⣶⡀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣁⣠⣤⣤⣴⣶⣿⣿⠿⠿⠛⠋⣁⡀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠋⣉⣉⣠⣤⣴⣶⣾⣿⣿⣷⡀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢦⣄⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠂⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡏⣿⣿⣿⣿⡿⣿⣿⢿⣿⡿⢿⣿⠻⡿⠛⠁⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⠀⡟⢹⣿⡿⠃⠸⠿⠀⠙⠃⠀⠁⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}                                     ${END}";


fclean: 		clean
				$(RM) $(NAME) libft/libft.a libmlx_Linux.a
				@clear
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡆⠀⠀Fclean⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡈⠻⠇⢸⣷⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡿⠿⠟⠛⠋⣉⣤⣴⣶⡀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣁⣠⣤⣤⣴⣶⣿⣿⠿⠿⠛⠋⣁⡀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠋⣉⣉⣠⣤⣴⣶⣾⣿⣿⣷⡀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢦⣄⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠂⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡏⣿⣿⣿⣿⡿⣿⣿⢿⣿⡿⢿⣿⠻⡿⠛⠁⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⠀⡟⢹⣿⡿⠃⠸⠿⠀⠙⠃⠀⠁⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}                                     ${END}";

re: 			fclean all

.PHONY:			all clean fclean re
