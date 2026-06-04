#include <stdio.h>

void firstFit(int blocks[], int m, int process[], int n) {
    int allocation[n];
    int used[m];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < m; i++)
        used[i] = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(blocks[j] >= process[i] && used[j] == 0) {
                allocation[i] = j;
                used[j] = 1;
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, process[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blocks[], int m, int process[], int n) {
    int allocation[n];
    int used[m];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < m; i++)
        used[i] = 0;

    for(int i = 0; i < n; i++) {
        int best = -1;

        for(int j = 0; j < m; j++) {
            if(blocks[j] >= process[i] && used[j] == 0) {
                if(best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }

        if(best != -1) {
            allocation[i] = best;
            used[best] = 1;
        }
    }

    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, process[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blocks[], int m, int process[], int n) {
    int allocation[n];
    int used[m];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < m; i++)
        used[i] = 0;

    for(int i = 0; i < n; i++) {
        int worst = -1;

        for(int j = 0; j < m; j++) {
            if(blocks[j] >= process[i] && used[j] == 0) {
                if(worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }

        if(worst != -1) {
            allocation[i] = worst;
            used[worst] = 1;
        }
    }

    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, process[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int blocks[m];

    printf("Enter sizes of %d memory blocks:\n", m);

    for(int i = 0; i < m; i++)
        scanf("%d", &blocks[i]);

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    int process[n];

    printf("Enter sizes of %d processes:\n", n);

    for(int i = 0; i < n; i++)
        scanf("%d", &process[i]);

    firstFit(blocks, m, process, n);
    bestFit(blocks, m, process, n);
    worstFit(blocks, m, process, n);

    return 0;
}
