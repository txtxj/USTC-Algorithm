#include <iostream>
#include <vector>

#define SCC_MAX 1001

class Graph
{
private:
	int v;
	int e;
	std::vector<int>* edge;
	int cnt;
	int sc;
	int top;
	int* scc;
	int* dfn;
	int* low;
	int* stack;
	bool* ins;
	bool* vis;
	bool** acs;
private:
	void Tarjan(int u)
	{
		dfn[u] = low[u] = ++cnt;
		ins[u] = true;
		stack[++top] = u;
		for (int& p : edge[u])
		{
			if (dfn[p] == 0)
			{
				Tarjan(p);
				low[u] = std::min(low[u], low[p]);
			}
			else if (ins[p])
			{
				low[u] = std::min(low[u], dfn[p]);
			}
		}
		if (dfn[u] == low[u])
		{
			sc++;
			do
			{
				scc[stack[top]] = sc;
				ins[stack[top]] = false;
			}while (stack[top--] != u);
		}
	}
	void DFS(int u)
	{
		acs[scc[u]][scc[u]] = true;
		for (auto& p : edge[u])
		{
			if (!vis[p])
			{
				vis[p] = true;
				acs[scc[u]][scc[p]] = true;
				DFS(p);
			}
			for (int i = 1; i <= sc; i++)
			{
				if (acs[scc[p]][i])
				{
					acs[scc[u]][i] = true;
				}
			}
		}
	}
public:
	Graph(int vv, int ee)
	{
		v = vv + 1;
		e = ee;
		edge = new std::vector<int>[v];
		cnt = 0;
		sc = 0;
		top = 0;
		scc = new int[v];
		dfn = new int[v];
		low = new int[v];
		stack = new int[v];
		ins = new bool[v];
		vis = new bool[v];
		acs = new bool*[SCC_MAX];
		for (int i = 0; i < SCC_MAX; i++)
		{
			acs[i] = new bool[v];
		}
	}
	~Graph()
	{
		delete[] edge;
		delete[] scc;
		delete[] dfn;
		delete[] low;
		delete[] ins;
	}
	void AddEdge(int from, int to)
	{
		edge[from].push_back(to);
	}
	bool IsArrival(int from, int to) const
	{
		return acs[scc[from]][scc[to]];
	}
	void Initiate()
	{
		for (int i = 1; i < v; i++)
		{
			if (dfn[i] == 0)
			{
				Tarjan(i);
			}
		}
		for (int i = 1; i < v; i++)
		{
			if (!vis[i])
			{
				vis[i] = true;
				DFS(i);
			}
		}
		#ifdef DEBUG
		std::cout << "/******************/" <<std::endl;
		for (int i = 1; i < v; i++)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
		for (int i = 1; i < v; i++)
		{
			std::cout << scc[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "/******************/" <<std::endl;
		#endif
	}
};

int main()
{
	int n, m, u, v, q;
	std::cin >> n >> m;
	Graph graph(n, m);
	for (int i = 0; i < m; i++)
	{
		std::cin >> u >> v;
		graph.AddEdge(u, v);
	}
	graph.Initiate();
	std::cin >> q;
	for (int i = 0; i < q; i++)
	{
		std::cin >> u >> v;
		std::cout << (int)graph.IsArrival(u, v) << std::endl;
	}
	return 0;
}