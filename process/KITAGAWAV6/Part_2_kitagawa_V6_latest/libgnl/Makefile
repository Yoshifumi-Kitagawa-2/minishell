NAME = libgnl.a

SRCDIR = ./
SRCS = get_next_line.c get_next_line_utils.c

CFLAGS = -Wall -Wextra -Werror
CC = cc

OBJDIR = ./obj/
OBJS = $(SRCS:%.c=$(OBJDIR)%.o)

all : $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p obj

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):	$(OBJS)
		ar rcs $@ $^

clean :
	rm -rf $(OBJDIR)

fclean : 
	rm -f $(NAME)
	rm -rf $(OBJDIR)

re : fclean all

.PHONY: all clean fclean re