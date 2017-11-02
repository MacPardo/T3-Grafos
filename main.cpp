#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <functional>

using namespace std;
typedef vector<set<pair<int, int> > > graph;

bool has_cycle(graph g, int v) {
  bool answer;
  bool ok[g.size()] = {false};
  function<bool (int, int)> dfs = [&dfs, &ok, g](int v, int p) -> bool {
    if (ok[v]) return true;
    ok[v] = true;
    for (set<pair<int, int> >::iterator it = g[v].begin(); it != g[v].end(); it++) {
      if (it->second != p && dfs(it->second, v)) return true;
    }
    return false;
  };
  return dfs(v, -1);
}

int main(void) {
  int v, e; //qtd vertices
  int a, b, w;
  cin >> v >> e;
  graph g(v);
  while (e--) {
    cin >> a >> b >> w;
    g[a].insert(pair<int, int>(w, b));
    g[b].insert(pair<int, int>(w, a));
  }
  for (int i = 0; i < g.size(); i++) {
    printf("%d: ", i);
    for (set<pair<int, int> >::iterator it = g[i].begin(); it != g[i].end(); it++) {
      printf("%d ", it->second);
    }
    printf("\n");
  }
  printf("%s\n", has_cycle(g, 0) ? "true" : "false");
  return 0;
}
