NAME	=	RT

# Linker
LD	= _
LD_WIN	= x86_64-w64-mingw32-ld
LD_LIN	= ld
LD_MAC	= ld

# Compiler
CC	= _
CC_WIN	= x86_64-w64-mingw32-gcc
CC_LIN	= gcc
CC_MAC	= gcc

# Compiler flags
CFLAGS	=	-Wall -Wextra $(CFLAGS_PLATFORM) -O2 -MMD
CFLAGS_PLATFORM = _
CFLAGS_WIN	= -mwindows
CFLAGS_LIN	= 
CFLAGS_MAC	= 

# Libraries
LIBS		=	$(LIBFT) $(LIBSDL)
INCLUDE_DIRS =  -I$(LFTDIR) -I$(SDLHDRS)

OPENCL		=	-lopencl
LIBFT		=	-L$(LFTDIR) -lft
LIBSDL		= _
LIBSDL_WIN	= -L$(SDLDIR) -lSDL2
LIBSDL_WIN	= -L$(SDLDIR) -lSDL2
LIBSDL_MAC	= -L./SDL2.framework/Versions/Current -F. -framework SDL2

# Directories that this Makefile will use
SRCDIR	=	./src/
OBJDIR	=	./obj/
INCDIR	=	./inc/
LFTDIR	=	./libft/
SDLDIR	=	./
SDLHDRS	=	./SDL2-2.0.9/include/

# Set platform-specific variables
ifeq ($(OS),Windows_NT)
	OSFLAG := "WIN"
	CC := $(CC_WIN)
	LD := $(LD_WIN)
	LIBSDL := $(LIBSDL_WIN)
	CFLAGS_PLATFORM := $(CFLAGS_WIN)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG := "LIN"
		CC := $(CC_LIN)
		LD := $(LD_LIN)
		LIBSDL := $(LIBSDL_LIN)
		CFLAGS_PLATFORM := $(CFLAGS_LIN)
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG := "MAC"
		CC := $(CC_MAC)
		LD := $(LD_MAC)
		LIBSDL := $(LIBSDL_MAC)
		CFLAGS_PLATFORM := $(CFLAGS_MAC)
	endif
endif



# List of C header files
HDRS	=	$(LFTDIR)libft.h 	\
			rt.h				\
			assets.h			\
			$(SRCDIR)debug.h	\
			$(SRCDIR)config.h	\
			$(SRCDIR)ui.h		\

# List of C source code files
SRCS	= 	main.c				\
			init.c				\
			debug.c				\
			config.c			\
			config_ini.c		\
			config_access.c		\
			event.c				\
			event_window.c		\
			ui.c				\
			render_ui.c			\
			render.c			\

# List of asset files to be embedded within the program
INCS	=	ui.chr



# define colors for terminal output
RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

# define object list and dependency files (.d)
OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}
DEPENDS	=	${OBJS:.o=.d}



all: libraries $(NAME)

$(OBJS): | objdir

$(NAME): $(OBJS) $(HDRS) assets.o
	@printf "Compiling program: "$@" -> "
	@$(CC) $(CFLAGS) $(OBJS) assets.o -o $@ $(LIBS)
	@if [ $(OSFLAG) = "MAC" ]; then install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @executable_path/SDL2.framework/Versions/A/SDL2 RT; fi
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDRS)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS) -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

ASSET_FILES	=	$(addprefix $(INCDIR),$(INCS))

assets.o : $(ASSET_FILES)
	@printf "Compiling assets: "$@" -> "
	@$(LD) -r -b binary -o assets.o $(ASSET_FILES)
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



replace:
	@sed -i -e "s|$(old)|$(new)|g" $(addprefix $(SRCDIR), $(SRCS)) $(addprefix $(HDRDIR), $(HDRS))
	@printf "Replaced all instances of \'"$(old)"\' with \'"$(new)"\'.\n"

rename:
	@sed -i -e "s|\<$(old)\>|$(new)|g" $(addprefix $(SRCDIR), $(SRCS)) $(addprefix $(HDRDIR), $(HDRS))
	@printf "Renamed all words matching \'"$(old)"\' with \'"$(new)"\'.\n"



PREPROCESSED	=	${SRCS:%.c=$(OBJDIR)%.c}

preprocessed: $(PREPROCESSED)
	@printf "Outputting preprocessed code...\n"

$(OBJDIR)%.c : $(SRCDIR)%.c $(HDRS)
	@printf "Preprocessing file: "$@" -> "
	@$(CC) $(CFLAGS) -E $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

-include ${DEPENDS}
