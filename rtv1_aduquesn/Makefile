NAME	=	rtv1

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O3 -MMD

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

ifeq ($(OS),Windows_NT)
	LIBMLX = $(LIBMLX_WIN)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LIBMLX = $(LIBMLX_LIN)
	endif
	ifeq ($(UNAME_S),Darwin)
		LIBMLX = $(LIBMLX_MAC)
	endif
endif

LIBS	=	$(LIBFT) $(LIBMATH) $(LIBMLX)

LIBFT		=	-L$(LFTDIR) -lft
LIBMATH		=	-lm
LMLX_PATH	=	/usr/lib/
LMLX_SUFFIX	=	
XWIN_PATH	=	/usr/include/X11/
LIBMLX_MAC	=	-lmlx -framework OpenGL -framework AppKit
LIBMLX_WIN	=	-L$(LMLX_PATH) -I$(XWIN_PATH) -lmlx -lX11.dll -lXext.dll
LIBMLX_LIN	=	-L$(LMLX_PATH) -lmlx$(LMLX_SUFFIX) -L$(XWIN_PATH) -lX11 -lXext
OPENCL		=	-lopencl

SRCDIR	=	./src/
OBJDIR	=	./obj/
LFTDIR	=	./libft/

HDRS	=	rtv1.h				\
			$(LFTDIR)libft.h
SRCS	= 	color.c				\
			vector.c			\
			vector_op.c			\
			matrix.c			\
			camera.c			\
			event.c				\
			shader.c			\
			render.c			\
			render_util.c		\
			rt_sphere.c			\
			rt_cylinder.c		\
			rt_cube.c			\
			rt_cone.c			\
			read_util.c			\
			read.c				\
			main.c

OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}
DEPENDS	=	${OBJS:.o=.d}

all: libraries $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling program: "$@" -> "
	@$(CC) $(OBJS) $(CFLAGS) -o $@ $(LIBS)
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@ -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

libraries:
	@make -C $(LFTDIR) all

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: "$(NAME)"\n"
	@rm -f $(NAME)

re: fclean all

-include ${DEPENDS}
