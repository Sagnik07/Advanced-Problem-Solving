/*
Problem Statement: Trie Implementation
Given an array ​ A ​ of ​ N ​ numbers, you will be given ​ q ​ queries.
Each query will contain a single integer ​ x.​ You have to find then maximum xor of ​ x ​ from any
number in ​ A.
Constraints :
1 <= N, q <= 1 0 5
1 <= A[i] <= 1 0 12
Example :
A = {1, 2, 3}
x = 4
Maximum xor of x is with 3, therefore answer is 4 xor 3 = 7
*/



#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
#define ll long long int
ll arr[100000],x[100000];
class node {
    public:
    node *child[2];
    int data;
    public:
    node()  {}
};

class trie  {
    public:
    trie();
    node *make_node(int);
    void insert(node *,ll,ll);
    bool search(node *,ll,ll);
    ll fastpow(ll,ll);
    ll xor1(node *,ll,ll);
};

trie::trie()    {}

node* trie::make_node(int x) {
    node *newnode=new node();
    newnode->data=x;
    for(int i=0;i<2;i++)   
           newnode->child[i]=NULL;
    return newnode;
}

void trie::insert(node *root,ll value,ll n)  {
    node *temp=root,*temp1=root;
    ll i,p=n-1;
    for(i=n-1;i>=0;i--)    {
        int index=(value>>i)&1;
        if(index==0)    {
            if(temp->child[0]==NULL)
                temp->child[0]=make_node(index);
            temp=temp->child[0];
        }
        else    {
            if(temp->child[1]==NULL)
                temp->child[1]=make_node(index);
            temp=temp->child[1];
        }
    }
}

ll trie::xor1(node *root,ll value,ll n)    {
    node *temp=root;
    ll i,ans=0,h=n-1,x=0;
    for(i=n-1;i>=0;i--)    {
        int index=(value>>i)&1;
        if(index==1) {
            if(temp->child[0]==NULL)    {
                temp=temp->child[1];
                x=0;
            }
            else    {
                temp=temp->child[0];
                x=1;
            }
        }
        else    {
            if((temp->child[1])==NULL)    {
                temp=temp->child[0];
                x=0;
            }
            else    {
                temp=temp->child[1];
                x=1;
            }
        }
        ans+=(fastpow(2,h))*(index^temp->data);
        h--;
    }
    //cout<<"ans: "<<ans<<endl;
    return ans;
}

ll trie::fastpow(ll a,ll b)    {
    ll temp;
    if(b==0)
        return 1;
    if(b==1)
        return a;
    temp=fastpow(a,b/2);
    if(b%2==0)
        return temp*temp;
    else
        return a*temp*temp;
}

int main()  {
    ll n,i,no_of_dig,q,sum=0;
    cin>>n;
    cin>>q;
    trie t;
    node *tn=t.make_node(2);
    int max=INT_MIN;
    for(i=0;i<n;i++)    {
        cin>>arr[i];
        if(arr[i]>max)
            max=arr[i];
    }
    //cin>>q;
    for(i=0;i<q;i++)    {
        cin>>x[i];
        if(x[i]>max)
            max=x[i];
    }
    no_of_dig=(int)(floor(log(max)/log(2))+1);
    ll p,k,j;
    string rev;
    for(i=0;i<n;i++)    {
        t.insert(tn,arr[i],no_of_dig);
    }
    for(i=0;i<q;i++)    {
        ll ans=t.xor1(tn,x[i],no_of_dig);
        cout<<ans<<endl;
    }
    return 0;
}

