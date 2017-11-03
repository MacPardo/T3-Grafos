#include <iostream>
#include <tuple>
#include <queue>
#include <set>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>

using namespace std;
typedef tuple<int, int, int> i3;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> graph;

bool has_cycle(graph g, int v) {
  bool ok[g.size()] = {false};
  function<bool (int, int)> dfs = [&dfs, &ok, &g](int v, int p) -> bool {
    if (ok[v]) return true;
    ok[v] = true;
    for (vii::iterator it = g[v].begin(); it != g[v].end(); it++) {
      if (it->second != p && dfs(it->second, v)) return true;
    }
    return false;
  };
  return dfs(v, -1);
}

pair<graph, int> kruskal(graph g) {
  uint32_t added_edges = 0;
  int total_weight = 0;
  set<i3 > edges;
  graph k(g.size());
  for (uint32_t i = 0; i < g.size(); i++) {
    for (vii::iterator it = g[i].begin(); it != g[i].end(); it++) {
      if (edges.find(i3(it->first, i, it->second)) == edges.end()) {
        edges.insert(i3(it->first, it->second, i));
      }
    }
  }

  for (set<i3 >::iterator it = edges.begin(); it != edges.end() && added_edges < g.size() - 1; it++) {
    graph test = k;
    test[get<1>(*it)].push_back(ii(get<0>(*it), get<2>(*it)));
    test[get<2>(*it)].push_back(ii(get<0>(*it), get<1>(*it)));
    if (!has_cycle(test, get<1>(*it))) {
      added_edges++;
      total_weight += get<0>(*it);
      k[get<1>(*it)].push_back(ii(get<0>(*it), get<2>(*it)));
      k[get<2>(*it)].push_back(ii(get<0>(*it), get<1>(*it)));
    }
  }
  return pair<graph, int>(k, total_weight);
}

pair<graph, int> prim(graph g) {
  uint32_t added_edges = 0;
  int total_weight = 0;
  priority_queue<i3, vector<i3>, greater<i3> > q;
  bool ok[g.size()] = {false};
  graph k(g.size());

  for (vii::iterator it = g[0].begin(); it != g[0].end(); it++) {
    q.push(i3(it->first, 0, it->second));
  }
  ok[0] = true;

  while (!q.empty() && added_edges < g.size() - 1) {
    i3 edge = q.top();
    q.pop();
    int w = get<0>(edge);
    int u = get<1>(edge);
    int v = get<2>(edge);

    if (!ok[u] || !ok[v]) {
      ok[u] = ok[v] = true;
      added_edges++;
      total_weight += w;
      k[u].push_back(ii(w, v));
      k[v].push_back(ii(w, u));

      int not_ok = ok[u] ? v : u;
      for_each(g[not_ok].begin(), g[not_ok].end(), 
          [&](ii it){q.push(i3(it.first, not_ok, it.second));});
    }
  }

  return pair<graph, int>(k, total_weight);
}

void prt_grafo(graph g) {
  for (uint32_t i = 0; i < g.size(); i++) {
    cout << i << ": ";
    for (vii::iterator it = g[i].begin(); it != g[i].end(); it++) {
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
    g[a].push_back(ii(w, b));
    g[b].push_back(ii(w, a));
  }
  cout << "GRAFO 1:\n";
  prt_grafo(g);

  pair<graph, int> ans = kruskal(g);
  cout << "ÁRVORE GERADORA MÍNIMA DO GRAFO 1:\n";
  prt_grafo(ans.first);
  cout << "Peso total do grafo: " << ans.second << '\n';



  cin >> v >> e;
  graph k(v);
  while (e--) {
    cin >> a >> b >> w;
    k[a].push_back(ii(w, b));
    k[b].push_back(ii(w, a));
  }
  cout << "GRAFO 2:\n";
  prt_grafo(k);
  ans = prim(k);
  cout << "ÁRVORE GERADORA MÍNIMA DO GRAFO 2:\n";
  prt_grafo(ans.first);
  cout << "Peso total do grafo: " << ans.second << '\n';
  return 0;
}
