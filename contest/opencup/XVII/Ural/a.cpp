#include <bits/stdc++.h>
using namespace std;
#define N 111
int n , m;
vector<int> v[ N ];
bool tag[ N ];
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  scanf( "%d%d" , &n , &m ); while( m -- ){
    int ai , bi;
    scanf( "%d%d" , &ai , &bi );
    v[ ai ].push_back( bi );
    v[ bi ].push_back( ai );
  }
  if( n < 4 ){
    puts( "No" );
    exit(0);
  }
  vector<int> deg;
  for( int i = 1 ; i <= n ; i ++ )
    deg.push_back( v[ i ].size() );
  sort( deg.begin() , deg.end() );
  if( deg[ 0 ] != 1 or deg[ 1 ] != 2 or
      deg[ n - 1 ] != 3 or deg[ n - 2 ] != 2){
    puts( "No" );
    exit(0);
  }
  vector<int> root;
  for( int i = 1 ; i <= n ; i ++ )
    if( (int)v[ i ].size() == 1 )
      root.push_back( i );
  if( root.size() != 1u ){
    puts( "No" );
    exit(0);
  }
  int now = root[ 0 ] , fr = -1 , got = 0;
  bool loop = false;
  while( !tag[ now ] ){
    tag[ now ] = true;
    got ++;
    vector<int> nxt;
    for( int i : v[ now ] ){
      if( i == fr ) continue;
      nxt.push_back( i );
    }
    if( (int)nxt.size() == 2u ){
      if( loop ){
        puts( "No" );
        exit(0);
      }
      loop = true;
      fr = now;
      now = nxt[ 0 ];
      continue;
    }
    if( (int)nxt.size() == 1u ){
      fr = now;
      now = nxt[ 0 ];
      continue;
    }
    puts( "No" );
    exit(0);
  }
  puts( got == n ? "Yes" : "No" );
}
