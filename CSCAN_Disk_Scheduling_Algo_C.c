// C program to implement CSCAN Disk Scheduling algorithm

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int comparator(const void * a, const void *b)
{
   int x =*(int *)a;
   int y =*(int *)b;
   if(x<y)
     return -1;  // No sorting
   else if( x>=y) // = is for stable sort
    return 1;    // Sort
} 

int min_element(int request_queue[],int n)
{
    int min = INT_MAX;
    for(int i=0;i<n;i++)
    {
       if(request_queue[i] < min)
          min = request_queue[i];
    }
    return min;  
}

int max_element(int request_queue[],int n)
{
   int max = INT_MIN;
   for(int i=0;i<n;i++)
   {
      if(request_queue[i] > max)
          max = request_queue[i];
   }
    return max;  
}


int moveRight(int left[],int right[],int j,int k,int total_cylinders, int request_queue[], int initial_pos, int seek_sequence[],int *sequence_size,int n)
{
    //j is right array size and k is left array size
   int total_head_movement=0; 
   for (int i = 0; i < j; i++) 
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - right[i]);	
        initial_pos = right[i];
        // appending current track to seek sequence
        seek_sequence[*sequence_size]=right[i]; 
        (*sequence_size)++;
   }

   k ?  total_head_movement += (total_cylinders - 1): 0 ;
   initial_pos = 0;
   
   //move right again if needed (i.e if left array is not empty)
   for (int i = 0; i < k; i++) 
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - left[i]);	
        initial_pos = left[i];
        // appending current track to seek sequence
        seek_sequence[*sequence_size]=left[i]; 
        (*sequence_size)++;
   }
   
   return total_head_movement;
}


int moveLeft(int left[],int right[],int j, int k,int total_cylinders, int request_queue[], int initial_pos, int seek_sequence[],int *sequence_size,int n)
{
   int total_head_movement=0; 
   for (int i = k - 1; i >=0; i--) 
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - left[i]);	
        initial_pos = left[i];
        // appending current track to seek sequence
        seek_sequence[*sequence_size]=left[i]; 
        (*sequence_size)++;
   }
   j ?  total_head_movement += (total_cylinders - 1): 0 ;
   initial_pos = total_cylinders - 1;
   
   //move right
   for (int i = j -1; i >=0; i--)
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - right[i]);	
        initial_pos = right[i];
        // appending current track to seek sequence
        seek_sequence[*sequence_size]=right[i]; 
        (*sequence_size)++; 
   }
   return total_head_movement;
}

int applyCSCANAlgo(int total_cylinders, int request_queue[], int initial_pos, int seek_sequence[], int * sequence_size,int direction,int n)
{
	int total_head_movement=0,j=0,k=0;
	int left[n+1], right[n+1];  //in worst case(corner cases), size will be n+1

	// appending end values which has to be visited during reversing the direction
    if( ( initial_pos > min_element(request_queue,n)) && (initial_pos < max_element(request_queue,n)) )
    {
          right[j++] = total_cylinders - 1;
          left[k++] = 0;  //here  0 is initial cylinder of HDD
    }
    

    //Decide on basis of direction where to put initial position (this is only needed if we want to print this initia_pos also
    // in seek_sequence otherwise remove thsi if-else
	if(direction == 0)
        right[j++] = initial_pos;
    else if(direction == 1)
        left[k++] = initial_pos;    

	for (int i = 0; i<n; i++) 
    {
		if (request_queue[i] < initial_pos)
			left[k++]=request_queue[i];
		if (request_queue[i] > initial_pos)
			right[j++]=request_queue[i];
	}
  
	// sorting left and right arrays
    qsort((void *)left,k, sizeof(int),comparator);
    qsort((void *)right,j, sizeof(int),comparator);

	if(direction == 0 ) //right
        total_head_movement += moveRight(left, right,j,k, total_cylinders,request_queue, initial_pos, seek_sequence,sequence_size,n);
    else if(direction == 1 ) //left
       total_head_movement += moveLeft( left,right,j,k, total_cylinders, request_queue,  initial_pos, seek_sequence,sequence_size,n);
    return total_head_movement;
}


int main()
{
    int total_cylinders,total_head_movement=0,initial_pos,n,direction,pos;
    printf("\nEnter the total no. of cylinders in HDD:\n");
    scanf("%d",&total_cylinders);

    printf("\nEnter the no. of cylinders to enter in Request queue:\n");
    scanf("%d",&n);
    
    int request_queue[n];
    int seek_sequence[n+10];   // i.e take somewhat bigger size than n
    int sequence_size=0;

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
    
    total_head_movement = applyCSCANAlgo(total_cylinders, request_queue,initial_pos,seek_sequence,&sequence_size,direction,n);
    
    // *********** OUTPUT ********** 
    printf("\n\n*********** OUTPUT **********");
    printf("\nSeek Sequence: ");
    for(int i=0;i<sequence_size;i++)
     printf("%d ",seek_sequence[i]);

    printf("\nTotal No. of Head Movements = %d\n",total_head_movement);
    printf("\nAverage head movements = %.2f\n\n",(float)total_head_movement/n);

    return 0;
}