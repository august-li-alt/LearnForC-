/*
该题为PAT 1003题Emergency
*/

#include <iostream>
#include "math.h"
#include <vector>

//首先C++ 创建图结构应该至少有两种方法，一种是构建邻接矩阵，另外一种是使用链表法
using namespace std;

const int INF=10000000;

//定义一个输入类
class edges{
public:
    int point_first,point_second;
    int distance;
};

class Graph{
public:
    int point_num;
    int **graph_matrix;
    vector<int> MinDistance;
    int *TeamsNum;
    int *PathNum;
    


private:

    int** graph_mat(int point_num){
        int **mat;
        mat= new int*[point_num];
        for (int i=0;i<point_num;i++){
            mat[i]=new int[point_num];
            mat[i]={0};
        }
        return mat;
    }

    //将边填充入邻接矩阵
    void edgetomat(int road_num,edges *roads){
        //将没有的边赋值INF，自身设置为0
        for (int i = 0; i < point_num; i++)
        {
            for (int j = 0; j < point_num; j++)
            {
                if (j==i){
                    graph_matrix[i][j]=0;
                }
                else{
                    graph_matrix[i][j]=INF;
                }
            }
            
        }
        //根据已有的边进行赋值
        for(int i=0;i<road_num;i++){
            graph_matrix[roads[i].point_first][roads[i].point_second]=roads[i].distance;
        } 
    }

public:
    Graph(int point_num,int road_num,edges *roads){
        this->point_num=point_num;
        this->graph_matrix=graph_mat(point_num);//在此先生成n*n维的空邻接矩阵
        edgetomat(road_num,roads);
    }


};



//此题我使用的是图的方法来构建的，不能使用深度或广度优先搜索算法，需要用dijkstra算法寻找最短路径
void Dijkstra(Graph graph,int start_point,int *point_add_teams)
{
    vector<int> visited_distance(graph.point_num);   //用来记录每个点到起始点的最短路程
    fill(visited_distance.begin(),visited_distance.end(),INF);
    bool *g_visited;
    g_visited=new bool[graph.point_num];
    //题目缘故，需要将经过路径的队伍数累计起来
    int *team_num;
    team_num=new int[graph.point_num];
    int *path_num;              //记录在该顶点处发生最短路径分支的次数
    path_num=new int[graph.point_num];
    for (size_t i = 0; i < graph.point_num; i++)
    {
        team_num[i]=point_add_teams[i];
        path_num[i]=0;
    }
    
    //初始化未被访问的顶点数组
    for (int i=0;i<graph.point_num;i++)
    {
        g_visited[i]=false;
    }
    //初始化顶点
    // g_visited[start_point]=true;
    visited_distance[start_point]=0;
    path_num[start_point]=1;
    for(int i=0;i <graph.point_num;i++)
    {
        //先寻找到距离起始点最短的点
        int MIN=INF;
        // visited_distance[i]=INF;
        int u=-1;
        for (int j =0;j<graph.point_num;j++)
        {
            if (g_visited[j]==false && visited_distance[j]<MIN)
            {
                MIN=visited_distance[j];
                u=j;
            }
        }
        if (u==-1)
        {
            //若进入此判断内，说明没有顶点直接与起始点相连
            cout<<"没有顶点与起始点直接相连"<<endl;
            return;
        }
        //寻找与最短距离点连接的点，并且更新通过其余各顶点到起始点的距离
        g_visited[u]=true;
        for (int v=0;v<graph.point_num;v++)
        {
            if (g_visited[v]==false && visited_distance[u]+graph.graph_matrix[u][v]<visited_distance[v])
            {
                //更新距离表
                visited_distance[v]=visited_distance[u]+graph.graph_matrix[u][v];
                //更新队伍数量表
                team_num[v]=point_add_teams[v]+team_num[u];
                //更新路径条数
                path_num[v]=path_num[u];
            }
            //如果出现相等的情况，就代表出现了分支
            if (g_visited[v]==false && visited_distance[u]+graph.graph_matrix[u][v]==visited_distance[v])
            {
                //判断队伍数量大小
                if (point_add_teams[v]+team_num[u]>team_num[v])
                {
                    team_num[v]=point_add_teams[v]+team_num[u];
                }
                //更新路径条数
                path_num[v]=path_num[u]+path_num[v];
            }
            
            
        }

    }
    graph.MinDistance.assign(visited_distance.begin(),visited_distance.end());
    graph.TeamsNum=team_num;
    graph.PathNum=path_num;

}

//深度优先搜索算法
void DFS(Graph graph,int start_point,int target_city){
    bool *g_visited;
    g_visited=new bool[graph.point_num];
    //初始化未被访问的顶点数组
    for (int i=0;i<graph.point_num;i++)
    {
        g_visited[i]=false;
    }
    g_visited[start_point]=true;//起始顶点已被访问    

}
//打印vector
template<typename T>
void PrintVector(vector<T> &input_vector)
{
    for (auto it=input_vector.begin(); it != input_vector.end(); it++)
    {
        cout<<*it<<endl;
    }
    
}

//打印数组
template<typename T>
void PrintArray(T &input_array)
{
    for (int i=0; i< sizeof(input_array)/sizeof(input_array[0]);i++)
    {
        cout<<input_array[i];
    }
}



int main(){
    int city_num;
    int road_num;
    int first_mat[4];
    for (int i=0;i<4;i++){
        cin>>first_mat[i];
    }
    city_num=first_mat[0];
    road_num=first_mat[1];
    int initial_city=first_mat[2];
    int target_city=first_mat[3];
    //定义每个城市拥有消防队的数组
    int *city_add_teams;
    city_add_teams=new int[city_num];
    for (int i=0;i<city_num;i++){
        cin>>city_add_teams[i];
    }
    edges *road;
    road=new edges[road_num];
    for (int i=0;i<road_num;i++){
        cin>>road[i].point_first>>road[i].point_second>>road[i].distance;
    }
    Graph city_graph(city_num,road_num,road);
    //图构建完成,开始进行搜索算法，使用dijkstra算法
    Dijkstra(city_graph,initial_city,city_add_teams);
    
    cout<<"各点到起始点的最短路程："<<endl;
    PrintVector(city_graph.MinDistance);
    cout<<"每个顶点的最短路径条数"<<endl;
    PrintArray(city_graph.PathNum);
    cout<<"最短路径下每个顶点能召集的最大队伍数"<<endl;
    PrintArray(city_graph.TeamsNum);

    return 0;
    
    
}

