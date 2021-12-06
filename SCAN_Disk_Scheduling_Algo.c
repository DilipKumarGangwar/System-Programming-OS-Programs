//C Program to Implement the FCFS Disk Scheduling Algorithm

#include<stdio.h>
#include<stdlib.h> //for abs
#include<stdbool.h>  //for bool
#include<limits.h>  //for INT_MAX
#include<string.h> //for memset

int applyScanAlgo(int request_queue[], int total_cylinders,int initial_pos,int pos,int direction,int n)
{
   int total_head_movement=0,total_cylinders_traversed=0;
   int visited[n];
   if(direction==0)
   {
      for(int i=pos;i<n;i++)
      {
         total_head_movement += abs(initial_pos-request_queue[i]);
         initial_pos = request_queue[i];   
         visited[i]=true;   
         total_cylinders_traversed++;
      }
      printf("total=%d %d",total_head_movement,initial_pos);
      //total_head_movement += abs(initial_pos - (total_cylinders-1));  
      printf("ggtotal h=%d ",total_head_movement);
      
      if(total_cylinders_traversed != n) 
      {
         total_head_movement += abs((total_cylinders-1) - request_queue[pos-1]);   
         initial_pos = request_queue[pos-1];  
         for(int i=pos-2;i>=0;i--)
            total_head_movement += abs(initial_pos - request_queue[i]);
      }
      
      printf("total h=%d ",total_head_movement);
      
         

         printf("ff  dfd");
   } 
      
   else if(direction == 1)
   {   
      
      for(int i=pos-1; i>=0; i--)
      {
         total_head_movement += abs(initial_pos-request_queue[i]);
         initial_pos = request_queue[i];   
         visited[i]=true;   
         total_cylinders_traversed++;   
      }
      printf("r = %d",total_head_movement);
      
      
      printf("rg = %d",total_head_movement);
      if(total_cylinders_traversed != n) 
      {  
         
         total_head_movement += abs(initial_pos - 0);
         total_head_movement += abs(0 - request_queue[pos+1]);
         initial_pos = request_queue[pos+1];
         printf("vvrg = %d",total_head_movement);  
         for(int i=pos+2;i<n;i++)
         {
         
         total_head_movement += abs(initial_pos-request_queue[i]);
         printf("x = %d",total_head_movement);  
         initial_pos = request_queue[i];      
         } 
      printf("vvrg = %d",total_head_movement);  
      printf("dfd");
      }
   }
   return total_head_movement;    
}

int findPosition(int request_queue[],int initial_pos,int n)
{
    int i;
    for( i=0;i<n;i++)
    {
        if( request_queue[i] == initial_pos)
           return i;
        if( request_queue[i] < initial_pos)
           continue;
        break;
    }
    return i;
}

//Function to find and return the closest cylinder to the position of RW head
int comparator(const void * a, const void *b)
{
   int x =*(int *)a;
   int y =*(int *)b;
   if(x<y)
     return -1;  // No sorting
   else if( x>=y)
    return 1;    // Sort  
}

int main()
{
    int total_cylinders,total_head_movement=0,initial_pos,n,direction,pos;
    
  
    printf("\nEnter the total no. of cylinders in HDD:\n");
    scanf("%d",&total_cylinders);

    printf("\nEnter the no. of cylinders to enter in Request queue:\n");
    scanf("%d",&n);
    
    int request_queue[n];

    printf("\nEnter the cylinders no. in Request queue :\n");
    for(int i=0;i<n;i++)
     scanf("%d",&request_queue[i]);
    printf("\nEnter the initial Position of RW head: ");
    scanf("%d",&initial_pos);
    printf("\nEnter the direction in which Read Write head is moving:\n ");
    printf("\nEnter 0 if moving to higher cylinder else Enter 1: ");
    scanf("%d",&direction);

    if(initial_pos < 0 || initial_pos > total_cylinders - 1)
    {
        printf("Wrong Initial Position Enetered !!");
        exit(0);
    }
    
    

    bool visited[n];//to keep track of visited cylinder;
    memset(visited,false,n*sizeof(bool));

    //sort
    qsort((void *)request_queue,n, sizeof(int),comparator);
    
    for(int i=0;i<n;i++)
     printf("%d ",request_queue[i]);
    
    if(initial_pos == request_queue[0] )
      total_head_movement = applyScanAlgo(request_queue, total_cylinders,initial_pos, 0, direction,n);
    else if ( initial_pos == request_queue[n-1] )
      total_head_movement = applyScanAlgo(request_queue, total_cylinders,initial_pos, n-1, direction,n);
   
    else
    {
    //find the just lesser number than RW initial_pos 
      pos=findPosition(request_queue, initial_pos,n); 
      printf("pos=%d ",pos);
      printf("rp=%d ",request_queue[pos]);
      total_head_movement = applyScanAlgo(request_queue,total_cylinders, initial_pos, pos, direction,n);
    }
      
   printf("\nTotal No. of Head Movements = %d\n",total_head_movement);
   printf("\nAverage head movements = %.2f\n\n",(float)total_head_movement/n);

   return 0;
}