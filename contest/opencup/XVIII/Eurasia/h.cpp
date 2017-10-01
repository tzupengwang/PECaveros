#include <bits/stdc++.h>
using namespace std;
const int inf = 1e6;
vector< pair<int,int> > ans;
int ask( int xi , int yi ){
  printf( "? %d %d\n" , xi , yi );
  fflush( stdout );
  int cnt; scanf( "%d" , &cnt );
  for( auto i : ans )
    if( i.first <= xi and
        i.second <= yi )
      cnt --;
  return cnt;
}
int n;
void answer(){
  assert( (int)ans.size() == n );
  printf( "!" );
  for( auto i : ans )
    printf( " %d %d" , i.first , i.second );
  puts( "" );
  fflush( stdout );
}
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    int ax , ay;
    {
      int bl = 0 , br = inf + inf , ba = bl;
      while( bl <= br ){
        int bmid = (bl + br) >> 1;
        if( ask( bmid - inf , inf ) )
          ba = bmid , br = bmid - 1;
        else
          bl = bmid + 1;
      }
      ax = ba - inf;
    }
    {
      int bl = 0 , br = inf + inf , ba = bl;
      while( bl <= br ){
        int bmid = (bl + br) >> 1;
        if( ask( ax , bmid - inf ) )
          ba = bmid , br = bmid - 1;
        else
          bl = bmid + 1;
      }
      ay = ba - inf;
    }
    ans.push_back( { ax , ay } );
  }
  answer();
}
