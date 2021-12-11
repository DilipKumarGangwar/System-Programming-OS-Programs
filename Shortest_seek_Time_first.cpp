//C++ Program to Implement the SSTF Disk Scheduling Algorithm

#include<iostream>
#include<cstdlib> //for abs
#include<climits>  //for INT_MAX
#include<cstring> //for memset
#include<vector>
#include<iomanip>  // for manipulator
//#include<bits/stdc++.h>
using namespace std;


//Function to find and return the closest cylinder to the position of RW head
int findclosestCylinder(int initial_pos, vector<bool> visited,vector<int> request_queue,int n)
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

int applySSTFAlgo(vector<int> request_queue, int initial_pos,vector<bool> visited,vector<int> &seek_sequence,int n)
{
    int i=0;            //used in seek_sequence
    int completed=0,total_head_movement=0;
    while(completed!=n)
    {
      int min_index=findclosestCylinder(initial_pos,visited,request_queue,n);
      //find total head movement
      total_head_movement += abs(initial_pos - request_queue[min_index]);
      initial_pos = request_queue[min_index];
      seek_sequence[i++] = request_queue[min_index];
      visited[min_index]=true;    // so that we don't pick this cylinder in next iteration
      completed++;
    }    
    
    return total_head_movement; 
}


int main()
{
    cout << fixed << setprecision(2);
    int total_cylinders,total_head_movement=0,initial_pos,n,completed=0,i;
    
    // *********** INPUT ********** 
    cout<<endl<<"Enter the total no. of cylinders in HDD:"<<endl;
    cin>>total_cylinders;
    if(total_cylinders <= 0) 
    {
      cout<<"Total Cylinders must be greater than 0";
      exit(0);
    }
    cout<<"\nEnter the no. of cylinders to enter in Request queue:\n";
    cin>>n;

    vector<int> request_queue;  
    vector<int> seek_sequence(n);

    cout<<"\nEnter the cylinders no. in Request queue :\n";
    for(int i=0;i<n;i++)
    {
     int cylinder;
     cin>>cylinder;   
     request_queue.push_back(cylinder);
    }
    cout<<"\nEnter the initial Position of RW head: ";
    cin>>initial_pos;
    
    vector<bool> visited(n,false);        //to keep track of visited cylinder
   
    
    if(initial_pos < 0 || initial_pos > total_cylinders - 1)
    {
        cout<<"Wrong Initial Position Enetered !!";
        exit(0);
    }
    total_head_movement = applySSTFAlgo(request_queue,initial_pos,visited,seek_sequence,n);
    
   // *********** OUTPUT ********** 
   cout<<"\n\n*********** OUTPUT **********";
   cout<<"\nSeek Sequence: ";
   for(int i=0;i<n;i++)
     cout<<seek_sequence[i]<<" ";
   cout<<"\nTotal No. of Head Movements: "<<total_head_movement;
   cout<<"\nAverage head movements:"<<total_head_movement/n;

   return 0;
}