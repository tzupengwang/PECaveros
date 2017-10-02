#include <bits/stdc++.h>
using namespace std;
#define N 111
typedef long long LL;
inline int count_bit( LL x ){
  return __builtin_popcountll( x );
}
int n , m;
LL f[ N ] , e[ N ] , neighbor , eli , other;
int dp[ 1 << 22 ];
LL bm[ 1 << 22 ];
int bk[ 1 << 22 ];
int nwho[ N ] , nid[ N ] , nptr;
int owho[ N ] , oid[ N ] , optr;
void solve1(){
  for( int i = 0 ; i < (1 << nptr) ; i ++ ){
    for( int j = 0 ; j < nptr ; j ++ )
      if( (i >> j) & 1 ){
        int who = nwho[ j ];
        int tdp = dp[ i ^ (1 << j) ] +
          count_bit( f[ who ] & (~bm[ i ^ (1 << j)]) );
        bm[ i ] = bm[ i ^ (1 << j) ] | f[ who ] | e[ who ];
        if( tdp >= dp[ i ] ){
          dp[ i ] = tdp;
          bk[ i ] = j;
        }
      }
  }
  int ans = count_bit( f[ 1 ] ) + dp[ (1 << nptr) - 1 ];
  printf( "%.12f\n" , (double)ans / ( n - 1 ) );
  vector<int> va; int msk = (1 << nptr) - 1;
  while( msk ){
    va.push_back( nwho[ bk[ msk ] ] );
    msk ^= (1 << bk[ msk ]);
  }
  reverse( va.begin() , va.end() );
  for( size_t i = 0 ; i < va.size() ; i ++ )
    printf( "%d%c" , va[ i ] , " \n"[ i + 1 == va.size() ] );
}
int bkst[ 1 << 22 ] , of[ N ] , oe[ N ];
void solve2(){
  for( int i = 2 ; i <= n ; i ++ )
    for( int j = 0 ; j < optr ; j ++ ){
      if( (f[ i ] >> owho[ j ]) & 1LL )
        of[ i ] |= (1 << j);
      if( (e[ i ] >> owho[ j ]) & 1LL )
        oe[ i ] |= (1 << j);
    }
  dp[ 0 ] = 1;
  int bst = 0 , bc = 0;
  for( int i = 1 ; i < (1 << optr) ; i ++ ){
    for( int j = 0 ; j < nptr ; j ++ ){
      if( oe[ nwho[ j ] ] & i ) continue;
      int ni = i & (~of[ nwho[ j ] ]);
      if( dp[ ni ] ){
        dp[ i ] = 1;
        bk[ i ] = nwho[ j ];
        bkst[ i ] = ni;
        break;
      }
    }
    if( dp[ i ] and count_bit( i ) > bc ){
      bst = i;
      bc = count_bit( i );
    }
  }
  int ans = count_bit( f[ 1 ] ) + bc;
  printf( "%.12f\n" , (double)ans / ( n - 1 ) );
  vector<int> va;
  while( bst ){
    va.push_back( bk[ bst ] );
    neighbor ^= (1LL << bk[ bst ]);
    bst = bkst[ bst ];
  }
  for( int i = 2 ; i <= n ; i ++ )
    if( (neighbor >> i) & 1LL )
      va.push_back( i );
  for( size_t i = 0 ; i < va.size() ; i ++ )
    printf( "%d%c" , va[ i ] , " \n"[ i + 1 == va.size() ] );
}
int main(){
  cin >> n >> m;
  while( m -- ){
    int ui , vi , fi;
    cin >> ui >> vi >> fi;
    if( fi == 0 ){
      f[ ui ] |= (1LL << vi);
      f[ vi ] |= (1LL << ui);
    }else{
      e[ ui ] |= (1LL << vi);
      e[ vi ] |= (1LL << ui);
    }
  }
  neighbor = f[ 1 ] | e[ 1 ];
  eli = neighbor | 2;
  other = 0;
  for( int i = 2 ; i <= n ; i ++ ){
    f[ i ] &= ~eli;
    e[ i ] &= ~eli;
    if( (neighbor >> i) & 1LL ){
      other |= f[ i ];
      other |= e[ i ];
    }
  }
  for( int i = 2 ; i <= n ; i ++ )
    if( (e[ 1 ] >> i) & 1LL )
      swap( f[ i ] , e[ i ] );
  for( int i = 2 ; i <= n ; i ++ )
    if( (neighbor >> i) & 1LL ){
      nwho[ nptr ] = i;
      nid[ i ] = nptr ++;
    }else if( (other >> i) & 1LL ){
      owho[ optr ] = i;
      oid[ i ] = optr ++;
    }
  if( count_bit( neighbor ) <= count_bit( other ) )
    solve1();
  else
    solve2();
}
