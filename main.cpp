#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> ReverseGraph(int n, const vector<vector<int>> & graph)
{
	vector<vector<int>> reversed_graph(n + 1);
	for (int u = 1; u <= n; ++u) {
		for (int v : graph[u]) {
			reversed_graph[v].push_back(u);
		}
	}
	return reversed_graph;
}

void PseudoTopsort(int u, const vector<vector<int>> & graph, vector<bool> & used,
	vector<int> & topsort)
{
	used[u] = true;
	for (int v : graph[u]) {
		if (!used[v]) {
			PseudoTopsort(v, graph, used, topsort);
		}
	}
	topsort.push_back(u);
}

void HighlightNewComponent(int u, const vector<vector<int>> & graph,
	vector<int> & components, int cur_component)
{
	components[u] = cur_component;
	for (int v : graph[u]) {
		if (components[v] == 0) {
			HighlightNewComponent(v, graph, components, cur_component);
		}
	}
}

int GraphCondensation(int n, const vector<vector<int>> & graph, vector<int> & components,
	vector<int> & size_of_components, vector<vector<int>> & tree)
{
	vector<bool> used(n + 1);
	vector<int> pseudo_topsort;
	for (int u = 1; u <= n; ++u) {
		if (!used[u]) {
			PseudoTopsort(u, graph, used, pseudo_topsort);
		}
	}
	reverse(pseudo_topsort.begin(), pseudo_topsort.end());
	vector<vector<int>> reversed_graph = ReverseGraph(n, graph);
	int number_of_components = 0;
	for (int u : pseudo_topsort) {
		if (components[u] == 0) {
			++number_of_components;
			HighlightNewComponent(u, reversed_graph, components, number_of_components);
		}
	}
	size_of_components.resize(number_of_components + 1);
	for (int u = 1; u <= n; ++u) {
		++size_of_components[components[u]];
	}
	tree.resize(number_of_components + 1);
	for (int u = 1; u <= n; ++u) {
		for (int v : graph[u]) {
			if (components[u] != components[v]) {
				tree[components[u]].push_back(components[v]);
			}
		}
	}
	return number_of_components;
}

const double eps = 1e-8;

void dfs(int u, int slice, const vector<vector<int>> & graph, const vector<vector<double>> & points,
	vector<vector<double>> & min_reachable_point)
{
	min_reachable_point[u][slice] = points[u][slice];
	for (int v : graph[u]) {
		if (min_reachable_point[v][slice] > 1.5) {
			dfs(v, slice, graph, points, min_reachable_point);
		}
		min_reachable_point[u][slice] =
			min(min_reachable_point[u][slice], min_reachable_point[v][slice]);
	}
}

const int number_of_slices = 50;

vector<int> Solve(int n, const vector<vector<int>> & graph)
{
	vector<int> components(n + 1), size_of_components;
	vector<vector<int>> tree;
	int number_of_components = GraphCondensation(n, graph, components, size_of_components, tree);
	vector<vector<double>> points(number_of_components + 1, vector<double>(number_of_slices));
	for (int u = 1; u <= number_of_components; ++u) {
		for (int i = 0; i < number_of_slices; ++i) {
		points[u][i] = 1;
			for (int j = 0; j < size_of_components[u]; ++j) {
				points[u][i] = min(points[u][i], (double)rand() / RAND_MAX);
			}
		}
	}
	vector<vector<double>> min_reachable_point(number_of_components + 1, 
		vector<double>(number_of_slices, 2));
	for (int i = 0; i < number_of_slices; ++i) {
		for (int u = 1; u <= number_of_components; ++u) {
			if (min_reachable_point[u][i] > 1.5) {
				dfs(u, i, tree, points, min_reachable_point);
			}
		}
	}
	for (int u = 1; u <= number_of_components; ++u) {
		for (int i = 1; i < number_of_slices; ++i) {
			min_reachable_point[u][0] += min_reachable_point[u][i];
		}
		min_reachable_point[u][0] /= number_of_slices;
	}
	vector<int> answer(n + 1);
	for (int u = 1; u <= n; ++u) {
		int component = components[u];
		double MIN = min_reachable_point[component][0];
		answer[u] = (int)(1.0 / MIN - 1 + 0.5);
	}
	return answer;
}

int main()
{
	ifstream fin;
	fin.open("input.txt");
	ofstream fout;
	fout.open("output.txt");
	ios_base::sync_with_stdio(0);
	fin.tie(NULL);
	fout.tie(NULL);
	int n, m;
	fin >> n >> m;
	srand(n + 342);
	vector<vector<int>> graph(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b;
		fin >> a >> b;
		graph[a].push_back(b);
	}
	vector<int> answer = Solve(n, graph);
	for (int u = 1; u <= n; ++u) {
		fout << answer[u] << "\n";
	}
	return 0;
}
