SRCNAME	=	ft_atoi.c			\
			ft_bzero.c			\
			ft_calloc.c			\
			ft_isalnum.c		\
			ft_isalpha.c		\
			ft_isascii.c		\
			ft_isdigit.c		\
			ft_isprint.c		\
			ft_itoa.c			\
			ft_memccpy.c		\
			ft_memcpy.c			\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_memmove.c		\
			ft_memset.c			\
			ft_printf.c			\
			ft_putchar_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_putstr_fd.c		\
			ft_split.c			\
			ft_strchr.c			\
			ft_strcmp.c			\
			ft_strdup.c			\
			ft_strjoin.c		\
			ft_strlcat.c		\
			ft_strlcpy.c		\
			ft_strlen.c			\
			ft_strmapi.c		\
			ft_strncmp.c		\
			ft_strnstr.c		\
			ft_strrchr.c		\
			ft_strtrim.c		\
			ft_substr.c			\
			ft_tolower.c		\
			ft_toupper.c		\
			#ft_strcmp_skipchar.c

BSRC	=	ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstlast.c		\
			ft_lstnew.c			\
			ft_lstsize.c		\

SRCS	= ${SRCNAME}

OBJS	= ${SRCS:.c=.o}
BOBJ	= ${BSRC:.c=.o}

NAME	= libft.a

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}

bonus:		${OBJS} ${BOBJ}
			ar rc ${NAME} ${OBJS} ${BOBJ}

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJ}

fclean:		clean
			${RM} ${NAME}
			${RM} a.out

re:			fclean all

.PHONY:		all clean fclean re
