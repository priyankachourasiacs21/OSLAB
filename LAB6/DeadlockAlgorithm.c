#include <stdio.h>

int main() {

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m];
    int request[n][m];
    int available[m];

    int work[m];
    int finish[n];

    // INPUT ALLOCATION MATRIX
    printf("\nEnter Allocation Matrix:\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            scanf("%d", &allocation[i][j]);
        }
    }

    // INPUT REQUEST MATRIX
    printf("\nEnter Request Matrix:\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            scanf("%d", &request[i][j]);
        }
    }

    // INPUT AVAILABLE VECTOR
    printf("\nEnter Available Resources:\n");

    for(int j = 0; j < m; j++) {

        scanf("%d", &available[j]);
    }

    // STEP 1 : INITIALIZE WORK = AVAILABLE

    for(int j = 0; j < m; j++) {

        work[j] = available[j];
    }

    // STEP 2 : INITIALIZE FINISH

    for(int i = 0; i < n; i++) {

        int zero = 1;

        for(int j = 0; j < m; j++) {

            if(allocation[i][j] != 0) {
                zero = 0;
                break;
            }
        }

        if(zero)
            finish[i] = 1;

        else
            finish[i] = 0;
    }

    // STEP 3 : FIND PROCESS

    int found;

    do {

        found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(request[i][j] > work[j]) {

                        possible = 0;

                        break;
                    }
                }

                if(possible) {

                    // Work = Work + Allocation

                    for(int j = 0; j < m; j++) {

                        work[j] += allocation[i][j];
                    }

                    finish[i] = 1;

                    found = 1;

                    printf("\nProcess P%d can finish", i);

                    printf("\nUpdated Work Vector: ");

                    for(int j = 0; j < m; j++) {

                        printf("%d ", work[j]);
                    }

                    printf("\n");
                }
            }
        }

    } while(found);

    // STEP 4 : CHECK DEADLOCK

    int deadlock = 0;

    for(int i = 0; i < n; i++) {

        if(finish[i] == 0) {

            deadlock = 1;

            printf("\nProcess P%d is DEADLOCKED", i);
        }
    }

    if(deadlock == 0) {

        printf("\n\nSystem is NOT in Deadlock State\n");
    }

    return 0;
}
