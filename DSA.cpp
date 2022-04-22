#include "bits/stdc++.h"
using namespace std;
struct DSU
{
    vector<int> parent, sze;
    void build(int n)
    {
        parent.resize(n, 0), sze.resize(n, -1);
        for (int k = 0; k < n; k++)
            parent[k] = k, sze[k] = 1;
    }
    int find(int v)
    {
        if (parent[v] == v)
            return v;
        else
            return parent[v] = find(parent[v]);
    }
    void unite(int a, int b)
    {
        a = find(a), b = find(b);
        if (a != b)
        {
            if (sze[a] < sze[b])
                swap(a, b);
            parent[b] = a, sze[a] += sze[b];
        }
    }
};
class Maze
{
public:
    vector<vector<char>> maze;
    int start;
    int end;
    int n;
    void printmaze();
    void buildmaze();
    int AssignWeight();
    Maze(int t);

private:
    set<tuple<int, int, int>> edges;
    set<pair<int, int>> mst;
    DSU dsu;
};
Maze::Maze(int t)
{
    n = t;
    maze.resize(2 * n + 1, vector<char>(2 * n + 1, '-'));
    dsu.build(n * n + 1);
    for (int i = 1; i <= 2 * n + 1; i += 2)
    {
        for (int j = 1; j <= 2 * n + 1; j += 2)
        {
            if (i != 2 * n + 1 && j != 2 * n + 1)
                maze[i][j] = ' ';
            if (j != 2 * n + 1)
                maze[i - 1][j] = '-';
            maze[i - 1][j - 1] = '+';
            if (i != 2 * n + 1)
                maze[i][j - 1] = '|';
        }
    }
}
void Maze::printmaze()
{
    int st = 2 * start + 1, ed = 2 * end + 1;
    while (st--)
        cout << ' ';
    cout << 'v' << endl;
    for (int i = 0; i < 2 * n + 1; i++)
    {
        for (int j = 0; j < 2 * n + 1; j++)
            cout << maze[i][j];
        cout << endl;
    }
    while (ed--)
        cout << ' ';
    cout << 'v' << endl;
}
void Maze::buildmaze()
{
    for (int i = 1; i <= n; i++)
    {
        int f = (i - 1) * n;
        for (int j = f + 1; j <= f + n; j++)
        {
            if (j < f + n)
            {
                int getWeight = AssignWeight();
                edges.insert({getWeight, j, j + 1});
            }
            if (j + n <= n * n)
            {
                int getWeight = AssignWeight();
                edges.insert({getWeight, j, j + n});
            }
        }
    }
    for (auto [w, u, v] : edges)
    {
        if (dsu.find(u) != dsu.find(v))
        {
            dsu.unite(u, v);
            mst.insert({u, v});
        }
    }
    for (auto [u, v] : mst)
    {
        int i = (u - 1) / n, j = (u - 1) % n;
        if (v == u + 1) maze[2 * i + 1][2 * j + 2] = ' ';
        else maze[2 * i + 2][2 * j + 1] = ' ';
    }

    start = rand() % n;
    end = rand() % n;
    maze[0][2 * start + 1] = ' ';
    maze[2 * n][2 * (end) + 1] = ' ';
}

int Maze::AssignWeight()
{
    return rand()%1000;
}
int dijkstra(Maze m)
{
    int n = 2 * m.n + 1;
    pair<int, int> start = {0, 2 * m.start + 1}, end = {2 * m.n, 2 * m.end + 1};
    vector<vector<int>> dis(n, vector<int>(n, INT_MAX));
    vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(n));
    set<pair<int, pair<int, int>>> s;
    s.insert({0, start});
    while (!s.empty())
    {
        pair<int, pair<int, int>> a = *s.begin();
        s.erase(s.begin());
        int dist = a.first, x = a.second.first, y = a.second.second;
        if (x < n - 1 and m.maze[x + 1][y] == ' ' and dis[x + 1][y] > dist + 1)
        {
            if (s.find({dis[x + 1][y], {x + 1, y}}) != s.end())
                s.erase(s.find({dis[x + 1][y], {x + 1, y}}));
            s.insert({dist + 1, {x + 1, y}});
            dis[x + 1][y] = dist + 1;
            par[x + 1][y] = {x, y};
        }
        if (x > 0 and m.maze[x - 1][y] == ' ' and dis[x - 1][y] > dist + 1)
        {
            if (s.find({dis[x - 1][y], {x - 1, y}}) != s.end())
                s.erase(s.find({dis[x - 1][y], {x - 1, y}}));
            s.insert({dist + 1, {x - 1, y}});
            dis[x - 1][y] = dist + 1;
            par[x - 1][y] = {x, y};
        }
        if (y > 0 and m.maze[x][y - 1] == ' ' and dis[x][y - 1] > dist + 1)
        {
            if (s.find({dis[x][y - 1], {x, y - 1}}) != s.end())
                s.erase(s.find({dis[x][y - 1], {x, y - 1}}));
            s.insert({dist + 1, {x, y - 1}});
            dis[x][y - 1] = dist + 1;
            par[x][y - 1] = {x, y};
        }
        if (y < n - 1 and m.maze[x][y + 1] == ' ' and dis[x][y + 1] > dist + 1)
        {
            if (s.find({dis[x][y + 1], {x, y + 1}}) != s.end())
                s.erase(s.find({dis[x][y + 1], {x, y + 1}}));
            s.insert({dist + 1, {x, y + 1}});
            dis[x][y + 1] = dist + 1;
            par[x][y + 1] = {x, y};
        }
    }
    if (dis[end.first][end.second] > 1e9)
    {
        cout << "No Solution\n";
        return -1;
    }
    else
    {
        pair<int, int> x = end;
        while (x != start)
        {
            int a = x.first, b = x.second;
            m.maze[a][b] = '\'';
            x = par[a][b];
            if (x == start)
                break;
        }
        m.maze[x.first][x.second] = '\'';
        m.printmaze();
    }
    return 0;
}

int main()
{

    cout << "Enter the size of the maze : ";
    srand(time(0));
    int n;
    cin >> n;
    cout << "\n\n";
    Maze m(n);
    cout << "Building the Maze........\n\n";
    m.buildmaze();
    m.printmaze();
    cout << "Solution to the Maze using Dijkstra's Algorithm: \n\n";
    dijkstra(m);
}
