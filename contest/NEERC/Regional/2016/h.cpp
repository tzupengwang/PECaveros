#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1024
char buf[ N ];
#define BS 101010
int ok[ BS + BS ];
int to_int( const string& ss ){
  int sgn = 1 , tmp = 0 , s = 0;
  if( ss[ 0 ] == '-' ) sgn = -1 , s = 1;
  for( int i = s ; i < (int)ss.length() ; i ++ )
    tmp = tmp * 10 + ss[ i ] - '0';
  int ret = tmp * sgn;
  ret = max( ret , -BS );
  ret = min( ret , BS - 1 );
  return ret;
}
void add_constraint( vector<string> vv ){
  bool ge = false , le = false;
  int gev = 0 , lev = 0;
  int cur = 2;
  while( cur < (int)vv.size() ){
    int vl = to_int( vv[ cur ] );
    if( vv[ cur - 1 ] == ">=" ){
      if( !ge or vl > gev ){
        ge = true;
        gev = vl;
      }
    }else{
      if( !le or vl < lev ){
        le = true;
        lev = vl;
      }
    }
    cur += 4;
  }
  if( ge and le and lev < gev ) return;
  if( ge and le ){
    ok[ BS + gev ] ++;
    ok[ BS + lev + 1 ] --;
  }
  else if( ge )
    ok[ BS + gev ] ++;
  else if( le ){
    ok[ 0 ] ++;
    ok[ BS + lev + 1 ] --;
  }
}
int linf = -32768;
int rinf =  32767;
int main(){
  freopen( "hard.in" , "r" , stdin );
  freopen( "hard.out" , "w" , stdout );
  while( fgets( buf , N , stdin ) ){
    int len = strlen( buf );
    vector<string> vv;
    string tmp = "";
    for( int i = 0 ; i < len ; i ++ )
      if( i + 1 == len or buf[ i ] == ' ' ){
        if( tmp.length() )
          vv.push_back( tmp );
        tmp = "";
      }else
        tmp += buf[ i ];
    add_constraint( vv );
  }
  for( int i = 1 ; i < BS + BS ; i ++ )
    ok[ i ] += ok[ i - 1 ];
  int cnt = 0;
  for( int i = linf + BS ; i <= rinf + BS ; i ++ )
    if( ok[ i ] )
      cnt ++;
  if( !cnt ){
    puts( "false" );
    return 0;
  }
  if( cnt == rinf - linf + 1 ){
    puts( "true" );
    return 0;
  }
  vector< pair<int,int> > vv;
  for( int i = linf + BS ; i <= rinf + BS ; )
    if( !ok[ i ] ) i ++;
    else{
      int s = i;
      while( i <= rinf + BS and ok[ i ] ) i ++;
      vv.push_back( { s - BS , i - BS - 1 } );
    }
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    pair<int,int> ii = vv[ i ];
    bool first = false;
    if( ii.first > linf ){
      printf( "x >= %d" , ii.first );
      first = true;
    }
    if( ii.second < rinf ){
      if( first ) printf( " && " );
      printf( "x <= %d" , ii.second );
    }
    if( i + 1 < vv.size() ) printf( " ||" );
    puts( "" );
  }
}
