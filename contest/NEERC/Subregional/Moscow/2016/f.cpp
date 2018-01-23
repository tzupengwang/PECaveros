#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define X 256
bool pos[ X ];
char c[ N ];
string dp[ X ];
inline bool in_set( char ctmp ){
  return isdigit( ctmp ) ||
         isalpha( ctmp ) ||
         ctmp == ' ';
}
inline bool better( const string&s1 , const string& s2 ){
  if( s1.length() != s2.length() )
    return s1.length() < s2.length();
  return s1 < s2;
}
string find_ans(){
  dp[ 31 ] = "";
  for( int i = 32 ; i <= 126 ; i ++ ){
    if( !in_set( i ) || pos[ i ] ){
      dp[ i ] = dp[ i - 1 ] + (char)i;
      for( int j = i - 1 ; j >= 32 ; j -- ){
        if( in_set( j ) && !pos[ j ] ) break;
        string tans = dp[ j - 1 ] + (char)j + "-" + (char)i;
        if( better( tans , dp[ i ] ) )
          dp[ i ] = tans;
      }
    }else dp[ i ] = dp[ i - 1 ];
    if( !pos[ i ] ){
      if( better( dp[ i - 1 ] , dp[ i ] ) )
        dp[ i ] = dp[ i - 1 ];
      for( int j = i - 1 ; j >= 32 ; j -- ){
        if( pos[ j ] ) break;
        string tans = dp[ j - 1 ];
        if( better( tans , dp[ i ] ) )
          dp[ i ] = tans;
      }
    }
  }
  if( dp[ 126 ] == "" )
    return "!";
  return dp[ 126 ];
}
int main(){
  fgets( c , N , stdin );
  int len = strlen( c );
  for( int i = 0 ; i < len ; i ++ )
    pos[ (int)c[ i ] ] = true;
  string ans1 = find_ans();
  for( int i = 32 ; i < 127 ; i ++ )
    if( in_set( i ) )
      pos[ i ] = !pos[ i ];
  string ans2 = "^" + find_ans();
  //cout << ans1 << endl;
  //cout << ans2 << endl;
  if( better( ans2 , ans1 ) )
    ans1 = ans2;
  cout << "%[" << ans1 << "]" << endl;
}
