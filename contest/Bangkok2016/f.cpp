#include <bits/stdc++.h>
using namespace std;
#define N 55
struct Nd{
  map<char,Nd*> nxt;
  int vl;
  Nd(){
    vl = 0;
    nxt.clear();
  }
};
char c[ N ];
int len;
void add( Nd* now , int cur ){
  if( cur == len ) return;
  auto it = now->nxt.find( c[ cur ] );
  if( it != now->nxt.end() ){
    now->vl ^= it->second->vl + 1;
    add( it->second , cur + 1 );
    now->vl ^= it->second->vl + 1;
  }else{
    Nd* tmp = new Nd();
    now->nxt[ c[ cur ] ] = tmp;
    add( tmp , cur + 1 );
    now->vl ^= tmp->vl + 1;
  }
}
Nd* root;
int n , q;
void init(){
  root = new Nd();
  scanf( "%d" , &n ); while( n -- ){
    scanf( "%s" , c );
    len = strlen( c );
    add( root , 0 );
  }
}
int cs;
void clear( Nd* now ){
  if( !now ) return;
  for( auto i : now->nxt )
    clear( i.second );
  delete now;
}
void solve(){
  printf( "Case %d:\n" , ++ cs );
  scanf( "%d" , &q ); while( q -- ){
    scanf( "%s" , c );
    len = strlen( c );
    add( root , 0 );
    puts( root->vl ? "1" : "2" );
  }
  clear( root );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
