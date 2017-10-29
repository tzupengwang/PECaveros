#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
//#define int long long
#define LEN (5 * (1 << 20))
#define N 202020
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
struct Upper{
  int vl[ N ];
  void build(){
    for( int i = 0 ; i < N ; i ++ )
      vl[ i ] = 1000000010;
  }
  vector< pair<int*,int> > vv;
  vector<size_t> stk;
  void assign( int* pt , int v ){
    vv.push_back( { pt , *pt } );
    *pt = v;
  }
  void save(){
    stk.push_back( vv.size() );
  }
  void undo(){
    while( vv.size() > stk.back() ){
      *vv.back().first = vv.back().second;
      vv.pop_back();
    }
    stk.pop_back();
  }
} upp;
struct SegT{
  LL lv[ N << 1 ] , rv[ N << 1 ] , ct[ N << 1 ];
  LL ls[ N << 1 ] , rs[ N << 1 ] , mx[ N << 1 ];
  void build( int no , int l , int r ){
    lv[ no ] = rv[ no ] = ls[ no ] = rs[ no ]
      = mx[ no ] = ct[ no ] = 0;
    if( l == r ) return;
    build( L( no ) , l , mid );
    build( R( no ) , mid + 1 , r );
  }
  vector< pair<LL*,LL> > vv;
  vector<size_t> stk;
  int query( int no , int l , int r , int p ){
    if( l == r ) return lv[ no ];
    if( p <= mid ) return query( L( no ) , l , mid , p );
    return query( R( no ) , mid + 1 , r , p );
  }
  void modify( int no , int l , int r , int p , int vl ){
    if( l == r ){
      assign( &lv[ no ] , vl );
      assign( &rv[ no ] , vl );
      assign( &ls[ no ] , vl );
      assign( &rs[ no ] , vl );
      assign( &mx[ no ] , vl );
      assign( &ct[ no ] , vl ? 1 : 0 );
      return;
    }
    if( p <= mid )
      modify( L( no ) , l , mid , p , vl );
    else
      modify( R( no ) , mid + 1 , r , p , vl );
    assign( &lv[ no ] , lv[ L( no ) ] );
    assign( &rv[ no ] , rv[ R( no ) ] );
    assign( &ct[ no ] , ct[ L( no ) ] + ct[ R( no ) ] );
    if( ct[ L( no ) ] == mid - l + 1 )
      assign( &ls[ no ] , ls[ L( no ) ] + ls[ R( no ) ] );
    else
      assign( &ls[ no ] , ls[ L( no ) ] );
    if( ct[ R( no ) ] == r - mid )
      assign( &rs[ no ] , rs[ L( no ) ] + rs[ R( no ) ] );
    else
      assign( &rs[ no ] , rs[ R( no ) ] );
    LL bst = max( mx[ L( no ) ] , mx[ R( no ) ] );
    if( rv[ L( no ) ] and lv[ R( no ) ] )
      bst = max( bst , rs[ L( no ) ] + ls[ R( no ) ] );
    assign( &mx[ no ] , bst );
  }
  void assign( LL* pt , LL v ){
    vv.push_back( { pt , *pt } );
    *pt = v;
  }
  void save(){
    stk.push_back( vv.size() );
  }
  void undo(){
    while( vv.size() > stk.back() ){
      *vv.back().first = vv.back().second;
      vv.pop_back();
    }
    stk.pop_back();
  }
} segT;
void Save(){
  segT.save();
  upp.save();
}
void Undo(){
  segT.undo();
  upp.undo();
}
set<LL> got;
char g[ LEN ];
LL n , k;
int len , pr[ LEN ] , fst , ptr;
void parse_statement( int til );
pair<int,int> parse_cond( int l , int r ){
   //fprintf( stderr , "Starting parsing cond at (%d,%d)\n" , l , r );
  int tptr = l;
  while( g[ tptr ] != '[' ) tptr ++;
  tptr ++;
  int vl = 0;
  while( g[ tptr ] != ']' ){
    vl = vl * 10 + g[ tptr ] - '0';
    tptr ++;
  }
  tptr += 3;
  int vl2 = 0;
  while( tptr <= r ){
    vl2 = vl2 * 10 + g[ tptr ] - '0';
    tptr ++;
  }
  //fprintf( stderr , "a[%d] >= %d\n" , vl , vl2 );
  return { vl , vl2 };
}

