NAME =	cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm
RM = rm -rf

SRCS = \
	main.c \
	srcs/player/player.c \
	srcs/player/player2.c \
	srcs/player/player_controls.c \
	srcs/3d/display_map.c \
	srcs/parsing/map_file.c \
	srcs/parsing/map_memory.c \
	srcs/3d/render_3D.c \
	srcs/3d/render_3Dbis.c \
	srcs/3d/render_3Dtres.c \
	srcs/3d/textures.c \
	srcs/parsing/init.c \
	srcs/parsing/map_parser.c \
	srcs/parsing/map_parsing.c \
	srcs/parsing/map_player.c \
	srcs/parsing/map_textures.c \
	srcs/parsing/map_validation.c \
	srcs/parsing/parse_textures.c \
	srcs/utils/free_utils.c \
	srcs/utils/map_validation_utils.c \
	srcs/utils/parsing_utils.c \
	srcs/utils/utils.c \
	srcs/utils/utils2.c \
	srcs/utils/utils3.c \
	bonus/mouse.c

OBJS = $(SRCS:.c=.o)

YELLOW		= \033[1;33m
MAGENTA		= \033[1;35m
END			= \033[0m

TOTAL_FILES = $(words $(SRCS))

all:			$(NAME)
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
