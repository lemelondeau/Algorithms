//
//  main.cpp
//  SumProduct
//
//  Created by tong on 15/10/17.
//  Copyright (c) 2015年 tong. All rights reserved.
//

#include <iostream>
using namespace std;

void BuildAdjMatrix(int ** adjmat,int n)
{
    //initialize matrix
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            adjmat[i][j]=0;

    int a,b;//a,b<=n
    while(1)
    {
    cin>>a;
    cin>>b;
        if(a>0&&a<=n&&b>0&&b<=n)
        {
        adjmat[a-1][b-1]=1;
        adjmat[b-1][a-1]=1;
        }
        else
        {
            cout<<"invalid edge!"<<endl;
        }
        
    // input end
        if(getchar()==27)
            break;
    }
    cout<<"Adjecent Matrix builed"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        { cout<<adjmat[i][j]<<" " ;}
        cout<<endl;
    }
    
}
void SendMessage(int j,int i,int **adjmat,double ***mesmat,int n)
{
    double edge[2][2]={{1,0.5},{0.5,1}};
    double node[6][2]={{0.7,0.3},{0.1,0.9},{0.7,0.3},{0.1,0.9},{0.7,0.3},{0.1,0.9}};
    for(int ik=0;ik<2;ik++)
    {
        double sum_m=0;
        for(int k=0;k<2;k++)
        {
            double product_m=1;//incase of leaf
            for(int p=0;p<n;p++)
            {
                if(adjmat[j-1][p]==1&&p!=i-1)
                    product_m=product_m*mesmat[p][j-1][k];
            }
            
            sum_m=sum_m+node[j-1][k]*edge[ik][k]*product_m;
            
        }
        mesmat[j-1][i-1][ik]=sum_m;
                    cout<<"message("<<j<<","<<i<<","<<ik<<")"<<sum_m<<endl;
    }
    
}
//calculate j to i and save
void Collect(int i,int j,int **adjmat, double ***mesmat,int n)
{
    for(int p=0;p<n;p++)
    {
        if(adjmat[j-1][p]==1&&p!=i-1)
            Collect(j, p+1, adjmat, mesmat, n);
    }
    
    SendMessage(j,i,adjmat,mesmat,n);
}

void Distribute(int i,int j,int **adjmat,double ***mesmat,int n)
{
    SendMessage(i, j, adjmat, mesmat, n);
    
    for(int p=0;p<n;p++)
    {
        if(adjmat[j-1][p]==1&&p!=i-1)
            Distribute(j, p+1, adjmat, mesmat, n);
    }
    
}

void Start(int **adjmat, double ***mesmat,int n)
{
    
    
    for(int i=0;i<n;i++)
    {
        if(adjmat[0][i]==1)
            Collect(1, i+1,adjmat,mesmat,n);
    }
    cout<<"collect end..."<<endl;
    for(int j=0;j<n;j++)
    {
        if(adjmat[0][j]==1)
            Distribute(1, j+1, adjmat, mesmat, n);
    }
    
}
void CalMarginals(double ***mesmat,int n)
{
    double node[6][2]={{0.7,0.3},{0.1,0.9},{0.7,0.3},{0.1,0.9},{0.7,0.3},{0.1,0.9}};
    double p[6][2]={{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}};
    
    double sum=0;
    cout<<"p without normalization:"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int k=0;k<2;k++)
        {
            double product=1;
            for(int j=0;j<n;j++)
            {
                product=product*mesmat[j][i][k];
            }
            p[i][k]=node[i][k]*product;
            cout<<"p("<<i+1<<"="<<k<<")"<<p[i][k]<<endl;
            sum=sum+p[i][k];
        }
        
    }
    
    cout<<"p with normalization:"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int k=0;k<2;k++)
        {
            cout<<"p("<<i+1<<"="<<k<<")"<<p[i][k]/(sum/n)<<endl;
        }
    }

    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    //Create the Adjecent Matrix
    cout << "Hello! Please input the number of nodes:"<<endl;
    int n;
    cin>>n;
    int ** adjmat;
    adjmat=new int *[n];
    for(int i=0;i<n;i++)
    {
        adjmat[i]=new int[n];
    }
    
    cout<<"Please input edges('1 2' denotes there is a edge between node 1 and node 2)"<<endl<<"Press ESC to end input"<<endl;
    BuildAdjMatrix(adjmat,n);
    
    
    double *** mesmat=new double**[n];
    for(int i=0;i<n;i++)
    {
        mesmat[i]=new double*[n];
        for(int j=0;j<n;j++)
        {
            mesmat[i][j]=new double[2];
            
            for(int k=0;k<2;k++)
                mesmat[i][j][k]=1;
        }
        
    }
    
    Start(adjmat, mesmat, n);
    CalMarginals(mesmat, n);
    return 0;
}

