#include <bits/stdc++.h>
using namespace std;
#define N 6
const int mod = 1000000007;
int n , m;
vector< pair<int,int> > nxt[ 1 << N ][ 1 << N ];
int vst[ 1 << (N * 3) ];
int si , sj;

int v[ 333 ][ 333 ];

typedef long long LL;
set<LL> cans;

void go( int tn , int tm ){
  if( tn >= n ){
    tn = 0;
    tm ++;
  }
  if( tm >= m ){
    LL tmp = 0;
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < m ; j ++ )
        tmp = (tmp << 1) | (v[ i ][ j ] - 1);
    cans.insert( tmp );
    return;
  }
  if( v[ tn ][ tm ] ) go( tn + 1 , tm );
  else{
    if( tm + 1 < m ){
      for( int b = 0 ; b < 2 ; b ++ ){
        v[ tn ][ tm ] = b + 1;
        v[ tn ][ tm + 1 ] = 2 - b;
        go( tn + 1 , tm );
        v[ tn ][ tm ] = 0;
        v[ tn ][ tm + 1 ] = 0;
      }
    }
    if( tn + 1 < n and v[ tn + 1 ][ tm ] == 0 ){
      for( int b = 0 ; b < 2 ; b ++ ){
        v[ tn ][ tm ] = b + 1;
        v[ tn + 1 ][ tm ] = 2 - b;
        go( tn + 2 , tm );
        v[ tn ][ tm ] = 0;
        v[ tn + 1 ][ tm ] = 0;
      }
    }
  }
}

int bf(){
  cans.clear();
  go( 0 , 0 );
  return cans.size();
}

int cdp[ 2 ][ 1 << N ][ 1 << N ][ 1000 ];
bool gt[ 2 ][ 1 << N ][ 1 << N ][ 1000 ];
queue< tuple<int,int,int> > q[ 2 ];
bool okay( int i , int j , int k ){
  for( int dd = 1 ; dd + 1 < n ; dd ++ )
    if( ((i >> dd) & 1) and
        ((k >> dd) & 1) and
        ((j >> dd) & 1) and
        ((j >> (dd-1)) & 1) and
        ((j >> (dd+1)) & 1) )
      return false;
  return true;
}
int guess(){
  cdp[ 0 ][ 0 ][ 0 ][ 0 ] = 1;
  int cur = 0 , pre = 1;
  int nd = (n * m) / 2;
  q[ 0 ].push( make_tuple( 0 , 0 , 0 ) );
  for( int _ = 1 ; _ <= m ; _ ++ ){
    swap( cur , pre );
    while( q[ pre ].size() ){
      auto x = q[ pre ].front(); q[ pre ].pop();
      int i = get<0>( x );
      int j = get<1>( x );
      int c = get<2>( x );

      for( int nxtj = 0 ; nxtj < (1 << n) ; nxtj ++ ){
        int nc = c + __builtin_popcount( nxtj );
        if( nc > nd ) continue;
        
        if( _ < 3 or okay( i , j , nxtj ) ){
          if( not gt[ cur ][ j ][ nxtj ][ nc ] ){
            q[ cur ].push( make_tuple( j , nxtj , nc ) );
            gt[ cur ][ j ][ nxtj ][ nc ] = true;
          }
          cdp[ cur ][ j ][ nxtj ][ nc ] = ( cdp[ cur ][ j ][ nxtj ][ nc ] +
                                          cdp[ pre ][ i ][ j ][ c ] ) % mod;
        }
      }

      cdp[ pre ][ i ][ j ][ c ] = 0;
      gt[ pre ][ i ][ j ][ c ] = false;
    }
  }
  int ret = 0;
  for( int i = 0 ; i < (1 << n) ; i ++ )
    for( int j = 0 ; j < (1 << n) ; j ++ )
      ret = ( ret + cdp[ cur ][ i ][ j ][ nd ] ) % mod;
  return ret;
}

