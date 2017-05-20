#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
char c[12][99][99]={{"....x","....x","....x","....x","....x","....x","....x",},{"xxxxx","....x","....x","xxxxx","x....","x....","xxxxx",},{"xxxxx","....x","....x","xxxxx","....x","....x","xxxxx",},{"x...x","x...x","x...x","xxxxx","....x","....x","....x",},{"xxxxx","x....","x....","xxxxx","....x","....x","xxxxx",},{"xxxxx","x....","x....","xxxxx","x...x","x...x","xxxxx",},{"xxxxx","....x","....x","....x","....x","....x","....x",},{"xxxxx","x...x","x...x","xxxxx","x...x","x...x","xxxxx",},{"xxxxx","x...x","x...x","xxxxx","....x","....x","xxxxx",},{"xxxxx","x...x","x...x","x...x","x...x","x...x","xxxxx",},
  {".....",
"..x..",
"..x..",
"xxxxx",
"..x..",
"..x..",
"....."}
};
char in[ 10 ][ 1021 ];
LL vl1 , vl2 , mst;
char ans[ 10 ][ 1021 ];
void write( int pos , int v ){
  for( int i = 0 ; i < 7 ; i ++ )
    for( int j = 0 ; j < 5 ; j ++ )
      ans[ i ][ pos + j ] = c[ v ][ i ][ j ];
  mst = max( mst , (LL)pos + 4 );
}
void print(){
  for( int i = 0 ; i < 7 ; i ++ , puts( "" ) )
    for( int j = 0 ; j <= mst ; j ++ )
      putchar( ans[ i ][ j ] );
}
LL cal( int l , int r ){
  LL ret = 0;
  for( int st = l ; st < r ; st += 6 ){
    int who = -1;
    for( int vv = 0 ; vv < 10 ; vv ++ ){
      bool eq = true;
      for( int i = 0 ; i < 7 and eq ; i ++ )
        for( int j = 0 ; j < 5 and eq ; j ++ )
          if( c[ vv ][ i ][ j ] != in[ i ][ st + j ] )
            eq = false;
      if( eq ){
        who = vv;
        break;
      }
    }  
    who = ( who + 1 ) % 10;
    ret = ret * 10 + who;
  }
  return ret;
}
int main(){
  while( scanf( "%s" , in[ 0 ] ) == 1 ){
    mst = 0;
    for( int i = 1 ; i < 7 ; i ++ )
      scanf( "%s" , in[ i ] );
    for( int i = 0 ; i < 7 ; i ++ )
      for( int j = 0 ; j < 1021 ; j ++ )
        ans[ i ][ j ] = '.';
    int plus = -1;
    int len = strlen( in[ 0 ] );
    for( int i = 0 ; i < len ; i += 6 ){
      bool equal = true;
      for( int j = 0 ; j < 7 and equal ; j ++ )
        for( int k = 0 ; k < 5 and equal ; k ++ )
          if( c[ 10 ][ j ][ k ] != in[ j ][ i + k ] )
            equal = false;
      if( equal ){
        plus = i;
        break;
      }
    }
    vl1 = cal( 0 , plus - 1 );
    vl2 = cal( plus + 6 , len );
    vl1 += vl2;
    if( vl1 == 0 ){
      write( 0 , 9 );
      print();
      continue;
    }
    vector<LL> res;
    while( vl1 ){
      res.push_back( vl1 % 10 );
      vl1 /= 10;
    }
    reverse( res.begin() , res.end() );
    int st = 0;
    for( LL dd : res ){
      write( st , dd == 0 ? 9 : dd - 1 );
      st += 6;
    }
    print();
  }
}
