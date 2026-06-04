#include <stdio.h>
#include <math.h>

void edf(int n, int BT[], int DL[], int P[]) {
    int CT[n], TAT[n], WT[n];
    int order[n];

    for (int i = 0; i < n; i++)
        order[i] = i;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (DL[order[i]] > DL[order[j]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    float U = 0;
    for (int i = 0; i < n; i++)
        U += (float)BT[i] / P[i];

    printf("\nEarliest Deadline First (EDF) Scheduling\n");
    printf("CPU Utilization: %.2f\n", U);

    if (U <= 1)
        printf("Schedulable (Utilization <= 1)\n");
    else {
        printf("NOT Schedulable (Utilization > 1)\n");
        return;
    }

    int t = 0;

    for (int i = 0; i < n; i++) {
        int idx = order[i];
        t += BT[idx];
        CT[idx] = t;
        TAT[idx] = CT[idx];
        WT[idx] = TAT[idx] - BT[idx];
    }

    printf("ID\tBF\tDeadline\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
        i, BT[i], DL[i], CT[i], WT[i], TAT[i]);
    }
}

void rms(int n, int BT[], int DL[], int P[]) {
    int CT[n], TAT[n], WT[n];
    int order[n];

    for (int i = 0; i < n; i++)
        order[i] = i;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (P[order[i]] > P[order[j]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    float U = 0;
    for (int i = 0; i < n; i++)
        U += (float)BT[i] / P[i];

    float bound = n * (pow(2, 1.0/n) - 1);

    printf("\n Rate Monotonic Scheduling (RMS) \n");
    printf("CPU Utilization: %.2f\n", U);
    printf("RM Bound: %.4f\n", bound);

    if (U <= bound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else
        printf("NOT Schedulable (Utilization > RM Bound)\n");

    int t = 0;

    for (int i = 0; i < n; i++) {
        int idx = order[i];
        t += BT[idx];
        CT[idx] = t;
        TAT[idx] = CT[idx];
        WT[idx] = TAT[idx] - BT[idx];
    }

    printf("ID\tBF\tPeriod\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
        i, BT[i], P[i], CT[i], WT[i], TAT[i]);
    }
}

void proportional(int n, int BT[], int DL[], int P[]) {
    int total = 0;

    for (int i = 0; i < n; i++)
        total += P[i];

    printf("\n Proportional Scheduling \n");

    for (int i = 0; i < n; i++) {
        float share = (float)P[i] / total;
        printf("P%d -> %.2f%%\n", i, share * 100);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int BT[n], DL[n], P[n];

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i);

        printf("Burst Time: ");
        scanf("%d", &BT[i]);

        printf("Deadline (for EDF): ");
        scanf("%d", &DL[i]);

        printf("Period (for RMS): ");
        scanf("%d", &P[i]);
    }

    edf(n, BT, DL, P);
    rms(n, BT, DL, P);
    proportional(n, BT, DL, P);

    return 0;
}
