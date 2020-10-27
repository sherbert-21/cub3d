NAME	= 	cub

FLAGS	= 	-Wall -Werror -Wextra -g -fsanitize=address

SRC		= 	file_parce.c \
			valid_input.c \
			error.c \
			color.c \
			texture.c \
			map.c \
			resolution.c \
			player.c \
			gnl.c \
			utils_gnl.c \
			init.c \
			move.c \
			bmp.c \
			manage.c \
			ray.c \
			screen.c \
			texturisation.c \
			cub3d.c

SRC_DIR	= 	./src

OBJ		= 	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OBJ_DIR	= 	./obj

INC		= 	-I ./include -I ./libft -I ./mlx

LIBFT	=	-L ./libft -lft

MLX		=	-L ./mlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./mlx
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc $(WFLAGS) $(INC) -o $@ -c $<

clean:
	/bin/rm -rf ./obj
	make -C ./libft/ clean
	make -C ./mlx/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft/ fclean

re: fclean all
