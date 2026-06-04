#include <stdio.h>

void non_preemptive(int n, int AT[], int BT[], int PR[]) {
    int CT[n], TAT[n], WT[n], RT[n], completed[n];

    for(int i=0;i<n;i++)
        completed[i]=0;

    int t=0,count=0;

    while(count<n){
        int in=-1;
        int high_pr=9999;

        for(int i=0;i<n;i++){
            if(AT[i]<=t && completed[i]==0){

                if(PR[i] < high_pr){
                    high_pr = PR[i];
                    in = i;
                }

                if(PR[i] == high_pr){
                    if(AT[i] < AT[in])
                        in = i;
                }
            }
        }

        if(in!=-1){
            RT[in] = t - AT[in];
            CT[in] = t + BT[in];
            TAT[in] = CT[in] - AT[in];
            WT[in] = TAT[in] - BT[in];

            completed[in] = 1;
            t = CT[in];
            count++;
        }
        else{
            t++;
        }
    }

    float avgTAT=0,avgWT=0,avgRT=0;

    printf("\nPriority Non-Preemptive Result:\n");
    printf("Process\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,AT[i],BT[i],PR[i],CT[i],TAT[i],WT[i],RT[i]);

        avgTAT += TAT[i];
        avgWT += WT[i];
        avgRT += RT[i];
    }

    printf("\nAverage TAT = %.2f",avgTAT/n);
    printf("\nAverage WT  = %.2f",avgWT/n);
    printf("\nAverage RT  = %.2f\n",avgRT/n);
}

void preemptive(int n, int AT[], int BT[], int PR[]) {
    int CT[n],TAT[n],WT[n],RT[n];
    int temp_BT[n],completed[n],first_time[n];

    for(int i=0;i<n;i++){
        temp_BT[i]=BT[i];
        completed[i]=0;
        first_time[i]=-1;
    }

    int t=0,count=0;

    while(count<n){

        int in=-1;
        int high_pr=9999;

        for(int i=0;i<n;i++){

            if(AT[i]<=t && completed[i]==0){

                if(PR[i] < high_pr){
                    high_pr = PR[i];
                    in = i;
                }

                if(PR[i]==high_pr){
                    if(temp_BT[i] < temp_BT[in])
                        in = i;
                }
            }
        }

        if(in!=-1){
            if(first_time[in]==-1)
                first_time[in]=t;
            temp_BT[in]--;
            t++;
            if(temp_BT[in]==0){

                CT[in]=t;
                TAT[in]=CT[in]-AT[in];
                WT[in]=TAT[in]-BT[in];
                RT[in]=first_time[in]-AT[in];
                completed[in]=1;
                count++;
            }
        }
        else{
            t++;
        }
    }

    float avgTAT=0,avgWT=0,avgRT=0;
    printf("\nPriority Preemptive Result:\n");
    printf("Process\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,AT[i],BT[i],PR[i],CT[i],TAT[i],WT[i],RT[i]);
        avgTAT += TAT[i];
        avgWT += WT[i];
        avgRT += RT[i];
    }
    printf("\nAverage TAT = %.2f",avgTAT/n);
    printf("\nAverage WT  = %.2f",avgWT/n);
    printf("\nAverage RT  = %.2f\n",avgRT/n);
}

int main(){

    int n,choice;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    int AT[n],BT[n],PR[n];
    for(int i=0;i<n;i++){
        printf("Enter AT, BT and Priority for P%d: ",i+1);
        scanf("%d%d%d",&AT[i],&BT[i],&PR[i]);
    }
    printf("\n1. Priority Non-Preemptive");
    printf("\n2. Priority Preemptive");
    printf("\nEnter choice: ");
    scanf("%d",&choice);
    if(choice==1)
        non_preemptive(n,AT,BT,PR);
    else if(choice==2)
        preemptive(n,AT,BT,PR);
    else
        printf("Invalid Choice");
}
