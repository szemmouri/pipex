GREEN=\033[0;32m
NC=\033[0m

NAME     = ../pipex

CC       = cc
CFLAGS   = -Wall -Wextra -Werror

SRCSDIR      = srcs/
GNLDIR       = lib/get_next_line/
LIBFTDIR     = lib/libft/

LIBFT        = $(LIBFTDIR)libft.a

SRCS    =   $(GNLDIR)get_next_line_utils.c    \
            $(GNLDIR)get_next_line.c           \
            $(SRCSDIR)pipex_bonus.c		   		\
			$(SRCSDIR)parcing_bonus.c 		  	 \
			$(SRCSDIR)pipex_utils_bonus.c         \
			$(SRCSDIR)error_utils_bonus.c	       \
			$(SRCSDIR)list_utils_bonus.c			\
			$(SRCSDIR)here_doc_bonus.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Bonus compiled$(NC)"

%.o: %.c includes/pipex_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFTDIR)
	@rm -f $(OBJS)
	@echo "$(GREEN)Bonus Object files cleaned$(NC)"

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -f $(NAME)
	@echo "$(GREEN)All Bonus cleaned$(NC)"

re: clean fclean all


.PHONY: clean