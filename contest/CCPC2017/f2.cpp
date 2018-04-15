#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int getint(){
  int x = 0; char c = getchar();
  while( c < '0' or c > '9' ) c = getchar();
  while(c >= '0' and c <= '9') x = x * 10 + c - '0' , c = getchar();
  return x;
}
#define N 222
#define Q 500050
#define NONE -2
#define TSAN -1
inline int comb( int x , int y ){
  if( x == NONE or y == NONE ) return x + y - NONE;
  if( x == TSAN or y == TSAN ) return TSAN;
  return x == y ? x : TSAN;
}
const LL inf = 1e9;
LL sub( LL a , LL b , LL mod ){
  a -= b;
  return a < 0 ? a + mod : a;
}
LL mul( LL a , LL b , LL mod ){
  if( mod < inf ) return a * b % mod;
  LL ret = 0;
  while( b ){
    if( b & 1LL ) ret = (ret + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return ret;
}
pair<LL,LL> gcd( LL a , LL b , LL lcm ){
  if( b == 0 ) return {1, 0};
  pair<LL,LL> q = gcd( b , a % b , lcm );
  return {q.second, sub( q.first , mul( q.second , (a / b) , lcm ) , lcm )};
}
pair<LL,LL> cr( LL x1 , LL m1 , LL x2 , LL m2 ){
  LL g = __gcd( m1 , m2 );
  if( (x2 - x1) % g ) return {-1, -1};
  m1 /= g; m2 /= g;
  LL lcm = (m1 * g) * m2;
  pair<LL,LL> p = gcd(m1, m2, lcm);
  LL res = (x2 - x1) % lcm;
  if( res < 0 ) res += lcm;
  res = mul( res , (p.first % lcm + lcm) % lcm , lcm );
  res = mul( res , m1 , lcm );
  res = (res + x1) % lcm;
  return {res , lcm};
}
int n , m, q;
int ql[ Q ] , qr[ Q ] , qu[ Q ] , qd[ Q ];
int a[ N ][ N ] , b[ N ][ N ];
LL ans[ Q ];
vector<int> wt[ N ][ N ];
void init(){
  //scanf( "%d%d" , &n , &m );
  n = getint();
  m = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      a[ i ][ j ] = getint();
      //scanf( "%d" , &a[ i ][ j ] );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      b[ i ][ j ] = getint();
      //scanf( "%d" , &b[ i ][ j ] );
  q = getint();
  //scanf( "%d" , &q );
  for( int i = 0 ; i < q ; i ++ ){
    ql[ i ] = getint();
    qu[ i ] = getint();
    qr[ i ] = getint();
    qd[ i ] = getint();
    //scanf( "%d%d%d%d" , &ql[ i ] , &qu[ i ] , &qr[ i ] , &qd[ i ] );
    wt[ ql[ i ] ][ qr[ i ] ].push_back( i );
  }
}
#define K 41
int cs , v[ K ][ N ] , lft[ K ][ N ] , fst[ K ][ N ];
void solve(){
  for( int l = 1 ; l <= n ; l ++ ){
    for( int kk = 0 ; kk < K ; kk ++ )
      for( int j = 1 ; j <= m ; j ++ )
        v[ kk ][ j ] = NONE;
    for( int r = l ; r <= n ; r ++ ){
      for( int j = 1 ; j <= m ; j ++ )
        v[ b[ r ][ j ] ][ j ] = comb( v[ b[ r ][ j ] ][ j ] , a[ r ][ j ] );

      for( int kk = 1 ; kk <= 40 ; kk ++ ){
        int nlft = 1 , nfst = 0 , cnt[ K ] = {} , tot = 0;
        for( int j = 1 ; j <= m ; j ++ ){
          if( v[ kk ][ j ] != NONE ) nfst = j;
          fst[ kk ][ j ] = nfst;
          if( v[ kk ][ j ] == TSAN ){
            while( nlft <= j ){
              if( v[ kk ][ nlft ] != TSAN and
                  v[ kk ][ nlft ] != NONE )
                cnt[ v[ kk ][ nlft ] ] = 0;
              nlft ++;
            }
            tot = 0;
          }else if( v[ kk ][ j ] != NONE ){
            cnt[ v[ kk ][ j ] ] ++;
            if( cnt[ v[ kk ][ j ] ] == 1 ) tot ++;
            while( tot > 1 ){
              if( v[ kk ][ nlft ] != TSAN and
                  v[ kk ][ nlft ] != NONE ){
                cnt[ v[ kk ][ nlft ] ] --;
                if( cnt[ v[ kk ][ nlft ] ] == 0 )
                  tot --;
              }
              nlft ++;
            }
          }
          lft[ kk ][ j ] = nlft;
        }
      }

      for( int qid : wt[ l ][ r ] ){
        LL aa = -1 , am = -1;
        for( int md = 1 ; md <= 40 ; md ++ ){
          if( fst[ md ][ qd[ qid ] ] < qu[ qid ] )
            continue;
          if( lft[ md ][ qd[ qid ] ] > qu[ qid ] ){
            aa = -1;
            break;
          }
          LL val = v[ md ][ fst[ md ][ qd[ qid ] ] ];
          if( am == -1 )
            aa = val , am = md;
          else
            tie( aa , am ) = cr( aa , am , val , md );
          if( aa == -1 ) break;
        }
        ans[ qid ] = aa;
      }

      wt[ l ][ r ].clear();
    }
  }
  printf( "Case #%d:\n" , ++ cs );
  for( int i = 0 ; i < q ; i ++ )
    printf( "%lld\n" , ans[ i ] );
}
int main(){
  int t = getint();
  //scanf( "%d" , &t );
  while( t -- ){
    init();
    solve();
  }
}
