#include<stdio.h>
#include<stdbool.h>
struct process_struct
{
  
  int at;
  int bt;
  int priority;
  int ct,wt,tat,rt,start_time;
}ps[100];

int main()
{
    
    int n;
    bool is_completed[100]={false};
    int bt_remaining[100];
    int current_time = 0;
    int completed = 0;;
    //printf("Enter total number of processes");
    scanf("%d",&n);    
    float sum_tat=0,sum_wt=0,sum_rt=0;

    int i;
    
    //printf("\nEnter Process Number\n");
    // for(i=0;i<n;i++)
    // {
    //   scanf("%f",&ps[i].process_num);
    // }
    //printf("\nEnter Process Arrival Time\n");
    for(i=0;i<n;i++)
    {
      scanf("%d",&ps[i].at);
    }
    //printf("\nEnter Process Burst Time\n");
    for(i=0;i<n;i++)
      scanf("%d",&ps[i].bt);
    //printf("\nEnter Priority\n");
    for(i=0;i<n;i++)
      scanf("%d",&ps[i].priority);
   
    while(completed!=n)
    {
        //find process with min. burst time in ready queue at current time
        int max_index = -1;
        int maximum = -1;
        for(int i = 0; i < n; i++) {
            if(ps[i].at <= current_time && is_completed[i] == 0) {
                if(ps[i].priority > maximum) {
                    maximum = ps[i].priority;
                    max_index = i;
                }
                if(ps[i].priority== maximum) {
                    if(ps[i].at < ps[max_index].at) {
                        maximum= ps[i].priority;
                        max_index = i;
                    }
                }
            }
        }

   // printf("max Index=%d ",max_index);
    if(max_index==-1)
    {
        current_time++;
    }
    else
    {
       if(bt_remaining[max_index]==ps[max_index].bt)
           ps[max_index].start_time = current_time;

       bt_remaining[max_index]--;
       current_time++;
       
       if(bt_remaining[max_index]==0)
       {
            ps[max_index].start_time = current_time;
            ps[max_index].ct = ps[max_index].start_time + ps[max_index].bt;
            ps[max_index].tat = ps[max_index].ct - ps[max_index].at;
            ps[max_index].wt= ps[max_index].tat - ps[max_index].bt;
            ps[max_index].rt = ps[max_index].start_time - ps[max_index].at;
            
            
            sum_tat +=ps[max_index].tat;
            sum_wt += ps[max_index].wt;
            sum_rt += ps[max_index].rt;
            completed++;
            is_completed[max_index]=true;
            
            printf("Max=%d ", ps[max_index].ct);
       }
    }
  }
    for(int i=0;i<n;i++)
    {
        printf("%.2d ",ps[i].ct);
    }
    
    printf("\n%.2f",sum_tat/n);
    printf("\n%.2f",sum_wt/n);
    printf("\n%.2f",sum_rt/n);
    return 0;
}
