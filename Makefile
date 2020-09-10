NAME = cub

FLAGS = -Wall -Werror -Wextra

HEAD = cub3d.h

SRCS = ./*.c

OBJS = ./*.o

all: $(NAME)

$(NAME): 
	gcc -c $(SRCS) -L ./libft/libft.a libmlx.a -framework OpenGL -framework Appkit

bonus: $(SRCS_BONUS)
	gcc $(FLAGS) -c $(SRCS_BONUS) $(SRCS)
	ar rc $(NAME) $(OBJS)

clean:
	/bin/rm -f $(OBJS)
	/bin/rm -f *so
	/bin/rm -rf *gch

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

so:
	gcc -fPIC $(FLAGS) -c $(SRCS) $(HEAD)
	gcc -shared -o libft.so *.o

.PHONY: clean fclean all re $(NAME)