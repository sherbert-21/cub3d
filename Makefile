NAME	= cub

FLAGS	= -Wall -Werror -Wextra

SRC		= valid_map.c \
			valid_input.c \
			parcer.c \
			ident_parce.c \
			ident.c \
			cub_window.c

SRC_DIR	= ./src

OBJ		= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OBJ_DIR	= ./obj

INC		= -I ./include -I ./libft -I ./gnl -I ./mlx

LIBFT		=		-L ./libft -lft

MLX			=		-L ./mlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

all: make_libs $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) $(INC) -o $@ -c $<

make_libs:
	make bonus -C ./libft
	make -C ./mlx

clean:
	/bin/rm -rf ./obj
	make -C ./libft/ clean
	make -C ./mlx/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft/ fclean
	make -C ./mlx/ clean

re: fclean all