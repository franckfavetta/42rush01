all: final

final: norm main.c map_browsing.c map_checking.c
	cc -Wall -Wextra -Werror -o rush-01 *.c
	
comp: main.c map_browsing.c map_checking.c
	cc -o rush-01 *.c
	
norm: map_browsing.c map_checking.c main.c
	norminette map_browsing.c map_checking.c main.c

clean:
	rm -f rush-01
