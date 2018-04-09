// O(N^3), 0-base
struct Edge{
  int from, to, cap, flow;
  Edge(int _from, int _to, int _cap, int _flow = 0):
    from(_from), to(_to), cap(_cap), flow(_flow) {}	
};
struct PushRelabel{
  int n;
  vector<Edge> edges;
  vector<int> count, h, inQ, excess;
  vector<vector<int> > G;
  queue<int> Q;
  PushRelabel(int _n):
    n(_n), count(_n<<1), G(_n), h(_n), inQ(_n), excess(_n) {}
  void addEdge(int from, int to, int cap) {
    G[from].push_back(edges.size());
    edges.push_back(Edge(from, to, cap));
    G[to].push_back(edges.size());
    edges.push_back(Edge(to, from, 0));
  }
  void enQueue(int u) {
    if(!inQ[u] && excess[u] > 0) Q.push(u), inQ[u] = true;
  }
  void Push(int EdgeIdx) {
    Edge & e = edges[EdgeIdx];
    int toPush = min<int>(e.cap - e.flow, excess[e.from]);
    if(toPush > 0 && h[e.from] > h[e.to]) {
      e.flow += toPush;
      excess[e.to] += toPush;
      excess[e.from] -= toPush;
      edges[EdgeIdx^1].flow -= toPush;
      enQueue(e.to);
    }
  }
  void Relabel(int u) {
    count[h[u]] -= 1; h[u] = 2*n-2;
    for (size_t i = 0; i < G[u].size(); ++i) {
      Edge & e = edges[G[u][i]];
      if(e.cap > e.flow) h[u] = min(h[u], h[e.to]);
    }
    count[++h[u]] += 1;
  }
  void gapRelabel(int height) {
    for (int u = 0; u < n; ++u) if(h[u] >= height && h[u] < n) {
      count[h[u]] -= 1;
      count[h[u] = n] += 1;
      enQueue(u);
    }
  }
  void Discharge(int u) {
    for (size_t i = 0; excess[u] > 0 && i < G[u].size(); ++i)
      Push(G[u][i]);
    if(excess[u] > 0) {
      if(h[u] < n && count[h[u]] < 2) gapRelabel(h[u]);
      else Relabel(u);
    }
    else if(!Q.empty()) { // dequeue
      Q.pop();
      inQ[u] = false;
    }
  }
  int solve(int src, int snk) {
    h[src] = n; inQ[src] = inQ[snk] = true;
    count[0] = n - (count[n] = 1);
    for (size_t i = 0; i < G[src].size(); ++i) {
      excess[src] += edges[G[src][i]].cap;
      Push(G[src][i]);
    }
    while (!Q.empty())
      Discharge(Q.front());
    return excess[snk];
  }
};
