#gcc -Wall -Wextra -Werror -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit fdf.c drawing.c parsing.c processing.c debug_utils.c matrix_utils.c -g -fsanitize=address -o fdf

gcc -Wall -Wextra -Werror -O2 -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit fdf.c drawing.c parsing.c processing.c debug_utils.c matrix_utils.c -o fdf
