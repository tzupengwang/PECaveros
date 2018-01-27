#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define V 101
#define N 222
typedef long long LL;
struct Rd{
  int to , deg , odeg , dst , mrk , nxt;
} rd[ N + N ];
bool used[ 360 ];
int from[ N ];

int stmp;

int c , e , m , mxd , s , t , dir;
bool choice[ N ];
vector< int > ord[ V ][ 360 ];
int tg[ V ][ 360 ];

bool cmp( pair<int,int> p1 , pair<int,int> p2 ){
  if( abs( p1.first - 180 ) != 
      abs( p2.first - 180 ) )
    return abs( p1.first - 180 ) < abs( p2.first - 180 );
  return p1.first > p2.first;
}
void find_ord( int st , int sdir ){
  if( tg[ st ][ sdir ] == stmp ) return;
  tg[ st ][ sdir ] = stmp;

  vector< pair<int,int> > wt;
  for( int j = from[ st ] ; j ; j = rd[ j ].nxt ){
    int cdir = rd[ j ].deg - sdir;
    if( cdir <    0 ) cdir += 360;
    if( cdir >= 360 ) cdir -= 360;
    wt.push_back( { cdir , j } );
  }
  sort( wt.begin() , wt.end() , cmp );

  ord[ st ][ sdir ].clear();
  for( auto i : wt )
    ord[ st ][ sdir ].push_back( i.second );
}

void upd( int eid , int vv ){
  if( rd[ eid ].mrk == -1 or vv < rd[ eid ].mrk )
    rd[ eid ].mrk = vv;
}

void init(){
  ++ stmp;
  cin >> c >> e >> m >> mxd >> s >> t >> dir;
  if( c + e + m + mxd + s + t + dir == 0 ) exit(0);
  for( int i = 0 ; i < V ; i ++ ){
    choice[ i ] = false;
    from[ i ] = 0;
  }
  dir = (dir + 180) % 360;
  while( c -- ){
    int who; cin >> who;
    choice[ who ] = true;
  }
  for( int i = 1 ; i <= e ; i ++ ){
    int ui , vi , out , in , dd;
    cin >> ui >> vi >> out >> in >> dd;
    rd[ i * 2 ] = { vi , out , in , dd , -1 , from[ ui ] };
    from[ ui ] = i * 2;
    rd[ i * 2 + 1 ] = { ui , in , out , dd , -1 , from[ vi ] };
    from[ vi ] = i * 2 + 1;
  }
  while( m -- ){
    int si , ei , at;
    cin >> si >> ei >> at;
    ei <<= 1;
    if( rd[ ei ].to == si ) ei ++;
    upd( ei     , at );
    upd( ei ^ 1 , rd[ ei ^ 1 ].dst - at );
  }
}

int stk[ (1 << 20) ];

vector<int> route;
LL ans , pans;

bool go( int now , int ndir , int ndep );
bool goc( int now , int ndir , int ndep , int resd ){
  if( choice[ now ] and resd != mxd ) return false;
  if( resd == 0 ) return false;

  if( choice[ now ] ){
    while( true ){
      find_ord( now , ndir );
      int id = -1;
      for( auto i : ord[ now ][ ndir ] )
        if( not used[ rd[ i ].deg ] ){
          used[ rd[ i ].deg ] = true;
          id = i;
          break;
        }
      if( id == -1 ) break;
      //printf( "now = %d , ndir = %d , choose = %d\n" , now , ndir , id );
      if( rd[ id ].mrk != -1 and rd[ id ].mrk <= resd ){
        ans += rd[ id ].dst;
        stk[ ndep ] = id;
        //printf( "good choice trying %d %d, road id = %d\n" , now , rd[ id ].to , id );
        assert( go( rd[ id ].to , rd[ id ].odeg , ndep + 1 ) );
        return true;
      }
      if( rd[ id ].dst >= resd ){
        //printf( "ggwp %d\n" , resd );
        ans += resd + resd;
      }else{
        ans += rd[ id ].dst;
        stk[ ndep ] = id;
        //printf( "choice trying %d %d\n" , now , rd[ id ].to );
        if( goc( rd[ id ].to , rd[ id ].odeg , ndep + 1 , resd - rd[ id ].dst ) )
          return true;
        ans += rd[ id ].dst;
        //printf( "choice back from %d to %d\n" , rd[ id ].to , now );
      }
      ndir = rd[ id ].deg;
    }
  }else{
    find_ord( now , ndir );
    int id = ord[ now ][ ndir ][ 0 ];
    //printf( "now = %d , ndir = %d , choose = %d\n" , now , ndir , id );
    if( rd[ id ].mrk != -1 and rd[ id ].mrk <= resd ){
      ans += rd[ id ].dst;
      stk[ ndep ] = id;
      //printf( "good choice trying %d %d, road id = %d\n" , now , rd[ id ].to , id );
      assert( go( rd[ id ].to , rd[ id ].odeg , ndep + 1 ) );
      return true;
    }
    if( rd[ id ].dst >= resd ){
      //printf( "ggwp %d\n" , resd );
      ans += resd + resd;
    }else{
      ans += rd[ id ].dst;
      stk[ ndep ] = id;
      //printf( "choice trying %d %d\n" , now , rd[ id ].to );
      if( goc( rd[ id ].to , rd[ id ].odeg , ndep + 1 , resd - rd[ id ].dst ) )
        return true;
      ans += rd[ id ].dst;
      //printf( "choice back from %d to %d\n" , rd[ id ].to , now );
    }
    ndir = rd[ id ].deg;
  }
  return false;
}

bool go( int now , int ndir , int ndep ){
  if( now == t ){
    for( int i = 0 ; i < ndep ; i ++ ){
      pans += rd[ stk[ i ] ].dst;
      route.push_back( stk[ i ] / 2 );
    }
    return true;
  }
  find_ord( now , ndir );
  if( choice[ now ] ){
    for( int i = 0 ; i < 360 ; i ++ )
      used[ i ] = false;
    used[ ndir ] = true;
    return goc( now , ndir , ndep , mxd );
  }
  stk[ ndep ] = ord[ now ][ ndir ][ 0 ];
  ans += rd[ stk[ ndep ] ].dst;
  return go( rd[ stk[ ndep ] ].to , rd[ stk[ ndep ] ].odeg , ndep + 1 );
}

int _cs;

void solve(){
  pans = ans = 0;
  route.clear();
  assert( go( s , dir , 0 ) );

  printf( "Case %d:\n" , ++ _cs );
  printf( "   Length of hare's route is %lld\n" , pans );
  printf( "   Length of hound's search is %lld\n" , ans );
  printf( "   Route:" );
  for( auto i : route )
    printf( " %d" , i );
  puts( "\n" );
}
int main(){
  while( true ){
    init();
    solve();
  }
}
