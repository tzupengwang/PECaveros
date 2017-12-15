#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL n , a[ N ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
deque< pair<LL,LL> > st[ N << 2 ];
#define M first
#define C second
inline void add( int no , pair<LL,LL> pv ){
  deque< pair<LL,LL> >& cur = st[ no ];
  while( cur.size() > 1u ){
    int sz = cur.size();
    if( (__int128)( cur[ sz - 2 ].C - cur[ sz - 1 ].C ) * ( pv.M - cur[ sz - 2 ].M ) >=
        (__int128)( cur[ sz - 2 ].C - pv.C ) * ( cur[ sz - 1 ].M - cur[ sz - 2 ].M ) ){
      cur.pop_back();
      continue;
    }
    break;
  }
  cur.push_back( pv );
}
const LL inf16 = 10000000000000000LL;
inline LL query( int no , LL x ){
  if( st[ no ].empty() ) return -inf16;
  deque< pair<LL,LL> >& cur = st[ no ];
  while( cur.size() > 1u ){
    if( ( cur[ 0 ].C - cur[ 1 ].C ) <= 
        x * ( cur[ 1 ].M - cur[ 0 ].M ) ){
      cur.pop_front();
      continue;
    }
    break;
  }
  return cur[ 0 ].M * x + cur[ 0 ].C;
}
void add( int no , int l , int r , int p , pair<LL,LL> vv ){
  add( no , vv );
  if( l == r ) return;
  if( p <= mid ) add( L( no ) , l , mid , p , vv );
  else add( R( no ) , mid + 1 , r , p , vv );
}
LL query( int no , int l , int r , int ql , int qr , LL x ){
  if( l == ql and r == qr ) return query( no , x );
  if( qr <= mid ) return query( L( no ) , l , mid , ql , qr , x );
  if( mid < ql ) return query( R( no ) , mid + 1 , r , ql , qr , x );
  return max( query( L( no ) , l , mid , ql , mid , x ) ,
              query( R( no ) , mid + 1 , r , mid + 1 , qr , x ) );
} 
vector<LL> li;
inline int id( LL x ){
  return lower_bound( li.begin() , li.end() , x ) - li.begin() + 1;
}
void init(){
  scanf( "%lld" , &n );
  for( LL i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &a[ i ] );
    li.push_back( a[ i ] );
  }
  sort( li.begin() , li.end() );
  li.resize( unique( li.begin() , li.end() ) - li.begin() );
}
int lsz;
LL ans = -inf16;
void upd_ans( int id , LL cv ){
  LL tans = cv - (LL)(n - id) * (n - id + 1LL) / 2;
  ans = max( ans , tans );
}
void solve(){
  lsz = li.size();
  add( 1 , 0 , lsz , 0 , { 0 , 0 } );
  upd_ans( 0 , 0 );
  for( int i = 1 ; i <= n ; i ++ ){
    int vl = id( a[ i ] );
    LL bst = query( 1 , 0 , lsz , 0 , vl , i );
    bst += i + a[ i ] + a[ i ] - (LL)i * i;
    bst /= 2;
    upd_ans( i , bst );
    LL curm = i + i;
    LL curc = bst + bst - ((LL)i * i + i);
    add( 1 , 0 , lsz , vl , { curm , curc } );
  }
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
