/*
Problem Statement: Implement ordered set with suitable data structure.
An ordered set is a common data structure that supports O(log N) lookups, insertions
and removals. Ordered set is also sometimes used as an alternative to a hash map, for
example in STL’s map.
Following operation should be implemented on ordered set.
O(log N) insertion and removal.
O(log N) check if contains a value.
O(log N) to find the element in the set closest to some value.
O(log N) to find k-th largest element in the set.
O(log N) to count the number of elements in the set whose values fall into a
given range.
*/


#include<iostream>
#include<bits/stdc++.h>
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

class ordered_set	{
	public:
	ordered_set();
	int height(node *);
	node *insert(node *,int);
    node *insertutil(node *,int);
	node *llrotation(node *);
	node *lrrotation(node *);
	node *rlrotation(node *);
	node *rrrotation(node *);
	node *checkheight(node *);
	void inorder(node *);
	node *maxinleft(node *);
	node *mininright(node *);
	node *deleten(node *,int);
    node *deleteutil(node *,int);
	int max(int,int);
    int kth_smallest_util(node *,int,int);
    int kth_smallest(node *,int);
    int kth_largest_util(node *,int,int);
    int kth_largest(node *,int);
    bool contains(node *,int);
	int closest_util(node *,int,int);
	int closest(node *,int);
	int rangequery(node *,int,int);
	int no_smallest_util(node *,int,int);
    int no_smallest(node *,int);
};
ordered_set::ordered_set()    {}

int ordered_set::max(int a,int b)    {
    return (a>b)?a:b;
}
int ordered_set::height(node *x)    {
    if(x==NULL)
        return 0;
    return x->height;
}

