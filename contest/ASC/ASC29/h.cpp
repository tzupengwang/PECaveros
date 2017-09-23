#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , nn[ N ];
char type[ N ][ 10 ];
vector< pair<pair<int,int>,int> > pos[ N ];
bool ook[ N ] , ans[ N ];
void build_ans(){
  for( int i = 0 ; i < n ; i ++ )
    if( type[ i ][ 0 ] == '$' ){
      int j = ( i - 1 + n ) % n;
      bool lstok = ook[ i ];
      ans[ i ] = lstok;
      while( type[ j ][ 0 ] != '$' ){
        if( type[ j ][ 0 ] == '-' )
          lstok = not lstok;
        ans[ j ] = lstok;
        j = ( j - 1 + n ) % n;
      }
    }
  puts( "consistent" );
  for( int i = 0 ; i < n ; i ++ )
    putchar( "ft"[ ans[ i ] ] );
  puts( "" );
  exit(0);
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "truth.in" , "r" , stdin );
  freopen( "truth.out" , "w" , stdout );
#endif
  cin >> n;
  int cnt = 0;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> type[ i ];
    if( type[ i ][ 0 ] == '$' ){
      cin >> nn[ i ];
      cnt ++;
    }
  }
  if( cnt == 0 ){
    int cc = 0;
    for( int i = 0 ; i < n ; i ++ )
      if( type[ i ][ 0 ] == '-' )
        cc ++;
    puts( cc & 1 ? "inconsistent" : "consistent" );
    if( !(cc & 1) ){
      cc = 0;
      for( int i = 0 ; i < n ; i ++ ){
        putchar( "ft"[ cc ] );
        if( type[ i ][ 0 ] == '-' )
          cc = 1 - cc;
      }
      puts( "" );
    }
    exit(0);
  }
  int totok = 0 , totnok = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( type[ i ][ 0 ] == '$' ){
      int ok = 1 , nok = 0 , j = ( i - 1 + n ) % n;
      int lstok = 1;
      while( type[ j ][ 0 ] != '$' ){
        if( type[ j ][ 0 ] == '+' ){
          if( lstok ) ok ++;
          else nok ++;
        }else{
          if( lstok ) nok ++;
          else ok ++;
          lstok = 1 - lstok;
        }
        j = ( j - 1 + n ) % n;
      }
      //printf( "%d %d %d\n" , i , ok , nok );
      pos[ nn[ i ] ].push_back( { { ok , nok } , i } );
      totok += nok;
      totnok += ok;
    }
  //cout << totok << " " << totnok << endl;
  for( int i = 0 ; i <= n ; i ++ ){
    int curok = 0 , curnok = 0;
    for( auto j : pos[ i ] ){
      curok += j.first.first;
      curnok += j.first.second;
    }
    //cout << i << " " << curok << " " << curnok << endl;
    if( curok + totok - curnok == i ){
      for( auto j : pos[ i ] )
        ook[ j.second ] = true;
      build_ans();
      exit(0);
    }
  }
  puts( "inconsistent" );
}
