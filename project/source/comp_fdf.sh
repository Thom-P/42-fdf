gcc -Wall -Wextra -Werror -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit fdf.c drawing.c parsing.c processing.c debug_utils.c -g -fsanitize=address -o fdf

