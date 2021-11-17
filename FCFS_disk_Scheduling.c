//C Program to Implement the FCFS Disk Scheduling
#include<stdio.h>

int main()
{
    int total_head_movement=0,initial_pos,n ;
    printf("\n Enter the no. of cylinders in Request queue:\n");
    scanf("%d",&n);
    int request_queue[n]; 
    printf("\n Enter the cylinders no. in Request queue :\n");
    for(int i=0;i<n;i++)
     scanf("%d",&request_queue[i]);
    printf("\n Enter the initial Position of RW head: ");
    scanf("%d",&initial_pos);
    for(int i=0;i<n;i++)
    {
        total_head_movement += abs(initial_pos - request_queue[i]);
        initial_pos = request_queue[i];
    }    
   
   printf("\nTotal No. of Head Movements = %d\n",total_head_movement);
   printf("\nAverage head movements = %.2f\n",(float)total_head_movement/n);

   return 0;
}