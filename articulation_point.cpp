/*
Problem Statement: Find Articulation point in a graph
For a disconnected undirected graph, an articulation point is a vertex removing which
increases number of connected components.
NOTE: You are not allowed to use STLs or any other inbuilt libraries.
*/

#include<bits/stdc++.h>
using namespace std;
int time1=0;
class Graph {
    public:
    int V;
    int **adj;
    public:
    Graph(int);
    void addedge(int,int);
    void printgraph(int);
    void findartpt(int,int,bool[],int[],int[],int[],int[]);

};
Graph::Graph(int v)  {
    this->V=v;
    adj=new int*[v];
    for(int i=0;i<v;i++)    {
        adj[i]=new int[v];
        for(int j=0;j<v;j++)    
            adj[i][j]=0;
    }
}
void Graph::addedge(int u,int v)    {
    adj[u][v]=1;
    adj[v][u]=1;
}
void Graph::printgraph(int n)    {
    for(int i=0;i<n;i++)    {
        for(int j=0;j<n;j++) {
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void Graph::findartpt(int v,int n,bool visited[],int parent[],int lowtime[],int vistime[],int artpts[])    {
    visited[v]=true;
    lowtime[v]=time1+1;
    vistime[v]=time1+1;
    time1++;
    int child=0;
    bool isartpt=false;
    for(int k=0;k<n;k++)    {
        if(adj[v][k]==1 && k!=v)    {
            int it=k;
            if(!visited[it])    {
                child++;
                parent[it]=v;
                findartpt(it,n,visited,parent,lowtime,vistime,artpts);
                if(vistime[v]<=lowtime[it])
                    isartpt=true;
                else    
                    lowtime[v]=min(lowtime[v],lowtime[it]);
            }
            else    
                lowtime[v]=min(lowtime[v],vistime[it]);
        }
    }
    if(parent[v]==-1 && child>=2)
        artpts[v]=1;
    else if(parent[v]!=-1 && isartpt==true)
        artpts[v]=1;
}

int main()  {
    int v,v1,v2,e,i;
    cout<<"Enter the number of vertices in the graph: "<<endl;
    cin>>v;
    Graph g(v);
    cout<<"Enter the number of edges: "<<endl;
    cin>>e;
    for(i=0;i<e;i++)    {
        cin>>v1;
        cin>>v2;
        g.addedge(v1,v2);
    }
    int *vistime,*lowtime,*artpts,*parent;
    bool *visited;
    vistime=new int[v];
    lowtime=new int[v];
    artpts=new int[v];
    parent=new int[v];
    visited=new bool[v];
    for(i=0;i<v;i++)    {
        visited[i]=false;
        parent[i]=-1;
        artpts[i]=0;
    }
    for(i=0;i<v;i++)    {
        if(visited[i]==false)
           g.findartpt(i,v,visited,parent,lowtime,vistime,artpts);
    }
    cout<<"The articulation points are: "<<endl;
    for(i=0;i<v;i++)    {
        if(artpts[i]==1)
           cout<<i<<" ";
    }
    cout<<endl;
}
