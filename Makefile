CC=gcc

nebula_draw: nebula_draw.c
	$(CC) -o ndraw nebula_draw.c -lncurses
