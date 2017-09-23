#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define M 20202
struct Arc{
  int to , nxt;
  double d;
  Arc(){}
  Arc( int _to , double _d , int _nxt ){
    to = _to;
    d = _d;
    nxt = _nxt;
  }
} r[ M * 2 ];
int n , m , from[ N ] , od[ M ];
bool mark[ M ];
void init(){
  cin >> n >> m;
  for( int i = 1 ; i <= m ; i ++ ){
    int ui , vi , di;
    cin >> ui >> vi >> di;
    od[ i ] = di;
    r[ i * 2     ] = Arc( vi , di , from[ ui ] ); from[ ui ] = i * 2;
    r[ i * 2 + 1 ] = Arc( ui , di , from[ vi ] ); from[ vi ] = i * 2 + 1;
  }
  int l; cin >> l; while( l -- ){
    int x; cin >> x;
    mark[ x ] = true;
  }
}
int vst[ N ] , stmp;
double SP(){
  ++ stmp;
  priority_queue< pair<double,int>,
          vector< pair<double,int> >,
         greater< pair<double,int> > > heap;
  heap.push( { 0 , 1 } );
  while( heap.size() ){
    auto tp = heap.top(); heap.pop();
    double dd = tp.first;
    int who = tp.second;
    if( who == n ) return dd;
    if( vst[ who ] == stmp ) continue;
    vst[ who ] = stmp;
    for( int i = from[ who ] ; i ; i = r[ i ].nxt ){
      if( vst[ r[ i ].to ] == stmp ) continue;
      heap.push( { dd + r[ i ].d , r[ i ].to } );
    }
  }
  assert( false );
}
double eps = 1e-9;
bool okay( double dlt ){
  double sp2 = 0;
  for( int i = 1 ; i <= m ; i ++ )
    if( mark[ i ] ){
      r[ i * 2     ].d = max( 1. , od[ i ] - dlt );
      r[ i * 2 + 1 ].d = max( 1. , od[ i ] - dlt );
      sp2 += r[ i * 2 ].d;
    }else{
      r[ i * 2     ].d = od[ i ] + dlt;
      r[ i * 2 + 1 ].d = od[ i ] + dlt;
    }
  return SP() > sp2 - eps;
}
void solve(){
  double bl = 0.0 , br = 1e6;
  for( int i = 0 ; i < 50 ; i ++ ){
    double bmid = (bl + br) * 0.5;
    if( okay( bmid ) ) br = bmid;
    else bl = bmid;
  }
  printf( "%.12f\n" , bl );
  for( int i = 1 ; i <= m ; i ++ ){
    double tans = od[ i ];
    if( mark[ i ] ) tans = max( 1. , tans - bl );
    else tans += bl;
    printf( "%.12f%c" , tans , " \n"[ i == m ] );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "lateagain.in" , "r" , stdin );
  freopen( "lateagain.out" , "w" , stdout );
#endif
  init();
  solve();
}
