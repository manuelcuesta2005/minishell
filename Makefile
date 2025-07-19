# **************************************************************************** #
#                              MAKEFILE PARA MINISHELL                         #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

LIBS        = -lreadline

SRCDIR      = src
OBJDIR      = obj
INCDIR      = include
LIBDIR      = libft

SRC         = $(shell find $(SRCDIR) -name '*.c')
OBJ         = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

LIBFT       = $(LIBDIR)/libft.a

INC_FLAGS   = -I$(INCDIR) -I$(LIBDIR)

GREEN       = \033[0;32m
NC          = \033[0m

# ****************************************************** #

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compilando $(NAME)...$(NC)"
	$(CC) $(CFLAGS) $(INC_FLAGS) $^ -o $@ $(LIBFT) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Compilando libft...$(NC)"
	@$(MAKE) -C $(LIBDIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBDIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBDIR)

re: fclean all

.PHONY: all clean fclean re
