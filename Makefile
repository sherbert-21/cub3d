NAME	= 	cub

FLAGS	= 	-Wall -Werror -Wextra -g -fsanitize=address

SRC		= 	cub3d.c \
			parce/file_parce.c \
			parce/error.c \
			parce/color.c \
			parce/texture.c \
			parce/map.c \
			parce/resolution.c \
			parce/player.c \
			init.c \
			move.c \

SRC_DIR	= 	./src

OBJ		= 	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OBJ_DIR	= 	./obj

INC		= 	-I ./include -I ./libft -I ./gnl -I ./mlx

LIBFT	=	-L ./libft -lft

MLX		=	-L ./mlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./mlx
	make -C ./gnl
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(WFLAGS) $(INC) -o $@ -c $<

clean:
	/bin/rm -rf ./obj
	make -C ./libft/ clean
	make -C ./mlx/ clean
	make -C ./gnl/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft/ fclean
	make -C ./gnl/ fclean

re: fclean all
