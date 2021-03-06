#include<iostream>
#include<queue>
#include<string>
#include<cstdio>
using namespace std;
typedef struct 
{
    int x;
    int y;
    int z;
    int num;
}point;
int n;
point begin_;
point end_;
bool ture;
char map[11][11][11];
int dir[6][3]={{0,0,1},{0,0-1},{0,1,0},{0,-1,0},{1,0,0},{-1,0,0}};
void bfs(point start)
{
    queue<point>enqueue;
    point next,outqueue;
    if(start.x==end_.x&&start.y==end_.y&&start.z==end_.z)
    {
        ture=true;
        return;
    }
    map[start.x][start.y][start.z]='X';
    enqueue.push(start);
    while(!enqueue.empty())
    {
        outqueue=enqueue.front();
        enqueue.pop();
        for(int i=0;i<6;++i)
        {
            next.x=outqueue.x+dir[i][0];
            next.y=outqueue.y+dir[i][1];
            next.z=outqueue.z+dir[i][2];
            next.num=outqueue.num+1;
            if(next.x==end_.x&&next.y==end_.y&&next.z==end_.z)
            {
                begin_.num=next.num;
                ture=true;
                return;
            }
            if(next.x<0||next.y<0||next.z<0||next.x>=n||next.y>=n||next.z>=n)
                continue;
            if(map[next.z][next.x][next.y]=='X')
                continue;
            map[next.z][next.x][next.y]='X';
            enqueue.push(next);
        }
    }
    return;
}
int main()
{
    string END,START;
    while(cin>>START>>n)
    {
        ture=false;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin>>map[i][j];
        cin>>begin_.x>>begin_.y>>begin_.z;
        cin>>end_.x>>end_.y>>end_.z;
        cin>>END;
        begin_.num=0;
        bfs(begin_);
        if(ture)cout<<n<<' '<<begin_.num<<endl;
        else cout<<"NO ROUTE"<<endl;
    }
    return 0;
}
