#include<stdio.h>
#define NO_OF_PROCESSES 5
#define TIME_QUANTUM 2

// result variables 
int waitingTime[NO_OF_PROCESSES] = {0};
int turnAroundTime[NO_OF_PROCESSES] = {0};
int completed[NO_OF_PROCESSES] = {0};
int totalTurnAroundTime = 0;
int totalWaitingTime = 0;

// function declarations
void roundRobin(int, int [], int, int []);



int main(){

    // process variables
    int n = NO_OF_PROCESSES;
    int burstTime[NO_OF_PROCESSES] = {3, 1, 6, 2, 8};
    int c_burstTime[NO_OF_PROCESSES] = {3, 1, 6, 2, 8};
   
    int timeQuantum = TIME_QUANTUM;
    
    // implement the algorithm
    roundRobin(n, burstTime, timeQuantum, c_burstTime); 
    
    
    // display results
    printf("Process ID\t\tBurst Time\t\tWaiting Time\t\tTurn Around Time\n");
     
    int i;
    for (i = 0; i < n; i++){
        
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n\n", i, c_burstTime[i], waitingTime[i], turnAroundTime[i]); 
        
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i]; 
    }   

    printf("Averge Wait Time: %.3f\nAverage Turnaround Time: %.3f\n", (float)totalWaitingTime/n, (float)totalTurnAroundTime/n);   

    return 0;
}



/**
 *  Round Robin Scheduling Algorithm
 */
void roundRobin(int n, int b[], int t, int c_b[]){
    
    
    int i, j, k;
    
    // completion status for all process 
    int allProcessesCompleted = n;
   
   
    // calculate waiting time for all processes
    // repeat until all process are completed
    while (allProcessesCompleted){
        
        // execute all process
        for (i = 0; i < n; i++){
            
            // check if a process has completed status
            if (completed[i] == 0){
                
                
                // check if time quantum is greater than the burst time of the process to which token is allocated         
                if(b[i] - t <= 0){
                    
                    // finish current process execution
                    b[i] = 0;
                    completed[i] = 1;
                    allProcessesCompleted--; 
                    
                    // increment waiting times for other processes by the execution time remaining for current process
                    for (k = 0; k < n; k++){
                    
                        if (k != i && completed[k] == 0){
                            waitingTime[k] += b[i];
                        }
                    }
                    
                }
                else{
                
                    // reduce execution time for current process by time quantum
                    b[i] = b[i] - t;
                    
                    // increment waiting times for other processes by time quantum
                    for (k = 0; k < n; k++){
                    
                        if (k != i && completed[k] == 0){
                            waitingTime[k] += t;    
                        }
                    } 
                    
                }
            
            }
     
        }
        
    }
    
    // calculate turn around time for each process
    for (i = 0; i < n; i++){
        
        turnAroundTime[i] = waitingTime[i] + c_b[i];
        
    }   
    
} 