bool ok;

void check( int x ){
  int ub = upp.vl[ x ];
  int lb = segT.query( 1 , 1 , n , x );
  if( lb > ub )
    ok = false;
  if( segT.mx[ 1 ] > k )
    ok = false;
}

void parse_if(){
   //fprintf( stderr , "Starting parsing branch statement at %d\n" , ptr );
  ptr += 2;
  int x , y;
  tie( x , y ) = parse_cond( ptr + 1 , pr[ ptr ] - 1 );
  ptr = pr[ ptr ] + 1;

  Save();
  bool ook = ok;

  int vl = segT.query( 1 , 1 , n , x );
  if( vl < y )
    segT.modify( 1 , 1 , n , x , y );

  check( x );
  parse_statement( len - 1 );

  ok = ook;
  Undo();

  if( ptr < len and g[ ptr ] == 'e' ){
    ptr += 4; y --;

    Save();
    ook = ok;

    vl = upp.vl[ x ];
    if( vl > y )
      upp.assign( &upp.vl[ x ] , y );

    check( x );
    parse_statement( len - 1 );
  
    ok = ook;
    Undo();
  }
}
void parse_body( int til );
void parse_statement( int til ){
  while( ptr < til and
         g[ ptr ] != '{' and
         g[ ptr ] != 'a' and
         g[ ptr ] != 'i')
    ptr ++;
  if( ptr >= til ) return;
  //fprintf( stderr , "Starting parsing statement at %d(til = %d)\n" , ptr , til );
  if( g[ ptr ] == '{' ){
    int nxt = pr[ ptr ] + 1;
    ptr ++;
    parse_body( nxt - 1 );
    ptr = nxt;
    return;
  }
  if( g[ ptr ] == 'a' ){
    ptr += 4;
    int vl = 0;
    while( g[ ptr ] != ')' ){
      vl = vl * 10 + g[ ptr ] - '0';
      ptr ++;
    }
    ptr ++;
    if( ok )
      got.insert( vl );
    return;
  }
  if( g[ ptr ] == 'i' )
    parse_if();
}
void parse_body( int til ){
  //fprintf( stderr , "Starting parsing body from %d(til = %d)\n" , ptr , til );
  while( ptr < til )
    parse_statement( til );
}
void solve(){
  segT.build( 1 , 1 , n );
  upp.build();
  ptr = fst + 1;
  parse_body( len - 1 );
}
int32_t main(){
  ok = true;

  while( scanf( "%s" , g + len ) == 1 )
    len += strlen( g + len );
  int tlen = 0;
  for( int i = 0 ; i < len ; i ++ )
    if( g[ i ] != ';' )
      g[ tlen ++ ] = g[ i ];
  len = tlen;
  g[ len ] = 0;

  //for( int i = 0 ; i < len ; i ++ )
     //fprintf( stderr , "%d" , i % 10 == 0 ? i / 10 : 0 );
   //fprintf( stderr , "\n" );
  //for( int i = 0 ; i < len ; i ++ )
     //fprintf( stderr , "%d" , i % 10 );
   //fprintf( stderr , "\n" );
   //fprintf( stderr , "%s\n" , g );

  vector<int> stk;
  for( int i = 0 ; i < len ; i ++ )
    if( g[ i ] == '{' or g[ i ] == '(' ){
      if( !fst and g[ i ] == '{' ) fst = i;
      stk.push_back( i );
    }else if( g[ i ] == '}' or g[ i ] == ')' ){
      pr[ stk.back() ] = i;
      stk.pop_back();
    }
  {
    vector<LL> tv;
    LL vl = 0; bool gt = false;
    int sgn = 1;
    for( int i = 0 ; i <= fst ; i ++ )
      if( g[ i ] == '-' ){
        sgn = -1;
      }else if( '0' <= g[ i ] and g[ i ] <= '9' ){
        vl = vl * 10 + g[ i ] - '0';
        vl = min( vl , 1000000000000000LL );
        gt = true;
      }else{
        if( gt )
          tv.push_back( vl * sgn );
        vl = 0;
        sgn = 1;
        gt = false;
      }
    n = tv[ 0 ];
    k = tv[ 1 ];
  }
  //fprintf( stderr , "n = %lld, k = %lld\n" , n , k );
  if( k >= 0 )
    solve();
  cout << got.size() << endl;
}
