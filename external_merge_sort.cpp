/*
External Sorting
Problem Statement: External Sorting is a class of algorithms used to deal with massive
amounts of data that do not fit in memory. The questions aim at implementing one such type:
K-Way merge sort algorithm to sort a very large array. This algorithm is a perfect example of
the use of divide and conquer where with limited resources large problems are tackled by
breaking the problem space into small computable subspaces and then operations are done
on them.
Input Constraints:1. A file containing a large unsorted list of integers (Will not fit in your usual
Laptop RAM).
2.Do not use any in-built data structures.
Output : A file containing non-Descending sorted list of the given integers
Languages allowed : C, C++, Python Evaluation parameters :
1. Time and Space Complexity of the algorithm
2. Efficient use of Data-Structures
Example Format:
If your input file is at ./data/input.txt And if you need your output file at ./data/ named
output.txt
*/




#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int rem=0;
class Node {
    public:
    int data;
    int fileno;
};
class Minheap   {
    public:
    Node *arr;
    int size;
    public:
    Minheap(Node n[],int);
    int parent(int);
    int leftchild(int);
    int rightchild(int);
    Node extractmin();
    void getnewmin(Node);
    void heapify(int);
};
Minheap::Minheap(Node n[],int k)  {
    int i;
    arr=n;
    size=k;
    i=(k-1)/2;
    for(int x=i;x>=0;x--)
        heapify(x);
}
int Minheap::leftchild(int v)   {
    return (2*v)+1;
}
int Minheap::rightchild(int v)   {
    return (2*v)+2;
}
int Minheap::parent(int v)   {
    if(v%2 == 0)
        return v/2;
    else
        return (v/2)-1;
}
Node Minheap::extractmin()   {
    return arr[0];
}
void Minheap::getnewmin(Node n)  {
    arr[0]=n;
    heapify(0);
}
void Minheap::heapify(int x) {
    int l=leftchild(x);
    int r=rightchild(x);
    int ldata=arr[l].data;
    int rdata=arr[r].data;
    int data1=arr[x].data;
    int min=x;
    Node temp;
    if(l<size && ldata<data1)   
        min=l;
    if(r<size && rdata<arr[min].data)
        min=r;
    if(min!=x)  {
        temp=arr[min];
        arr[min]=arr[x];
        arr[x]=temp;
        heapify(min);
    }
}

    
void merge(int a[],int l,int mid,int mid1,int r)   {
    int i=l,j=mid1,m=mid,n=r;
	int b[r-l+1],k=0;
    while(i<=m && j<=n) {
        if(a[i]<=a[j])   {
            b[k]=a[i];
            k++;
            i++;
        }
        else    {
            b[k]=a[j];
            j++;
            k++;
        }
    }
    while(i<=m)  {
        b[k]=a[i];
        k++;
        i++;
    }
    while(j<=n)  {
        b[k]=a[j];
        k++;
        j++;
    }
    for(int x=l;x<=r;x++)    {
        a[x]=b[x-l];
    }
}
void mergesort(int arr[],int l,int r)   {
    if(l<r) {
        int mid=l+(r-l)/2;
        mergesort(arr,l,mid);
        mergesort(arr,mid+1,r);
        merge(arr,l,mid,mid+1,r);
    }
}

int divideinchunks(char *filename,int recordsize) {
    cout<<filename<<endl;
    int i,nooffiles=0,j=0,records=0,flag=0;
    string line;
    ifstream file(filename);
    while (getline(file, line))
        records++;
    file.close();
    nooffiles=records/recordsize;
    if(records%recordsize!=0)   {
        rem=records%recordsize;
        flag=1;
    }

    FILE *fp=fopen(filename,"r");
    FILE *fp1[nooffiles+1];
    for(j=0;j<nooffiles;j++)    {
        int arr[recordsize];
        for(i=0;i<recordsize;i++)   {
            fscanf(fp,"%d",&arr[i]);
        }
        mergesort(arr,0,recordsize-1);
        string fname="file"+to_string(j);
        char ch[1000];
        strcpy(ch,fname.c_str());
        fp1[j]=fopen(ch,"w");
        for(i=0;i<recordsize;i++)   {
            fprintf(fp1[j],"%d\n",arr[i]);
        }
    }
    if(flag==1) {
        int arr[rem];
        for(i=0;i<rem;i++)   {
            fscanf(fp,"%d",&arr[i]);
        }
        mergesort(arr,0,rem-1);
        string fname="file"+to_string(j);
        char ch[1000];
        strcpy(ch,fname.c_str());
        fp1[j]=fopen(ch,"w");
        for(i=0;i<rem;i++)   {
            fprintf(fp1[j],"%d\n",arr[i]);
        }
        nooffiles+=1;
    }
    for(i=0;i<nooffiles;i++)
        fclose(fp1[i]);

    fclose(fp);
    return nooffiles;
}
void mergefiles(char *filename,int nooffiles,int recordsize)   {
    FILE *fp1[nooffiles];
    FILE *fp=fopen(filename,"w");
    int i=0,j,totalrecords=0,x,f,c=0;
    Node* n=new Node[nooffiles];
    for(j=0;j<nooffiles;j++)    {
        string fname="file"+to_string(j);
        char ch[1000];
        strcpy(ch,fname.c_str());
        fp1[j]=fopen(ch,"r");
        fscanf(fp1[j],"%d",&n[i].data);
        n[i].fileno=i;
        i++;
    }
    Minheap heap(n,nooffiles);
    Node top;
    if(rem==0)
        totalrecords=recordsize*nooffiles;
    else
        totalrecords=(recordsize*(nooffiles-1))+rem;
    cout<<"totalrecords: "<<totalrecords<<endl;
    for(i=0;i<totalrecords;i++) {
        top=heap.extractmin();
        x=top.data;
        f=top.fileno;
        cout<<"x: "<<x<<" f: "<<f<<endl;
        fprintf(fp,"%d\n",x);
        if(fscanf(fp1[f],"%d",&top.data) == EOF)  
            top.data=INT_MAX;
        heap.getnewmin(top);        
    }
    for(i=0;i<nooffiles;i++)
        fclose(fp1[i]);

    fclose(fp);
    
}
int main(int argc,char *argv[])  {
    char *f1,*f2;
    f1=argv[1];
    f2=argv[2];
    int nooffiles=divideinchunks(f1,10000);
    mergefiles(f2,nooffiles,10000);
}
