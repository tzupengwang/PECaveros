#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
char c[ N ];
vector<int> pos[ 26 ];
int ans;
int main(){
  scanf( "%s" , c );
  for( int i = 0 ; c[ i ] ; ){
    int cc = c[ i ] - 'a';
    if( pos[ cc ].empty() ){
      ans ++;
      pos[ cc ].push_back( i );
      i ++;
    }else{
      int si = i;
      int pre = -1;
      while( c[ i ] ){
        int bl = 0 , br = (int)pos[ c[ i ] - 'a' ].size() - 1 , ba = -1;
        while( bl <= br ){
          int bmid = (bl + br) >> 1;
          if( pos[ c[ i ] - 'a' ][ bmid ] > pre )
            ba = bmid , br = bmid - 1;
          else
            bl = bmid + 1;
        }
        if( ba == -1 ) break;
        pre = pos[ c[ i ] - 'a' ][ ba ];
        i ++;
      }
      for( int j = si ; j < i ; j ++ )
        pos[ c[ j ] - 'a' ].push_back( j );
      ans ++;
    }
  }
  printf( "%d\n" , ans );
}
