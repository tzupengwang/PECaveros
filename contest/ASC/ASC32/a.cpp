#include <bits/stdc++.h>
using namespace std;
#define N 55
int d , r;
int main(){
#ifdef ONLINE_JUDGE
  freopen( "graph.in" , "r" , stdin );
  freopen( "graph.out" , "w" , stdout );
#endif
  cin >> d >> r;
  if( r == 1 ){
    if( d == 1 ){
      puts( "YES" );
      puts( "2 1" );
      puts( "1 2" );
      exit(0);
    }
    if( d == 2 ){
      puts( "YES" );
      puts( "3 2" );
      puts( "1 2" );
      puts( "3 2" );
      exit(0);
    }
    assert( false );
  }
  int nn = r + r;
  vector< pair<int,int> > e;
  for( int i = 1 ; i <= r + r ; i ++ )
    e.push_back( { i , i == r + r ? 1 : i + 1 } );
  int res = d - r;
  while( res -- ){
    e.push_back( { nn , 1 + nn } );
    nn ++;
  }
  puts( "YES" );
  cout << nn << " " << e.size() << endl;
  for( auto i : e )
    cout << i.first << " " << i.second << endl;
}
