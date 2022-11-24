#gcc -Wall -Wextra -Werror -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -g -fsanitize=address -o fdf

#gcc -Wall -Wextra -Werror -Wconversion -O2 -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -o fdf

#Using leaks
#export MallocStackLogging=1 #to allow line finding
#unset MallocStackLogging #to remove 
gcc -Wall -Wextra -Werror -O0 -I../include/ -L../lib/ -lmlx -lft -framework OpenGL -framework AppKit *.c -g -o fdf
#leaks --atExit --list -- ./fdf basictest.fdf
#nb: leaks only detect lost pointers to allocated mem, blocks that for sure can no longer be freed, does not detect alloc but not freed memory
