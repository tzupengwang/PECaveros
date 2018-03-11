#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10
#define L 1021
bool ok[ 1 << N ][ L ];
pair<int,int> fr[ 1 << N ][ L ];
int base , n , s , t , _l , bs;
int life[ 1 << N ];
int init_state;
int l[ N ];
char name[ N ][ 100 ];
void init(){
  scanf( "%d%d%d%d" , &n , &s , &t , &_l );
  bs = _l;
  for( int i = 0 ; i < n ; i ++ ){
    char buf[ 9 ];
    scanf( "%s%d" , buf , &l[ i ] );
    getchar();
    fgets( name[ i ] , 100 , stdin );
    if( buf[ 0 ] == '+' ){
      init_state |= (1 << i);
      bs -= l[ i ];
    }
  }
  for( int i = 1 ; i < (1 << n) ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( (i >> j) & 1 ){
        life[ i ] = life[ i ^ (1 << j) ] + l[ j ];
        break;
      }
}
int new_ss( int old_s , int l1 , int l2 ){
  if( l1 % 2 == 0 and (old_s * l2) % l1 == l1 / 2 ){
    int val = (old_s * l2) / l1;
    if( val & 1 ) val ++;
    return val;
  }
  return (old_s * l2 + l1 / 2) / l1;
}
void find_ans( int nstate , int ss ){
  vector< pair<int,int> > val;
  while( nstate != init_state or ss != s ){
    val.push_back( {ss , bs + life[ nstate ]} );
    int pstate , ps;
    tie( pstate , ps ) = fr[ nstate ][ ss ];
    int dlt = pstate ^ nstate;
    if( nstate & dlt )
      val.push_back( {-1 , __lg( dlt )} );
    else
      val.push_back( {-2 , __lg( dlt )} );
    tie(nstate, ss) = tie(pstate, ps);
  }
  val.push_back( {ss, bs + life[ nstate ]} );
  printf( "%d\n" , (int)val.size() / 2 );
  reverse( val.begin() , val.end() );
  for( auto i : val )
    if( i.first == -1 )
      printf( "+ %s" , name[ i.second ] );
    else if( i.first == -2 )
      printf( "- %s" , name[ i.second ] );
    else
      printf( "%d / %d\n" , i.first , i.second );
  exit(0);
}
void solve(){
  queue< pair<int,int> > Q;
  Q.push( {init_state, s} );
  ok[ init_state ][ s ] = true;
  while( Q.size() ){
    int msk , ss;
    tie( msk , ss ) = Q.front(); Q.pop();
    for( int i = 0 ; i < n ; i ++ ){
      int nmsk = msk ^ (1 << i);
      int cur_life = bs + life[  msk ];
      int nxt_life = bs + life[ nmsk ];
      int nxt_ss = new_ss( ss , cur_life , nxt_life );
      if( ok[ nmsk ][ nxt_ss ] ) continue;
      ok[ nmsk ][ nxt_ss ] = true;
      fr[ nmsk ][ nxt_ss ] = {msk , ss};
      Q.push( {nmsk , nxt_ss} );
    }
  }
  for( int i = t ; i < L ; i ++ )
    if( ok[ init_state ][ i ] )
      find_ans( init_state , i );
  puts( "-1" );
}
int main(){
  init();
  solve();
}
