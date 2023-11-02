NAME := philosophers

HEADERS:= philosophers.h

ERRFLAGS:= -Wall -Werror -Wextra
FLAGS:= -g -O0
SRCS:= src/printing.c src/gettime.c src/exit_handler.c src/philo_behaviour.c src/init.c src/checker.c src/cleanup.c src/create_table.c src/ft_atoi.c 

MAIN:= main.c

OBJDIR:= obj
MAIN_OBJ:= $(MAIN:%.c=$(OBJDIR)/%.o)
SRCS_OBJS:= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

ALLFLAGS:= $(ERRFLAGS) $(FLAGS)

$(NAME): $(SRCS_OBJS) $(MAIN_OBJ) $(LIBFB_OBJS)  $(HEADERS)
	@echo "compiling $@"
	@cc $(ALLFLAGS) $(SRCS_OBJS) $(MAIN_OBJ) -pthread -o $@

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "creating $@"
	@gcc -c $(ALLFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re:fclean all

.PHONY:all clean fclean re
