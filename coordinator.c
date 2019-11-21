// getpid(): obtain my own ID
// getppid(): get the ID of my parent
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

void checker(const char *whoami){
        printf("I am a %s.  My pid is:%d  my ppid is %d\n",
                        whoami, getpid(), getppid() );
}

int main(int argc, char** argv){
    // argv[1] is number of peers
    // argv[2] is number of entries
    int status;
    int n;
    pid_t pid;

    if (argc != 3) {
		fprintf(stderr, "Usage: need more arguments!\n");
        exit(0);
    }
    int peers_num=atoi(argv[1]);
    int entries_num=atoi(argv[2]);
    printf("Parameters argc: %d, num of peers: %d and num of entries: %d.\n", argc, peers_num, entries_num);
    
    for(int i=0; i<argc; i++){
        printf("For i %d argv[i] %s\n", i, argv[i]);
    }
    
    int ar_entry[entries_num];
    for(int i=0; i<entries_num; i++){
        ar_entry[i]=i+1;
    }
    // // // // // // // // // // // // // // // // // // // // // // // // // 
    pid_t pids[peers_num];
    
    checker("parent");
    /* Start children. */
    for (int i = 0; i < peers_num; ++i) {

        if ( (pids[i] = fork()) < 0 ) {
            perror("fork failed");
			exit(1);
        }
        else if (pids[i] == 0) {
            checker("child");
            exit(0);
        }

    }

    /* Wait for children to exit. */
    n=peers_num;
    while (n > 0) {
        pid = wait(&status);
        printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
        --n;  // TODO(pts): Remove pid from the pids array.
    }

    return 0;
}