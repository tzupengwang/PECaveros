#include <bits/stdc++.h>
using namespace std;
#define FZ(X) memset(X,0,sizeof(X))
#define PB push_back
#define SZ(X) ((X).size())
struct KM{
// Maximum Bipartite Weighted Matching (Perfect Match)
	static const int MXN = 650;
	static const int INF = 1021514; // long long
	int n,match[MXN],vx[MXN],vy[MXN];
	int edge[MXN][MXN],lx[MXN],ly[MXN],slack[MXN];
	// ^^^^ long long
	void init(int _n){
		n = _n;
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				edge[i][j] = -INF;
	}
	void add_edge(int x, int y, int w){
		edge[x][y] = -w;
	}
	bool DFS(int x){
		vx[x] = 1;
		for (int y=0; y<n; y++){
			if (vy[y]) continue;
			if (lx[x]+ly[y] > edge[x][y]){
				slack[y] = min(slack[y], lx[x]+ly[y]-edge[x][y]);
			} else {
				vy[y] = 1;
				if (match[y] == -1 || DFS(match[y])){
					match[y] = x;
					return true;
				}
			}
		}
		return false;
	}
	int solve(){
		fill(match,match+n,-1);
		fill(lx,lx+n,-INF);
		fill(ly,ly+n,0);
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				lx[i] = max(lx[i], edge[i][j]);
		for (int i=0; i<n; i++){
			fill(slack,slack+n,INF);
			while (true){
				fill(vx,vx+n,0);
				fill(vy,vy+n,0);
				if ( DFS(i) ) break;
				int d = INF; // long long
				for (int j=0; j<n; j++)
					if (!vy[j]) d = min(d, slack[j]);
				for (int j=0; j<n; j++){
					if (vx[j]) lx[j] -= d;
					if (vy[j]) ly[j] += d;
					else slack[j] -= d;
				}
			}
		}
		int res=0;
		for (int i=0; i<n; i++)
			res += edge[match[i]][i];
		return res;
	}
} graph;
#define N 514
int n , m , k , s;
int x[ N ] , y[ N ];
bool sw[ 22 ][ 22 ];
int trans( int ni , int mi ){
  return ( ni - 1 ) * m + mi - 1;
}
int id[ 22 ][ 22 ] , cnto;
int ox[ N ] , oy[ N ];
void init(){
  scanf( "%d%d%d%d" , &n , &m , &k , &s );
  for( int i = 0 ; i < k ; i ++ ){
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
    sw[ x[ i ] ][ y[ i ] ] = true;
  }
  for( int i = 0 ; i < s ; i ++ ){
    int xi, yi;
    scanf( "%d%d" , &xi , &yi );
    sw[ xi ][ yi ] = true;
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      if( sw[ i ][ j ] ) continue;
      ox[ cnto ] = i;
      oy[ cnto ] = j;
      id[ i ][ j ] = cnto ++;
    }
}
int ind[ N ] , mx[ N ] , my[ N ] , dst[ N ];
vector< int > v[ N ];
void build_edge(){
  for( int _ = 0 ; _ < k ; _ ++ )
    for( int __ = 0 ; __ < k ; __ ++ ){
      if( _ == __ ) continue;
      int dst2 = abs( x[ _ ] - mx[ __ ] ) +
                 abs( y[ _ ] - my[ __ ] );
      if( dst2 < dst[ _ ] ||
          ( dst2 == dst[ _ ] && tie( mx[ __ ] , my[ __ ] ) <
                                tie( mx[ _ ] , my[ _ ] ) ) ){
        v[ __ ].push_back( _ );
        ind[ _ ] ++;
      }
    }
}
void output(){
  queue< int > Q;
  for( int i = 0 ; i < k ; i ++ )
    if( ind[ i ] == 0 )
      Q.push( i );
  vector< int > ans;
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    ans.push_back( tn + 1 );
    for( int nxt : v[ tn ] ){
      ind[ nxt ] --;
      if( ind[ nxt ] == 0 )
        Q.push( nxt );
    }
  }
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
void solve(){
  graph.init( cnto );
  for( int _ = 0 ; _ < k ; _ ++ ){
    int nx = x[ _ ] , ny = y[ _ ];
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= m ; j ++ ){
        if( sw[ i ][ j ] ) continue;
        int tdst = abs( i - nx ) + abs( j - ny );
        graph.add_edge( id[ i ][ j ] , _ , tdst );
      }
  }
  graph.solve();
  for( int _ = 0 ; _ < k ; _ ++ ){
    int to = graph.match[ _ ];
    int mn = ox[ to ] , mm = oy[ to ];
    // printf( "%d %d %d\n" , _ + 1 , mn , mm );
    dst[ _ ] = abs( x[ _ ] - mn ) + abs( y[ _ ] - mm );
    mx[ _ ] = mn;
    my[ _ ] = mm;
  }
  build_edge();
  output();
}
int main(){
  freopen( "agrarian.in" , "r" , stdin );
  freopen( "agrarian.out" , "w" , stdout );
  init();
  solve();
}
