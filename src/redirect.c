#include "../include/minishell.h"
#include "structs.h"

int redirect_input(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}

int redirect_output(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

int redirect_output_append(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

int handle_heredoc(const char *delimiter)
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    while (1) {
        char *line = readline("> ");
        if (!line || strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    return 0;
}

int handle_redirection(const char *operator, const char *target)
{
    if (!operator || !target) {
        ft_printf(stderr, "Error: redirección incompleta.\n");
        return -1;
    }

    if (strcmp(operator, "<") == 0) {
        return redirect_input(target);
    } else if (strcmp(operator, ">") == 0) {
        return redirect_output(target);
    } else if (strcmp(operator, ">>") == 0) {
        return redirect_output_append(target);
    } else if (strcmp(operator, "<<") == 0) {
        return handle_heredoc(target);
    } else {
        ft_printf(stderr, "Error: operador de redirección desconocido: %s\n", operator);
        return -1;
    }
}



