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

INCS		= jo_lowbat.hpp

OBJS		= $(patsubst ${SRCS_DIR}%.cpp,${OBJS_DIR}%.o,${SRCS})



CC			= g++

DEBUG		= -g3
FSANITIZE	= -fsanitize=address

OPTIMIZE	= -O3

CFLAGS		= -Wall
CFLAGS	 	+= -Wextra
CFLAGS	 	+= -Werror
CFLAGS		+= ${OPTIMIZE}

NAME		= lowbat



MKDIR		= mkdir -p
RM			= rm -rf

OS			= $(shell uname -s)
ifeq ($(OS), Darwin)
	PREFIX	= /usr/local
else
	PREFIX	= /usr
endif
MANPREFIX	= $(PREFIX)/share/man



${OBJS_DIR}%.o:		${SRCS_DIR}%.cpp ${INCS_DIR}${INCS}
	@${MKDIR} ${OBJS_DIR}
	${CC} ${CFLAGS} -I${INCS_DIR} -c -o $@ $<

${NAME}:			${OBJS}
	@${MKDIR} ${TRGT_DIR}
	${CC} ${CFLAGS} -o ${TRGT_DIR}${NAME} ${OBJS}

all:				${NAME}

clean:
	${RM} ${OBJS_DIR}

fclean:				clean
	${RM} ${TRGT_DIR}

re:					fclean all

install:			all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f bin/lowbat $(DESTDIR)$(PREFIX)/bin/
	chmod 755 $(DESTDIR)$(PREFIX)/bin/lowbat
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f man/lowbat.1 $(DESTDIR)$(MANPREFIX)/man1/lowbat.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/lowbat
	rm -f $(DESTDIR)$(MANPREFIX)/man1/lowbat.1

.PHONY: all lowbat clean fclean re install uninstall
