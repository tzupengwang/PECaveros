#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int b , s , tot;
vector< int > v; //Vi -> i, 0 -> E, Ri -> -i
int pr[ 1021 ];
LL bs;

int mst;

struct info{
  LL r[ 13 ][ 13 ] , s , t;
  info(){
    s = t = 0;
    for( int i = 1 ; i <= mst ; i ++ )
      for( int j = 1 ; j <= mst ; j ++ )
        r[ i ][ j ] = 0;
  }
  info& operator+=( int k ){
    r[ t ][ k ] ++;
    if( s == 0 )
      s = t = k;
    else
      t = k;
    return *this;
  }
  info& operator+=( const info& he ){
    for( int i = 1 ; i <= mst ; i ++ )
      for( int j = 1 ; j <= mst ; j ++ )
        r[ i ][ j ] += he.r[ i ][ j ];
    r[ t ][ he.s ] ++;
    if( s == 0 ){
      s = he.s;
      t = he.t;
    }else if( he.s )
      t = he.t;
    return *this;
  }
  info& operator*=( LL tk ){
    for( int i = 1 ; i <= mst ; i ++ )
      for( int j = 1 ; j <= mst ; j ++ )
        r[ i ][ j ] *= tk;
    r[ t ][ s ] += tk - 1;
    return *this;
  }
};

int mapping[ 20 ];

info parse( int l , int r ){
  info ret;
  for( int i = l ; i <= r ; ){
    if( v[ i ] > 0 ){
      int nid = mapping[ v[ i ] ];
      if( nid == 0 ){
        i ++;
        continue;
      }
      ret += nid;
      i ++;
      continue;
    }
    info tmp = parse( i + 1 , pr[ i ] - 1 );

    tmp *= (-v[ i ]);
    
    ret += tmp;

    i = pr[ i ] + 1;
  }
  return ret;
}

LL ans , other;
LL dp[ 14 ][ 1 << 14 ] , cst[ 1 << 14 ];

void go( int msk ){
  int cid = 0;
  for( int i = 0 ; i < tot ; i ++ )
    if( (msk >> i) & 1 )
      mapping[ i + 1 ] = 0;
    else
      mapping[ i + 1 ] = ++ cid;
  info ret = parse( 0 , (int)v.size() - 1 );

  other = 0;
  for( int i = 1 ; i <= mst ; i ++ )
    for( int j = 1 ; j <= mst ; j ++ )
      if( i != j )
        other += ret.r[ i ][ j ];


  for( int j = 0 ; j < (1 << mst) ; j ++ )
    cst[ j ] = 0;
  for( int j = 0 ; j < (1 << mst) ; j ++ ){
    if( __builtin_popcount( j ) > s )
      continue;
    for( int k = 0 ; k < mst ; k ++ )
      if( (j >> k) & 1 ){
        cst[ j ] = cst[ j ^ (1 << k) ];
        for( int o = 0 ; o < mst ; o ++ )
          if( ((j >> o) & 1) and o != k ){
            cst[ j ] -= ret.r[ k + 1 ][ o + 1 ];
            cst[ j ] -= ret.r[ o + 1 ][ k + 1 ];
          }
        break;
      }
  }

  for( int i = 0 ; i < b ; i ++ )
    for( int j = 0 ; j < (1 << mst) ; j ++ )
      dp[ i ][ j ] = 0;

  for( int i = 1 ; i < b ; i ++ )
    for( int j = 0 ; j < (1 << mst) ; j ++ )
      for( int jj = j ; jj ; jj = (jj - 1) & j )
        dp[ i ][ j ] = min( dp[ i ][ j ] ,
                            dp[ i - 1 ][ j ^ jj ] + cst[ jj ] );

  LL tans = bs + other + dp[ b - 1 ][ (1 << mst) - 1 ];

  ans = min( ans , tans );
}

void solve(){
  ans = bs * 2;
  
  mst = tot - s;
  for( int i = 0 ; i < (1 << tot) ; i ++ )
    if( __builtin_popcount( i ) == s )
      go( i );

  ans ++;

  printf( "%lld\n" , ans );
  exit(0);
}

LL cal( int l , int r ){
  LL ret = 0;
  for( int i = l ; i <= r ; ){
    if( v[ i ] > 0 ){
      ret ++;
      i ++;
      continue;
    }else if( v[ i ] < 0 ){
      LL tmp = cal( i + 1 , pr[ i ] - 1 );
      ret += (-v[ i ]) * tmp;
      i = pr[ i ] + 1;
    }else
      assert( false );
  }
  return ret;
}
int main(){
  cin >> b >> s;
  string ss;
  vector<int> wt;
  while( cin >> ss ){
    if( ss[ 0 ] == 'E' )
      v.push_back( 0 );
    if( ss[ 0 ] == 'R' ){
      int rep = 0;
      sscanf( ss.c_str() + 1 , "%d" , &rep );
      v.push_back( -rep );
    }
    if( ss[ 0 ] == 'V' ){
      int id = 0;
      sscanf( ss.c_str() + 1 , "%d" , &id );
      v.push_back( +id );
      wt.push_back( id );
    }
  }
  {
    sort( wt.begin() , wt.end() );
    wt.resize( unique( wt.begin() , wt.end() ) - wt.begin() );
    for( size_t i = 0 ; i < v.size() ; i ++ )
      if( v[ i ] > 0 )
        v[ i ] = lower_bound( wt.begin() , wt.end() , v[ i ] ) - wt.begin() + 1;
    tot = wt.size();
  }
  {
    vector<int> stk;
    for( size_t i = 0 ; i < v.size() ; i ++ )
      if( v[ i ] < 0 )
        stk.push_back( i );
      else if( v[ i ] == 0 ){
        pr[ stk.back() ] = i;
        stk.pop_back();
      }
  }
  bs = cal( 0 , (int)v.size() - 1 );
  if( tot <= s ){
    printf( "%lld\n" , bs );
    exit(0);
  }
  solve();
}
