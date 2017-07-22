#include <bits/stdc++.h>
using namespace std;
#define N 101010
vector< pair<int,int> > at;
vector<int> v;
char tar = '\'';
char c[ N ];
bool tg[ N ];
int len;
bool dp[ N ][ 5 ];
int bk[ N ][ 5 ];
int bkpre[ N ][ 5 ];
int bknxt[ N ][ 5 ];
void imp(){
  puts( "!@#$%" );
  exit(0);
}
int cst[] = { 0 , 2 , 3 , 5 , 5 };
// X , i , b , ib , bi
int ap[ N ] , an[ N ];
bool okay( int lft , int rgt ){
  if( lft == 1 and rgt == 4 ) return false;
  if( lft == 2 and rgt == 3 ) return false;
  if( lft == 3 and rgt == 1 ) return false;
  if( lft == 3 and rgt == 3 ) return false;
  if( lft == 4 and rgt == 2 ) return false;
  if( lft == 4 and rgt == 4 ) return false;
  return true;
}
int link( int lft , int rgt ){
  if( lft == 0 ) return rgt;
  if( lft == 1 ){
    int res[] = { 1 , 0 , 3 , 2 , -1 };
    return res[ rgt ];
  }
  if( lft == 2 ){
    int res[] = { 2 , 4 , 0 , -1 , 1 };
    return res[ rgt ];
  }
  if( lft == 3 ){
    int res[] = { 3 , -1 , 1 , -1 , 0 };
    return res[ rgt ];
  }
  if( lft == 4 ){
    int res[] = { 4 , 2 , -1 , 0 , -1 };
    return res[ rgt ];
  }
  assert( false );
  return -1;
}
bool okk( int pre , int res ){
  if( pre == 0 ) return true;
  if( pre > 2 ) return false;
  if( pre == 1 ) return res % 6 == 0;
  return res % 4 == 0;
}
void solve(){
  dp[ 0 ][ 0 ] = true;
  int sz = (int)v.size();
  for( auto k : v )
    if( k < 2 )
      imp();
  for( int i = 0 ; i < sz ; i ++ )
    for( int j = 0 ; j < 5 ; j ++ ){
      if( not dp[ i ][ j ] ) continue;
      for( int pre = 0 ; pre < 5 ; pre ++ ){
        if( not okay( j , pre ) ) continue;
        int act = link( j , pre );
        for( int nxt = 0 ; nxt < 5 ; nxt ++ ){
          if( not okay( act , nxt ) ) continue;
          int to = link( act , nxt );
          int nd = cst[ pre ] + cst[ nxt ];
          int res = v[ i ] - nd;
          if( res < 0 or res % 2 or res == 2 )
            continue;
          if( not okk( act , res ) )
            continue;
          dp[ i + 1 ][ to ] = true;
          bk[ i + 1 ][ to ] = j;
          bkpre[ i + 1 ][ to ] = pre;
          bknxt[ i + 1 ][ to ] = nxt;
        }
      }
    }
  if( not dp[ sz ][ 0 ] ) imp();
  int pp = 0;
  for( int i = sz ; i >= 1 ; i -- ){
    ap[ i - 1 ] = bkpre[ i ][ pp ];
    an[ i - 1 ] = bknxt[ i ][ pp ];
    pp = bk[ i ][ pp ];
  }
}
string ans = "";
vector<int> stk;
vector<int> rr[ 5 ] = { {} , {0} , {1} , {0, 1}, {1, 0} };
void gen( int msk ){
  for( auto i : rr[ msk ] ){
    if( stk.size() and i == stk.back() ){
      if( i == 0 )
        ans += "</i>";
      else
        ans += "</b>";
      stk.pop_back();
    }else{
      if( i == 0 )
        ans += "<i>";
      else
        ans += "<b>";
      stk.push_back( i );
    }
  }
}
void gen2( int tlen ){
  if( tlen == 0 ) return;
  int pre = 0;
  for( auto i : stk )
    pre |= (1 << i);
  if( pre == 0 ){
    while( tlen > 6 ){
      tlen -= 4;
      ans += "<i></i>";
    }
    if( tlen == 4 ){
      ans += "<i></i>";
      return;
    }
    if( tlen == 6 ){
      ans += "<b></b>";
      return;
    }
  }
  if( pre == 1 ){
    while( tlen ){
      ans += "<b></b>";
      tlen -= 6;
    }
    return;
  }
  if( pre == 2 ){
    while( tlen ){
      ans += "<i></i>";
      tlen -= 4;
    }
    return;
  }
  assert( false );
}
void gen(){
  int ptr = 0;
  for( int i = 0 ; i < len ; i ++ )
    if( not tg[ i ] )
      ans += c[ i ];
    else{
      int tot = v[ ptr ];
      gen( ap[ ptr ] );
      gen2( tot - cst[ ap[ ptr ] ] - cst[ an[ ptr ] ] );
      gen( an[ ptr ] );
      i = at[ ptr ].second;
      ptr ++;
    }
  cout << ans;
  exit(0);
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "wikipidia.in" , "r" , stdin );
  freopen( "wikipidia.out" , "w" , stdout );
#endif 
  fgets( c , N , stdin );
  len = strlen( c );
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] == tar ){
      int r = i;
      while( r < len and c[ r ] == tar ) r ++;
      at.push_back( { i , r - 1 } );
      for( int j = i ; j < r ; j ++ )
        tg[ j ] = true;
      v.push_back( r - i );
      i = r;
    }
  if( v.empty() ){
    printf( c );
    exit(0);
  }
  solve();
  gen();
}
