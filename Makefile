#================================ Makefile ====================================#
.POSIX:

default: all 
#==============================================================================#
#--------------------------------- Shell --------------------------------------#
#==============================================================================#
SHELL		:= /bin/sh
#==============================================================================#
#------------------------------ Directories -----------------------------------#
#==============================================================================#
SRCS_DIR	= src/
INCS_DIR	= inc/
OBJS_DIR	= obj/
TRGT_DIR	= bin/
#==============================================================================#
#--------------------------------- Files --------------------------------------#
#==============================================================================#
SRCS		= ${SRCS_DIR}main.cpp
SRCS		+= ${SRCS_DIR}jo_exec.cpp
SRCS		+= ${SRCS_DIR}jo_notify.cpp
#------------------------------------------------------------------------------#
INCS		= jo_lowbat.hpp
#------------------------------------------------------------------------------#
OBJS		= $(patsubst ${SRCS_DIR}%.cpp,${OBJS_DIR}%.o,${SRCS})
#==============================================================================#
#-------------------------------- Compiler ------------------------------------#
#==============================================================================#
CC			= g++
#------------------------------------------------------------------------------#
DEBUG		= -g3
FSANITIZE	= -fsanitize=address
#------------------------------------------------------------------------------#
OPTIMIZE	= -O2
#------------------------------------------------------------------------------#
CFLAGS		= -Wall
CFLAGS	 	+= -Wextra
CFLAGS	 	+= -Werror
CFLAGS		+= ${OPTIMIZE}
#------------------------------------------------------------------------------#
NAME		= lowbat
#==============================================================================#
#--------------------------------- UNIX ---------------------------------------#
#==============================================================================#
MKDIR		= mkdir -p
RM			= rm -rf
#------------------------------------------------------------------------------#
OS			= $(shell uname -s)
ifeq ($(OS), Darwin)
	PREFIX	= /usr/local
else
	PREFIX	= /usr
endif
MANPREFIX	= $(PREFIX)/share/man
#==============================================================================#
#--------------------------------- Rules --------------------------------------#
#==============================================================================#
${OBJS_DIR}%.o:		${SRCS_DIR}%.cpp ${INCS_DIR}${INCS}
	@${MKDIR} ${OBJS_DIR}
	${CC} ${CFLAGS} -I${INCS_DIR} -c -o $@ $<
#------------------------------------------------------------------------------#
${NAME}:			${OBJS}
	@${MKDIR} ${TRGT_DIR}
	${CC} ${CFLAGS} -o ${TRGT_DIR}${NAME} ${OBJS}
#------------------------------------------------------------------------------#
all:
	@${MAKE} -j5 ${NAME}
#------------------------------------------------------------------------------#
install:			all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f bin/lowbat $(DESTDIR)$(PREFIX)/bin/
	chmod 755 $(DESTDIR)$(PREFIX)/bin/lowbat
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f man/lowbat.1 $(DESTDIR)$(MANPREFIX)/man1/lowbat.1
#------------------------------------------------------------------------------#
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/lowbat
	rm -f $(DESTDIR)$(MANPREFIX)/man1/lowbat.1
#------------------------------------------------------------------------------#
clean:
	${RM} ${OBJS_DIR}
#------------------------------------------------------------------------------#
fclean:				clean
#------------------------------------------------------------------------------#
re:					fclean all
#------------------------------------------------------------------------------#
	${RM} ${TRGT_DIR}
.PHONY: all lowbat clean fclean re install uninstall
#==================================== EOF =====================================#
