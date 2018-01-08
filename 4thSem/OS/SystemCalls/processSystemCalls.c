#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// header file contains declarations for the types used by system-level calls to obtain file status or time information.
#include <sys/types.h>

// Accompanies fcntl() system call and provides symbolic constants for its arguments
// fcntl() can be used to retrieve or modify open file flags given a file descriptor
#include <fcntl.h>

// header file that is your code's entry point to various constant, type and function declarations that comprise the POSIX operating system API
// The Portable Operating System Interface is a family of standards specified by the IEEE Computer Society for maintaining compatibility between operating systems
#include <unistd.h>

// for signal() function used to deal with various signal sent to a program
#include <signal.h>

#include <sys/wait.h>


int alarmSig = 0;

// function declarations
void fwk();
void interruptHandler();
void alarmHandler();
void changeDir();
void id();
void forkId();
void fe();


int main(){

    // SIGINT: (Signal Interrupt) Interactive attention signal. Generally generated by the application user.
    signal(SIGINT, interruptHandler);

    // SIGALRM: Alarm signal generated by alarm()
    signal(SIGALRM, alarmHandler);

	int choice;

	printf("==== MENU ===\n\n1. Fork, Wait, Kill\n2. Alarm\n3. Exit\n4. Change Directory\n5. Various id's\n6. Fork and execl\n\n");
	printf("Enter choice: ");
	scanf("%d", &choice);

	switch (choice){

		case 1:
			fwk();
			break;
		case 2:
		    printf("\n\nSent alarm(5): Waiting for 5 seconds ....\n\n");
		    alarm(5);
		    while(!alarmSig);
            break;
		case 3:
		    exit(0);
		    break;
		case 4:
		    changeDir();
		    break;
		case 5:
		    forkId();
		    break;
		case 6:
            fe();
		    break;


	}


	return 0;
}


/**
 * Fork: creates a new process, Wait:  blocks the calling process until one of its child processes exits or a signal is received, Kill: terminates stalled or unwanted processes
 */
void fwk(){


	// for getting process id for child process
    pid_t pid;



    // child process because return value zero
    if ((pid = fork()) == 0){

    	printf("\nForked : inside child process\n");
    }
    // parent process because return value non-zero.
    else if (pid > 0) {
    	printf("\nForked: inside parent process\n");
    }
    else{
    	printf("\nUnable to fork\n\n");
    }


	// kill child
    if(pid == 0){

    	printf("Killed child process from child itself!");

		kill(pid, SIGHUP);
    }

    else if (pid > 0){
    	printf("Killed child process from parent!");

		kill(pid, SIGHUP);
    }


	// WAIT

	if (fork() == 0)
        printf("\n\nhello from child\n");
    else
    {
        printf("\n\nhello from parent\n");

        // wait will hold the execution of parent until child has been terminated
        // so "child has terminated" will only print after "hello from child" as after that child will end execution
        // then parent is executed to print "child has terminated"
        while(wait(NULL)>0);
        printf("\nchild has terminated\n");
    }



}



/**
 * Interrupt handler for SIGINT type signal
 * sigNum denotes which signal it is
 * 2 for Ctrl + C
 */
void interruptHandler(int sigNum){

    if(sigNum == 2){
        printf("\nYou want to exit the program! using Ctrl + C\n");
        exit(0);
    }

}


/**
 * Interrupt handler for SIGALRM type signal
 */
void alarmHandler(int sigNum){

    printf("\nAlarm received... \n");
    alarmSig = 1;

}


/**
 * chdir: Change current working direcory
 * The current working directory is local to the process
 * Thus it won't show up in terminal
 * The shell is simply a process, just like the program is. Each program has it's own working directory
 */
void changeDir(){

    char path[200];

    // get path
	printf("Specify path of directory to go to:  ");
	getchar();
	gets(path);

    char *tmp;

    if ((tmp = strrchr(path, '\n')) != NULL) {
        *tmp = '\0';
    }


    // stripping off \n and changing directory
	if(chdir(path) == -1){
	    printf("\n\nUnsuccessful\n");
	}

    // get current working directory
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
	printf("\nDirectory changed local to process and not shell: %s\n\n",cwd);

}


/**
 * gives user id, group id, process id
 */
void id(){

    printf("\nReal User id: %ld\n", (long)getuid());
    printf("\nEffective User id: %ld\n", (long)geteuid());
    printf("\nReal Group id: %ld\n", (long)getgid());
    printf("\nEffective Group id: %ld\n", (long)getegid());
    printf("\nProcess id: %ld\n", (long)getpid());
    printf("\nParent process id: %ld\n\n", (long)getppid());
}

/**
 * Get Id's for parent and child processes
 * If parent process is terminated then child process gets ppid  = 1
 */
void forkId(){

    pid_t pid;

    if ((pid = fork()) == 0){

        printf("\nChild Process\n");

    }
    else{
        printf("\nParent Process\n");

    }

    id();

    // halt the parent process until child process terminates
    while(wait(NULL)>0);

}

/**
 * execl: replaces the current process image with a new process image specified by path
 */
void fe(){


    if(fork() == 0){

        printf("\nChild process: (to be replaced by ls command)\n\n");

        // replace this child process image with ls process
        // (path, other arguments to be passed to new process)
        execl("/bin/ls", "ls", "-l", (char *)0);
    }
    else{

        printf("\nParent process waiting for child process to execute\n");

        // wait for child process to complete
        while(wait(NULL) > 0);

        printf("\nChild process completed\n\n");


    }


}