node* ordered_set::checkheight(node *x)    {
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
node* ordered_set::llrotation(node *gp)    {
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

node* ordered_set::rrrotation(node *gp)    {
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

node* ordered_set::lrrotation(node *gp)    {
    node *p;
    p=gp->left;
    gp->left=rrrotation(p);
    gp=llrotation(gp);
    return gp;
}

node* ordered_set::rlrotation(node *gp)    {
    node *p;
    p=gp->right;
    gp->right=llrotation(p);
    gp=rrrotation(gp);
    return gp;
}

node* ordered_set::insertutil(node *root,int val)    {
    if(root==NULL)    {
        root=new node(val);
        return root;
    }
    else    {
        if(val<root->data)    {
            root->leftc++;
            root->left=insertutil(root->left,val);
            root->height=max(height(root->left),height(root->right))+1;
            root=checkheight(root);
        }
        else if(val>root->data)    {
            root->rightc++;
            root->right=insertutil(root->right,val);
            root->height=max(height(root->left),height(root->right))+1;
            root=checkheight(root);
        }
    }
        
        return root;
}
node* ordered_set::insert(node *root,int val)    {
    if(contains(root,val))  {
        cout<<"Set cannot contain duplicate elements\n";
        return root;
    }
    return insertutil(root,val);
}

void ordered_set::inorder(node *root)    {
    if(root!=NULL)    {
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
    else
        return;
    
}
node* ordered_set::maxinleft(node *root)	{
	if(root->right==NULL)
		return root;
	return maxinleft(root->right);
}

node* ordered_set::mininright(node* root)   { 
	if(root->left==NULL)
		return root;
	return mininright(root->left);
}

node* ordered_set::deleteutil(node *root,int val)	{
	if(root==NULL)
		return root;
	if(val==root->data)	{
		if(root->left==NULL && root->right==NULL)	{
			node *child=root;
			root=NULL;
			free(child);
		}
		else if(root->left==NULL)	{
			node *child=root->right;
			*root=*child;
			free(child);
		}
		else if(root->right==NULL)	{
			node *child=root->left;
			*root=*child;
			free(child);
		}
		else	{
			node *child=mininright(root->right);
			root->data=child->data;
			root->rightc--;
			root->right=deleteutil(root->right,child->data);
		}
	}
	else if(val<root->data)	{
		root->leftc--;
		root->left=deleteutil(root->left,val);
	}
	else	{
		root->rightc--;
		root->right=deleteutil(root->right,val);
	}
	if(root==NULL)
		return root;
	root=checkheight(root);
	return root;	
}

node* ordered_set::deleten(node *root,int val)	{
    if(!contains(root,val)) {
        cout<<"Value not present in set. Cannot delete!\n";
        return root;
    }
    return deleteutil(root,val);
}

int ordered_set::kth_smallest_util(node *root,int index,int pos)	{
	if(root==NULL)
		return -1;
	
	pos+=root->leftc +1;
	if(pos==index)
		return root->data;
	else	{
		if(index<pos)	{
			return kth_smallest_util(root->left,index,pos-(root->leftc+1));
		}
		else
		{
			return kth_smallest_util(root->right,index,pos);
		}
		
	}	
}

int ordered_set::kth_smallest(node *root,int k)    {
    return kth_smallest_util(root,k,0);
}

int ordered_set::kth_largest_util(node *root,int index,int pos)	{
	if(root==NULL)
		return -1;
	
	pos+=root->rightc +1;
	if(pos==index)
		return root->data;
	else	{
		if(index>pos)	{
			return kth_largest_util(root->left,index,pos);
		}
		else
		{
			return kth_largest_util(root->right,index,pos-(root->rightc +1)); 
		}
		
	}	
}

int ordered_set::kth_largest(node *root,int k)    {
    return kth_largest_util(root,k,0);
}

bool ordered_set::contains(node *root,int val)   {
	if(root==NULL)
		return false;
    if(root->data == val)
        return true;
    else if(val<root->data)
        return contains(root->left,val);
    else
        return contains(root->right,val);
}

int ordered_set::closest_util(node *root,int val,int x) {
	int diffparent,diffchild;
    if(val==root->data)
        return root->data;
	diffparent=abs(x-val);
	diffchild=abs(root->data - val);
	if(diffparent<=diffchild && root->right==NULL && val>root->data)	{
		if(diffparent==diffchild)
			return (x<=root->data)?x:root->data;
		return x;
	}
	if(diffparent<=diffchild && root->left==NULL && val<root->data)	{
		if(diffparent==diffchild)
			return (x<=root->data)?x:root->data;
		return x;
	}
    else if(root->left==NULL && root->right==NULL)
        return root->data;

    if(val<root->data)  {
		if(diffparent==diffchild)	{
			x=(x<=root->data)?x:root->data;
		}
		else
        x=(diffparent<diffchild)?x:root->data;
        return closest_util(root->left,val,x);
    }
	else	{
		if(diffparent==diffchild)	{
			x=(x<=root->data)?x:root->data;
		}
		else
        x=(diffparent<diffchild)?x:root->data;
		return closest_util(root->right,val,x);
	}
	return -1;
}

int ordered_set::closest(node *root,int val) {
    if(root==NULL)
	return -1;
    if(val==-1)
        return kth_smallest(root,1);
	return closest_util(root,val,INT_MAX);
}

int ordered_set::no_smallest_util(node *root,int val,int pos)	{
	int leftheight=0,rightheight=0;
	if(root==NULL)
		return pos;
	
	pos+=root->leftc +1;
	if(root->data==val)
		return pos;
	else	{
		if(val<root->data)	{
			return no_smallest_util(root->left,val,pos-(root->leftc+1));
		}
		else
		{
			return no_smallest_util(root->right,val,pos);
		}
		
	}
}

int ordered_set::no_smallest(node *root,int value)    {
    return no_smallest_util(root,value,0);
}

int ordered_set::rangequery(node *root,int val1,int val2) {
	int temp,c1=0,c2=0,counter=0;
	if(val2<val1)	{
		temp=val2;
		val2=val1;
		val1=temp;
	}
	if(contains(root,val1) && contains(root,val2))
		counter=1;
	else if(contains(root,val1) && (!(contains(root,val2))))
		counter=1;
	c1=no_smallest(root,val1);
	c2=no_smallest(root,val2);
	return (c2-c1+counter);
}

int main()    {
    ordered_set a;
    node *tn=NULL;
    int ch;
	cout<<"Enter your choice: \n 1 to insert \n 2 to delete \n 3 to display \n";
	cout<<" 4 to check if it contains a value \n 5 to find element in set closest to some value \n";
	cout<<" 6 to find kth largest element in set \n";
	cout<<" 7 to count number of elements in a given range\n -1 to exit\n";
	cin>>ch;
	while(ch!=-1)	{
		switch (ch)	{
		case 1:
			int num;
			cin>>num;
			tn=a.insert(tn,num);
			break;
		case 2:
			int num1;
			cin>>num1;
			tn=a.deleten(tn,num1);
			break;
		case 3:
			a.inorder(tn);
			break;
		case 4:
			int con;
			cin>>con;
			if(a.contains(tn,con))
				cout<<"Yes\n";
			else
				cout<<"No\n";
			break;
		case 5:
			int cl,cl1;
			cin>>cl;
			cl1=a.closest(tn,cl);
			cout<<"Closest to "<<cl<<" is: "<<cl1<<endl;
			break;
		case 6:
			int k,kl;
			cin>>k;
			kl=a.kth_largest(tn,k);
			cout<<kl<<endl;
			break;
		case 7:
			int r,r1,r2;
			cin>>r1;
			cin>>r2;
			r=a.rangequery(tn,r1,r2);
			cout<<r<<endl;
			break;	
		default:
			cout<<"Wrong input\n";
		}
		cout<<"\nEnter your choice: \n 1 to insert \n 2 to delete \n 3 to display \n";
		cout<<" 4 to check if it contains a value \n 5 to find element in set closest to some value \n";
		cout<<" 6 to find kth largest element in set \n";
		cout<<" 7 to count number of elements in a given range\n -1 to exit\n";
		cin>>ch;
	}
        
    return 0;
}

