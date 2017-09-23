#include <bits/stdc++.h>
using namespace std;
#define N 101010
struct Nd{
  int mx , who;
  Nd *tl , *tr;
  Nd(){
    mx = who = 0;
    tl = tr = NULL;
  }
};
#define mid ((l+r)>>1)
int MX( Nd* now ){
  return now ? now->mx : 0;
}
int Who( Nd* now ){
  return now ? now->who : 0;
}
void modify( Nd* now , int l , int r , int p , int x , int w ){
  if( l == r ){
    if( x <= now->mx ) return;
    now->mx = x;
    now->who = w;
    return;
  }
  if( p <= mid ){
    if( !now->tl ) now->tl = new Nd();
    modify( now->tl , l , mid , p , x , w );
  }else{
    if( !now->tr ) now->tr = new Nd();
    modify( now->tr , mid + 1 , r , p , x , w );
  }
  if( MX( now->tl ) > MX( now->tr ) ){
    now->mx = MX( now->tl );
    now->who = Who( now->tl );
  }else{
    now->mx = MX( now->tr );
    now->who = Who( now->tr );
  }
}
pair<int,int> query( Nd* now , int l , int r , int ql , int qr ){
  if( !now or r < ql or l > qr or ql > qr ) return { 0 , 0 };
  if( ql <= l and r <= qr ) return { MX( now ) , Who( now ) };
  pair<int,int> tl = query( now->tl , l , mid , ql , qr );
  pair<int,int> tr = query( now->tr , mid + 1 , r , ql , qr );
  if( tl < tr ) return tr;
  return tl;
}
int n , k , a[ N ] , dp[ N ] , pre[ N ];
const int inf = 1000000000;
int main(){
#ifdef ONLINE_JUDGE
  freopen( "financial.in" , "r" , stdin );
  freopen( "financial.out" , "w" , stdout );
#endif
  cin >> n >> k;
  for( int i = 1 ; i <= n ; i ++ )
    cin >> a[ i ];
  Nd* root = new Nd();
  int bst = 0 , bi = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    pair<int,int> ret1 = query( root , 1 , inf , 1 , a[ i ] - k );
    pair<int,int> ret2 = query( root , 1 , inf , a[ i ] + k , inf );
    if( ret2 > ret1 ) ret1 = ret2;
    pre[ i ] = ret1.second;
    dp[ i ] = dp[ pre[ i ] ] + 1;
    if( dp[ i ] > bst ){
      bst = dp[ i ];
      bi = i;
    }
    modify( root , 1 , inf , a[ i ] , dp[ i ] , i );
  }
  vector<int> va;
  while( bi ){
    va.push_back( a[ bi ] );
    bi = pre[ bi ];
  }
  reverse( va.begin() , va.end() );
  printf( "%d\n" , (int)va.size() );
  for( size_t i = 0 ; i < va.size() ; i ++ )
    printf( "%d%c" , va[ i ] , " \n"[ i + 1 == va.size() ] );
}
