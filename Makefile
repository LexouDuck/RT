NAME	=	RT

CC		= _
CC_WIN	= gcc
CC_LIN	= gcc
CC_MAC	= gcc

CFLAGS	=	-Wall -Wextra -Werror $(CFLAGS_WIN) -O3 -MMD
CFLAGS_PLATFORM = _
CFLAGS_WIN	= 
CFLAGS_LIN	= 
CFLAGS_MAC	= 

LIBS	=	$(LIBFT) $(LIBSDL)

OPENCL		=	-lopencl
LIBFT		=	-L$(LFTDIR) -lft
LIBSDL		=	-L$(SDLDIR) -lSDL2

SRCDIR	=	./src/
OBJDIR	=	./obj/
INCDIR	=	./inc/
LFTDIR	=	./libft/
SDLDIR	=	./
#SDLDIR_PLATFORM = _
#SDLDIR_WIN		=	./SDL2/SDL2-win/
#SDLDIR_MAC		=	./SDL2/SDL2-mac/
#SDLDIR_LIN		=	./SDL2/SDL2-lin/

ifeq ($(OS),Windows_NT)
	CC := $(CC_WIN)
	CFLAGS_PLATFORM := $(CFLAGS_WIN)
	SDLDIR_PLATFORM := $(SDLDIR_WIN)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC := $(CC_LIN)
		CFLAGS_PLATFORM := $(CFLAGS_LIN)
		SDLDIR_PLATFORM := $(SDLDIR_LIN)
	endif
	ifeq ($(UNAME_S),Darwin)
		CC := $(CC_MAC)
		CFLAGS_PLATFORM := $(CFLAGS_MAC)
		SDLDIR_PLATFORM := $(SDLDIR_MAC)
	endif
endif

HDRS	=	rt.h				\
			$(LFTDIR)libft.h

SRCS	= 	main.c

# define colors for terminal output
RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

# define object list and dependency files (.d)
OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}
DEPENDS	=	${OBJS:.o=.d}



all: libraries $(NAME)

$(OBJS): | objdir

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling program: "$@" -> "
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
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

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: "$(NAME)"\n"
	@rm -f $(NAME)

rclean:
	@make -C $(LFTDIR) rclean
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)

re: fclean all



PREPROCESSED	=	${SRCS:%.c=$(OBJDIR)%.c}

preprocessed: $(PREPROCESSED)
	@printf "Outputting preprocessed code...\n"

$(OBJDIR)%.c : $(SRCDIR)%.c $(HDRS)
	@printf "Preprocessing file: "$@" -> "
	@$(CC) $(CFLAGS) -E $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

-include ${DEPENDS}
