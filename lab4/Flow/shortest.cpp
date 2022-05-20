// Shortest version(Edmonds-Karp)
#include <iostream>
#include <queue>

class Graph
{
private:
	int v;
	int* pre;
	int** cf;
private:
	// Use BFS to find the shortest path
	bool BFS(int from, int to)
	{
		for (int i = 0; i < v; i++)
		{
			pre[i] = -1;
		}
		pre[from] = from;
		std::queue<int> q;
		q.push(from);
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int i = 1; i < v; i++)
			{
				if (cf[u][i] > 0 && pre[i] == -1)
				{
					pre[i] = u;
					q.push(i);
					if (i == to)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
public:
	explicit Graph(int vv)
	{
		v = vv + 1;
		pre = new int[v];
		cf = new int*[v];
		for (int i = 0; i < v; i++)
		{
			cf[i] = new int[v];
			for (int j = 0; j < v; j++)
			{
				cf[i][j] = 0;
			}
		}
	}
	~Graph()
	{
		delete[] pre;
		for (int i = 0; i < v; i++)
		{
			delete[] cf[i];
		}
		delete[] cf;
	}
	void AddEdge(int from, int to, int val)
	{
		cf[from][to] = val;
	}
	int MaxFlow(int from, int to)
	{
		int ans = 0;
		while (BFS(from, to))
		{
			int c = cf[pre[to]][to];
			for (int u = to; u != from; u = pre[u])
			{
				c = std::min(c, cf[pre[u]][u]);
			}
			ans += c;
			for (int u = to; u != from; u = pre[u])
			{
				cf[pre[u]][u] -= c;
				cf[u][pre[u]] += c;
			}
		}
		return ans;
	}
};

int main()
{
	int n, m, u, v, w;
	std::cin >> n >> m;
	Graph graph(n);
	for (int i = 0; i < m; i++)
	{
		std::cin >> u >> v >> w;
		graph.AddEdge(u, v, w);
	}
	std::cin >> u >> v;
	std::cout << graph.MaxFlow(u, v);
	return 0;
}