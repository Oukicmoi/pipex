# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 16:45:54 by gtraiman          #+#    #+#              #
#    Updated: 2024/07/11 19:15:57 by gtraiman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = pipex
AR            = ar rcs
CC            = cc 
CFLAGS        = -Werror -Wall -Wextra -I .

PATH_LIBFT = libft
LIBFT = ${PATH_LIBFT}/libft.a

SRCS	=	parsing.c \
		pipex.c \
        	


OBJS_FILES = ${SRCS:.c=.o}


all: ${LIBFT} ${NAME} 

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS_FILES}
	$(CC) $(OBJS_FILES) -o $(NAME) -L ${PATH_LIBFT} -lft
    

${LIBFT}:
	${MAKE} -C ${PATH_LIBFT}

clean:
	rm -f ${OBJS_FILES}
	${MAKE} -C  ${PATH_LIBFT} clean


fclean: clean
	rm -f ${NAME}
	${MAKE} -C ${PATH_LIBFT} fclean 

re: fclean all

.PHONY: all clean fclean re