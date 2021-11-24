//C Program to Implement the FCFS Disk Scheduling Algorithm

#include<stdio.h>
#include<stdlib.h> //for abs
#include<stdbool.h>  //for bool
#include<limits.h>  //for INT_MAX
#include<string.h> //for memset

//Function to find and return the closest cylinder to the position of RW head
int findclosestCylinder(int initial_pos, bool visited[],int request_queue[],int n)
{
  int min=INT_MAX,min_index=-1;  
  for(int i=0;i<n;i++)
  {
      if(visited[i] == false && abs(initial_pos - request_queue[i]) < min)
      {
          min = abs(initial_pos - request_queue[i]);
          min_index = i;
      }
  }
  return min_index;

}

int main()
{
    int total_head_movement=0,initial_pos,n ;
    printf("\nEnter the no. of cylinders to enter in Request queue:\n");
    scanf("%d",&n);
    int request_queue[n]; 
    printf("\nEnter the cylinders no. in Request queue :\n");
    for(int i=0;i<n;i++)
     scanf("%d",&request_queue[i]);
    printf("\nEnter the initial Position of RW head: ");
    scanf("%d",&initial_pos);
    
    bool visited[n];        //to keep track of visited cylinder
    memset(visited,false,n*sizeof(bool));
    
    for(int i=0;i<n;i++)
    {
      int min_index=findclosestCylinder(initial_pos,visited,request_queue,n);
      visited[min_index]=true;  // so that we don't pick this cylinder in next iteration

      //find total head movement
      total_head_movement += abs(initial_pos-request_queue[min_index]);
      initial_pos = request_queue[min_index];
    }    
   
   printf("\nTotal No. of Head Movements = %d\n",total_head_movement);
   printf("\nAverage head movements = %.2f\n\n",(float)total_head_movement/n);

   return 0;
}