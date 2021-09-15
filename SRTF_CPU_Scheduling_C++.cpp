/*.................C++ Program to Implement SRTF ( Shortest Remaining Time First) CPU SCheduling Algorithm.....................
SRTF - A Preemptive Algorithm
This Program works for same as well as different arrival times
*/

#include<iostream>
#include<algorithm>
#include<iomanip>
#include<climits>
using namespace std;

struct process_struct
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,start_time;
}ps[100];


int main()
{
    
    int n;
    float bt_remaining[100];
    bool is_completed[100]={false},is_first_process=true;
    int current_time = 0;
    int completed = 0;;    
    float sum_tat=0,sum_wt=0,sum_rt=0,total_idle_time=0,length_cycle,prev=0;
    float cpu_utilization;
    int max_completion_time,min_arrival_time;
    
    cout << fixed << setprecision(2);

    cout<<"Enter total number of processes: ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process" <<i<< "Arrival Time: ";
        cin >> ps[i].at;
        ps[i].pid=i;
    }
    
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process" <<i<< "Burst Time: ";
        cin >> ps[i].bt;
        bt_remaining[i]= ps[i].bt;
    }
    
    
    while(completed!=n)
    {
        //find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) {
            if(ps[i].at <= current_time && is_completed[i] == false) {
                if(bt_remaining[i] < minimum) {
                    minimum = bt_remaining[i];;
                    min_index = i;
                }
                if(bt_remaining[i]== minimum) {
                    if(ps[i].at < ps[min_index].at) {
                        minimum= bt_remaining[i];;
                        min_index = i;
                    }
                }
            }
        }

    
        if(min_index==-1)
        {
            current_time++;
        }
        else
        {
            if(bt_remaining[min_index] == ps[min_index].bt)
            {
                        ps[min_index].start_time = current_time;
                        total_idle_time += (is_first_process==true) ? 0 : (ps[min_index].start_time -  prev);
                        is_first_process=false;
            }
            bt_remaining[min_index] -= 1;
            current_time++; 
            prev=current_time;
            if(bt_remaining[min_index] == 0)
            {
                ps[min_index].ct = current_time;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt= ps[min_index].tat - ps[min_index].bt;
                ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;
            
            
                sum_tat +=ps[min_index].tat;
                sum_wt += ps[min_index].wt;
                sum_rt += ps[min_index].rt;
                completed++;
                is_completed[min_index]=true;       
                
                
            }
        }
    }
    //Calculate Length of Process completion cycle
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for(int i=0;i<n;i++)
    {
        max_completion_time = max(max_completion_time,ps[i].ct);
        min_arrival_time = min(min_arrival_time,ps[i].at);
    }
    length_cycle = max_completion_time - min_arrival_time;

    
     //Output
    cout<<"\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for(int i=0;i<n;i++)
     cout<<i<<"\t\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<endl;
    cout<<endl;  
    
    cpu_utilization = (float)(length_cycle - total_idle_time)/ length_cycle;

    cout<<"\nAverage Turn Around time= "<< (float)sum_tat/n;
    cout<<"\nAverage Waiting Time= "<<(float)sum_wt/n;
    cout<<"\nAverage Response Time= "<<(float)sum_rt/n;    
    cout<<"\nThroughput= "<<n/(float)length_cycle;
    cout<<"\nCPU Utilization(Percentage)= " << cpu_utilization*100;
    return 0;
}
