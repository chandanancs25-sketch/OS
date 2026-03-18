

#include <stdio.h>

int main() {

    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], resp[n];
    int visited[n];

    for(int i=0;i<n;i++){
        printf("\nProcess P%d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        rt[i] = bt[i];
        visited[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    while(completed < n){

        int found = 0;

        for(int i=0;i<n;i++){

            if(at[i] <= current_time && rt[i] > 0){

                found = 1;


                if(visited[i] == 0){
                    resp[i] = current_time - at[i];
                    visited[i] = 1;
                }

                if(rt[i] > tq){
                    current_time += tq;
                    rt[i] -= tq;
                }
                else{
                    current_time += rt[i];
                    rt[i] = 0;

                    ct[i] = current_time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    total_wt += wt[i];
                    total_tat += tat[i];
                    total_rt += resp[i];

                    completed++;
                }
            }
        }

        if(found == 0){
            current_time++;
        }
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],tat[i],wt[i],resp[i]);
    }

    printf("\nAverage WT = %.2f", total_wt/n);
    printf("\nAverage TAT = %.2f", total_tat/n);
    printf("\nAverage RT = %.2f\n", total_rt/n);

    return 0;
}
