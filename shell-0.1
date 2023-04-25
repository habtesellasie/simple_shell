#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1000
#define MAX_ARGUMENTS 100

extern char **environ;

int main(int argc, char *argv[]) {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    int num_arguments;
    pid_t pid;
    int status;

    while(1) {
        // Display prompt
        printf("$ ");
        fflush(stdout);

        // Read input from the user
        if(fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // Handle end of file condition
            printf("\n");
            break;
        }

        // Remove newline character from input
        command[strcspn(command, "\n")] = '\0';

        // Parse input into arguments
        char *token = strtok(command, " ");
        num_arguments = 0;

        while(token != NULL && num_arguments < MAX_ARGUMENTS - 1) {
            arguments[num_arguments] = token;
            num_arguments++;
            token = strtok(NULL, " ");
        }

        arguments[num_arguments] = NULL;

        // Check for exit command
        if(strcmp(arguments[0], "exit") == 0) {
            // Check for argument for exit status
            if(num_arguments == 2) {
                int status = atoi(arguments[1]);
                exit(status);
            }
            else if(num_arguments > 2) {
                fprintf(stderr, "Usage: exit [status]\n");
            }
            else {
                exit(EXIT_SUCCESS);
            }
        }

        // Check for env command
        if(strcmp(arguments[0], "env") == 0) {
            // Print environment variables
            char **env = environ;

            while(*env) {
                printf("%s\n", *env);
                env++;
            }

            continue;
        }

        // Check for setenv command
        if(strcmp(arguments[0], "setenv") == 0) {
            if(num_arguments != 3) {
                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                continue;
            }

            if(setenv(arguments[1], arguments[2], 1) != 0) {
                fprintf(stderr, "Failed to set environment variable\n");
            }

            continue;
        }

        // Check for unsetenv command
        if(strcmp(arguments[0], "unsetenv") == 0) {
            if(num_arguments != 2) {
                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                continue;
            }

            if(unsetenv(arguments[1]) != 0) {
                fprintf(stderr, "Failed to unset environment variable\n");
            }

            continue;
        }

        // Check for cd command
        if(strcmp(arguments[0], "cd") == 0) {
            char *dir;
            char current_dir[MAX_COMMAND_LENGTH];
            getcwd(current_dir, sizeof(current_dir));

            if(num_arguments == 1) {
                dir = getenv("HOME");
            }
            else if(strcmp(arguments[1], "-") == 0) {
                // "-" as argument means change to previous working directory
                dir = getenv("OLDPWD");
            }
            else {
                dir = arguments[1];
            }

            if(chdir(dir) != 0) {
                fprintf(stderr, "Failed to change directory\n");
            }
            else {
                // Update PWD and OLDPWD environment variables
                setenv("OLDPWD", current_dir, 1);
                getcwd(current_dir, sizeof(current_dir));
                setenv("PWD", current_dir, 1);
            }
	        continue;
    }

    // Check for cd command
    if(strcmp(arguments[0], "cd") == 0) {
        char current_dir[MAX_COMMAND_LENGTH];

        // Check for argument for directory
        if(num_arguments == 1) {
            // No argument given, change to HOME directory
            char *home_dir = getenv("HOME");
            if(home_dir == NULL) {
                fprintf(stderr, "cd: HOME directory not set\n");
                continue;
            }
            if(chdir(home_dir) != 0) {
                fprintf(stderr, "cd: %s: No such file or directory\n", home_dir);
                continue;
            }
        }
        else if(num_arguments == 2) {
            if(strcmp(arguments[1], "-") == 0) {
                // "-" as argument means change to previous working directory
                char *old_dir = getenv("OLDPWD");
                if(old_dir == NULL) {
                    fprintf(stderr, "cd: OLDPWD not set\n");
                    continue;
                }
                if(chdir(old_dir) != 0) {
                    fprintf(stderr, "cd: %s: No such file or directory\n", old_dir);
                    continue;
                }
            }
            else {
                // Change to given directory
                if(chdir(arguments[1]) != 0) {
                    fprintf(stderr, "cd: %s: No such file or directory\n", arguments[1]);
                    continue;
                }
            }
        }
        else {
            fprintf(stderr, "cd: too many arguments\n");
            continue;
        }

        // Update PWD and OLDPWD environment variables
        getcwd(current_dir, sizeof(current_dir));
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", current_dir, 1);

        continue;
    }

    // Check if command exists
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *path_token = strtok(path_copy, ":");

    while(path_token != NULL) {
        char command_path[MAX_COMMAND_LENGTH];
        snprintf(command_path, sizeof(command_path), "%s/%s", path_token, arguments[0]);
        if(access(command_path, F_OK) == 0) {
            // Command exists, fork and execute
            pid = fork();

            if(pid == 0) {
                // Child process

                // Execute command
                if(execve(command_path, arguments, environ) == -1) {
                    printf("Error executing command\n");
                    exit(EXIT_FAILURE);
                }
            }
            else if(pid < 0) {
                // Forking error
                printf("Forking error\n");
                exit(EXIT_FAILURE);
            }
            else {
                // Parent process, wait for child to complete
                if(waitpid(pid, &status, 0) == -1) {
                    printf("Error waiting for child process\n");
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }

        path_token = strtok(NULL, ":");
    }

    if(path_token == NULL) {
        // Command not found
        printf("%s: command not found\n", arguments[0]);
    }
}

return 0;
}
