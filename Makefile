CFLAGS =	-std=iso9899:1999 -fdiagnostics-show-location=every-line -Wall \
		-Werror -pedantic -pedantic-errors -Wfatal-errors -ftrapv \
		-g

SRCS =		${wildcard *.c}
BINS =		${patsubst %.c, bin/%, $(SRCS)}

bin/%: %.c
	${CC} ${CFLAGS} -c $< -o $@

all: ${BINS}
.PHONY: all

clean:
	rm bin/*
.PHONY: clean
