#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int inf = 1e6;
struct Nd{
  int sum;
  Nd *tl , *tr;
  Nd(){
    tl = tr = NULL;
    sum = 0;
  }
};
inline Nd *copy( Nd* now ){
  Nd * ret = new Nd();
  if( now ){
    ret->sum = now->sum;
    ret->tl = now->tl;
    ret->tr = now->tr;
  }
  return ret;
}
int Sum( Nd* now ){
  return now ? now->sum : 0;
}
#define mid ((l+r)>>1)
void modify( Nd* now , int l , int r , int p , int tv ){
  if( l == r ){
    now->sum = tv;
    return;
  }
  if( p <= mid ){
    now->tl = copy( now->tl );
    modify( now->tl , l , mid , p , tv );
  }else{
    now->tr = copy( now->tr );
    modify( now->tr , mid + 1 , r , p , tv );
  }
  now->sum = Sum( now->tl ) + Sum( now->tr );
}
int query_sum( Nd* now , int l , int r , int ql , int qr ){
  if( !now or r < ql or l > qr ) return 0;
  if( ql <= l and r <= qr ) return now->sum;
  return query_sum( now->tl , l , mid , ql , qr ) +
         query_sum( now->tr , mid + 1 , r , ql , qr );
}
int til( Nd* now , int ql , int S ){
  int bl = ql , br = n , ba = inf;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( query_sum( now , 1 , n , ql , bmid ) >= S )
      ba = bmid , br = bmid - 1;
    else
      bl = bmid + 1;
  }
  return ba;
}
int main(){

}
