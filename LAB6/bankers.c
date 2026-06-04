#include <stdio.h>

int main() {

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int allocation[n][m];
    int max[n][m];
    int need[n][m];
    int available[m];

    int finish[n];
    int safeSequence[n];

    // INPUT ALLOCATION MATRIX
    printf("\nEnter Allocation Matrix:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // INPUT MAX MATRIX
    printf("\nEnter Max Matrix:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // INPUT AVAILABLE
    printf("\nEnter Available Resources:\n");

    for(int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // CALCULATE NEED MATRIX
    printf("\nNEED MATRIX:\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            need[i][j] = max[i][j] - allocation[i][j];

            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    // ---------------- SAFETY ALGORITHM ----------------

    for(int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;

    int work[m];

    for(int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    printf("\nProcess P%d is executing", i);

                    for(int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    printf("\nAvailable Resources: ");

                    for(int j = 0; j < m; j++) {
                        printf("%d ", work[j]);
                    }

                    printf("\n");

                    safeSequence[count++] = i;

                    finish[i] = 1;

                    found = 1;
                }
            }
        }

        if(found == 0) {

            printf("\nSystem is NOT in SAFE STATE\n");

            return 0;
        }
    }

    printf("\nSystem is in SAFE STATE");

    printf("\nSafe Sequence: ");

    for(int i = 0; i < n; i++) {

        printf("P%d", safeSequence[i]);

        if(i != n - 1) {
            printf(" -> ");
        }
    }

    // ---------------- RESOURCE REQUEST ALGORITHM ----------------

    int process;

    printf("\n\nEnter process number for request: ");
    scanf("%d", &process);

    int request[m];

    printf("Enter Request Matrix:\n");

    for(int j = 0; j < m; j++) {
        scanf("%d", &request[j]);
    }

    // STEP 1 : Request <= Need

    for(int j = 0; j < m; j++) {

        if(request[j] > need[process][j]) {

            printf("\nERROR: Process exceeded maximum claim\n");

            return 0;
        }
    }

    // STEP 2 : Request <= Available

    for(int j = 0; j < m; j++) {

        if(request[j] > available[j]) {

            printf("\nResources not available. Process must wait.\n");

            return 0;
        }
    }

    // STEP 3 : Pretend Allocation

    for(int j = 0; j < m; j++) {

        available[j] -= request[j];

        allocation[process][j] += request[j];

        need[process][j] -= request[j];
    }

    // STEP 4 : RUN SAFETY ALGORITHM AGAIN

    for(int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    count = 0;

    for(int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = 1;

                    safeSequence[count++] = i;

                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    // STEP 5 : SAFE OR UNSAFE

    if(count == n) {

        printf("\nRequest can be GRANTED.\n");

        printf("New Safe Sequence: ");

        for(int i = 0; i < n; i++) {

            printf("P%d", safeSequence[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }

    else {

        printf("\nRequest CANNOT be granted.");

        printf("\nSystem will enter UNSAFE STATE.\n");
    }

    return 0;
}
