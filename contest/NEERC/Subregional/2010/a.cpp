#include <bits/stdc++.h>
using namespace std;
#define N 101010
string ss;
inline void balance(){
  string tt = "";
  int len = ss.length() , pp = 0;
  for( int i = 0 ; i < len ; i ++ )
    if( ss[ i ] == '(' ){
      pp ++;
      tt += ss[ i ];
    }else if( ss[ i ] == ')' ){
      if( pp == 0 ) tt += '(';
      else pp --;
      tt += ')';
    }else
      tt += ss[ i ];
  while( pp -- ) tt += ')';
  ss = tt;
}
int pr[ N ];
string rr;
void go( int l , int r ){
  if( l > r ){
    rr += '0';
    return;
  }
  for( int i = l ; i <= r ;  )
    if( ss[ i ] == '(' ){
      rr += '(';
      go( i + 1 , pr[ i ] - 1 );
      rr += ')';
      i = pr[ i ] + 1;
    }else
      rr += ss[ i ++ ];
}
void make_sense(){
  vector< int > vv;
  int len = ss.length();
  for( int i = 0 ; i < len ; i ++ )
    if( ss[ i ] == '(' )
      vv.push_back( i );
    else if( ss[ i ] == ')' ){
      pr[ vv.back() ] = i;
      vv.pop_back();
    }
  rr = "";
  for( int i = 0 ; i < len ; )
    if( ss[ i ] == '(' ){
      rr += '(';
      go( i + 1 , pr[ i ] - 1 );
      rr += ')';
      i = pr[ i ] + 1;
    }else rr += ss[ i ++ ];
  ss = rr;
}
void make_more_sense(){
  string tt = "";
  int len = ss.length();
  if( ss[ 0 ] == '+' ) tt += "0";
  for( int i = 0 ; i < len ; i ++ ){
    if( i && ss[ i ] == '(' && ( ss[ i - 1 ] == ')' ||
                                 isdigit( ss[ i - 1 ] ) ) )
      tt += '+';
    if( i && ss[ i ] == '+' && ( ss[ i - 1 ] == '+' ||
                                 ss[ i - 1 ] == '(' ) )
      tt += '0';
    if( i && ss[ i ] == ')' && ss[ i - 1 ] == '+' )
      tt += '0';
    tt += ss[ i ];
  }
  if( tt[ tt.length() - 1 ] == '+' ) tt += "0";
  ss = tt;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "auxiliary.in" , "r" , stdin );
  freopen( "auxiliary.out" , "w" , stdout );
#endif 
  cin >> ss;
  balance();
  make_sense();
  make_more_sense();
  cout << ss << endl;
}
