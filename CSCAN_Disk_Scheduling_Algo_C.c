// C program to implement CSCAN Disk Scheduling algorithm
//TO BE UPDATED... Currently it is incorrect

#include<stdio.h>
#include<stdlib.h>


int moveRight(vector<int> left,vector<int> right,int total_cylinders, vector<int> request_queue, int initial_pos, vector<int> &seek_sequence,int n)
{
   int total_head_movement=0; 
   for (int i = 0; i < right.size(); i++) 
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - right[i]);	
        initial_pos = right[i];
        // appending current track to seek sequence
        seek_sequence.push_back(right[i]); 
   }
   total_head_movement += (total_cylinders - 1);
   initial_pos = 0;
   
   //move right
   for (int i = 0; i < left.size(); i++) 
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - left[i]);	
        initial_pos = left[i];
        // appending current track to seek sequence
        seek_sequence.push_back(left[i]); 
   }
   return total_head_movement;
}


int moveLeft(vector<int> left,vector<int> right, int total_cylinders,vector<int> request_queue, int initial_pos, vector<int> &seek_sequence,int n)
{
   int total_head_movement=0; 
   for (int i = left.size() - 1; i >=0; i--) 
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - left[i]);	
        initial_pos = left[i];
        // appending current track to seek sequence
        seek_sequence.push_back(left[i]); 
   }
   total_head_movement += (total_cylinders - 1);
   initial_pos = total_cylinders - 1;
   
   //move right
   for (int i = right.size() -1; i >=0; i--)
   {
        // calculate absolute distance
        total_head_movement += abs(initial_pos - right[i]);	
        initial_pos = right[i];
        // appending current track to seek sequence
        seek_sequence.push_back(right[i]); 
   }
   return total_head_movement;
}

int applyCSCANAlgo(int total_cylinders, vector<int> request_queue, int initial_pos, vector<int> &seek_sequence, int direction,int n)
{
	int total_head_movement=0;
	vector<int> left, right;

	// appending end values which has to be visited before reversing the direction
    right.push_back(total_cylinders-1);
	left.push_back(0);  //here  0 is initial cylinder of HDD

	for (int i = 0; i<n; i++) 
    {
		if (request_queue[i] < initial_pos)
			left.push_back(request_queue[i]);
		if (request_queue[i] > initial_pos)
			right.push_back(request_queue[i]);
	}
  
	// sorting left and right vectors
	sort(left.begin(), left.end());
	sort(right.begin(), right.end());

	// run the while loop two times one by one scanning right and left of the head
	if(direction == 0 ) //right
        total_head_movement += moveRight(left, right, total_cylinders,request_queue, initial_pos, seek_sequence, n);

    else if(direction == 1 ) //left
       total_head_movement += moveLeft( left,right, total_cylinders, request_queue,  initial_pos, seek_sequence,  n);
	
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
    int seek_sequence[n+10];   // i.e take somewaht bigger size than n
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
    
    total_head_movement = applyCSCANAlgo(total_cylinders, request_queue,initial_pos,seek_sequence,direction,n);
    
    // *********** OUTPUT ********** 
    printf("\n\n*********** OUTPUT **********");
    printf("\nSeek Sequence: ");
    for(int i=0;i<sequence_size;i++)
     printf("%d ",seek_sequence[i]);

    printf("\nTotal No. of Head Movements = %d\n",total_head_movement);
    printf("\nAverage head movements = %.2f\n\n",(float)total_head_movement/n);

    return 0;
}