pair<int,int> ss[ 1 << (N * 3) ];
pair<int,int> tt[ 1 << (N * 3) ];

void go( int cur , int i , int j , int i2 , int j2 ){
  if( cur == n ){
    int tgt = (i << (n + n)) | (i2 << n) | j2;
    if( vst[ tgt ] ){
      if( i == 3 and j == 9 and i2 == 10 and j2 == 0 ){
        cerr << ss[ tgt ].first << " " << ss[ tgt ].second << " ";
        cerr << tt[ tgt ].first << " " << tt[ tgt ].second << "\n";
      }
      return;
    }
    vst[ tgt ] = 1;
    ss[ tgt ] = { si , sj };
    tt[ tgt ] = { i2 , j2 };
    nxt[ si ][ sj ].push_back( { i2 , j2 } );
    return;
  }
  if( (j >> cur) & 1 ){
    go( cur + 1 , i , j , i2 , j2 );
    return;
  }
  for( int b = 0 ; b < 2 ; b ++ )
    go( cur + 1 , i , j , i2 | (b << cur) , j2 | (1 << cur) );
  if( cur + 1 < n and ((j >> (cur + 1)) & 1) == 0 ){
    for( int b = 0 ; b < 2 ; b ++ ){
      int ni2 = i2;
      ni2 |= (b << cur);
      ni2 |= ((1-b) << (cur+1));
      go( cur + 2 , i , j , ni2 , j2 );
    }
  }
}
void build(){
  for( int i = 0 ; i < (1 << n) ; i ++ )
    for( int j = 0 ; j < (1 << n) ; j ++ ){
      si = i; sj = j;
      int i2 = 0;
      for( int ii = 0 ; ii < n ; ii ++ )
        if( (j >> ii) & 1 ){
          if( ((i >> ii) & 1) == 0 )
            i2 |= (1 << ii);
        }
      go( 0 , i , j , i2 , 0 );
    }
}
int dp[ 2 ][ 1 << N ][ 1 << N ];
int main(){
  //for( n = 1 ; n <= 6 ; n ++ )
    //for( m = 1 ; m <= 6 ; m ++ ){
      //printf( "%d %d : %d\n" , n , m , bf() );
    //}
  //return 0;
  cin >> n >> m;
  if( (n * m) & 1 ){
    puts( "0" );
    exit(0);
  }
  //if( n * m < 30 ){
    //cout << bf() << endl;
    //return 0;
  //}
  cout << guess() << endl;
  exit(0);
  build();
  dp[ 0 ][ 0 ][ 0 ] = 1;
  int cur = 0 , pre = 1;
  for( int i = 1 ; i <= m ; i ++ ){
    swap( cur , pre );
    for( int j = 0 ; j < (1 << n) ; j ++ )
      for( int k = 0 ; k < (1 << n) ; k ++ )
        dp[ cur ][ j ][ k ] = 0;
    for( int j = 0 ; j < (1 << n) ; j ++ )
      for( int k = 0 ; k < (1 << n) ; k ++ ){
        if( dp[ pre ][ j ][ k ] == 0 ) continue;
        for( auto ii : nxt[ j ][ k ] ){
          int& to = dp[ cur ][ ii.first ][ ii.second ];
          to = (to + dp[ pre ][ j ][ k ]) % mod;
        }
      }
    //int cc = 0;
    //for( int j = 0 ; j < (1 << n) ; j ++ )
      //for( int k = 0 ; k < (1 << n) ; k ++ )
        //if( dp[ cur ][ j ][ k ] ){
          //printf( "%2d %2d %2d : %2d" , cur , j , k , dp[ cur ][ j ][ k ] );
          //putchar( " \n"[ (++ cc) % 5 == 0 ] );
        //}
    //puts( "" );
  }
  int ans = 0;
  for( int i = 0 ; i < (1 << n) ; i ++ )
    ans = (ans + dp[ cur ][ i ][ 0 ]) % mod;
  //cerr << bf() << endl;
  cout << ans << endl;
}
