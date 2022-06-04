SRCS		=	ft_atoi.c					\
				ft_itoa.c					\
				ft_split.c					\
				ft_strjoin.c				\
				ft_strlen.c					\
				get_next_line_utils.c		\
				get_next_line.c				\
				main.c						\
				my_brush_helper.c			\
				my_brush_helper2.c			\
				my_brush_helper3.c			\
				my_brush.c					\
				my_colors.c					\
				my_main_helper.c			\
				my_mesh_helper.c			\
				my_mesh.c					\
				my_perspective.c			\
				my_transform_helper.c		\
				my_transform.c
OBJS		= ${SRCS:.c=.o}
DEPS		= ${SRCS:.c=.d}
NAME		= fdf
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
DEPFLAGS	= -MMD -MF ${<:.c=.d}
RM			= rm -f

all:		${NAME}

$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS}  -lmlx -framework OpenGL -framework AppKit

-include ${DEPS}

%.o:		%.c
			${CC} ${CFLAGS} -c $< ${DEPFLAGS}

clean:
			${RM} ${OBJS} ${DEPS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
