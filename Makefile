
NAME	=		cluster

SRCS	=		./src/*.c

FLAGS	=		-Wall -Werror -Wextra -Imlx -g

MLX		=		libraries/mlx/libmlx.dylib

HEADER	=		includes/*.h

OBJS	=		$(SRCS:%.c=%.o)

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) -g -fsanitize=address $^ -o $(NAME)


%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C libraries/mlx && test -e libmlx.dylib || ln -sf libraries/mlx/libmlx.dylib libmlx.dylib 

clean:
	make clean -C libraries/mlx
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -f libmlx.dylib

fclean: clean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all









