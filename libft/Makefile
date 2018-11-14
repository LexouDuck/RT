NAME	=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O2 -MMD

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

DIR_MEMORY	:=	memory/
SRC_MEMORY	:=	ft_memalloc.c	\
				ft_memset.c		\
				ft_memdel.c		\
				ft_memcpy.c		\
				ft_memdup.c		\
				ft_memmove.c	\
				ft_memcmp.c		\
				ft_memchr.c		\
				ft_swap.c		\
				ft_getbits.c	

DIR_STRING	:=	string/
SRC_STRING	:=	ft_strnew.c		\
				ft_strset.c		\
				ft_strclr.c		\
				ft_strdel.c		\
				ft_strdup.c		\
				ft_strcpy.c		\
				ft_strcat.c		\
				ft_strlen.c		

DIR_CHAR	:=	char/
SRC_CHAR	:=	ft_isalpha.c	\
				ft_isdigit.c	\
				ft_isprint.c	\
				ft_to.c	

DIR_CONVERT	:=	convert/
SRC_CONVERT	:=	

DIR_MATH	:=	math/
SRC_MATH	:=	

DIR_LIST	:=	list/
SRC_LIST	:=	

DIR_IO		:=	io/
SRC_IO		:=	ft_output.c		\
				ft_write.c		\
				ft_read.c		\
				ft_getnextline.c

SRCDIR	=	./src/
OBJDIR	=	./obj/

HDRS	=	libft_memory.h	\
			libft_string.h	\
			libft_char.h	\
			libft_convert.h	\
			libft_math.h	\
			libft_list.h	\
			libft_io.h		\
			libft.h			
SRCS	=	$(addprefix $(DIR_MEMORY),	$(SRC_MEMORY)	)	\
			$(addprefix $(DIR_STRING),	$(SRC_STRING)	)	\
			$(addprefix $(DIR_CHAR),	$(SRC_CHAR)		)	\
			$(addprefix $(DIR_CONVERT),	$(SRC_CONVERT)	)	\
			$(addprefix $(DIR_MATH),	$(SRC_MATH)		)	\
			$(addprefix $(DIR_LIST),	$(SRC_LIST)		)	\
			$(addprefix $(DIR_IO),		$(SRC_IO)		)

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
	@mkdir -p $(OBJDIR)$(DIR_CONVERT)
	@mkdir -p $(OBJDIR)$(DIR_MATH)
	@mkdir -p $(OBJDIR)$(DIR_LIST)
	@mkdir -p $(OBJDIR)$(DIR_IO)

clean:
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@printf "Deleting library file: "$(NAME)"\n"
	@rm -f $(NAME)

rclean:
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)

tclean:
	@printf "Deleting libft test...\n"
	@rm -f test
	@rm -f test.exe*

re: fclean all

replace:
	@sed -i -e "s|$(old)|$(new)|g" $(addprefix $(SRCDIR), $(SRCS))
	@printf "Replaced all instances of \'"$(old)"\' with \'"$(new)"\'.\n"

rename:
	@sed -i -e "s|\<$(old)\>|$(new)|g" $(addprefix $(SRCDIR), $(SRCS))
	@printf "Renamed all words matching \'"$(old)"\' as \'"$(new)"\'.\n"

TESTS :=	test_memory.c	\
			test_string.c	\
			test_char.c		\
			test_convert.c	\
			test_math.c		\
			test_list.c		\
			test_io.c		\
			test.c			\
			util_test.c

testprogram: all
	@$(CC) -o test $(addprefix $(SRCDIR), $(TESTS)) $(NAME)

test: testprogram
	@./test

test_memory: testprogram
	@./test -memory

test_string: testprogram
	@./test -string

test_char: testprogram
	@./test -char

test_convert: testprogram
	@./test -convert

test_math: testprogram
	@./test -math

test_list: testprogram
	@./test -list

test_io: testprogram
	@./test -io

-include ${DEPENDS}
