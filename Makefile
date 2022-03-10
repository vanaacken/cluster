NAME	=		cluster

SRCS	=		./srcs/main.c \
				./srcs/create_interface.c \
				./srcs/init.c \
				./srcs/my_mlx_pixel_put.c
FLAGS	=		-Wall -Werror -Wextra -g -lglfw #-Imlx -g

# MLX		=		mlx/libmlx.dylib
MLX		=		MLX42/libmlx42.a

HEADER	=		includes/*.h

OBJS	=		$(SRCS:%.c=%.o)

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) -g -fsanitize=address $^ -o $(NAME)


%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C mlx 
	
#&& test -e libmlx.dylib || ln -sf mlx/libmlx.dylib libmlx.dylib 

clean:
	make clean -C mlx
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -f libmlx.dylib

fclean: clean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all


