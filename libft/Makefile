NAME	=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O2 -MMD

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

DIR_MEMORY	:=	memory/
SRC_MEMORY	:=	

DIR_STRING	:=	string/
SRC_STRING	:=	FT_StringLength.c	

DIR_CHAR	:=	char/
SRC_CHAR	:=	FT_Is.c		\
				FT_To.c

DIR_IO		:=	io/
SRC_IO		:=	FT_Write.c		\
				FT_Output.c

DIR_LIST	:=	list/
SRC_LIST	:=	

DIR_CONVERT	:=	convert/
SRC_CONVERT	:=	

DIR_MATH	:=	math/
SRC_MATH	:=	

SRCDIR	=	./src/
OBJDIR	=	./obj/

HDRS	=	libft_memory.h	\
			libft_string.h	\
			libft_char.h	\
			libft_io.h		\
			libft_list.h	\
			libft_convert.h	\
			libft_math.h	\
			libft.h			
SRCS	=	$(addprefix $(DIR_MEMORY),	$(SRC_MEMORY)	)	\
			$(addprefix $(DIR_STRING),	$(SRC_STRING)	)	\
			$(addprefix $(DIR_CHAR),	$(SRC_CHAR)		)	\
			$(addprefix $(DIR_IO),		$(SRC_IO)		)	\
			$(addprefix $(DIR_LIST),	$(SRC_LIST)		)	\
			$(addprefix $(DIR_CONVERT),	$(SRC_CONVERT)	)	\
			$(addprefix $(DIR_MATH),	$(SRC_MATH)		)

OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}

all: $(NAME)

$(OBJS): | objdir

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDRS)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@ -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

objdir:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)$(DIR_MEMORY)
	@mkdir -p $(OBJDIR)$(DIR_STRING)
	@mkdir -p $(OBJDIR)$(DIR_CHAR)
	@mkdir -p $(OBJDIR)$(DIR_IO)
	@mkdir -p $(OBJDIR)$(DIR_LIST)
	@mkdir -p $(OBJDIR)$(DIR_CONVERT)
	@mkdir -p $(OBJDIR)$(DIR_MATH)

clean:
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

rclean:
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "Deleting library file: "$(NAME)"\n"
	@rm -f $(NAME)

re: fclean all

test: all
	$(CC) -o test test.c $(NAME) && ./test

test_io: all
	$(CC) -o test test_io.c $(NAME) && ./test

-include ${DEPENDS}
