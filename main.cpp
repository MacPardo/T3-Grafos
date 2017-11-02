#include <iostream>
#include <tuple>
#include <set>
#include <vector>
#include <utility>
#include <functional>

using namespace std;
typedef vector<vector<pair<int, int> > > graph;

bool has_cycle(graph g, int v) {
  bool ok[g.size()] = {false};
  function<bool (int, int)> dfs = [&dfs, &ok, &g](int v, int p) -> bool {
    if (ok[v]) return true;
    ok[v] = true;
    for (vector<pair<int, int> >::iterator it = g[v].begin(); it != g[v].end(); it++) {
      if (it->second != p && dfs(it->second, v)) return true;
    }
    return false;
  };
  return dfs(v, -1);
}

graph kruskal(graph g) {
  uint32_t added_edges = 0;
  set<tuple<int, int, int> > edges;
  graph k(g.size());
  for (uint32_t i = 0; i < g.size(); i++) {
    for (vector<pair<int, int> >::iterator it = g[i].begin(); it != g[i].end(); it++) {
      if (edges.find(tuple<int, int, int>(it->first, i, it->second)) == edges.end()) {
        edges.insert(tuple<int, int, int>(it->first, it->second, i));
      }
    }
  }

  for (set<tuple<int, int, int> >::iterator it = edges.begin(); it != edges.end() && added_edges < g.size() - 1; it++) {
    graph test = k;
    test[get<1>(*it)].push_back(pair<int, int>(get<0>(*it), get<2>(*it)));
    test[get<2>(*it)].push_back(pair<int, int>(get<0>(*it), get<1>(*it)));
    if (!has_cycle(test, get<1>(*it))) {
      added_edges++;
      k[get<1>(*it)].push_back(pair<int, int>(get<0>(*it), get<2>(*it)));
      k[get<2>(*it)].push_back(pair<int, int>(get<0>(*it), get<1>(*it)));
    }
  }
  return k;
}

void prt_grafo(graph g) {
  for (uint32_t i = 0; i < g.size(); i++) {
    cout << i << ": ";
    for (vector<pair<int, int> >::iterator it = g[i].begin(); it != g[i].end(); it++) {
      cout << it->second << ' ';
    }
    cout << '\n';
  }
}

int main(void) {
  int v, e; //qtd vertices
  int a, b, w;
  cin >> v >> e;
  graph g(v);
  while (e--) {
    cin >> a >> b >> w;
    g[a].push_back(pair<int, int>(w, b));
    g[b].push_back(pair<int, int>(w, a));
  }
  prt_grafo(g);
  cout << (has_cycle(g, 0) ? "true" : "false") << '\n';

  graph k = kruskal(g);
  prt_grafo(k);
  return 0;
}
