#include <stdio.h>

int main(){

    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    int AT[n],BT[n],type[n];

    printf("Enter AT, BT and Type (0=System, 1=User)\n");

    for(int i=0;i<n;i++){
        printf("For process %d:\t", i+1);
        scanf("%d%d%d",&AT[i],&BT[i],&type[i]);
    }

    int CT[n],TAT[n],WT[n],done[n];

    for(int i=0;i<n;i++)
        done[i]=0;

    int t=0,count=0;

    while(count<n){

        int in=-1;
        int min_at=9999;

        for(int i=0;i<n;i++){
            if(done[i]==0 && AT[i]<=t && type[i]==0){
                if(AT[i]<min_at){
                    min_at=AT[i];
                    in=i;
                }
            }
        }

        if(in==-1){
            for(int i=0;i<n;i++){
                if(done[i]==0 && AT[i]<=t && type[i]==1){
                    if(AT[i]<min_at){
                        min_at=AT[i];
                        in=i;
                    }
                }
            }
        }

        if(in==-1){
            t++;
            continue;
        }

        t+=BT[in];
        CT[in]=t;
        TAT[in]=CT[in]-AT[in];
        WT[in]=TAT[in]-BT[in];

        done[in]=1;
        count++;
    }

    float avgWT=0,avgTAT=0;

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for(int i=0;i<n;i++){
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
        i+1,type[i]==0?"System":"User",
        AT[i],BT[i],CT[i],WT[i],TAT[i]);

        avgWT+=WT[i];
        avgTAT+=TAT[i];
    }

    printf("\nAverage Waiting Time: %.2f",avgWT/n);
    printf("\nAverage Turnaround Time: %.2f\n",avgTAT/n);

    return 0;
}
