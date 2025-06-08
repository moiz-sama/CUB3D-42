CC = cc 
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx_Linux -lXext -lX11 -lm
NAME = cub3d
BONUS = cub3d_bonus

SRC	=	src/main.c \
		src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c \
		src/libft/ft_strchr.c src/libft/ft_strncmp.c src/libft/ft_split.c src/libft/ft_strtrim.c src/libft/ft_isdigit.c src/libft/ft_atoi.c \
		src/parsing/start_parsing.c src/parsing/line_parse.c src/parsing/color_parse.c src/parsing/exit_error.c src/parsing/ft_check.c src/parsing/map_parse.c \
		src/raycasting/draw.c src/raycasting/init.c src/raycasting/player.c src/raycasting/utils.c src/raycasting/raycasting.c src/raycasting/set_raycasting.c \
		src/raycasting/texture.c

SRC_BONUS =	src_bonus/main_bonus.c \
			src_bonus/get_next_line/get_next_line_bonus.c src_bonus/get_next_line/get_next_line_utils_bonus.c \
			src_bonus/libft/ft_strchr_bonus.c src_bonus/libft/ft_strncmp_bonus.c src_bonus/libft/ft_split_bonus.c src_bonus/libft/ft_strtrim_bonus.c src_bonus/libft/ft_isdigit_bonus.c src_bonus/libft/ft_atoi_bonus.c \
			src_bonus/parsing/start_parsing_bonus.c src_bonus/parsing/line_parse_bonus.c src_bonus/parsing/color_parse_bonus.c src_bonus/parsing/exit_error_bonus.c src_bonus/parsing/ft_check_bonus.c src_bonus/parsing/map_parse_bonus.c \
			src_bonus/raycasting/draw_bonus.c src_bonus/raycasting/init_bonus.c src_bonus/raycasting/player_bonus.c src_bonus/raycasting/utils_bonus.c src_bonus/raycasting/raycasting_bonus.c src_bonus/raycasting/set_raycasting_bonus.c \
			src_bonus/raycasting/texture_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

$(BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX) -o $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all
