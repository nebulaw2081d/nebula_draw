CC=gcc

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

nebula_draw: nebula_draw.c
	$(CC) -o ndraw nebula_draw.c -lncurses

install: ndraw
	cp -p ndraw "$(PREFIX)/bin"
