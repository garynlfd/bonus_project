#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <string>
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

class city
{
public:
    string name;
    int num;
    int h_credit;
    int open_t;
    int close_t;
};
typedef pair<int, int> bridge;
class Map
{
    int V;
    int quota, s_time;
    int location;
    list<bridge> *adj;
public:
    Map(int V, int quota, int s_time, city& a)
    {
        this->V = V;
        this->quota = quota;
        this->s_time = s_time;
        this->location = 0;
        adj = new list<bridge> [V];
    }
    void addEdge(city u, city v, int w)
    {
        adj[u.num].push_back(make_pair(v.num, w));
        adj[v.num].push_back(make_pair(u.num, w));
    }
    void shortestPath(int src)
    {
        priority_queue<bridge, vector<bridge>, greater<bridge> > pq;
        vector<int> dist(V, INF);
        pq.push(make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = (*i).first;
                int weight = (*i).second;

                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        for(int i = 0; i < V; ++i)
        {
            if((a[i].h_credit/dist[i]))
        }
    }
    bool back_to_start(int src)
    {
        priority_queue<bridge, vector<bridge>, greater<bridge> > pq;
        vector<int> dist(V, INF);
        pq.push(make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = (*i).first;
                int weight = (*i).second;

                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        if(dist[0] > quota) return true;
        else return false;
    }
    void make_move(int time) //time = dist[last node to cur node]
    {
        path.insert(a[], s_time + time);
        a[location].h_credit = 0;
        location = ;
    }
};

int main(int argc, const char *argv[]) {
    std::string file = "./";
    std::string studentID = argv[1];
    std::string fileinput = file + studentID + "/tp.data";
    std::string fileoutput = file + studentID + "/ans1.txt";
    std::ifstream input;
    std::ofstream output;
    input.open(fileinput.c_str());
    if(input)
    {
        int nodes, edges, quota, s_time;
        input >> nodes >> edges >> quota >> s_time;
        city *a = new city[nodes];
        city city1, city2;
        int distance, k, m;
        Map m1(nodes, t_time, s_time);
        for(int i = 0; i < nodes; ++i)
        {
            input >> a[i].name >> a[i].h_credit >> a[i].open_t >> a[i].close_t;
            a[i].num = i;
        }
        for(int j = 0; j < edges; ++j)
        {
            input >> city1.name >> city2.name >> distance;
            for(k = 0; k < nodes; ++k)
            {
                if(a[k].name == city1.name) break;
            }
            for(m = 0; m < nodes; ++m)
            {
                if(a[m].name == city2.name) break;
            }
            m1.addEdge(a[k], a[m], distance);
        }
        output.open(fileoutput.c_str());
        std::vector<FloorCleaner::Cell> path = robot->CleaningPath();
        output << robot->TotalSteps() << std::endl;
        output.close();
        input.close();
    }
    else std::cerr << "failed to open \"floor.data\"" << std::endl;
    return 0;
}
