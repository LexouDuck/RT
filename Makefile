NAME	=	RT

# Compiler
CC	= _
CC_WIN	= x86_64-w64-mingw32-gcc
CC_LIN	= gcc
CC_MAC	= gcc

CFLAGS	=	-Wall -Wextra $(CFLAGS_PLATFORM) -O2 -MMD
CFLAGS_PLATFORM = _
CFLAGS_WIN	= -mwindows
CFLAGS_LIN	= 
CFLAGS_MAC	= 

# Libraries
LIBS		=	$(LIBFT) $(LIBSDL)

OPENCL		=	-lopencl
LIBFT		=	-L$(LFTDIR) -lft -I$(LFTDIR)
LIBSDL		=	-L$(SDLDIR) -lSDL2 -I$(SDLHDRS)

# Directories that this Makefile will use
SRCDIR	=	./src/
OBJDIR	=	./obj/
INCDIR	=	./inc/
LFTDIR	=	./libft/
SDLDIR	=	./
SDLHDRS	=	./SDL2-2.0.9/include/

# Set platform-specific variables
ifeq ($(OS),Windows_NT)
	CC := $(CC_WIN)
	CFLAGS_PLATFORM := $(CFLAGS_WIN)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC := $(CC_LIN)
		CFLAGS_PLATFORM := $(CFLAGS_LIN)
	endif
	ifeq ($(UNAME_S),Darwin)
		CC := $(CC_MAC)
		CFLAGS_PLATFORM := $(CFLAGS_MAC)
	endif
endif



# List of C header files
HDRS	=	$(LFTDIR)libft.h 	\
			rt.h				\
			$(SRCDIR)debug.h	\
			$(SRCDIR)config.h	\

# List of C source code files
SRCS	= 	main.c				\
			init.c				\
			debug.c				\
			config.c			\
			config_ini.c		\
			config_access.c		\
			event.c				\
			event_window.c		\
			render.c			\



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
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

objdir:
	@mkdir -p $(OBJDIR)

libraries:
	@make -C $(LFTDIR) all

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)
	@rm -f assets.o

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
