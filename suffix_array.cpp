/*
Problem Statement: Implementation of suffix array
Implement a Suffix Array that is capable of performing following operations on Strings in a
most efficient way.

Given a string S print its minimum lexicographic rotation. ​ O(nlogn)

String consist of either Lower/Upper Case Alphabet and Numeric digits.

Example :
S = “dcabca”
1. All possible rotation are “dcabca” , “cabcad” , “abcadc” , “bcadca” , “cadcab” , “adcabc” .
Among all lexicographically minimum is “abcadc” .
*/



#include<bits/stdc++.h>
#include<string.h>
using namespace std;
int ch[100];
class suffix_array  {
    public:
    int index;
    int rank;
    int next_rank;
    public:
    suffix_array();
    int* insert(char *);
    static bool comp1(suffix_array const & sa1,suffix_array const & sa2)  {
        if(sa1.rank==sa2.rank)  {
            if(sa1.next_rank>=sa2.next_rank)
                return false;
            else 
                return true;
        }
        else if(sa1.rank>=sa2.rank)
            return false;
        return true;
    }
};
suffix_array::suffix_array()    {}

int* suffix_array::insert(char *str)   {
    //int n=str.length();
    int n=strlen(str);
    suffix_array s[n];
    int j=0;
    for(char i='0';i<='9';i++)  {
        ch[i]=j;
        j++;
    }
    for(char i='A';i<='Z';i++)  {
        ch[i]=j;
        j++;
    }
    for(char i='a';i<='z';i++)  {
        ch[i]=j;
        j++;
    }
    int i;
    for(i=0;i<n;i++)    {
        s[i].index=i;
        s[i].rank=ch[str[i]];
        if(i+1<n)   {
            s[i].next_rank=ch[str[i+1]];
        }
        else
            s[i].next_rank=-1;
    }
    sort(s,s+n,comp1);

    for(int k=2;k<4*n;k*=2) {
        int last_rank=s[0].rank,last_next_rank=s[0].next_rank,cur_rank=0;
        s[0].rank=0;
        cur_rank=0;
        int indices[n];
        indices[s[0].index]=0;
        for(i=1;i<n;i++)    {
            if(s[i].rank==last_rank && s[i].next_rank==last_next_rank)  {
                s[i].rank=cur_rank;
            }
            else    {
                last_rank=s[i].rank;
                last_next_rank=s[i].next_rank;
                cur_rank++;
                s[i].rank=cur_rank;
            }
            indices[s[i].index]=i;
        }
        for(i=0;i<n;i++)    {
            j=s[i].index;
            if((j+k)<n)
                s[i].next_rank=s[indices[j+k]].rank;
            else
                s[i].next_rank=-1;
        }
        sort(s,s+n,comp1);
    }
    /*for(i=0;i<n;i++)    {
        cout<<s[i].rank<<" ";
    }
    cout<<endl;
    for(i=0;i<n;i++)    {
        cout<<s[i].next_rank<<" ";
    }
    cout<<endl;
    for(i=0;i<n;i++)    {
        cout<<s[i].index<<" ";
    }
    cout<<endl;*/
    int *suff_arr;
    suff_arr = new int[100000];
    for(i=0;i<n;i++)    {
        suff_arr[i]=s[i].index;
    }
    return suff_arr;
}

void lexirotation(string str,int sa[],int n)   {
    string ans="";
    int a,b;
    for(int i=0;i<2*n;i++)    {
        //cout<<sa[i]<<" ";
        if(sa[i]<n) {
            ans=str.substr(sa[i],n);
            break;
        }
    }
    cout<<ans<<endl;
}
int main()  {
    char txt[100000];
    string str;
    int length;
    cin>>length;
    //cout<<"Enter the string: "<<endl;
    cin>>str;
    //int length=str.size();
    str+=str;
    strcpy(txt,str.c_str());
    int *arr;
    suffix_array sa;
    arr=sa.insert(txt);
    //for(int i=0;i<2*length;i++)
    //    cout<<arr[i]<<" ";
    //cout<<endl;
    lexirotation(str,arr,length);  
    return 0; 
}
