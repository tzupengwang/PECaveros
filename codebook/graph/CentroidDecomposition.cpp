vector<int> adj[N];
int p[N], vis[N];
int sz[N], M[N]; // subtree size of u and M(u)

inline void maxify(int &x, int y) { x = max(x, y); }
int centroidDecomp(int x) {
  vector<int> q;
  { // bfs
    size_t pt = 0;
    q.push_back(x);
    p[x] = -1;
    while (pt < q.size()) {
      int now = q[pt++];
      sz[now] = 1;
      M[now] = 0;
      for (auto &nxt : adj[now])
        if (!vis[nxt] && nxt != p[now])
          q.push_back(nxt), p[nxt] = now;
    }
  }

  // calculate subtree size in reverse order
  reverse(q.begin(), q.end());
  for (int &nd : q)
    if (p[nd] != -1) {
      sz[p[nd]] += sz[nd];
      maxify(M[p[nd]], sz[nd]);
    }
  for (int &nd : q)
    maxify(M[nd], (int)q.size() - sz[nd]);

  // find centroid
  int centroid = *min_element(q.begin(), q.end(),
                              [&](int x, int y) { return M[x] < M[y]; });

  vis[centroid] = 1;
  for (auto &nxt : adj[centroid]) if (!vis[nxt])
    centroidDecomp(nxt);
  return centroid;
}

