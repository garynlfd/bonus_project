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
int back_to_start_distance[100];
string back_to_start_city[100];
int index_of_back_to_start;
queue<string> name;
queue<int> T;
int credit_ans;
int distance_ans;

class city
{
public:
    string name;
    int* adj;
    int num;
    int h_credit;
    int open_t;
    int close_t;
};
class Map
{
    city* a;
    int V;
    int quota, s_time;
    int distance_accumulation;
    int credit_accumulation;
public:
    vector<pair<string, int> >path;
    Map(int V, int quota, int s_time)
    {
        this->V = V;
        this->quota = quota;
        this->s_time = s_time;
        this->distance_accumulation = 0;
        this->credit_accumulation = 0;
    }
    void pluse_start_credit(city *a)
    {
        credit_accumulation += a[0].h_credit;
    }
    void make_move(int src, city *a)
    {
        int flag = 0;
        int next_src = 0;
        int num_of_pre_path = 0;
        for(int i = 0; i < V; ++i)
        {
            if(a[src].adj[i] >= 0)
            {
                num_of_pre_path++;
            }
        }
        int* max_distance = new int [num_of_pre_path];
        int* max_credit = new int [num_of_pre_path];
        int* order = new int [num_of_pre_path];
        for(int i = 0; i < num_of_pre_path; ++i)
        {
            max_distance[i] = 0;
            max_credit[i] = 0;
        }
        int max_index = 0;
        for(int i = 0; i < V; ++i)
        {
            if(a[src].adj[i] >= 0)
            {
                max_distance[max_index] = a[src].adj[i];
                order[max_index] = i;
                max_credit[max_index++] = a[i].h_credit;
            }
        }
        for (int i = 1; i < max_index; ++i) //insertion sort
        {
            int key = max_credit[i];
            int key_2 = max_distance[i];
            int key_3 = order[i];
            int j = i - 1;
            while (key < max_credit[j] && j >= 0)
            {
                max_credit[j+1] = max_credit[j];
                max_distance[j+1] = max_distance[j];
                order[j+1] = order[j];
                j--;
            }
            max_credit[j+1] = key;
            max_distance[j+1] = key_2;
            order[j+1] = key_3;
        }
        for(int i = max_index - 1; i >= 0; --i)
        {
            if(quota - max_distance[i] >= distance_accumulation + max_distance[i])
            {
                next_src = order[i];
                back_to_start_distance[index_of_back_to_start] = a[src].adj[next_src];
                back_to_start_city[index_of_back_to_start++] = a[next_src].name;
                distance_accumulation += max_distance[i];
                credit_accumulation += a[next_src].h_credit;
                quota -= a[src].adj[next_src];
                name.push(a[next_src].name);
                T.push(s_time + distance_accumulation);
                a[src].h_credit = 0;
                make_move(next_src, a);
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            for(int i = index_of_back_to_start - 1; i >= 0; --i)
            {
                if(i == 0)
                {
                    name.push(a[0].name);
                    T.push(s_time + distance_accumulation + back_to_start_distance[i]);
                    distance_accumulation += back_to_start_distance[i];
                    credit_ans = credit_accumulation;
                    distance_ans = distance_accumulation;
                }
                else
                {
                    name.push(back_to_start_city[i-1]);
                    T.push(s_time + distance_accumulation + back_to_start_distance[i]);
                    distance_accumulation += back_to_start_distance[i];
                }
            }
            return;
        }
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
        cin >> nodes >> edges >> quota >> s_time;
        city *a = new city[nodes];
        city city1, city2;
        int distance, k, m;
        Map m1(nodes, quota, s_time);
        for(int i = 0; i < nodes; ++i)
        {
            cin >> a[i].name >> a[i].h_credit >> a[i].open_t >> a[i].close_t;
            a[i].num = i;
            for(int j = 0; j < nodes; ++j)
            {
                if(j == 0)
                {
                    a[i].adj = new int [nodes];
                    a[i].adj[j] = -1;
                }
                else a[i].adj[j] = -1;
            }
        }
        for(int j = 0; j < edges; ++j)
        {
            cin >> city1.name >> city2.name >> distance;
            for(k = 0; k < nodes; ++k)
            {
                if(a[k].name == city1.name) break;
            }
            for(m = 0; m < nodes; ++m)
            {
                if(a[m].name == city2.name) break;
            }
            a[k].adj[m] = distance;
        }
        int distance_tmp = 0;
        for(int i = 0; i < nodes; ++i)
        {
            for(int j = 0; j < nodes; ++j)
            {
                if(a[i].adj[j] > 0)
                {
                    a[j].adj[i] = a[i].adj[j];
                }
            }
        }
        m1.pluse_start_credit(a);
        m1.make_move(0, a);
        output.open(fileoutput.c_str());
        output << credit_ans << " " << distance_ans << endl;
        output << a[0].name << " " << s_time << " " << s_time << endl;
        while(name.size() != 0)
        {
            output << name.front() << " " << T.front() << " " << T.front() << endl;
            name.pop();T.pop();
        }
        output.close();
        delete a;
        input.close();
    }
    else std::cerr << "failed to open \"tp.data\"" << std::endl;
    return 0;
}
