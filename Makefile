SRCNAME		=	src/main.c	\
				src/ELFparser.c

SRCS		= ${SRCNAME}

OBJS		= ${SRCS:.c=.o}

FT_NM		= ft_nm

CC		= gcc
RM		= rm -f
CFLAGS		= -Wall -Wextra -Werror -I./inc/libft

CGREEN		= \033[38;2;0;153;0m
CRED		= \033[0;31m
CYELLOW		= \033[0;33m
CGREY		= \033[38;2;128;128;128m
CEND		= \033[0m

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${FT_NM}:	${OBJS}
		@echo
		@echo "$(CYELLOW)Libft compilation$(CEND)"
		@echo "$(CGREY)"
		make -C ./inc/libft
		@echo "$(CEND)"
		@echo "$(CGREEN)Compilation libft done !$(CEND)"
		@echo
		${CC} -o ${FT_NM} ${OBJS} -L./inc/libft -lft
		@echo "$(CEND)"
		@echo "$(CGREEN)Compilation done !$(CEND)"
		@echo

all:		${FT_NM}

clean:
		@echo
		@echo "$(CYELLOW)Deleting .o files$(CEND)"
		@echo "$(CGREY)"
		make -C ./inc/libft clean
		@echo
		${RM} ${OBJS}
		@echo "$(CEND)"
		@echo "$(CGREEN)Deleting done !$(CEND)"
		@echo
		@echo

fclean:		clean
		@echo "$(CYELLOW)Deleting .o files, libft.a and ft_nm$(CEND)"
		@echo "$(CGREY)"
		${RM} ${FT_NM} ./inc/libft/libft.a
		@echo "$(CEND)"
		@echo "$(CGREEN)Deleting done !$(CEND)"
		@echo
		@echo

re: 		fclean all

c: 		all clean

.PHONY: 	clean fclean all re
