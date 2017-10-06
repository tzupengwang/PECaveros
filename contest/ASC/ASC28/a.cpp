#include <bits/stdc++.h>
using namespace std;
#define N 201010
int n , k , ord[ N ] , lo[ N ] , ro[ N ];
int left_ord( int ki ){ return lo[ ki ]; }
int right_ord( int ki ){ return ro[ ki ]; }
int a[ N ] , bstl;
int lnxtl[ N ] , rnxtl[ N ];
int lnxtr[ N ] , rnxtr[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  n += n;
  bstl = 0;
  for( int i = 1 ; i <= k + k ; i ++ ){
    scanf( "%d" , &ord[ i ] );
    if( ord[ i ] > 0 ) lo[ ord[ i ] ] = i;
    else ro[ -ord[ i ] ] = i;
    if( ord[ i ] > 0 and bstl == 0 )
      bstl = ord[ i ];
  }
  int nxtl = -1 , nxtr = -1;
  for( int i = k + k ; i >= 1 ; i -- ){
    if( ord[ i ] > 0 ){
      lnxtl[ ord[ i ] ] = nxtl;
      lnxtr[ ord[ i ] ] = nxtr;
      nxtl = ord[ i ];
    }else{
      rnxtl[ -ord[ i ] ] = nxtl;
      rnxtr[ -ord[ i ] ] = nxtr;
      nxtr = -ord[ i ];
    }
  }
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
}
int ssz[ N ] , swho[ N ];
vector<int> stk;
void go( int pre , int add ){
  if( add ) a[ ++ pre ] = add;
  stk.clear();
  for( int i = 1 ; i <= pre ; i ++ ){
    if( a[ i ] > 0 )
      stk.push_back( a[ i ] );
    else
      stk.pop_back();
  }
  for( int i = pre + 1 ; i <= n ; i ++ ){
    int lok = 0 , rok = 0;
    if( i + (int)stk.size() + 1 <= n )
      lok = bstl;
    if( (int)stk.size() )
      rok = (int)stk.back();
    if( rok == 0 or
        ( lok != 0 and
          left_ord( lok ) < right_ord( rok ) ) ){
      stk.push_back( lok );
      a[ i ] = lok;
    }else{
      a[ i ] = -stk.back();
      stk.pop_back();
    }
  }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , a[ i ] , " \n"[ i == n ] );
}
void solve(){
  stk.clear();
  for( int i = 1 ; i <= n ; i ++ ){
    if( a[ i ] > 0 )
      stk.push_back( a[ i ] );
    else
      stk.pop_back();
    ssz[ i ] = (int)stk.size();
    if( stk.size() )
      swho[ i ] = stk.back();
    else
      swho[ i ] = 0;
  }
  for( int i = n ; i >= 1 ; i -- ){
    int lok = 0 , rok = 0;
    {
      int nxtl = -1;
      if( a[ i ] > 0 )
        nxtl = lnxtl[ a[ i ] ];
      else
        nxtl = rnxtl[ -a[ i ] ];
      if( nxtl != -1 and i + ssz[ i - 1 ] + 1 <= n )
        lok = nxtl;
    }
    if( a[ i ] > 0 and swho[ i - 1 ] and
        left_ord( a[ i ] ) < right_ord( swho[ i - 1 ] ) ){
      if( i + ssz[ i - 1 ] - 1 <= n )
        rok = -swho[ i - 1 ];
    }
    if( lok != 0 and
        ( rok == 0 or
          left_ord( lok ) < right_ord( -rok ) ) ){
      go( i - 1 , lok );
      return;
    }else if( rok ){
      go( i - 1 , rok );
      return;
    }
  }
  go( 0 , 0 );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "brackets.in" , "r" , stdin );
  freopen( "brackets.out" , "w" , stdout );
#endif
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
