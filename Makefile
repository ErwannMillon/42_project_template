SRCS := main.c \
		input_parse.c \
		list_utils.c \
		stack_operations.c \
		lis_algo.c \
		lis_algo2.c \
		cleanup_functions.c \
		list_search.c \
		num_utils.c \
		move_operations.c \
		path_find_from_b.c \
		move_unsorted_to_b.c
NAME = push_swap
CFLAGS = -Wall -Wextra -Werror
INCLUDEDIR = ./headers
SRCDIR = ./srcs
ASAN = -fsanitize=address -g
LIBFTDIR = $(SRCDIR)/libftextended
LIBFTINCLUDES = $(LIBFTDIR)/headers
SRCSPREFIX = $(addprefix $(SRCDIR)/, $(SRCS))
OBJS := $(SRCSPREFIX:%.c=%.o)
#ADD CFLAGS!!!

%.o: %.c
	gcc -ggdb3 -I$(INCLUDEDIR) -I$(LIBFTINCLUDES) -c $< -o $@
all: $(NAME)
$(NAME): $(LIBFTDIR)/libft.a $(OBJS)
	gcc -ggdb3 $(OBJS) $(CFLAGS) -o $(NAME) $(LIBFTDIR)/libft.a
$(LIBFTDIR)/libft.a:
	$(MAKE) -C $(LIBFTDIR)
test: $(LIBFTDIR)/libft.a $(OBJS)
	gcc -fsanitize=address $(OBJS) -o test_$(NAME) $(LIBFTDIR)/libft.a
asan: $(LIBFTDIR)/libft.a $(OBJS)
	gcc -fsanitize=address $(OBJS) -o $(NAME) $(LIBFTDIR)/libft.a
git:
	git add $(SRCSPREFIX) Makefile $(INCLUDEDIR) .gitmodules
clean:
	$(MAKE) -C $(LIBFTDIR)/ clean
	rm -f $(OBJS)
fclean: clean
	$(MAKE) -C $(LIBFTDIR)/ fclean
	rm -f $(NAME)
re: fclean $(NAME)

.PHONY:	all clean fclean re 
