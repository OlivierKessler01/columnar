#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RESPONSE 1000
//void child_reap_handler(int sig)
//{
//    int pid;
//    sig++;
//    while((pid = waitpid(-1, NULL, 0)) != -1) {
//        printf("Child with PID %d terminated", pid);
//    }
//}

int main()
{
    char buffer[100];
    int pipefd[2];
    //   signal(SIGCHLD, child_reap_handler);
    while (1) {
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);

        if (strcmp(buffer,"exit\n") == 0)
            exit(EXIT_SUCCESS);

        pipe(pipefd);
        if (fork() == 0){
            //In the child process
            
            //close the read end of the pipe
            close(pipefd[0]);
            //Add the check that makes sure that THE RESPONSE IS NO MORE THAN
            //MAX_RESPONSE IN LENGTH !!
            //send the result of the server request to the parent process
            write(pipefd[1], "com", 3);
            exit(EXIT_SUCCESS);
        } else {
            //In the parent process
            
            // close the write end of the pipe
            close(pipefd[1]);
            char buf_resp[MAX_RESPONSE]{0};
            int i = 0;
            char b;

            while (read(pipefd[0], &b, 1) > 0){ // read while EOF
                buf_resp[i] = b;
                i++; 
            }
            buf_resp[i] = '\n';

            printf("%s\n",buf_resp);

            //The parent make sure to reap the child process 
            int pid;
            while((pid = waitpid(-1, NULL, 0)) != -1) {
                printf("Child with PID %d terminated\n", pid);
            }
        }
    }

    return 0;
}
