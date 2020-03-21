/*
In a sorted array of integers , median of the array is defined as follows
● If there are odd numbers of elements in an array , median element is the middle
of that array E.x [ 1 , 2 , 3] median is 2 and for [ 1 , 3 , 3] median is 3
● If there are even numbers of elements in an array , median element is average of
two middle elements of that array E.x [ 1 , 2 , 3 , 4 ] median is ( 2 + 3 ) / 2 and for
[ 1 , 3 , 3 , 5 ] median is 3.
Problem Description​ : Given a stream of integers , after occurrence of every
number , output the median of array.
Example:​ Given sequence is 5 , 7 , 1 , 6 , 2 , 3
Explanation:​ [ 5 ] median is 5 [ 5 , 7] median is (5+7)/2 [ 5 7 1 ] sorted array is
[1 5 7 ] median is 5 [5 7 1 6] sorted array is [1 5 6 7] median is (5 + 6)/2.
*/


#include<iostream>
using namespace std;

class node    {
    public:
    int data;
    node *left;
    node *right;
    int leftc;
    int rightc;
    int height;
    public:
    node()    {
        data=0;
        left=NULL;
        right=NULL;
        leftc=0;
        rightc=0;
        height=0;
    }
    node(int d)    {
        this->data=d;
        left=NULL;
        right=NULL;
        leftc=0;
        rightc=0;
        height=1;
    }
};

class avl_tree    {
    public:
    avl_tree();
    int height(node *);
    node *insert(node *,int);
    node *llrotation(node *);
    node *lrrotation(node *);
    node *rlrotation(node *);
    node *rrrotation(node *);
    node *checkheight(node *);
    int findmedian(node *,int);
    int findmedianutil(node *,int,int);
    void inorder(node *);
    int max(int,int);
};

avl_tree::avl_tree()    {}

int avl_tree::max(int a,int b)    {
    return (a>b)?a:b;
}
int avl_tree::height(node *x)    {
    if(x==NULL)
        return 0;
    return x->height;
}

node* avl_tree::checkheight(node *x)    {
    int lheight,rheight,rlheight,rrheight,lrheight,llheight,lheightdiff,rheightdiff,heightdiff=0;
    
    lheight=height(x->left);
    rheight=height(x->right);
    heightdiff=(lheight-rheight);
    if(heightdiff<-1)    {
        int rlheight=height(x->right->left);
        int rrheight=height(x->right->right);
        int rheightdiff=rlheight-rrheight;
        
        if(rheightdiff>0)
            x=rlrotation(x);
        else    {
            x=rrrotation(x);
        }
    }
    else if(heightdiff>1)    {
        int llheight=height(x->left->left);
        int lrheight=height(x->left->right);
        int lheightdiff=llheight-lrheight;
        if(lheightdiff>0)   {
            x=llrotation(x);
        }
        else
            x=lrrotation(x);
    }
    return x;
}
node* avl_tree::llrotation(node *gp)    {
    node *p;
    p=gp->left;
    gp->left=p->right;
    gp->leftc=((p->rightc));
    p->right=gp;
    p->rightc=((gp->leftc)+(gp->rightc))+1;

    gp->height=max(height(gp->left),height(gp->right))+1;
    p->height=max(height(p->left),height(p->right))+1;
    return p;
}

node* avl_tree::rrrotation(node *gp)    {
    node *p;
    p=gp->right;
    gp->rightc=((p->leftc));
    gp->right=p->left;
    p->leftc=((gp->leftc)+(gp->rightc))+1;
    p->left=gp;

    gp->height=max(height(gp->left),height(gp->right))+1;
    p->height=max(height(p->left),height(p->right))+1;
    return p;
}

node* avl_tree::lrrotation(node *gp)    {
    node *p;
    p=gp->left;
    gp->left=rrrotation(p);
    gp=llrotation(gp);
    return gp;
}

node* avl_tree::rlrotation(node *gp)    {
    node *p;
    p=gp->right;
    gp->right=llrotation(p);
    gp=rrrotation(gp);
    return gp;
}

node* avl_tree::insert(node *root,int val)    {
    if(root==NULL)    {
        root=new node(val);
        return root;
    }
    else    {
        if(val<=root->data)    {
            root->leftc++;
            root->left=insert(root->left,val);
            root->height=max(height(root->left),height(root->right))+1;
            root=checkheight(root);
        }
        else if(val>root->data)    {
            root->rightc++;
            root->right=insert(root->right,val);
            root->height=max(height(root->left),height(root->right))+1;
            root=checkheight(root);
        }
    }
        
        return root;
}

void avl_tree::inorder(node *root)    {
    if(root!=NULL)    {
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
    else
        return;
    
}
int avl_tree::findmedianutil(node *root,int index,int pos)    {
    int leftheight=0,rightheight=0;
    if(root==NULL)
        return -1;
    
    pos+=root->leftc +1;
    if(pos==index)
        return root->data;
    else    {
        if(index<pos)    {
            return findmedianutil(root->left,index,pos-(root->leftc+1));
        }
        else
        {
            return findmedianutil(root->right,index,pos);
        }
        
    }
    return 0;  
}

int avl_tree::findmedian(node *root,int index)    {
    return findmedianutil(root,index,0);
}

int main()    {
    string c;
    avl_tree a;
    node *tn=NULL;
    double ans=0.0;
    int n=1,index,ans1,ans2,num;
    int t;
    cin>>t;
    while(t--)    {
        cin>>num;
        if(num==-1)
            break;
        tn=a.insert(tn,num);
        if(n%2==0)    {
            ans1=a.findmedian(tn,(n/2));
            ans2=a.findmedian(tn,(n/2)+1);
            ans=(double)(ans1+ans2)/2;
            cout<<ans<<endl;
        }
        else    {
            ans=a.findmedian(tn,(n+1)/2);
            cout<<ans<<endl;
        }
        n++;
    }
    //a.inorder(tn);
    return 0;
}
