#include <bits/stdc++.h>
using namespace std;
#define N 303030
typedef long long LL;
struct DJS{
  int p[ N ] , mx[ N ] , mn[ N ] , emx[ N ];
  LL xans[ N ];
  int f( int x ){
    return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
  }
  void uni( int x , int y ){
    p[ f( x ) ] = f( y );
  }
} djs;
int n , m , a[ N ] , b[ N ];
vector< pair< int , pair<int,int> > > vv;
LL ans;
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d%d" , &a[ i ] , &b[ i ] );
    djs.mx[ i ] = a[ i ];
    djs.mn[ i ] = b[ i ];
    djs.emx[ i ] = 0;
    djs.p[ i ] = i;
    ans += (LL)a[ i ] * b[ i ];
    djs.xans[ i ] = (LL)a[ i ] * b[ i ];
  }
  while( m -- ){
    int ui , vi , ci;
    scanf( "%d%d%d" , &ui , &vi , &ci );
    vv.push_back( { ci , { ui , vi } } );
  }
}
void solve(){
  sort( vv.begin() , vv.end() );
  for( auto e : vv ){
    int ui = e.second.first;
    int vi = e.second.second;
    int cst = e.first;
    if( djs.f( ui ) == djs.f( vi ) )
      continue;
    ui = djs.f( ui );
    vi = djs.f( vi );

    LL tans = ans;
    LL mnn = min( djs.mn[ ui ] , djs.mn[ vi ] );
    LL vmx = max( djs.mx[ ui ] , djs.mx[ vi ] );
    LL tsum = djs.xans[ ui ] + djs.xans[ vi ];
    tans -= tsum;
    tans += max( (LL)cst , (LL)vmx ) * mnn;

    djs.uni( ui , vi );
    ui = djs.f( ui );
    djs.mn[ ui ] = mnn;
    djs.mx[ ui ] = vmx;
    djs.emx[ ui ] = cst;
    
    if( tans < ans ){
      ans = tans;
      djs.xans[ ui ] = max( (LL)cst , (LL)vmx ) * mnn;
    }else
      djs.xans[ ui ] = tsum;
  }
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
