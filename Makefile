NAME	=	RT

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O3 -MMD

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

LIBS	=	$(LIBMATH) $(LIBFT) $(LIBSDL)

OPENCL		=	-lopencl
LIBMATH		=	-lm
LIBFT		=	-L$(LFTDIR) -lft
LIBSDL		=	-L$(SDLDIR) -lSDL2
SDLDIR		=	./SDL2-2.0.9/

#SDL			=	_
#SDL_WIN		=	./SDL2/SDL2-win/
#SDL_MAC		=	./SDL2/SDL2-mac/
#SDL_LIN		=	./SDL2/SDL2-lin/
#
#ifeq ($(OS),Windows_NT)
#	SDL := $(SDL_WIN)
#else
#	UNAME_S := $(shell uname -s)
#	ifeq ($(UNAME_S),Linux)
#		SDL := $(SDL_LIN)
#	endif
#	ifeq ($(UNAME_S),Darwin)
#		SDL := $(SDL_MAC)
#	endif
#endif

SRCDIR	=	./src/
OBJDIR	=	./obj/
LFTDIR	=	./libft/

HDRS	=	rt.h				\
			$(LFTDIR)libft.h
SRCS	= 	main.c

OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}
DEPENDS	=	${OBJS:.o=.d}

all: libraries $(NAME)

$(OBJS): | objdir

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling program: "$@" -> "
	@$(CC) $(OBJS) $(CFLAGS) -o $@ $(LIBS)
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDRS)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@ -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

objdir:
	@mkdir -p $(OBJDIR)

libraries:
	@make -C $(LFTDIR) all
#	@make -C $(SDL) native

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

rclean:
	@make -C $(LFTDIR) rclean
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: "$(NAME)"\n"
	@rm -f $(NAME)

re: fclean all

-include ${DEPENDS}
