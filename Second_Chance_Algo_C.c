// C program to implement Second Chance Algorithm which is one of the LRU Approximation Page Replacement Algorithm 
// Find Video Explanation: https://www.youtube.com/watch?v=_dUNVEBSA_Y&list=PLVKIC9j3jSYtCEAffM_51qVWeQus70cqc&index=31&t=1337s

#include<stdio.h>
#include<stdbool.h>

typedef struct frame
{
  int page;
  bool reference_bit;
} frameType;

//Function to Print the Frames vector (only Page numbers are printed)
void printFrames(int no_of_frames,frameType frames[])
{
    for(int i=0;i<no_of_frames;i++)
    {
        printf("%d ",frames[i].page);
    }
   printf("\n");
}

// Function to find the victim page to be replaced and replace it accordingly by your new page
//It return the updated pointer of location from where the new search starts next time
int findAndReplace(int referenced_page, int no_of_frames, frameType frames[],int pointer)
{
    while(true)
    {
       if(frames[pointer].reference_bit == 0)
       {
           //Replace i.e put your page at this pointed location in frames
           frames[pointer].page = referenced_page;
           pointer = (pointer + 1)% no_of_frames;
           return pointer;
       }
       //if reference bit = 1 , then give the second chance and make this bit = 0 again
       // and proceed to next location to search
       frames[pointer].reference_bit = 0;
       pointer = (pointer + 1)% no_of_frames;
    }

    return pointer;
}

// Function to check if there is need for Updating/replacing the page inside Frames array 
bool isNeedForUpdate(int referenced_page, int no_of_frames, frameType frames[])
{
    //search the frames array
    for(int i = 0 ; i < no_of_frames; i++)
    {
        if(frames[i].page == referenced_page)        //page already exists in frame
        {
            frames[i].reference_bit = true;        //update the reference bit = 1 for giving second chance in future
            return false; // No need for Page replacement  
        } 
    }
    return true ;  // There is need for Adding new page/page replacement as page is not present already
}

//Function to return the total Page faults
int applySecondChanceAlgo(int reference_string[], int n,int no_of_frames,frameType frames[])
{
    int total_page_fault = 0,pointer=0;
    for(int i = 0 ; i<n; i++ )
    {
       //check if there is need for Updating(Add referenced page) or replacing(Page Replacement) the page inside Frames array 
       if(isNeedForUpdate( reference_string[i] ,no_of_frames,frames))
       {
          //if yes, then find the page in frames array which need to be replaced and replace accordingly  
          pointer = findAndReplace(reference_string[i],no_of_frames,frames,pointer);
          //increase page fault count
          total_page_fault++;
       } 

       //Print the content present inside frames
       printFrames(no_of_frames,frames);

    }
   //return total page faults to main()
   return total_page_fault;

}

int main()
{  
    int i,n,no_of_frames,total_page_fault=0;
    printf("\nEnter the no. of pages:\n");
    scanf("%d",&n);
    //create reference string array
    int reference_string[n]; 
    printf("\nEnter the reference string(actual page numbers) :\n");
    for(int i=0;i<n;i++)
     scanf("%d",&reference_string[i]);
    printf("\nEnter the no. of frames you want to give to the process :");
    scanf("%d",&no_of_frames);
 
    frameType frames[no_of_frames];

    //initialise the frames as page no = -1 , reference bit =0
    for(int i=0; i<no_of_frames; i++)
    {
      frames[i].page= -1;  
      frames[i].reference_bit = false;
    }

    total_page_fault = applySecondChanceAlgo(reference_string,n, no_of_frames,frames);
    
    // *********** OUTPUT ********** 
    printf("\n\n*********** OUTPUT **********\n");
    printf("\nTotal No. of Page faults =%d",total_page_fault);
    printf("\nPage fault Ratio= %.2f",(float)total_page_fault/n);
    printf("\nPage Hit Ratio= %.2f\n\n",(float)(n - total_page_fault)/n);

    return 0;
}