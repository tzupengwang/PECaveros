#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define SZ(C) ((int)C.size())
const int MAXV = 10101;
const int INF = 1e9;
struct MaxFlow{
    struct Edge{
        int v, c, r;
        Edge(int _v, int _c, int _r){
            v=_v, c=_c, r=_r;
        }
    };
    int s, t;
    vector<Edge> G[MAXV];
    int iter[MAXV], d[MAXV], gap[MAXV], tot;
    void init(int x){
        tot = x+2;
        s=x+1, t=x+2;
        for(int i=0; i <= tot; i++){
            G[i].clear();
            iter[i]=d[i]=gap[i]=0;
        }
    }
    void addEdge(int u, int v, int c){
        G[u].push_back(Edge(v, c, SZ(G[v])));
        G[v].push_back(Edge(u, c, SZ(G[u])-1));
    }
    int dfs(int p, int flow){
        if(p == t) return flow;
        for(int& i=iter[p]; i < SZ(G[p]); i++){
            Edge&e = G[p][i];
            if(e.c > 0 and d[p] == d[e.v] + 1){
                int f=dfs(e.v, min(flow, e.c));
                if(f){
                    e.c -= f;
                    G[e.v][e.r].c += f;
                    return f;
                }
            }
        }
        if((--gap[d[p]]) == 0) d[s]=tot;
        else{
            d[p]++;
            iter[p]=0;
            ++gap[d[p]];
        }
        return 0;
    }
    int solve(){
        int res=0;
        gap[0]=tot;
        for(res=0; d[s] < tot; res+=dfs(s, INF));
        return res;
    }
} flow;
const int N=1021;
int n, m, x[N], y[N], c[N][N];
int main(){
    int t; scanf("%d", &t); while(t--){
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++) scanf("%d", &x[i]);
        for(int i=1; i<=n; i++) scanf("%d", &y[i]);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                c[i][j]=0;
        while(m--){
            int a, b, cc;
            scanf("%d%d%d", &a, &b, &cc);
            c[a][b]+=cc;
            c[b][a]+=cc;
        }
        flow.init(n+n);
        for(int i=1; i<=n; i++)
            flow.addEdge(flow.s, i, x[i]);
        for(int i=1; i<=n; i++)
            flow.addEdge(i, flow.t, y[i]);
        for(int i=1; i<=n; i++)
            for(int j=i+1; j<=n; j++)
                if(i != j)
                    flow.addEdge(i, j, c[i][j]);
                //else
                  //  flow.addEdge(i, j+n, INF);
        printf("%d\n", flow.solve());
    }
}
