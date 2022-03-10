NAME	=		cluster

SRCS	=		./srcs/main.c \
				./srcs/create_interface.c \
				./srcs/my_mlx_pixel_put.c \
#				./srcs/init.c \

FLAGS	=		-Wall -Werror -Wextra #-Imlx -g

# MLX		=		mlx/libmlx.dylib
MLX		=		MLX42/libmlx42.a

HEADER	=		includes/*.h

OBJS	=		$(SRCS:%.c=%.o)

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) -lglfw -L /opt/homebrew/Cellar/glfw/3.3.6/lib -g -fsanitize=address $^ -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -lglfw -C MLX42
	
#&& test -e libmlx.dylib || ln -sf mlx/libmlx.dylib libmlx.dylib 

clean:
# make clean -C mlx
	rm -f $(OBJS) $(BONUS_OBJS)
# rm -f libmlx.dylib

fclean: clean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all
