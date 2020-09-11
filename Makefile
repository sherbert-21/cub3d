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

INC			= 		-I ./include -I ./libft -I ./gnl -I ./mlx

LIBFT		=		-L ./libft -lft

MLX			=		-L ./mlx -lmlx -framework OpenGL -framework AppKit

GNL			=		-L ./gnl -lgnl

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./mlx
	make -C ./gnl
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(MLX) $(GNL) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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