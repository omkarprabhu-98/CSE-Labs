#include<stdio.h>
#define NO_OF_PROCESSES 5


// result variables 
int pid[NO_OF_PROCESSES] = {0}; 
int waitingTime[NO_OF_PROCESSES] = {0};
int turnAroundTime[NO_OF_PROCESSES] = {0};
int totalTurnAroundTime = 0;
int totalWaitingTime = 0;

// function declarations
void priorityScheduling(int, int [], int []);



int main(){

    // process variables
    int n = NO_OF_PROCESSES;
    int burstTime[NO_OF_PROCESSES] = {3, 1, 6, 2, 8};
    int priority[NO_OF_PROCESSES] = {3, 1, 2, 5, 4};
    
    // initialize process id
    int j;
    for (j = 0; j < n; j++){
        pid[j] = j;
    }

    
    // implement the algorithm
    priorityScheduling(n, burstTime, priority); 
    
    
    // display results
    printf("Process ID\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurn Around Time\n");
     
    int i;
    for (i = 0; i < n; i++){
        
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n\n", pid[i], priority[i], burstTime[i], waitingTime[i], turnAroundTime[i]); 
        
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i]; 
    }   

    printf("Averge Wait Time: %.3f\nAverage Turnaround Time: %.3f\n", (float)totalWaitingTime/n, (float)totalTurnAroundTime/n);   
    
    return 0;
}



/**
 *  Priority Scheduling Algorithm
 */
void priorityScheduling(int n, int b[], int p[]){
    
    int i, j;
    
    // sort processes as per priority 
    for (i = 0; i < n - 1; i++){
        
        for (j = i; j < n; j++){
            
            if (p[i] > p[j]){
                int tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
                
                tmp = b[i];
                b[i] = b[j];
                b[j] = tmp;
                
                tmp = pid[i];
                pid[i] = pid[j];
                pid[j] = tmp;
            }
        }
    }
    
    // time for execution of processes before a particular process
    int timeForExec = 0;
    
    // calculate waiting time for each process
    for (i = 0; i < n; i++){
        
        // waiting time is (time for completion of processes before the current process)
        waitingTime[i] = timeForExec;
        
        timeForExec += b[i];
    } 
    
    // calculate turn around time for each process
    for (i = 0; i < n; i++){
        
        turnAroundTime[i] = waitingTime[i] + b[i];
        
    } 
} 
