.POSIX:

default: all

SHELL		:= /bin/sh

SRCS_DIR	= src/
INCS_DIR	= inc/
OBJS_DIR	= obj/
TRGT_DIR	= bin/

SRCS_NAME	= main.cpp
SRCS_NAME	+= jo_exec.cpp
SRCS_NAME	+= jo_notify.cpp

SRCS		= $(addprefix ${SRCS_DIR}, ${SRCS_NAME})

INCS		= jo_lowbat.hpp

OBJS		= $(patsubst ${SRCS_DIR}%.cpp,${OBJS_DIR}%.o,${SRCS})

DEBUG		+= Og -ggdb
DEBUG		= -ggdb
FSANITIZE	= -fsanitize=address

CXX			= g++

OPTIMIZE	= -O2
OPTIMIZE	+= -pipe

CXXFLAGS		= -Wall
CXXFLAGS	 	+= -Wextra
CXXFLAGS	 	+= -Werror
#CXXFLAGS		+= ${OPTIMIZE}
CXXFLAGS		+= ${DEBUG}
CXXFLAGS		+= ${FSANITIZE}

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
	${MKDIR} ${OBJS_DIR}
	${CXX} ${CXXFLAGS} -I${INCS_DIR} -c -o $@ $<

${NAME}:			${OBJS}
	${MKDIR} ${TRGT_DIR}
	${CXX} ${CXXFLAGS} -o ${TRGT_DIR}${NAME} ${OBJS}

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
