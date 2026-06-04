#include <stdio.h>

int fifo(int n, int ref[], int frames){
    int Cqueue[frames];
    for(int i=0;i<frames;i++){
    Cqueue[i] = -1;
    }
    int s=0;
    int found=0;
    int count=0;
    for(int i=0;i<n;i++){
        found=0;
        for(int j=0;j<frames;j++){
            if(Cqueue[j]==ref[i]){
                found=1;
                break;
            }
        }
        if(found==0){
            Cqueue[s]=ref[i];
            s=(s+1)%frames;
            count++;
        }
        printf("%d --> [ ", ref[i]);

        for(int j=0;j<frames;j++){
            if(Cqueue[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ", Cqueue[j]);
            }
        }
        printf("] ");
        if(found==0){
            printf("PAGE FAULT");
        }
        else{
            printf("PAGE HIT");
        }
        printf("\n");
    }
    return count;
}
int lru(int n, int ref[], int frames){
    int arr[frames];
    int recent[frames];

    for(int i=0;i<frames;i++){
        arr[i] = -1;
        recent[i] = -1;
    }
    int count = 0;
    int found = 0;
    int time = 0;
    for(int i=0;i<n;i++){
        found = 0;
        for(int j=0;j<frames;j++){
            if(arr[j] == ref[i]){
                found = 1;
                recent[j] = time++;
                break;
            }
        }
        if(found == 0){
            int pos = 0;

            for(int j=1;j<frames;j++){
                if(recent[j] < recent[pos]){
                    pos = j;
                }
            }
            arr[pos] = ref[i];
            recent[pos] = time++;
            count++;
        }

        printf("%d --> [ ", ref[i]);

        for(int j=0;j<frames;j++){
            if(arr[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ", arr[j]);
            }
        }
        printf("] ");
        if(found == 0){
            printf("PAGE FAULT");
        }
        else{
            printf("PAGE HIT");
        }
        printf("\n");
    }
    return count;
}

int optimal(int n, int ref[], int frames){
    int arr[frames];
    for(int i=0;i<frames;i++){
        arr[i] = -1;
    }
    int count = 0;
    int found = 0;
    for(int i=0;i<n;i++){
        found = 0;
        for(int j=0;j<frames;j++){
            if(arr[j] == ref[i]){
                found = 1;
                break;
            }
        }
        if(found == 0){
            int pos = -1;
            for(int j=0;j<frames;j++){
                if(arr[j] == -1){
                    pos = j;
                    break;
                }
            }
            if(pos == -1){
                int farthest = -1;
                for(int j=0;j<frames;j++){
                    int k;
                    for(k=i+1;k<n;k++){
                        if(arr[j] == ref[k]){
                            break;
                        }
                    }
                    if(k == n){
                        pos = j;
                        break;
                    }
                    if(k > farthest){
                        farthest = k;
                        pos = j;
                    }
                }
            }
            arr[pos] = ref[i];
            count++;
        }
        printf("%d --> [ ", ref[i]);
        for(int j=0;j<frames;j++){
            if(arr[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ", arr[j]);
            }
        }
        printf("] ");

        if(found == 0){
            printf("PAGE FAULT");
        }
        else{
            printf("PAGE HIT");
        }
        printf("\n");
    }
    return count;
}

int main(){
    int n;
    printf("Enter the length of reference string: ");
    scanf("%d", &n);
    int ref[n];
    printf("Enter the reference string: ");
    for(int i=0;i<n;i++){
        scanf("%d", &ref[i]);
    }
    int frames;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("\nFIFO Page Replacement:\n");
    int PFfifo = fifo(n, ref, frames);
    printf("\nTotal FIFO Page Faults = %d\n", PFfifo);
    printf("\nLRU Page Replacement:\n");
    int PFlru = lru(n, ref, frames);
    printf("\nTotal LRU Page Faults = %d\n", PFlru);
    printf("\nOptimal Page Replacement:\n");
    int PFoptimal = optimal(n, ref, frames);
    printf("\nTotal Optimal Page Faults = %d\n", PFoptimal);
    return 0;
}
