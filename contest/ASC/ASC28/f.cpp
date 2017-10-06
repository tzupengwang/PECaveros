#include <bits/stdc++.h>
using namespace std;
struct Nd{
  int vl;
  Nd *tl , *tr;
  Nd(){
    vl = 0;
    tl = tr = NULL;
  }
};
#define mid ((l+r)>>1)
int Vl( Nd* now ){
  return now ? now->vl : 0;
}
void assign( Nd* now , int l , int r , int p , int v ){
  if( l == r ){
    now->vl = v;
    return;
  }
  if( p <= mid ){
    if( !now->tl ) now->tl = new Nd();
    assign( now->tl , l , mid , p , v );
  }else{
    if( !now->tr ) now->tr = new Nd();
    assign( now->tr , mid + 1 , r , p , v );
  }
  now->vl = Vl( now->tl ) + Vl( now->tr );
}
int query( Nd* now , int l , int r , int ql , int qr ){
  if( !now or r < ql or l > qr or ql > qr ) return 0;
  if( ql <= l and r <= qr ) return Vl( now );
  return query( now->tl , l , mid , ql , qr ) +
         query( now->tr , mid + 1 , r , ql , qr );
}
#define N 101010
Nd *root, *root2;
int n , a[ N ] , b[ N ];
map<int,int> pre;
const int inf = 1000000000;
int main(){
#ifdef ONLINE_JUDGE
  freopen( "mtf.in" , "r" , stdin );
  freopen( "mtf.out" , "w" , stdout );
#endif
  root = new Nd();
  root2 = new Nd();
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
  for( int i = 1 ; i <= n ; i ++ ){
    auto it = pre.find( a[ i ] );
    if( it == pre.end() ){
      int ord = a[ i ] + query( root2 , 1 , inf , a[ i ] + 1 , inf );
      b[ i ] = ord;
      assign( root2 , 1 , inf , a[ i ] , 1 );
      assign( root , 1 , n , i , 1 );
      pre[ a[ i ] ] = i;
    }else{
      b[ i ] = query( root , 1 , n , pre[ a[ i ] ] , i );
      assign( root , 1 , n , pre[ a[ i ] ] , 0 );
      assign( root , 1 , n , i , 1 );
      pre[ a[ i ] ] = i;
    }
  }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , b[ i ] , " \n"[ i == n ] );
}
