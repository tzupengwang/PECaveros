#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mod = 1000000007;
LL add( LL a , LL b ){
  a += b;
  return a >= mod ? a - mod : a;
}
LL sub( LL a , LL b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
LL mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
LL mypow( LL a , LL b ){
  LL ret = 1;
  while( b ){
    if( b & 1LL ) ret = mul( ret , a );
    a = mul( a , a );
    b >>= 1;
  }
  return ret;
}
LL CC2( LL x ){
  return (1 + x) * x / 2;
}
#define M 4096
//__int128 cc[ M ][ M ];
__int128 inf = 4e18;
LL cc[ M ][ M ];
void build(){
  for( LL i = 0 ; i < M ; i ++ ){
    __int128 comb = 1 , sum = 0;
    for( LL j = i , kk = 0 ; j < M ; j ++ , kk ++ ){
      if( kk ){
        comb *= j;
        comb /= kk;
      }
      sum += comb;
      sum = min( sum , inf );
      cc[ i ][ j ] = sum;
      if( sum == inf ){
        for( LL k = j + 1 ; k < M ; k ++ )
          cc[ i ][ k ] = sum;
        break;
      }
    }
  }
}
bool smaller( LL a , LL b , LL k ){
  if( a < M and b < M ) return cc[ a ][ b ] < k;
  LL ca = b + 1 , cb = b - a;
  if( ca - cb < cb ) cb = ca - cb;
  __int128 g = k , r = 1;
  for( LL i = 0 ; i < cb ; i ++ ) g *= (cb - i);
  for( LL i = 0 ; i < cb ; i ++ ){
    r *= (ca - i);
    if( r >= g )
      return false;
  }
  return true;
}
LL C( LL a , LL b ){
  if( a < M and b < M ) return cc[ a ][ b ];
  LL ca = b + 1 , cb = b - a;
  if( ca - cb < cb ) cb = ca - cb;
  __int128 ret = 1;
  for( LL i = 0 ; i < cb ; i ++ ) ret *= (ca - i);
  for( LL i = 0 ; i < cb ; i ++ ) ret /= (cb - i);
  return ret;
}
void gogo( LL len , LL fre , LL bt , LL k ){
  LL ans = sub( mypow( 2 , len ) , mypow( 2 , fre ) );
  LL nxt = fre - 2;
  for( LL i = bt - 1 ; i >= 0 ; i -- ){
    //if( bt < 4 ){
      //__int128 comb = 1;
      //for( LL j = i , kk = 0 ; ; j ++ , kk ++ ){
        //if( kk ){
          //comb *= j;
          //comb /= kk;
        //}
        //if( comb < k ){
          //k -= comb;
          //continue;
        //}
        //ans = add( ans , mypow( 2 , j ) );
        //break;
      //}
      //continue;
    //}
    LL bl = i , br = nxt , ba = bl - 1;
    while( bl <= br ){
      LL bmid = (bl + br) / 2;
      if( smaller( i , bmid , k ) )
      //if( cc[ i ][ bmid ] < k )
        ba = bmid , bl = bmid + 1;
      else
        br = bmid - 1;
    }
    if( ba >= i )
      k -= C( i , ba );
      //k -= cc[ i ][ ba ];
    ans = add( ans , mypow( 2 , ba + 1 ) );
    nxt = ba;
  }
  printf( "%lld\n" , ans );
}
LL n , k;
void solve(){
  if( n == 1 ){
    if( k == 1 ) puts( "1" );
    else puts( "-1" );
    return;
  }
  LL bl = 1 , br = 2e9 , ba = 1;
  while( bl <= br ){
    LL bmid = (bl + br) * .5;
    if( CC2( bmid ) < n )
      ba = bmid , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  LL len = ba + 1 , res = n - CC2( ba );
  LL fre = len - res;
  if( fre <= 1 ){
    if( k != 1 ){
      puts( "-1" );
      return;
    }
    LL ans = mypow( 2 , len );
    ans = sub( ans , 1 + fre );
    printf( "%lld\n" , ans );
    return;
  }
  if( k == 1 ){
    LL a = mypow( 2 , len );
    LL b = mypow( 2 , fre );
    a = sub( a , b );
    printf( "%lld\n" , a );
    return;
  }
  __int128 comb = 1;
  for( LL bt = 0 ; bt <= fre - 1 ; bt ++ ){
    if( bt ){
      comb *= (fre - bt);
      comb /= bt;
    }
    if( comb < (__int128)k ){
      k -= (LL)comb;
      continue;
    }
    gogo( len , fre , bt , k );
    return;
  }
  puts( "-1" );
}
int main(){
  build();
  int _; scanf( "%d" , &_ ); while( _ -- ){
    scanf( "%lld%lld" , &n , &k );
    solve();
  }
}
