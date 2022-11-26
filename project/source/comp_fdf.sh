#gcc -Wall -Wextra -Werror -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -g -fsanitize=address -o fdf

#gcc -Wall -Wextra -Werror -Wconversion -O2 -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -o fdf

#gcc -Wall -Wextra -Werror -O2 -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -o fdf

gcc -Wall -Wextra -Werror -O2 -DBUFFER_SIZE=1000000 -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -o fdf

#for valgrind
#gcc -Wall -Wextra -Werror -O0 -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -g -o fdf
