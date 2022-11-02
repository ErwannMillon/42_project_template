SRCS := main.c \
		initialization.c \
		actions.c\
		philo_utils.c \
		philo_routine.c\
		checker.c\
		ft_atoi.c\
		pthread_utils.c\
		error_handling.c

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
	gcc -g $(CFLAGS) -I$(INCLUDEDIR) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJS)
	gcc -g $(OBJS) $(CFLAGS) -o $(NAME) 
$(LIBFTDIR)/libft.a:
	git submodule update --remote
	$(MAKE) -C $(LIBFTDIR)
test: $(LIBFTDIR)/libft.a $(OBJS)
	gcc -fsanitize=address $(OBJS) -o test_$(NAME) $(LIBFTDIR)/libft.a
asan: $(OBJS)
	gcc -fsanitize=address $(OBJS) -o $(NAME) 
git:
	git add $(SRCSPREFIX) Makefile $(INCLUDEDIR) .gitmodules
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean $(NAME)

.PHONY:	all clean fclean re 
