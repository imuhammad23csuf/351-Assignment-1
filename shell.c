//Ibraheem Muhammad and Luis Selgado
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char *line = NULL; size_t cap = 0;

    for (;;) {
        fputs("cmd> ", stdout); fflush(stdout);

        ssize_t n = getline(&line, &cap, stdin);
        if (n < 0) { putchar('\n'); break; }            // EOF (Ctrl+D)

        if (n && line[n-1] == '\n') line[n-1] = '\0';   // trim
        if (line[0] == '\0') continue;                  // empty line
        if (strcmp(line, "exit") == 0) break;           // exit

        char *cmd = strtok(line, " \t");                // first token only
        if (!cmd) continue;

        pid_t pid = fork();
        if (pid < 0) { perror("fork"); exit(-1); }

        if (pid == 0) {
            execlp(cmd, cmd, (char*)NULL);              // replace
            perror("execlp");                           // only if failed
            _exit(127);
        } else {
            if (wait(NULL) < 0) { perror("wait"); exit(-1); }
        }
    }

    free(line);
    return 0;
}
