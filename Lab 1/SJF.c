#include <stdio.h>

void non_preemptive(int n, int AT[], int BT[]) {
    int CT[n], TAT[n], WT[n], RT[n], completed[n];
    for (int i = 0; i < n; i++){
        completed[i] = 0;
    }
    int t = 0, count = 0;
    while (count < n) {
        int in = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (AT[i] <= t && completed[i] == 0) {
                if (BT[i] < min_bt) {
                    min_bt = BT[i];
                    in = i;
                }
                if (BT[i] == min_bt) {
                    if (AT[i] < AT[in]) in = i;
                }
            }
        }
        if (in != -1) {
            RT[in] = t - AT[in];
            CT[in] = t + BT[in];
            TAT[in] = CT[in] - AT[in];
            WT[in] = TAT[in] - BT[in];

            completed[in] = 1;
            t = CT[in];
            count++;
        }
        else {
            t++;
        }
    }
    printf("\nSJF Non-Preemptive Result:\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, AT[i], BT[i], CT[i], TAT[i], WT[i], RT[i]);
    }
}

void preemptive(int n, int AT[], int BT[]) {
    int CT[n], TAT[n], WT[n], RT[n], temp_BT[n], completed[n];
    int first_time[n];

    for (int i = 0; i < n; i++) {
        temp_BT[i] = BT[i];
        completed[i] = 0;
        first_time[i] = -1;
    }
    int t = 0, count = 0;
    while (count < n) {
        int in = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (AT[i] <= t && completed[i] == 0) {
                if (temp_BT[i] < min_bt) {
                    min_bt = temp_BT[i];
                    in = i;
                }
                if (temp_BT[i] == min_bt) {
                    if (AT[i] < AT[in]) in = i;
                }
            }
        }
        if (in != -1) {

            if (first_time[in] == -1){
                first_time[in] = t;
            }
            temp_BT[in]--;
            t++;
            if (temp_BT[in] == 0) {
                CT[in] = t;
                TAT[in] = CT[in] - AT[in];
                WT[in] = TAT[in] - BT[in];
                RT[in] = first_time[in] - AT[in];
                completed[in] = 1;
                count++;
            }
        }
        else {
            t++;
        }
    }

    printf("\nSJF Preemptive (SRTF) Result:\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, AT[i], BT[i], CT[i], TAT[i], WT[i], RT[i]);
    }
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &AT[i], &BT[i]);
    }

    printf("\n1. SJF Non-Preemptive\n2. SJF Preemptive (SRTF)\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        non_preemptive(n, AT, BT);
    }
    else if (choice == 2) {
        preemptive(n, AT, BT);
    }
    else {
        printf("Invalid choice");
    }
}
