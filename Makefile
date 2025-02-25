GREEN=\033[0;32m
NC=\033[0m

NAME     = pipex

CC       = cc
CFLAGS   = -Wall -Wextra -Werror

SRCSDIR      = srcs/
LIBFTDIR     = includes/libft/
BONUSDIR	 = bonus/

LIBFT        = $(LIBFTDIR)libft.a

SRCS    =  $(SRCSDIR)pipex.c				   \
			$(SRCSDIR)parcing.c 			  	\
			$(SRCSDIR)pipex_utils.c          	 \
			$(SRCSDIR)error_utils.c			 	  \
			$(SRCSDIR)list_utils.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus:
	@make -C $(BONUSDIR)

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Pipex compiled$(NC)"

%.o: %.c includes/pipex.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFTDIR)
	@rm -f $(OBJS)
	@make clean -C $(BONUSDIR)
	@echo "$(GREEN)Object files cleaned$(NC)"

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -f $(NAME)
	@make fclean -C $(BONUSDIR)
	@echo "$(GREEN)All cleaned$(NC)"

re: fclean all


.PHONY: clean bonus