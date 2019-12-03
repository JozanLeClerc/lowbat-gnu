.POSIX:

default: all 

SHELL		:= /bin/sh
SRCS_DIR	= src/
INCS_DIR	= inc/
OBJS_DIR	= obj/
TRGT_DIR	= bin/

SRCS		= ${SRCS_DIR}main.cpp
SRCS		+= ${SRCS_DIR}jo_exec.cpp
SRCS		+= ${SRCS_DIR}jo_notify.cpp

INCS		= ${INCS_DIR}jo_lowbat.hpp

OBJS		= $(patsubst ${SRCS_DIR}%.cpp,${OBJS_DIR}%.o,${SRCS})

CC			= g++
CFLAGS		= -Wall
CFLAGS	 	+= -Wextra
CFLAGS	 	+= -Werror

DEBUG		= -g3
FSANITIZE	= -fsanitize=address

OPTIMIZE	= -O2

CFLAGS		+= ${OPTIMIZE}

NAME		= ${TRGT_DIR}lowbat

MKDIR		= mkdir -p

OS			= $(shell uname -s)
ifeq ($(OS), Darwin)
	PREFIX	= /usr/local
else
	PREFIX	= /usr
endif
MANPREFIX	= $(PREFIX)/share/man

${OBJS_DIR}%.o:	${SRCS_DIR}%.cpp ${INCS_DIR}${INCS}
	@${MKDIR} ${OBJS_DIR}

${NAME}:	${OBJS}
	${CC} ${CFLAGS} -o ${TARGET} ${OBJS}

all:
	@${MAKE} -j5 ${NAME}
install:	all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f bin/lowbat $(DESTDIR)$(PREFIX)/bin/
	chmod 755 $(DESTDIR)$(PREFIX)/bin/lowbat
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f man/lowbat.1 $(DESTDIR)$(MANPREFIX)/man1/lowbat.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/lowbat
	rm -f $(DESTDIR)$(MANPREFIX)/man1/lowbat.1

.PHONY: install uninstall
