NAME	=	libft.a

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	./src/
OBJDIR	=	./obj/

HDRS	=	get_next_line.h		\
			libft.h
SRCS	=	ft_memalloc.c		\
			ft_memdel.c			\
			ft_bzero.c			\
			ft_memset.c			\
			ft_memcpy.c			\
			ft_memccpy.c		\
			ft_memmove.c		\
			ft_memsub.c			\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_swap.c			\
			ft_getbits.c		\
			ft_atoi.c			\
			ft_atoi_hex.c		\
			ft_atoi_base.c		\
			ft_atof.c			\
			ft_itoa.c			\
			ft_itoa_hex.c		\
			ft_itoa_base.c		\
			ft_ftoa.c			\
			ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isascii.c		\
			ft_isprint.c		\
			ft_isspace.c		\
			ft_toupper.c		\
			ft_tolower.c		\
			ft_strlen.c			\
			ft_strnew.c			\
			ft_strdel.c			\
			ft_strclr.c			\
			ft_strdup.c			\
			ft_strrev.c			\
			ft_strcpy.c			\
			ft_strncpy.c		\
			ft_strlcpy.c		\
			ft_strcat.c			\
			ft_strncat.c		\
			ft_strlcat.c		\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_strstr.c			\
			ft_strnstr.c		\
			ft_strcmp.c			\
			ft_strncmp.c		\
			ft_strequ.c			\
			ft_strnequ.c		\
			ft_striter.c		\
			ft_striteri.c		\
			ft_strmap.c			\
			ft_strmapi.c		\
			ft_strpad.c			\
			ft_strpad_l.c		\
			ft_strpad_r.c		\
			ft_strsub.c			\
			ft_strjoin.c		\
			ft_strtrim.c		\
			ft_strsplit.c		\
			ft_strrep_char.c	\
			ft_strrep_charset.c	\
			ft_strrep_string.c	\
			ft_putchar.c		\
			ft_putstr.c			\
			ft_putendl.c		\
			ft_putnbr.c			\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_lstnew.c			\
			ft_lstadd.c			\
			ft_lstappend.c		\
			ft_lstdelone.c		\
			ft_lstdel.c			\
			ft_lstsize.c		\
			ft_lstiter.c		\
			ft_lstmap.c			\
			ft_lstget.c			\
			ft_lstsub.c			\
			ft_array_fixed.c	\
			ft_array.c			\
			../get_next_line.c

OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling library: "$@" -> "
	@ar -rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@printf "Compiling file: "$@" -> "
	@$(CC) -c $< $(CFLAGS) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

clean:
	@echo "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@echo "Deleting library file: "$(NAME)"\n"
	@rm -f $(NAME)

re: fclean all

test: all
	$(CC) -w -o main main_atoi.c $(NAME) && ./main
	$(CC) -w -o main main.c $(NAME) && ./main
