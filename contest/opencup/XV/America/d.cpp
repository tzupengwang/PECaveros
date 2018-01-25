#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int mpow( int a , int b ){
  if( !b ) return 1;
  int ret = mpow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
#define N 111
int n , k , b[ N ] , len , slen;
bitset<N> bb;
char buf[ N ];
int dp[ 2 ][ 8 ];

int C[ 9 ][ 9 ];

inline int bit( int p ){
  return bb[ p % len ];
}

void reset( int id ){
  for( int i = 0 ; i < 8 ; i ++ )
    dp[ id ][ i ] = 0;
}

int cc[ 2 ][ 8 ][ 8 ][ 8 ];
bool gt[ 2 ][ 8 ];

void go_cal( int bt , int xn ){
  if( gt[ bt ][ xn ] ) return;
  gt[ bt ][ xn ] = true;
  for( int n_bnd = 0 ; n_bnd <= xn ; n_bnd ++ ){
    int other = xn - n_bnd;
    for( int one = 0 ; one <= n_bnd ; one ++ ){
      if( one and bt == 0 ) break;
      
      for( int other_one = 0 ; other_one <= other ; other_one ++ ){
        if( (one + other_one) & 1 ) continue;
        int to = mul( C[ n_bnd ][ one ] , C[ other ][ other_one ] );
        
        int nxt_bnd = one;
        if( bt == 0 )
          nxt_bnd = n_bnd;

        int& nxt_dp = cc[ bt ][ xn ][ n_bnd ][ nxt_bnd ];
        nxt_dp = add( nxt_dp , to );
      }
    }
  }
}

int cal( int xn ){
  reset( slen & 1 );
  dp[ slen & 1 ][ xn ] = 1;
  for( int i = slen - 1 ; i >= 0 ; i -- ){
    int now = i & 1 , pre = 1 ^ now;
    reset( now );
    go_cal( bit( i ) , xn );
    for( int j = 0 ; j <= xn ; j ++ )
      if( dp[ pre ][ j ] )
        for( int u = 0 ; u <= j ; u ++ )
          dp[ now ][ u ] = add( dp[ now ][ u ],
                                mul( dp[ pre ][ j ] ,
                                     cc[ bit( i ) ][ xn ][ j ][ u ] ) );
  }
  return dp[ 0 ][ 0 ];
}

int ca[ N ];


int fac[ N ] , ifac[ N ];

int go( int gg , int R , int v ){
  if( gg == n ) return (v == 0);
  int ret = 0;
  for( int i = 0 ; i < R ; i ++ )
    ret += go( gg + 1 , i , v ^ i );
  return ret;
}

int bf( int R ){
  return go( 0 , R , 0 );
}

int coe[ 10 ] , who[ 10 ];

map< vector<int> , int > ggt;

void go_cal_coe( int cur , int R ){
  if( cur == n ){
    map<int,int> mm;
    for( int i = 0 ; i < n ; i ++ )
      mm[ who[ i ] ] ++;
    vector<int> tv;
    for( auto i : mm )
      tv.push_back( i.second );
    sort( tv.begin() , tv.end() );
    if( ggt.find( tv ) != ggt.end() ) return;
    int cnt = 0 , ccc = 1 , cR = R;

    int rcc = fac[ n ];

    for( int i : tv ){
      cnt += (i & 1);
      if( i % 2 == 0 ){
        ccc = mul( ccc , cR );
        cR --;
      }
      rcc = mul( rcc , ifac[ i ] );
    }

    ccc = mul( ccc , rcc );

    ggt[ tv ] = ccc;
    //coe[ cnt ] = add( coe[ cnt ] , ccc );
    return;
  }
  for( int i = 0 ; i < n ; i ++ ){
    who[ cur ] = i;
    go_cal_coe( cur + 1 , R );
  }
}

bool cmp( vector<int> v1 , vector<int> v2 ){
  return v1.size() > v2.size();
}

