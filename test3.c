#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char** cmd, int input_fd, int output_fd) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        execvp(cmd[0], cmd);
        perror("execvp");
        exit(1);
    }
}

void execute_pipeline(char*** commands, int num_pipes) {
    int i;
    int input_fd = STDIN_FILENO;

    for (i = 0; i < num_pipes; i++) {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        execute_command(commands[i], input_fd, pipefd[1]);
        close(pipefd[1]);

        input_fd = pipefd[0];
    }

    // Last command
    execute_command(commands[i], input_fd, STDOUT_FILENO);
}

int main() {
    char* command1[] = {"echo", "hello world", NULL};
    char* command2[] = {"ls", NULL};
    char* command3[] = {"wc", NULL};
    char** commands[] = {command1, command2, command3};

    int num_pipes = sizeof(commands) / sizeof(commands[0]) - 1;

    execute_pipeline(commands, num_pipes);

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    return 0;
}

