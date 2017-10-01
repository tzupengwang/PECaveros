#include <bits/stdc++.h>
using namespace std;
vector<int> v;
string s;
int trans( char ctmp ){
  if( '0' <= ctmp and ctmp <= '9' )
    return ctmp - '0';
  if( 'A' <= ctmp and ctmp <= 'F' )
    return ctmp - 'A' + 10;
  assert( false );
  return -1;
}
char rtrans( int vl ){
  if( vl < 10 ) return vl + '0';
  return vl - 10 + 'A';
}
int decode(){
  return trans( s[ 0 ] ) * 16 + trans( s[ 1 ] );
}
bool okayqq( int len , int tmp ){
  if( len == 1 ) return ( ( tmp >> 7 ) & 1 ) == 0;
  if( len == 2 ) return ( ( tmp >> 5 ) & ((1 << 3) - 1) ) == 6;
  if( len == 3 ) return ( ( tmp >> 4 ) & ((1 << 4) - 1) ) == 14;
  if( len == 4 ) return ( ( tmp >> 3 ) & ((1 << 5) - 1) ) == 30;
  if( len == 5 ) return ( ( tmp >> 2 ) & ((1 << 6) - 1) ) == 62;
  if( len == 6 ) return ( ( tmp >> 1 ) & ((1 << 7) - 1) ) == 126;
  assert( false );
  return false;
}
pair<int,int> fb( int len , int vl ){
  if( len == 1 ) return { vl & ((1 << 7) - 1) , 7 };
  if( len == 2 ) return { vl & ((1 << 5) - 1) , 5 };
  if( len == 3 ) return { vl & ((1 << 4) - 1) , 4 };
  if( len == 4 ) return { vl & ((1 << 3) - 1) , 3 };
  if( len == 5 ) return { vl & ((1 << 2) - 1) , 2 };
  if( len == 6 ) return { vl & ((1 << 1) - 1) , 1 };
  assert( false );
  return { 0 , 0 };
}
int ffb( int vl ){
  return vl & ((1 << 6) - 1);
}
bool okaypp( int tmp ){
  return ( ( tmp >> 6 ) & 3 ) == 2;
}
void output( const vector<int>& ans ){
  if( ans.size() < 3u ) return;
  for( size_t i = 0 ; i < ans.size() ; i ++ ){
    string o = "";
    int vl = ans[ i ];
    while( vl ){
      o += rtrans( vl & 15 );
      vl >>= 4;
    }
    reverse( o.begin() , o.end() );
    if( o.empty() ) o = "0";
    printf( "%s%c" , o.c_str() , " \n"[ i + 1 == ans.size() ] );
  }
}
int parse( int st , int len ){
  int ret , plen;
  tie( ret , plen ) = fb( len , v[ st ] );
  for( int i = 1 ; i < len ; i ++ ){
    ret = (ret << 6) | ffb( v[ st + i ] );
    plen += 6;
  }
  return ret;
}
int main(){
  while( cin >> s )
    v.push_back( decode() );
  vector<int> ans;
  for( size_t i = 0 ; i < v.size() ; ){
    int oklen = -1;
    for( int x = 1 ; x <= 6 and (int)i + x <= (int)v.size() ; x ++ ){
      if( not okayqq( x , v[ i ] ) ) continue;
      bool good = true;
      for( int j = 1 ; j < x ; j ++ )
        if( not okaypp( v[ i + j ] ) ){
          good = false;
          break;
        }
      if( not good ) continue;
      oklen = x;
      break;
    }
    if( oklen == -1 ){
      output( ans );
      ans.clear();
      i ++;
    }else{
      ans.push_back( parse( i , oklen ) );
      i += oklen;
    }
  }
  output( ans );
}
