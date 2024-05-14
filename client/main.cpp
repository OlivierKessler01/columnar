#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//void child_reap_handler(int sig)
//{
//    int pid;
//    sig++;
//    while((pid = waitpid(-1, NULL, 0)) != -1) {
//        printf("Child with PID %d terminated", pid);
//    }
//}

int main(int argc, char** argv, char** envp)
{
    (void)argv;
    (void)argc;
    char buffer[100];
    //   signal(SIGCHLD, child_reap_handler);
    printf("> ");

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (fork() == 0){
            //In the child process
            char* argv_child[1];
            argv_child[0] = buffer;
            execve("/bin/ls",argv_child, envp);
        }
        
        //The parent make sure to reap the child process 
        int pid;
        while((pid = waitpid(-1, NULL, 0)) != -1) {
            printf("Child with PID %d terminated", pid);
        }
    }

    return 0;
}
