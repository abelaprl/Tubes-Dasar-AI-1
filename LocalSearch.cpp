#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int value;
    int state[6][6][6];
} CUBE;

int findValue(CUBE c)
{
    int cnt=0;
    for(int i=1; i<=5; i++) 
    {
        for(int j=1; j<=5; j++)
        {
            if(c.state[1][i][j]+c.state[2][i][j]+c.state[3][i][j]+
            c.state[4][i][j]+c.state[5][i][j]!=315) //baris
            {
                cnt--;
            }
            if(c.state[i][1][j]+c.state[i][2][j]+c.state[i][3][j]+
            c.state[i][4][j]+c.state[i][5][j]!=315) //kolom
            {
                cnt--;
            }
            if(c.state[i][j][1]+c.state[i][j][2]+c.state[i][j][3]+
            c.state[i][j][4]+c.state[i][j][4]!=315) //tiang
            {
                cnt--;
            }
        }
    }
    for(int i=1; i<=5; i++)
    {
        if(c.state[1][1][i]+c.state[2][2][i]+c.state[3][3][i]+
        c.state[4][4][i]+c.state[5][5][i]!=315) cnt--;
        if(c.state[1][5][i]+c.state[2][4][i]+c.state[3][3][i]+
        c.state[4][2][i]+c.state[5][1][i]!=315) cnt--;

        if(c.state[1][i][1]+c.state[2][i][2]+c.state[3][i][3]+
        c.state[4][i][4]+c.state[5][i][5]!=315) cnt--;
        if(c.state[1][i][5]+c.state[2][i][4]+c.state[3][i][3]+
        c.state[4][i][2]+c.state[5][i][1]!=315) cnt--;
        
        if(c.state[i][1][1]+c.state[i][2][2]+c.state[i][3][3]+
        c.state[i][4][4]+c.state[i][5][5]!=315) cnt--;
        if(c.state[i][1][5]+c.state[i][2][4]+c.state[i][3][3]+
        c.state[i][4][2]+c.state[i][5][1]!=315) cnt--;
    }
    if(c.state[1][1][1]+c.state[2][2][2]+c.state[3][3][3]+c.state[4][4][4]+c.state[5][5][5]) cnt--;
    if(c.state[5][1][1]+c.state[4][2][2]+c.state[3][3][3]+c.state[2][4][4]+c.state[1][5][5]) cnt--;
    if(c.state[1][5][1]+c.state[2][4][2]+c.state[3][3][3]+c.state[4][2][4]+c.state[5][1][5]) cnt--;
    if(c.state[5][5][1]+c.state[4][4][2]+c.state[3][3][3]+c.state[2][2][4]+c.state[1][1][5]) cnt--;
    return cnt;
}

CUBE highestSuccessor(CUBE c)
{
    CUBE h;
    h.value=-316;
    int i_ans, j_ans, k_ans, l_ans, m_ans, n_ans;
    for(int i=1; i<=5; i++)
    {
        for(int j=1; j<=5; j++)
        {
            for(int k=1; k<=5; k++)
            {
                for(int l=1; l<=5; l++)
                {
                    for(int m=1; m<=5; m++)
                    {
                        for (int n=1; n<=5; n++)
                        {
                            swap(c.state[i][j][k],c.state[l][m][n]);
                            if(findValue(c)>h.value)
                            {
                                h.value=findValue(c);
                                i_ans=i; j_ans=j; k_ans=k;
                                l_ans=l; m_ans=m; n_ans=n;
                            }
                            swap(c.state[i][j][k],c.state[l][m][n]);
                        }
                    }
                }
            }
        }
    }
    swap(c.state[i_ans][j_ans][k_ans],c.state[l_ans][m_ans][n_ans]);
    return c;
}

CUBE randomSuccessor(CUBE c)
{
    int i=((rand()%5)+1);
    int j=((rand()%5)+1);
    int k=((rand()%5)+1);
    int l=((rand()%5)+1);
    int m=((rand()%5)+1);
    int n=((rand()%5)+1);
    while(i==k && j==m && k==n)
    {
        k=((rand()%5)+1);
    }
    swap(c.state[i][j][k],c.state[l][m][n]);
    return c;
}

void generateInitialState(CUBE *c)
{
    int new_random;
    bool unique;
    bool check[126];
    memset(check, 0, sizeof(check));
    for (int i=1; i<=5; i++)
    {
        for (int j=1; j<=5; j++)
        {
            for (int k=1; k<=5; k++)
            {
                do
                {
                    new_random=((rand()%125)+1);
                    unique=true;
                    if(check[new_random]) unique=false;
                }
                while(!unique);
                check[new_random]=true;
                (*c).state[i][j][k]=new_random;
            }
        }
    }
}

void printState(CUBE c)
{
    for(int i=1; i<=5; i++)
    {
        cout<<"Layer "<<i<<endl;
        for(int j=1; j<=5; j++)
        {
            for (int k=1; k<=5; k++)
            {
                cout<<c.state[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}
int main()
{
    srand(time(0));
    CUBE current;
    generateInitialState(&current);
    printState(current);
    cout<<endl<<findValue(current)<<endl;
    current=highestSuccessor(current);
    printState(current);
    cout<<endl<<findValue(current);
}