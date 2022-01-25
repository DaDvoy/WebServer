SRCS		= main.cpp Request.cpp

SRCS_DIR	= ./src/

OBJS		= ${addprefix ${SRCS_DIR}, ${SRCS:.cpp=.o}}

NAME		= gulugulu


CC = clang++
RM = rm -f

CFLAGS		= -Wall -Wextra -Werror

# COLORS

GREEN	= \033[0;32m
YELO	= \033[0;33m
BLUE	= \033[0;34m
NEW		= \033[0;35m
SHALLOW = \033[0m

# END COLORS

.PHONY: all clean fclean re

all:		${NAME}

%.o:%.cpp		
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}


${NAME}:	${OBJS} 
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}
			@echo "${GREEN}${NAME} compile!${SHALLOW}"

clean:		
			@${RM} ${OBJS}
			@echo "${BLUE}clean done!${SHALLOW}"

fclean:		
			@${RM} ${OBJS} ${NAME} ${B_NAME}
			@echo "${YELO}fclean done!${SHALLOW}"

re:			fclean all
