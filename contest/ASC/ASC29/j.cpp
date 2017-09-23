#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define MXN 666
#define N 666
struct Arc{
  int to , nxt;
  Arc(){};
  Arc( int _to , int _nxt ){
    to = _to;
    nxt = _nxt;
  }
} E[ MXN * 2 ];
vector<int> vec;
int nScc , stmp , from[ MXN ] , rfrom[ MXN ] , ecnt = 1;
void add_edge( int ui , int vi ){
  E[ ecnt * 2     ] = Arc( vi ,  from[ ui ] );  from[ ui ] = ecnt * 2;
  E[ ecnt * 2 + 1 ] = Arc( ui , rfrom[ vi ] ); rfrom[ vi ] = ecnt * 2 + 1;
  ++ ecnt;
}
int vst[ MXN ];
bool tk[ MXN ] , used[ MXN ];
void dfs( int u ){
  vst[ u ] = stmp;
  for( int i = from[ u ] ; i ; i = E[ i ].nxt )
    if( not used[ i / 2 ] and
        vst[ E[ i ].to ] != stmp and
        tk[ E[ i ].to ] )
      dfs( E[ i ].to );
  vec.push_back( u );
}
int nid[ N ];
void rdfs(int u){
  vst[u] = stmp;
  nid[u] = nScc;
  for( int i = rfrom[ u ] ; i ; i = E[ i ].nxt )
    if( not used[ i / 2 ] and
        vst[ E[ i ].to ] != stmp and
        tk[ E[ i ].to ] )
      rdfs( E[ i ].to );
}
int n , m;
void Scc(){
  nScc = 0;
  vec.clear();
  ++ stmp;
  for( int i = 1 ; i <= n ; i ++ )
    if( tk[ i ] and vst[ i ] != stmp )
      dfs( i );
  reverse(vec.begin(), vec.end());
  ++ stmp;
  for( auto v : vec )
    if( vst[ v ] != stmp ){
      rdfs( v );
      nScc ++;
    }
}
void init(){
  cin >> n >> m;
  while( m -- ){
    int ui , vi;
    cin >> ui >> vi;
    add_edge( ui , vi );
  }
}
int deg[ N ];
vector< pair<int,int> > tmpv[ N ];
void print( int type , int id , int dep ){
  for( int i = 0 ; i < dep ; i ++ ) putchar( ' ' );
  if( type == 0 ) printf( "wheel " );
  else if( type == 1 ) printf( "edge " );
  else printf( "vertex " );
  printf( "%d\n" , id );
}
void go( const vector<int>& v , int dep ){
  if( v.empty() ) return;
  if( v.size() == 1u ){
    int ee = -1;
    for( int i = from[ v[ 0 ] ] ; i ; i = E[ i ].nxt )
      if( not used[ i / 2 ] ){
        used[ i / 2 ] = true;
        ee = i / 2;
        break;
      }
    if( ee != -1 ){
      print( 0 , 1 , dep );
      print( 2 , v[ 0 ] , dep );
      print( 1 , ee , dep );
    }else
      print( 2 , v[ 0 ] , dep );
    return;
  }
  for( int i = 1 ; i <= n ; i ++ )
    tk[ i ] = false;
  for( auto i : v )
    tk[ i ] = true;
  vector<int> cand;
  for( auto i : v )
    for( int j = from[ i ] ; j ; j = E[ j ].nxt ){
      if( used[ j / 2 ] ) continue;
      if( not tk[ E[ j ].to ] ) continue;
      cand.push_back( j / 2 );
    }
  for( auto ii : cand ){
    used[ ii ] = true;
    Scc();
    //printf( "%d\n" , ii );
    //for( auto i : v )
      //printf( "%d %d\n" , i , nid[ i ] );
    //puts( "" );
    for( int i = 0 ; i < nScc ; i ++ ){
      deg[ i ] = 0;
      tmpv[ i ].clear();
    }
    for( auto i : v )
      for( int j = from[ i ] ; j ; j = E[ j ].nxt ){
        if( used[ j / 2 ] ) continue;
        if( not tk[ E[ j ].to ] ) continue;
        if( nid[ i ] == nid[ E[ j ].to ] )
          continue;
        tmpv[ nid[ i ] ].push_back( { nid[ E[ j ].to ] , j / 2 } );
        deg[ nid[ E[ j ].to ] ] ++;
      }
    vector<int> topo , eid;
    for( int i = 0 ; i < nScc ; i ++ )
      if( deg[ i ] == 0 )
        topo.push_back( i );
    bool ok = true;
    for( int i = 0 ; i < nScc and ok ; i ++ ){
      if( (int)topo.size() != i + 1 ){
        ok = false;
        break;
      }
      int lst = topo.back();
      int eiid = -1;
      for( auto j : tmpv[ lst ] ){
        deg[ j.first ] --;
        if( deg[ j.first ] == 0 ){
          if( eiid == -1 )
            eiid = j.second;
          else
            ok = false;
          topo.push_back( j.first );
        }else
          ok = false;
      }
      if( i + 1 == nScc ){
        if( eiid != -1 ) ok = false;
        if( nid[ E[ ii * 2     ].to ] != topo[ 0 ] or
            nid[ E[ ii * 2 + 1 ].to ] != lst )
          ok = false;
        eiid = ii;
      }
      if( eiid == -1 )
        ok = false;
      else
        eid.push_back( eiid );
    }
    if( ok ){
      for( auto i : eid )
        used[ i ] = true;
      vector< vector<int> > vv;
      vv.resize( nScc );
      for( auto i : v )
        vv[ nid[ i ] ].push_back( i );
      print( 0 , (int)vv.size() , dep );
      for( size_t i = 0 ; i < vv.size() ; i ++ ){
        go( vv[ topo[ i ] ] , dep + 1 );
        print( 1 , eid[ i ] , dep + 1 );
      }
      return;
    }
    used[ ii ] = false;
  }
  assert( false );
}
void solve(){
  vector<int> v;
  for( int i = 1 ; i <= n ; i ++ )
    v.push_back( i );
  go( v , 0 );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "wheels.in" , "r" , stdin );
  freopen( "wheels.out" , "w" , stdout );
#endif
  init();
  solve();
}
