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

# Archivos fuente
SRC = $(wildcard $(SRCDIR)/*.c)

# Archivos objeto
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Colores para estética (opcional)
GREEN = \033[0;32m
NC = \033[0m

# ****************************************************** #

# Regla principal
all: $(NAME)

# Cómo construir el ejecutable
$(NAME): $(OBJ)
	@echo "$(GREEN)Compilando $(NAME)...$(NC)"
	$(CC) $(CFLAGS) -I$(INCDIR) $^ -o $@ $(LIBS)

# Cómo compilar los .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Limpieza de objetos
clean:
	@rm -rf $(OBJDIR)

# Limpieza total
fclean: clean
	@rm -f $(NAME)

# Recompilación completa
re: fclean all

# Phony (para evitar conflictos con archivos)
.PHONY: all clean fclean re
