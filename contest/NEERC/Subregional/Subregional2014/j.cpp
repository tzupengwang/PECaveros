#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
#define K 12
const LL mod = 1000000000;
LL x[ K ];
LL n , v[ N ];
char cmd[ N ];
int len;
void build(){
  for( int i = 0 ; i < n ; i ++ ){
    LL vl = 1;
    for( int j = 0 ; j < K ; j ++ ){
      // printf( "%d %d %lld\n" , i , j , vl );
      x[ j ] = ( x[ j ] + vl ) % mod;
      vl = ( vl * v[ i ] ) % mod;
    }
  }
  // for( int i = 0 ; i < 5 ; i ++ )
    // printf( "%d %lld\n" , i , x[ i ] );
}
int pl[ N ];
void init(){
  scanf( "%lld" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &v[ i ] );
  build();
  scanf( "%s" , cmd );
  len = strlen( cmd );
  vector< int > st;
  for( int i = len - 1 ; i >= 0 ; i -- )
    if( cmd[ i ] == ')' )
      st.push_back( i );
    else if( cmd[ i ] == '(' ){
      pl[ st.back() ] = i;
      st.pop_back();
    }
}
struct J{
  LL coe[ K ] , vl , type;
  J(){
    vl = 0;
    for( int i = 0 ; i < K ; i ++ )
      coe[ i ] = 0;
    type = 0;
  }
  J operator-() const{
    J tj = *this;
    tj.vl = ( mod - vl ) % mod;
    for( int i = 0 ; i < K ; i ++ )
      tj.coe[ i ] = ( mod - coe[ i ] ) % mod;
    return tj;
  }
  J sqr() const{
    J tj = *this;
    if( type == 0 ){
      tj.vl = ( vl * vl ) % mod;
    }else{
      for( int i = 0 ; i < K ; i ++ )
        tj.coe[ i ] = 0;
      for( int i = 0 ; i < K ; i ++ )
        for( int j = 0 ; j < K ; j ++ )
          if( i + j < K )
            tj.coe[ i + j ] = ( tj.coe[ i + j ] + 
                                coe[ i ] * coe[ j ] ) % mod;
    }
    return tj;
  }
  J sum() const{
    J tj;
    for( int i = 0 ; i < K ; i ++ )
      tj.vl = ( tj.vl + coe[ i ] * x[ i ] ) % mod;
    return tj;
  }
  J operator+( const J& tj ) const{
    if( type == 0 && tj.type == 0 ){
      J xf;
      xf.vl = ( vl + tj.vl ) % mod;
      return xf;
    }else if( type == 1 && tj.type == 1 ){
      J xf; xf.type = 1;
      for( int i = 0 ; i < K ; i ++ )
        xf.coe[ i ] = ( coe[ i ] + tj.coe[ i ] ) % mod;
      return xf;
    }else{
      J xf; xf.type = 1;
      for( int i = 0 ; i < K ; i ++ )
        xf.coe[ i ] = ( coe[ i ] + tj.coe[ i ] ) % mod;
      xf.coe[ 0 ] = ( xf.coe[ 0 ] + vl + tj.vl ) % mod;
      return xf;
    }
  }
  J operator-( const J& tj ) const{
    if( type == 0 && tj.type == 0 ){
      J xf;
      xf.vl = ( vl - tj.vl + mod ) % mod;
      return xf;
    }else if( type == 1 && tj.type == 1 ){
      J xf; xf.type = 1;
      for( int i = 0 ; i < K ; i ++ )
        xf.coe[ i ] = ( coe[ i ] - tj.coe[ i ] + mod ) % mod;
      return xf;
    }else{
      J xf; xf.type = 1;
      for( int i = 0 ; i < K ; i ++ )
        xf.coe[ i ] = ( coe[ i ] - tj.coe[ i ] + mod ) % mod;
      xf.coe[ 0 ] = ( xf.coe[ 0 ] + vl - tj.vl + mod ) % mod;
      return xf;
    }
  }
  J operator*( const J& tj ) const{
    if( type == 0 && tj.type == 0 ){
      J xf;
      xf.vl = ( vl * tj.vl ) % mod;
      return xf;
    }else if( type == 1 && tj.type == 1 ){
      J xf; xf.type = 1;
      for( int i = 0 ; i < K ; i ++ )
        for( int j = 0 ; j < K ; j ++ )
          if( i + j < K )
            xf.coe[ i + j ] = ( xf.coe[ i + j ] +
                                coe[ i ] * tj.coe[ j ] ) % mod;
      return xf;
    }else if( type == 1 ){
      J xf; xf.type = 1;
      for( int i = 0 ; i < K ; i ++ )
        xf.coe[ i ] = ( coe[ i ] * tj.vl ) % mod;
      return xf;
    }else{
      J xf; xf.type = 1;
      for( int i = 0 ; i < K ; i ++ )
        xf.coe[ i ] = ( tj.coe[ i ] * vl ) % mod;
      return xf;
    }
  }
  void print(){
    if( type == 0 ){
      printf( "N : %lld\n" , vl );
    }else{
      printf( "X :" );
      for( int i = 0 ; i < K ; i ++ )
        printf( " %lld" , coe[ i ] );
      puts( "" );
    }
  }
};
J parse( int l , int r ){
  deque< pair<J,int> > vj;
  for( int i = r ; i >= l ; i -- ){
    if( cmd[ i ] == 'X' ){
      J tj;
      tj.type = 1;
      tj.coe[ 1 ] = 1;
      vj.push_back( { tj , 0 } );
    }else if( cmd[ i ] == 'N' ){
      J tj;
      tj.vl = n;
      vj.push_back( { tj , 0 } );
    }else if( isdigit( cmd[ i ] ) ){
      int lft = i;
      while( lft >= l && isdigit( cmd[ lft ] ) )
        lft --;
      lft ++;
      LL tvl = 0;
      for( int j = max( lft , i - 8 ) ; j <= i ; j ++ )
        tvl = tvl * 10 + cmd[ j ] - '0';
      J tj;
      tj.vl = tvl;
      vj.push_back( { tj , 0 } );
      i = lft;
    }else if( cmd[ i ] == ')' ){
      vj.push_back( { parse( pl[ i ] + 1 , i - 1 ) , 0 } );
      i = pl[ i ];
    }else if( cmd[ i ] == '+' )
      vj.push_back( { J() , 1 } );
    else if( cmd[ i ] == '-' )
      vj.push_back( { J() , 2 } );
    else if( cmd[ i ] == '*' )
      vj.push_back( { J() , 3 } );
    else if( cmd[ i ] == ':' ){
      vj.push_back( { J() , 4 } );
      i --;
    }else if( cmd[ i ] == '/' ){
      vj.push_back( { J() , 5 } );
      i --;
    }else assert( false );
  }
  while( vj.size() > 1 ){
    // if( l == 0 ){
      // puts( "======" );
      // for( auto i : vj ){
        // if( i.second ){
          // printf( "%c\n" , " +-*^s"[ i.second ] );
        // }else i.first.print();
      // }
      // puts( "======" );
    // }
    if( (int)vj.size() == 2 ){
      if( vj.back().second == 2 )
        vj.front().first = -vj.front().first;
      else if( vj.back().second == 4 )
        vj.front().first = vj.front().first.sqr();
      else if( vj.back().second == 5 )
        vj.front().first = vj.front().first.sum();
      else assert( false );
      vj.pop_back();
      break;
    }
    pair<J,int> j1 = vj.front(); vj.pop_front();
    pair<J,int> j2 = vj.front(); vj.pop_front();
    pair<J,int> j3 = vj.front(); vj.pop_front();
    if( j2.second >= 4 ||
        ( j2.second == 2 && j3.second ) ){
      vj.push_front( j3 );
      if( j2.second == 2 )
        vj.push_front( { -j1.first , 0 } );
      else if( j2.second == 4 )
        vj.push_front( { j1.first.sqr() , 0 } );
      else if( j2.second == 5 )
        vj.push_front( { j1.first.sum() , 0 } );
      else assert( false );
    }else{
      if( j2.second == 2 )
        vj.push_front( { j3.first - j1.first , 0 } );
      else if( j2.second == 1 )
        vj.push_front( { j3.first + j1.first , 0 } );
      else if( j2.second == 3 )
        vj.push_front( { j3.first * j1.first , 0 } );
      else assert( false );
    }
  }
  return vj.back().first;
}
void solve(){
  J j = parse( 0 , len - 1 );
  printf( "%lld\n" , j.vl );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "j.in" , "r" , stdin );
  freopen( "j.out" , "w" , stdout );
#endif
  init();
  solve();
}
