#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define K 400
vector<int> pset;
#define N 3021
const LL inf9 = 1000000000;
const LL inf = 2 * inf9 * inf9;
inline LL mul( LL a , LL b ){
  if( !a or !b ) return 0;
  if( a > inf / b ) return inf;
  return min( a * b , inf );
}
inline LL add( LL a , LL b ){
  return min( a + b , inf );
}
int blen[ 101010 ];
LL dp[ N ][ N ] , wy[ N ][ N ];
void build(){
  for( int i = 2 ; (int)pset.size() < K ; i ++ ){
    bool isp = true;
    for( int j = 2 ; j * j <= i and isp ; j ++ )
      if( i % j == 0 )
        isp = false;
    if( isp )
      pset.push_back( i );
  }
  for( int i = (int)pset.size() - 1 ; i >= 0 ; i -- ){
    int pre = i + 1 , now = i;
    for( int j = 0 ; j < N ; j ++ ){
      dp[ now ][ j ] = dp[ pre ][ j ];
      wy[ now ][ j ] = wy[ pre ][ j ];
    }
    int len = blen[ pset[ i ] ];
    dp[ now ][ pset[ i ] ] = add( dp[ now ][ pset[ i ] ] , len + 4 );
    wy[ now ][ pset[ i ] ] = add( wy[ now ][ pset[ i ] ] , 1 );
    for( int j = 0 ; j + pset[ i ] < N ; j ++ )
      if( wy[ pre ][ j ] ){
        dp[ now ][ j + pset[ i ] ] = add( dp[ now ][ j + pset[ i ] ] ,
                                        add( dp[ pre ][ j ] ,
                                             mul( wy[ pre ][ j ] , len + 2 ) ) );
        wy[ now ][ j + pset[ i ] ] = add( wy[ now ][ j + pset[ i ] ] ,
                                        wy[ pre ][ j ] );
      }
  }
  LL tot = 0;
  for( int i = 0 ; i <= pset.back() ; i ++ )
    tot = add( tot , dp[ 0 ][ i ] );
  //cerr << pset.back() << endl;
  //cerr << tot << endl;
}
LL s , t , ptr;
char buf[ 101010 ];
int stk[ N ];
void go( size_t now , LL nd , int gt , int plen ){
  if( ptr >= t ) return;
  if( nd == 0 ){
    if( gt ){
      int tmp = 0;
      sprintf( buf + tmp , ", [%d" , stk[ 0 ] );
      tmp = strlen( buf + tmp );
      for( int i = 1 ; i < gt ; i ++ ){
        sprintf( buf + tmp , ", %d" , stk[ i ] );
        tmp += strlen( buf + tmp );
      }
      sprintf( buf + tmp , "]" );
      tmp ++;
      for( int i = 0 ; i < tmp ; i ++ ){
        ptr ++;
        if( s <= ptr and ptr <= t )
          putchar( buf[ i ] );
        if( ptr >= t ) break;
      }
    }
    return;
  }
  if( wy[ now ][ nd ] == 0 ) return;
  LL mr = add( dp[ now ][ nd ] ,
               mul( wy[ now ][ nd ] , plen ) );
  if( ptr + mr < s ){
    ptr += mr;
    return;
  }
  if( nd == pset[ now ] ){
    stk[ gt ] = pset[ now ];
    go( now + 1 , 0 , gt + 1 , plen + blen[ pset[ now ] ] + 2 );
  }
  if( ptr >= t ) return;
  if( nd > pset[ now ] ){
    if( add( ptr ,
             add( dp[ now + 1 ][ nd - pset[ now ] ] ,
             mul( wy[ now + 1 ][ nd - pset[ now ] ] , plen + blen[ pset[ now ] ] + 2 ) ) ) < s ){
      ptr += add( dp[ now + 1 ][ nd - pset[ now ] ] ,
                  mul( wy[ now + 1 ][ nd - pset[ now ] ] , plen + blen[ pset[ now ] ] + 2 ) );
    }else{
      stk[ gt ] = pset[ now ];
      go( now + 1 , nd - pset[ now ] , gt + 1 , plen + blen[ pset[ now ] ] + 2 );
    }
  }
  go( now + 1 , nd , gt , plen );
}
int main(){
#ifndef LOCAL
  freopen( "list.in" , "r" , stdin );
  freopen( "list.out" , "w" , stdout );
#endif
  for( int i = 1 ; i < 101010 ; i ++ )
    blen[ i ] = blen[ i / 10 ] + 1;
  build();
  cin >> s >> t;
  s += 2;
  t += 2;
  LL goal = 0 , pre = 0;
  while( pre < s ){
    pre = add( pre , dp[ 0 ][ goal ] );
    goal ++;
  }
  for( LL i = 1 ; i < goal - 1 ; i ++ )
    ptr += dp[ 0 ][ i ];
  for( LL ngoal = goal - 1 ; ptr < t ; ngoal ++ )
    go( 0 , ngoal , 0 , 0 );
  puts( "" );
}
