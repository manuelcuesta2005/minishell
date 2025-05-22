# **************************************************************************** #
#                              MAKEFILE PARA MINISHELL                         #
# **************************************************************************** #

# Nombre del ejecutable
NAME = minishell

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Librerías externas
LIBS = -lreadline

# Directorios
SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBDIR = libft

# Archivos fuente
SRC = $(shell find $(SRCDIR) -name '*.c')
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Libft
LIBFT = $(LIBDIR)/libft.a
LIBFT_INC = -I$(LIBDIR)

# Colores
GREEN = \033[0;32m
NC = \033[0m

# ****************************************************** #

all: $(LIBFT) $(NAME)

# Compilar minishell
$(NAME): $(OBJ)
	@echo "$(GREEN)Compilando $(NAME)...$(NC)"
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFT_INC) $^ -o $@ $(LIBFT) $(LIBS)

# Compilar objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFT_INC) -c $< -o $@

# Compilar libft
$(LIBFT):
	@echo "$(GREEN)Compilando libft...$(NC)"
	@$(MAKE) -C $(LIBDIR)

# Limpieza de objetos
clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBDIR)

# Limpieza total
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBDIR)

# Recompilación
re: fclean all

.PHONY: all clean fclean re
