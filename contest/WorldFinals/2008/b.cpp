#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
const LL inf = (1LL << 40);
inline LL add( LL a , LL b , LL mod ){
  if( mod == inf ) return a + b;
  a += b;
  return a >= mod ? a - mod : a;
}
inline LL mul( LL a , LL b , LL mod ){
  if( mod == inf ) return a * b;
  return a * b % mod;
}
inline LL mpow( LL a , LL b , LL mod ){
  LL ret = 1;
  while( b ){
    if(b & 1) ret = mul( ret , a , mod );
    a = mul( a , a , mod );
    b >>= 1;
  }
  return ret;
}
string buf;
typedef vector< pair<LL,LL> > poly;
typedef pair<poly,LL> func;
vector<func> v;
LL parse_int( const string& ss , int lc , int rc , LL mod ){
  if( lc >= rc ) return 1;
  LL sgn = 1;
  if( ss[ lc ] == '+' ) lc ++;
  if( ss[ lc ] == '-' ) sgn = mod - 1 , lc ++;
  if( lc >= rc ) return sgn;
  LL ret = 0;
  for( int i = lc ; i < rc ; i ++ )
    ret = add( mul( ret , 10 , mod ) , ss[ i ] - '0' , mod );
  return mul( ret , sgn , mod );
}
pair<LL,LL> parse( const string& ss , int lc , int rc , LL mod ){
  int nat = -1;
  for( int i = lc ; i < rc ; i ++ )
    if( ss[ i ] == 'n' ){
      nat = i;
      break;
    }
  if( nat == -1 )
    return { 0 , parse_int( ss , lc , rc , mod ) };
  return { parse_int( ss , nat + 2 , rc , inf ) ,
           parse_int( ss , lc , nat , mod ) };
}
void read( poly& pp , string ss , LL mod ){
  pp.clear();
  if( ss[ 0 ] != '-' ) ss = '+' + ss;
  size_t st = 0;
  while( st < ss.length() ){
    size_t lst = st;
    st ++;
    while( st < ss.length() and
           ss[ st ] != '+' and
           ss[ st ] != '-' ) st ++;
    pp.push_back( parse( ss , lst , st , mod ) );
  }
}
void read(){
  size_t ptr = 0;
  while( buf[ ptr ] != ')' ) ptr ++;
  func f;
  f.second = 0;
  for( size_t i = ptr + 2 ; i < buf.length() ; i ++ )
    f.second = (f.second * 10) + (buf[ i ] - '0');
  read( f.first , buf.substr( 1 , ptr - 1 ) , f.second );
  v.push_back( f );
}

LL nxt;
bool eval( const poly& pp , LL mod ){
  LL ret = 0;
  for( auto i : pp )
    ret = add( ret , mul( i.second , mpow( nxt , i.first , mod ) , mod ) , mod );
  //cout << mod << endl;
  //for( auto i : pp )
    //cout << i.first << " " << i.second << endl;
  //cout << nxt << " " << mod << " " << ret << endl;
  return ret > 0;
}

vector<bool> good;
vector<int> wt;
bool ggwp( int cid ){
  if( eval( v[ cid ].first , v[ cid ].second ) ){
    good[ cid ] = false;
    return true;
  }
  return false;
}
void gogo(){
  for( size_t i = 0 ; i < wt.size() ; i ++ ){
    int nid = wt[ i ];
    if( nxt >= v[ nid ].second or ggwp( nid ) ){
      swap( wt[ i ] , wt.back() );
      wt.pop_back();
      i --;
      continue;
    }
  }
  ++ nxt;
}
int main(){
  clock_t s = clock();
  while( cin >> buf ){
    if( buf[ 0 ] == '.' ) break;
    good.push_back( true );
    wt.push_back( v.size() );
    read();
  }

  //for( auto i : v ){
    //for( auto j : i.first )
      //printf( "%llu %llu   " , j.first , j.second );
    //printf( "%llu\n" , i.second );
  //}

  while( (clock() - s) < 4.8 * CLOCKS_PER_SEC )
    gogo();
  for( size_t i = 0 ; i < good.size() ; i ++ )
    if( good[ i ] )
      printf( "Case %d: Always an integer\n" , (int)(i + 1) );
    else
      printf( "Case %d: Not always an integer\n" , (int)(i + 1) );
}
