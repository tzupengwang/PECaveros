#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
struct Verdict{
  int state; // 0 for not submit 1 for ac -1 for not ac
  int times , last;
  void read(){
    char buf[ 9 ];
    scanf( "%s%d%d" , buf , &times , &last );
    if( buf[ 0 ] == '.' ) state = 0;
    if( buf[ 0 ] == '+' ) state = +1;
    if( buf[ 0 ] == '-' ) state = -1;
  }
};
struct Result{
  vector<Verdict> v;
  int ac , penalty , last;
  string name;
  void read( int k , const string& ss ){
    v.resize( k );
    for( int i = 0 ; i < k ; i ++ )
      v[ i ].read();
    ac = penalty = last = 0;
    for( int i = 0 ; i < k ; i ++ ){
      if( v[ i ].state != 1 ) continue;
      ac ++;
      penalty += v[ i ].last + (v[ i ].times - 1) * 20;
      last = max( last , v[ i ].last );
    }
    name = ss;
  }
  bool operator<( const Result& he ) const{
    if( ac != he.ac ) return ac > he.ac;
    if( penalty != he.penalty ) return penalty < he.penalty;
    if( last != he.last ) return last < he.last;
    return name < he.name;
  }
};
#define N 1021
int n , m , k , mid;
map<string,int> M;
inline int id( const string& name ){
  auto it = M.find( name );
  if( it != M.end() ) return it->second;
  return M[ name ] = mid ++;
}
Result f[ N ] , o[ N ];
int later[ N ];
bool ok = true , gt[ N ];

int main(){
  scanf( "%d%d%d" , &n , &m , &k );
  for( int i = 0 ; i < m ; i ++ ){
    string name; cin >> name;
    f[ id( name ) ].read( n , name );
  }
  for( int i = 0 ; i < k ; i ++ ){
    string name; cin >> name;
    int cid = id( name );
    later[ i ] = cid;
    o[ cid ].read( n , name );
    gt[ cid ] = true;
  }

  for( int i = 1 ; i < k ; i ++ )
    if( o[ later[ i ] ] < o[ later[ i - 1 ] ] )
      ok = false;
  
  for( int i = 0 ; i < m ; i ++ ){
    if( gt[ i ] ) continue;
    if( f[ i ] < o[ later[ 0 ] ] ) continue;
    if( o[ later[ k - 1 ] ] < f[ i ] ) continue;
    for( int j = 0 ; j < n ; j ++ )
      if( f[ i ].v[ j ].state != 1 ){
        f[ i ].ac ++;
        f[ i ].penalty += f[ i ].v[ j ].times * 20 + 240;
        f[ i ].last = 240;
      }
    if( f[ i ] < o[ later[ 0 ] ] ) continue;
    ok = false;
  }

  puts( ok ? "Leaked" : "Fake" );
}
