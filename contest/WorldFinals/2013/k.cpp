#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 28
char c[ 3 ][ N ];
int msk[ 3 ][ N ] , nxt[ 3 ][ 2 ];
int at[ 3 ][ N ];
vector<string> _name = {"Pre", "In", "Post"};
vector<int> ord;
typedef tuple<string,string,string> dat;
#define Pre(X) get<0>(X)
#define In(X) get<1>(X)
#define Post(X) get<2>(X)
int bs[] = {N, N, N, N, 3, 3, 3};
int enc( int len , int s0 , int s1 , int s2 , int k0 , int k1 , int k2 ){
  vector<int> _v = { len , s0 , s1 , s2 , k0 , k1 , k2 };
  int ret = 0;
  for( int i = 0 ; i < 7 ; i ++ )
    ret = (ret * bs[ i ] + _v[ i ]);
  return ret;
}
bool check( int ts , int tlen , int tk , int tat , int& llen ){
  if( tat < ts or tat >= ts + tlen ) return false;
  if( tk == 0 and tat != ts ) return false;
  if( tk == 2 and tat != ts + tlen - 1 ) return false;
  if( tk == 1 ){
    int tllen = tat - ts;
    if( llen != -1 and llen != tllen )
      return false;
    llen = tllen;
  }
  return true;
}
void upd( int ts , int tk , int llen , 
          int& sl , int& kl , int& sr , int& kr ){
  kl = nxt[ tk ][ 0 ];
  kr = nxt[ tk ][ 1 ];
  if( tk == 0 ){
    sl = ts + 1;
    sr = ts + llen + 1;
    return;
  }
  if( tk == 1 ){
    sl = ts;
    sr = ts + llen + 1;
    return;
  }
  if( tk == 2 ){
    sl = ts;
    sr = ts + llen;
    return;
  }
  assert( false );
}
unordered_map< int , pair<dat,bool> > memo;
dat DP( int len , int s0 , int s1 , int s2 , int k0 , int k1 , int k2 , bool& nok ){
  int ee = enc( len , s0 , s1 , s2 , k0 , k1 , k2 );
  nok = true;
  if( len <= 0 ) return make_tuple( "" , "" , "" );
  {
    int vl0 = msk[ 0 ][ s0 + len - 1 ] ^ msk[ 0 ][ s0 - 1 ];
    int vl1 = msk[ 1 ][ s1 + len - 1 ] ^ msk[ 1 ][ s1 - 1 ];
    int vl2 = msk[ 2 ][ s2 + len - 1 ] ^ msk[ 2 ][ s2 - 1 ];
    if( vl0 != vl1 or vl0 != vl2 ){
      nok = false;
      return make_tuple( "" , "" , "" );
    }
  }
  {
    auto it = memo.find( ee );
    if( it != memo.end() ){
      nok = it->second.second;
      return it->second.first;
    }
  }
  if( len == 1 ){
    string cur = "";
    cur += c[ 0 ][ s0 ];
    memo[ ee ] = { make_tuple( cur , cur , cur ) , true };
    return make_tuple( cur , cur , cur );
  }
  bool found = false;
  dat ret = make_tuple("", "", "");
  for( int root = 0 ; root < 26 ; root ++ ){
    int at0 = at[ 0 ][ root ];
    int at1 = at[ 1 ][ root ];
    int at2 = at[ 2 ][ root ];
    int s , t;
    {
      int llen = -1;
      if( not check( s0 , len , k0 , at0 , llen ) ) continue;
      if( not check( s1 , len , k1 , at1 , llen ) ) continue;
      if( not check( s2 , len , k2 , at2 , llen ) ) continue;
      s = (llen == -1 ? 0       : llen );
      t = (llen == -1 ? len - 1 : llen );
    }
    for( int llen = s ; llen <= t ; llen ++ ){
      int ssl[ 3 ] , kdl[ 3 ];
      int ssr[ 3 ] , kdr[ 3 ];
      upd( s0 , k0 , llen , ssl[ 0 ] , kdl[ 0 ] , ssr[ 0 ] , kdr[ 0 ] );
      upd( s1 , k1 , llen , ssl[ 1 ] , kdl[ 1 ] , ssr[ 1 ] , kdr[ 1 ] );
      upd( s2 , k2 , llen , ssl[ 2 ] , kdl[ 2 ] , ssr[ 2 ] , kdr[ 2 ] );
      bool cok;
      dat lret = DP( llen , ssl[ 0 ] , ssl[ 1 ] , ssl[ 2 ] ,
                            kdl[ 0 ] , kdl[ 1 ] , kdl[ 2 ] , cok );
      if( not cok ) continue;
      dat rret = DP( len - llen - 1 , ssr[ 0 ] , ssr[ 1 ] , ssr[ 2 ] ,
                                      kdr[ 0 ] , kdr[ 1 ] , kdr[ 2 ] , cok );
      if( not cok ) continue;
      dat got;
      Pre( got ) = (char)(root + 'A') + Pre( lret ) + Pre( rret );
      In( got ) = In( lret ) + (char)(root + 'A') + In( rret );
      Post( got ) = Post( lret ) + Post( rret ) + (char)(root + 'A');
      if( not found or got < ret ){
        found = true;
        ret = got;
      }
    }
  }
  memo[ ee ] = { ret , found };
  nok = found;
  return ret;
}
bool got;
int n;
void go(){
  bool nok;
  memo.clear();
  dat ret = DP( n , 1 , 1 , 1 , 0 , 1 , 2 , nok );
  if( !nok ) return;
  if( got ) puts( "" );
  got = true;
  for( int i = 0 ; i < 6 ; i ++ )
    printf( "%s%c" , _name[ ord[ i ] ].c_str() , " \n"[ i == 5 ] );
  printf( "%s\n%s\n%s\n" , Pre( ret ).c_str() ,
          In( ret ).c_str() , Post( ret ).c_str() );
}
int main(){
  for( int i = 0 ; i < 3 ; i ++ ){
    scanf( "%s" , c[ i ] + 1 );
    for( int j = 1 ; c[ i ][ j ] ; j ++ ){
      at[ i ][ c[ i ][ j ] - 'A' ] = j;
      msk[ i ][ j ] = msk[ i ][ j - 1 ] | (1 << (c[ i ][ j ] - 'A'));
    }
  }
  n = strlen( c[ 0 ] + 1 );
  ord = {0, 0, 1, 1, 2, 2};
  do{
    for( int i = 0 ; i < 6 ; i ++ )
      nxt[ i >> 1 ][ i & 1 ] = ord[ i ];
    go();
  }while( next_permutation( ord.begin() , ord.end() ) );
}
