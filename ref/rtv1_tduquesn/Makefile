# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2019/01/21 18:03:22 by fulguritu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	rtv1
LFT		:=	libft.a


PLATFORM:=	MACOS
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra -O3 -Wno-unused-result

ifeq ($(PLATFORM),LINUX)
DBFLAGS =	-fsanitize=address
LIBASAN =	-lasan
LOC_LX	=	/usr/lib/x86_64-linux-gnu/
LIB_SUFF=	_Linux
LOC_LMLX=	../
LIBS	=	$(LIBASAN) -lm -L$(LOC_LMLX) -lmlx$(LIB_SUFF) -L$(LFTDIR) -lft -L$(LOC_LX) -lX11 -lXext
else
DBFLAGS =
LIBASAN =
LOC_LX	=	/usr/X11/lib
LIB_SUFF=
LOC_LMLX=	../../other_src/ #remove at 42
LIBS	=	-L$(LOC_LMLX) -lmlx -framework OpenGL -framework AppKit -L$(LFTDIR) -lft
endif


HDRDIR	:=	./hdr/
LFTDIR	:=	./libft/
TSTDIR	:=	./tests/
SRCDIR	:=	./src/
OBJDIR  :=	./obj/

HDRS_	:=	$(NAME).h			\
			ft_integral.h ft_stat.h ft_random.h
SRCS_	:=	camera.c			\
			coordinates.c		\
			event_key.c			\
			image_utils.c		\
			reader.c			\
			reader_utils.c		\
			objects.c			\
			rays.c				\
			ray_utils.c			\
			primitive_utils.c	\
			primitives_2d.c		\
			sphere.c			\
			cylinder.c			\
			cone.c				\
			cube.c				\
			paraboloid.c		\
			shader.c			\
			render.c			\
			tracers.c			\
			samplers.c			\
			vec3_utils.c		\
			ft_stat.c ft_random.c ft_integral.c ft_stat_nblst_utils.c ft_prob.c\

MAIN	:=	main_$(NAME).c
MAINO	:=	$(MAIN:.c=.o)

OBJS_	:=	$(SRCS_:.c=.o)

SRCS	:=	$(addprefix $(SRCDIR),$(SRCS_))
HDRS	:=	$(addprefix $(HDRDIR),$(HDRS_))
OBJS	:=	$(addprefix $(OBJDIR),$(OBJS_))

#TST_DIR		:=	unit_tests
#TST_MAIN	:=	$(TST_DIR)/unit_tests.c
#TST_EXEC	:=	test.out

RESET	:=	"\033[0m"
RED		:=	"\033[0;31m"
GREEN	:=	"\033[0;32m"

$(NAME):$(LFTDIR)$(LFT) $(OBJS) $(OBJDIR)$(MAINO) $(HDRS)
	@echo "Compiling software: "$@" -> \c"$(RED)
	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(OBJDIR)$(MAINO) $(LIBS) -I$(HDRDIR) -o $@
	@echo $(GREEN)"OK!"$(RESET)

$(OBJS):

$(OBJDIR)%.o:$(SRCDIR)%.c $(HDRS)
	@echo $@"-> \c"
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -o $@
	@echo $(GREEN)"OK!"$(RESET)

#dependencies are taken care of in libft's makefile.
$(LFTDIR)$(LFT):
	@rm -f $@
	$(MAKE) -C $(LFTDIR) $(LFT)

all: $(NAME)

clean:
	@rm -f $(OBJS)

fclean:clean
	$(MAKE) -C $(LFTDIR) fclean
	@rm -f $(NAME)

re:fclean all

#test:$(LFTDIR)$(LFT) $(OBJS) $(HDRS)
#	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(TST_MAIN) $(LIBS) -o $(TST_EXEC)
#	./$(TST_EXEC)
#	@rm -f $(TST_MAIN:.c=.o) $(TST_EXEC)

mf_debug:
	@cat -e -t -v Makefile

.PHONY: all clean re test vlqtest capstest