void go_sub( vector<int> vv , int ss , int ii ){
  {
    vector<int> tv = vv;
    sort( tv.begin() , tv.end() );
    ggt[ tv ] -= ii;
  }
  if( ss >= (int)vv.size() ) return;
  go_sub( vv , ss + 1 , ii );
  for( size_t i = ss + 1 ; i < vv.size() ; i ++ ){
    vector<int> nxtv = vv;
    nxtv[ ss ] += vv[ i ];
    for( size_t j = i ; j + 1 < vv.size() ; j ++ )
      nxtv[ j ] = nxtv[ j + 1 ];
    nxtv.pop_back();
    go_sub( nxtv , ss , ii );
  }
}

void cal_coe( int R ){
  go_cal_coe( 0 , R );

  vector< vector<int> > wt;
  for( auto i : ggt )
    wt.push_back( i.first );
  sort( wt.begin() , wt.end() , cmp );
 
  for( auto i : wt ){
 
    int cnt = 0;
    for( int j : i )
      cnt += j & 1;

    coe[ cnt ] = add( coe[ cnt ] ,  ggt[ i ] );

    go_sub( i , 0 , ggt[ i ] );
  }
}


int inv( int x ){
  return mpow( x , mod - 2 );
}

int find_ans(){
  int ret = ca[ n ];
  for( int i = 1 ; i < n ; i ++ )
    ret = sub( ret , mul( coe[ i ] , ca[ i ] ) );
  return mul( ret , inv( coe[ n ] ) ) ;
}

int main(){

  fac[ 0 ] = ifac[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    ifac[ i ] = mpow( fac[ i ] , mod - 2 );
  }

  for( int i = 0 ; i < 9 ; i ++ )
    C[ i ][ 0 ] = C[ i ][ i ] = 1;
  for( int i = 2 ; i < 9 ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      C[ i ][ j ] = add( C[ i - 1 ][ j ],
                         C[ i - 1 ][ j - 1 ] );

  scanf( "%d%d" , &n , &k );
  scanf( "%s" , buf );
  len = strlen( buf );
  for( int i = 0 ; i < len ; i ++ )
    bb[ i ] = buf[ len - i - 1 ] - '0';
  slen = len * k;

  int R = 0;
  for( int i = slen - 1 ; i >= 0 ; i -- )
    R = add( add( R , R ) , bit( i ) );

  cal_coe( R );

  for( int i = 1 ; i <= n ; i ++ ){
    ca[ i ] = cal( i );
    printf( "%d => %d\n" , i , ca[ i ] );
  }

  cerr << "Correct ans = " << bf( R ) << endl;
  cerr << "Find ans = " << find_ans() << endl;
  cerr << (LL)bf( R ) * fac[ n ] << endl;

  int ans = 0;

  if( n == 3 ){
    ans = ca[ 3 ];
    ans = sub( ans , mul( mul( 3 , R ) , ca[ 1 ] ) );
    ans = add( ans , mul( 2 , ca[ 1 ] ) );
  }
  if( n == 4 ){
    ans = ca[ 4 ];
    ans = sub( ans , mul( mul( 12 , R ) , ca[ 2 ] ) );
    ans = add( ans , mul( 20 , ca[ 2 ] ) );
    ans = add( ans , mul( 9 , mul( R , sub( R , 1 ) ) ) );
    ans = sub( ans , mul( 9 , R ) );
  }
  if( n == 5 ){
    ans = ca[ 5 ];
    ans = sub( ans , mul( mul( 10 , R ) , ca[ 3 ] ) );
    ans = add( ans , add( 20 , ca[ 3 ] ) );

    ans = add( ans , mul( mul( 5 , R ) , ca[ 1 ] ) );

    ans = add( ans , add( 4 , ca[ 1 ] ) );
    ans = add( ans , mul( mul( 15 , mul( R , sub( R , 1 ) ) ) , ca[ 1 ] ) );
  }

  cout << ans << endl;

  ans = mul( ans , ifac[ n ] );

  cout << ans << endl;
}
