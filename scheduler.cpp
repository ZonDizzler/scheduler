#include <iostream>
using namespace std;

void fcfs( int processID[], int burstTime[], int n);
void sjf( int processID[], int burstTime[], int n);


int main() {

    int processID[] = {1, 2, 3, 4, 5}; 
    int burstTime[] = {2, 1, 8, 4, 5};

    int n = 5;

    // Call the FCFS function
    fcfs(processID, burstTime, n);
    cout << "\n" << endl;
    sjf(processID, burstTime, n);

    return 0;
}

void fcfs(int processID[], int burstTime[], int n) {
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Special case: the first process has 0 waiting time
    waitingTime[0] = 0;
    // Turnaround time for the first process is its burst time
    turnaroundTime[0] = burstTime[0];

    totalWaitingTime = waitingTime[0];
    totalTurnaroundTime = turnaroundTime[0];

    // Start at 1, as 0 is already calculated
    for (int i = 1; i < n; i++) {
        // Waiting time of the current process is the turnaround time of the previous process
        waitingTime[i] = turnaroundTime[i - 1];
        totalWaitingTime += waitingTime[i];

        // Turnaround time is waiting time plus burst time
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    } //end for loop

    // Display process information with waiting and turnaround times
    cout << "FCFS\n";
    cout << "Process ID\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << processID[i] << "\t\t\t" 
        << waitingTime[i] << "\t\t\t\t" 
        << turnaroundTime[i] << endl;
    }

    cout << "Total Waiting Time: " << (float)totalWaitingTime << endl;
    cout << "Total Turnaround Time: " << (float)totalTurnaroundTime << endl;

    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

void sjf(int processID[], int burstTime[], int n) {
    int processIDcopy[n];
    int burstTimeCopy[n];

    // Copy the original processID and burstTime arrays
    std::copy(processID, processID + n, processIDcopy);
    std::copy(burstTime, burstTime + n, burstTimeCopy);

    // Perform bubble sort on burstTimeCopy and corresponding processIDcopy
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // To optimize and stop if already sorted
        for (int j = 0; j < n - i - 1; j++) {
            if (burstTimeCopy[j] > burstTimeCopy[j + 1]) {
                // Swap burst time values
                std::swap(burstTimeCopy[j], burstTimeCopy[j + 1]);

                // Also swap the corresponding process IDs
                std::swap(processIDcopy[j], processIDcopy[j + 1]);

                swapped = true;
            }
        }
        // If no two elements were swapped, the array is already sorted
        if (!swapped)
            break;
    }

    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Special case: the first process has 0 waiting time
    waitingTime[0] = 0;
    // Turnaround time for the first process is its burst time
    turnaroundTime[0] = burstTimeCopy[0];

    totalWaitingTime = waitingTime[0];
    totalTurnaroundTime = turnaroundTime[0];

    // Calculate waiting and turnaround times for the remaining processes
    for (int i = 1; i < n; i++) {
        // Waiting time of the current process is the turnaround time of the previous process
        waitingTime[i] = turnaroundTime[i - 1];
        totalWaitingTime += waitingTime[i];

        // Turnaround time is waiting time plus burst time
        turnaroundTime[i] = waitingTime[i] + burstTimeCopy[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Display process information with waiting and turnaround times
    cout << "SJF\n";
    cout << "Process ID\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << processIDcopy[i] << "\t\t\t" 
        << waitingTime[i] << "\t\t\t\t" 
        << turnaroundTime[i] << endl;
    }

    cout << "Total Waiting Time: " << (float)totalWaitingTime << endl;
    cout << "Total Turnaround Time: " << (float)totalTurnaroundTime << endl;


    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

