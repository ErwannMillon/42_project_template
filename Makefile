SRCS := main.c \
		initialization.c \
		actions.c\
		philo_utils.c \
		philo_routine.c\
		checker.c

NAME = philo
CFLAGS = -Wall -Wextra -Werror
INCLUDEDIR = ./headers
SRCDIR = ./srcs
ASAN = -fsanitize=address -g
LIBFTDIR = $(SRCDIR)/libftextended
LFTINCLUDES = $(LIBFTDIR)/headers
SRCSPREFIX = $(addprefix $(SRCDIR)/, $(SRCS))
OBJS := $(SRCSPREFIX:%.c=%.o)
#ADD CFLAGS!!!

%.o: %.c
	gcc -g -I$(INCLUDEDIR) -I$(LFTINCLUDES) -c $< -o $@
all: $(NAME)
$(NAME): $(LIBFTDIR)/libft.a $(OBJS)
	gcc -g $(OBJS) $(CFLAGS) -o $(NAME) $(LIBFTDIR)/libft.a
$(LIBFTDIR)/libft.a:
	git submodule update --remote
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
