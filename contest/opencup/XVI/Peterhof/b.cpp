#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 111
typedef long long LL;
const int mod = 1000000007;
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mpow( int a , int b ){
  if( !b ) return 1;
  int ret = mpow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
inline int inv( int a ){
  return mpow( a , mod - 2 );
}

struct djs{
  int a[ 22 ] , sz;
  djs(){
    sz = 0;
  }
  void resize( int x ){
    sz = x;
  }
  int& operator[]( int x ){
    return a[ x ];
  }
  const int operator[]( int x ) const {
    return a[ x ];
  }
  size_t size()const {
    return sz;
  }
  bool operator==( const djs& he ) const{
    if( sz != he.sz ) return false;
    for( int i = 0 ; i < sz ; i ++ )
      if( a[ i ] != he.a[ i ] )
        return false;
    return true;
  }
};

inline LL to_ll( djs& d , int sz ){
  LL ret = 0;
  for( int i = 0 ; i < sz ; i ++ )
    ret = (ret << 4) | d[ i ];
  return ret;
}

inline void to_djs( LL cur , djs& d , int sz ){
  d.resize( sz );
  for( int i = sz - 1 ; i >= 0 ; i -- ){
    d[ i ] = cur & 15;
    cur >>= 4;
  }
}


#include <bits/extc++.h>
using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp>
typedef cc_hash_table<LL,int> map_t;

int rgt[ N ][ N ] , dn[ N ][ N ];
int r , c;
bool do_c;
inline int f( djs& dd , int who ){
  int ret = who;
  while( ret != dd[ ret ] )
    ret = dd[ ret ];
  return dd[ who ] = ret;
}
inline void uni( djs& dd , int ai , int bi ){
  ai = f( dd , ai );
  bi = f( dd , bi );
  if( ai == bi ) return;
  if( bi < ai ) swap( ai , bi );
  if( do_c and ai != 0 and bi + 1 == c )
    dd[ ai ] = bi;
  else
    dd[ bi ] = ai;
}
void uniq( djs& dd , int _n ){
  for( int i = 0 ; i < _n ; i ++ )
    f( dd , i );
}
void reset( djs& d , int sz ){
  d.resize( sz );
  for( int i = 0 ; i < sz ; i ++ )
    d[ i ] = i;
}
map_t dp[ 2 ];
int ans , inv100;
int main(){
  //scanf( "%d%d" , &r , &c );
  r = 10;
  c = 10;
  inv100 = inv( 100 );
  for( int i = 0 ; i < r ; i ++ )
    for( int j = 0 ; j + 1 < c ; j ++ ){
      //scanf( "%d" , &rgt[ i ][ j ] );
      rgt[ i ][ j ] = rand() % 98 + 1;
      rgt[ i ][ j ] = mul( rgt[ i ][ j ] , inv100 );
    }
  for( int i = 0 ; i + 1 < r ; i ++ )
    for( int j = 1 ; j + 1 < c ; j ++ ){
      //scanf( "%d" , &dn[ i ][ j ] );
      dn[ i ][ j ] = rand() % 98 + 1;
      dn[ i ][ j ] = mul( dn[ i ][ j ] , inv100 );
    }
  if( c - 1 <= r ){
    do_c = true;
    for( int i = 0 ; i < (1 << (c - 1)) ; i ++ ){
      djs st; reset( st , c );
      int prob = 1;
      for( int j = 0 ; j < c - 1 ; j ++ )
        if( (i >> j) & 1 ){
          prob = mul( prob , rgt[ 0 ][ j ] );
          uni( st , j , j + 1 );
        }else
          prob = mul( prob , sub( 1 , rgt[ 0 ][ j ] ) );
      uniq( st , c );
      if( f( st , c - 1 ) == 0 )
        ans = add( ans , prob );
      else{
        LL key = to_ll( st , c );
        dp[ 0 ][ key ] = add( dp[ 0 ][ key ] , prob );
      }
    }
    for( int i = 1 ; i < r ; i ++ ){
      int cur = i & 1 , pre = 1 - cur;
      map_t tmp;
      for( auto pre_st : dp[ pre ] ){
        djs pre_djs;
        to_djs( pre_st.first , pre_djs , c );
        int prob = pre_st.second;
        if( prob == 0 ) continue;

        djs nxt; reset( nxt , c + c );
        for( int j = 0 ; j < c ; j ++ )
          nxt[ c + j ] = pre_djs[ j ] > 0 and pre_djs[ j ] + 1 < c ?
                         pre_djs[ j ] + c : pre_djs[ j ];

        for( int msk = 0 ; msk < (1 << (c - 2)) ; msk ++ ){
          djs r_nxt = nxt;
          int nprob = prob;
          for( int j = 1 ; j + 1 < c ; j ++ )
            if( (msk >> (j - 1)) & 1 ){
              nprob = mul( nprob , dn[ i - 1 ][ j ] );
              uni( r_nxt , j , c + j );
            }else
              nprob = mul( nprob , sub( 1 , dn[ i - 1 ][ j ] ) );
          uniq( r_nxt , c + c );
          r_nxt.resize( c );

          LL key = to_ll( r_nxt , c );
          tmp[ key ] = add( tmp[ key ] , nprob );
        }
      }
      dp[ cur ].clear();
      for( auto pre_st : tmp ){
        djs pre_djs;
        to_djs( pre_st.first , pre_djs , c );
        int prob = pre_st.second;
        if( prob == 0 ) continue;
        for( int msk = 0 ; msk < (1 << (c - 1)) ; msk ++ ){
          djs cur_djs = pre_djs;
          int nprob = prob;
          for( int j = 0 ; j < c - 1 ; j ++ )
            if( (msk >> j) & 1 ){
              nprob = mul( nprob , rgt[ i ][ j ] );
              uni( cur_djs , j , j + 1 );
            }else
              nprob = mul( nprob , sub( 1 , rgt[ i ][ j ] ) );
          uniq( cur_djs , c );
          if( f( cur_djs , c - 1 ) == 0 )
            ans = add( ans , nprob );
          else{
            LL key = to_ll( cur_djs , c );
            dp[ cur ][ key ] = add( dp[ cur ][ key ] , nprob );
          }
        }
      }
    }
    printf( "%d\n" , ans );
    return 0;
  }else{
    djs s;
    reset( s , r + 1 );
    for( int i = 1 ; i <= r ; i ++ )
      s[ i ] = 0;
    dp[ 0 ][ to_ll( s , r + 1 ) ] = 1;
    for( int j = 1 ; j < c ; j ++ ){
      map_t tmp;
      int now = j & 1 , pre = 1 - now;
      for( auto pre_st : dp[ pre ] ){
        djs pre_djs;
        to_djs( pre_st.first , pre_djs , r + 1 );
        int prob = pre_st.second;
        if( prob == 0 ) continue;
        for( int msk = 0 ; msk < (1 << r) ; msk ++ ){
          djs cur_djs;
          reset( cur_djs , r + r + 1 );
          int nprob = prob;
          for( int i = 1 ; i <= r ; i ++ )
            cur_djs[ r + i ] = pre_djs[ i ] ? pre_djs[ i ] + r : pre_djs[ i ];
          for( int i = 0 ; i < r ; i ++ )
            if( (msk >> i) & 1 ){
              nprob = mul( nprob , rgt[ i ][ j - 1 ] );
              uni( cur_djs , i + 1 , i + 1 + r );
            }else
              nprob = mul( nprob , sub( 1 , rgt[ i ][ j - 1 ] ) );
          uniq( cur_djs , r + r + 1 );

          cur_djs.resize( r + 1 );
          LL key = to_ll( cur_djs , r + 1 );
          tmp[ key ] = add( tmp[ key ] , nprob );
        }
      }
      dp[ now ].clear();
      for( auto pre_st : tmp ){
        djs pre_djs;
        to_djs( pre_st.first , pre_djs , r + 1 );
        int prob = pre_st.second;
        if( prob == 0 ) continue;
        if( j + 1 == c ){
          bool ok = false;
          for( int i = 1 ; i <= r ; i ++ )
            if( f( pre_djs , i ) == 0 ){
              ok = true;
              break;
            }
          if( ok )
            ans = add( ans , prob );
          continue;
        }
        for( int msk = 0 ; msk < (1 << (r - 1)) ; msk ++ ){
          djs cur_djs = pre_djs;
          int nprob = prob;
          for( int i = 0 ; i + 1 < r ; i ++ ){
            if( (msk >> i) & 1 ){
              nprob = mul( nprob , dn[ i ][ j ] );
              uni( cur_djs , i + 1 , i + 2 );
            }else{
              nprob = mul( nprob , sub( 1 , dn[ i ][ j ] ) );
            }
          }
          uniq( cur_djs , r + 1 );
          bool keep = false;
          for( int i = 1 ; i <= r ; i ++ )
            if( cur_djs[ i ] == 0 ){
              keep = true;
              break;
            }
          if( not keep ) continue;
          LL key = to_ll( cur_djs , r + 1 );
          dp[ now ][ key ] = add( dp[ now ][ key ] , nprob );
        }
      }
      //cerr << dp[ now ].size() << endl;
    }
    printf( "%d\n" , ans );
  }
}
