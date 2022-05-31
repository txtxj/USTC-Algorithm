#include <iostream>
#include <vector>
#include <queue>

class Graph
{
private:
	int s, t, v;
	int* pre;
	int** cf;
	int** weight;
private:
	bool BFS(int from, int to)
	{
		for (int i = 0; i < v; i++)
		{
			pre[i] = -1;
		}
		pre[from] = from;
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
		q.push(std::make_pair(0, from));
		while (!q.empty())
		{
			int u = q.top().second;
			q.pop();
			for (int i = 1; i < v; i++)
			{
				if (cf[u][i] > 0 && pre[i] == -1)
				{
					pre[i] = u;
					q.push(std::make_pair(weight[u][i], i));
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
	explicit Graph(int _s, int _t)
	{
		s = _s;
		t = _t;
		v = s + t + 2;
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
		weight = new int*[v];
		for (int i = 0; i < v; i++)
		{
			weight[i] = new int[v];
			for (int j = 0; j < v; j++)
			{
				weight[i][j] = 0;
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
		for (int i = 0; i < v; i++)
		{
			delete[] weight[i];
		}
		delete[] weight;
	}
	void AddEdge(int from, int to, int val)
	{
		cf[from][to] = 1;
		weight[from][to] = val;
		weight[to][from] = -val;
	}
	std::pair<int, int> MaxFlow(int from, int to)
	{
		for (int i = 1; i <= s; i++)
		{
			AddEdge(from, i, 0);
		}
		for (int i = s + 1; i < to; i++)
		{
			AddEdge(i, to, 0);
		}
		int ans = 0;
		int w = 0;
		while (BFS(from, to))
		{
			ans += 1;
			for (int u = to; u != from; u = pre[u])
			{
				cf[pre[u]][u] -= 1;
				cf[u][pre[u]] += 1;
				w += weight[pre[u]][u];
			}
		}
		return std::make_pair(ans, w);
	}
};

int main()
{
	int s, t, m, u, v, c;
	std::cin >> s >> t >> m;
	Graph g(s, t);
	for (int i = 0; i < m; i++)
	{
		std::cin >> u >> v >> c;
		g.AddEdge(u, v, c);
	}
	auto ans = g.MaxFlow(0, s + t + 1);
	std::cout << ans.first << " " << ans.second << std::endl;
	return 0;
}