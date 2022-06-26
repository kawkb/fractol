NAME = fractol

SRCS = fractol.c fractol_utils.c


LIBFT = ./libft/libft.a

INCLUDE = -I ./libft/libft.h -I ./include/fractol.h -I /usr/local/include

# GCC = gcc -Wall -Werror -Wextra
GCC = gcc
GCCSANITIZE =  gcc -Wall -Werror -Wextra  -g3 -fsanitize=address
MLXMAC =  -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit 

all: $(NAME)

$(NAME): $(SRCS)
	# make -C libft
	# $(GCC) $(INCLUDE)  $(SRCS) $(LIBFT) $(MLXMAC) -o $(NAME) 
	$(GCC) $(INCLUDE)  $(SRCS) $(MLXMAC) -o $(NAME) 
clean:
	# make clean -C libft

a:
	make -C libft
	$(GCCSANITIZE)  $(SRCS) $(LIBFT) $(MLXMAC) -o $(NAME) 

fclean: clean
	# make fclean -C libft
	/bin/rm -rf $(NAME).dSYM
	/bin/rm -rf $(NAME)

re: fclean all