/*
Problem Statement : Nth no. of a unsorted array
Task: To find the nth smallest element in a given sequence. The operation should take
an amortized cost of O(n).
Aim: To learn how to use randomization in algorithms.
Hint: Think of the partition function of randomized quick-sort.
Testing: Time your function using time.h and compare it with the Standard Library Function
nth_element().
*/


#include<bits/stdc++.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
int partition(int arr[],int start,int end)   {
    int temp;
    int k,i=start,x=arr[end];
    for(k=start;k<=end-1;k++) {
        if(arr[k]<=x)    {
            temp=arr[k];
            arr[k]=arr[i];
            arr[i]=temp;
            i++;
        }
    }
    temp=arr[i];
    arr[i]=arr[end];
    arr[end]=temp;
    return i;
}
  
int randompart(int arr[],int start,int end) {
    int temp;
    srand(time(NULL));
    int rand1=start+rand()%(end-start+1);
    //cout<<"rand1: "<<rand1<<endl;
    temp=arr[rand1];
    arr[rand1]=arr[end];
    arr[end]=temp;
    int x=partition(arr,start,end);
    return x;
}
int nthsmallest(int arr[],int start,int end,int n)  {
    if(n<0)
        return -1;
    if(n>end)
        return -1;
    int pivot = randompart(arr,start,end);
    if(pivot==n)    {
        return arr[n];
    }
    else if(pivot<n)
        nthsmallest(arr,pivot+1,end,n);
    else
        nthsmallest(arr,start,pivot-1,n);
}
int main()  {
    int n,ans=0,i,k;
    /*cout<<"Enter no. of elements: "<<endl;
    cin>>n;
    int arr[n];
    for(i=0;i<n;i++)
        cin>>arr[i];*/
    const clock_t time1=clock();
    int arr[23]={7,10,4,3,15,20,100,156,890,567,101,589,456,6,78,962,475,1024,2048,3056,3036,1,598};
    n=23;
    //cout<<"Enter value of n: "<<endl;
    //cin>>k;
    k=9;
    ans=nthsmallest(arr,0,n-1,k-1);
    cout<<ans<<endl;
    printf("Time taken: %f seconds\n",(float(clock()-time1)/CLOCKS_PER_SEC));
    

    int arr1[23]={7,10,4,3,15,20,100,156,890,567,101,589,456,6,78,962,475,1024,2048,3056,3036,1,598};
    n=23;
    const clock_t time2=clock();
    nth_element(arr1, arr1+8, arr1+n);
    cout<<arr1[8]<<endl;
    printf("Time taken for STL: %f seconds\n",(float(clock()-time2)/CLOCKS_PER_SEC));
    return 0;
}
