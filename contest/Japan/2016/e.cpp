#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1021
typedef long long LL;
char c[ 1021 ];
char t[ 1021 ];
char opc[ 10 ] = "01+-*()=";
vector<char> cand;
int ans , len;
char to[ 1021 ];
bool used[ 10 ];
int pr[ N ] , mid;
bool flag;
LL cal( int l , int r ){
  vector< pair<int,LL> > vv;
  for( int i = l ; i <= r ; )
    if( t[ i ] == '+' ){
      vv.push_back( { 1 , 0 } );
      i ++;
    }else if( t[ i ] == '-' ){
      vv.push_back( { 2 , 0 } );
      i ++;
    }else if( t[ i ] == '*' ){
      vv.push_back( { 3 , 0 } );
      i ++;
    }else if( t[ i ] == '(' ){
      vv.push_back( { 0 , cal( i + 1 , pr[ i ] - 1 ) } );
      i = pr[ i ] + 1;
    }else{
      LL vl = 0;
      string wt;
      while( i <= r and isdigit( t[ i ] ) ){
        wt += t[ i ];
        vl = vl * 2 + (t[ i ] - '0');
        i ++;
      }
      if( (int)wt.length() > 1 and wt[ 0 ] == '0' )
        flag = false;
      vv.push_back( { 0 , vl } );
    }
  if( vv.empty() ){
    flag = false;
    return 0;
  }
  vector< pair<int,LL> > nv;
  for( size_t i = 0 ; i < vv.size() ; )
    if( i == 0 and vv[ i ].first ){
      if( vv[ i ].first != 2 ){
        flag = false;
        return 0;
      }
      int j = i + 1 , cnt = 1;
      while( j < (int)vv.size() and vv[ j ].first ){
        if( vv[ j ].first != 2 ){
          flag = false;
          return 0;
        }
        j ++;
        cnt ++;
      }
      if( j < (int)vv.size() ){
        if( cnt % 2 == 0 ){
          nv.push_back( vv[ j ] );
        }else{
          nv.push_back( { 0 , -vv[ j ].second } );
        }
        j ++;
      }else{
        flag = false;
        return 0;
      }
      i = j;
    }else if( i + 1 < vv.size() and
        vv[ i ].first and vv[ i + 1 ].first ){
      if( vv[ i + 1 ].first != 2 ){
        flag = false;
        return 0;
      }
      int j = i + 2 , cnt = 1;
      while( j < (int)vv.size() and vv[ j ].first ){
        if( vv[ j ].first != 2 ){
          flag = false;
          return 0;
        }
        cnt ++;
        j ++;
      }
      if( j < (int)vv.size() ){
        nv.push_back( vv[ i ] );
        if( cnt % 2 == 0 ){
          nv.push_back( vv[ j ] );
        }else{
          nv.push_back( { 0 , -vv[ j ].second } );
        }
        j ++;
      }else{
        flag = false;
        return 0;
      }
      i = j;
    }else{
      nv.push_back( vv[ i ] );
      i ++;
    }
  vv.swap( nv );
  if( vv.empty() ){
    flag = false;
    return 0;
  }
  if( vv[ 0 ].first or
      vv.back().first ){
    flag = false;
    return 0;
  }
  for( size_t i = 0 ; i + 1 < vv.size() ; i ++ )
    if( ( vv[ i ].first == 0 ) ==
        ( vv[ i + 1 ].first == 0 ) ){
      flag = false;
      return 0;
    }
  //if( !strcmp( t , "-10+1=-1" ) ){
    //puts( "got" );
    //for( auto i : vv )
      //cout << i.first << " " << i.second << endl;
  //}
  vector<LL> num;
  vector<int> op;
  for( auto i : vv )
    if( i.first == 0 ){
      num.push_back( i.second );
      continue;
    }else{
      while( op.size() and op.back() / 3 >= i.first / 3 ){
        int oop = op.back(); op.pop_back();
        if( num.size() < 2u ){
          flag = false;
          return 0;
        }
        LL n2 = num.back(); num.pop_back();
        LL n1 = num.back(); num.pop_back();
        if( oop == 1 )
          n1 += n2;
        else if( oop == 2 )
          n1 -= n2;
        else if( oop == 3 )
          n1 *= n2;
        else
          assert( false );
        num.push_back( n1 );
      }
      op.push_back( i.first );
    }
  while( op.size() ){
    int oop = op.back(); op.pop_back();
    if( num.size() < 2u ){
      flag = false;
      return 0;
    }
    LL n2 = num.back(); num.pop_back();
    LL n1 = num.back(); num.pop_back();
    if( oop == 1 )
      n1 += n2;
    else if( oop == 2 )
      n1 -= n2;
    else if( oop == 3 )
      n1 *= n2;
    else
      assert( false );
    num.push_back( n1 );
  }
  if( num.size() != 1u ){
    flag = false;
    return 0;
  }
  return num[ 0 ];
}
bool eval(){
  vector<int> eq;
  for( int i = 0 ; i < len ; i ++ )
    if( t[ i ] == '=' )
      eq.push_back( i );
  if( eq.size() != 1u ) return false;
  mid = eq[ 0 ];
  vector<int> wt;
  for( int i = 0 ; i < mid ; i ++ )
    if( t[ i ] == '(' )
      wt.push_back( i );
    else if( t[ i ] == ')' ){
      if( wt.empty() ) return false;
      pr[ wt.back() ] = i;
      wt.pop_back();
    }
  if( not wt.empty() ) return false;
  for( int i = mid + 1 ; i < len ; i ++ )
    if( t[ i ] == '(' )
      wt.push_back( i );
    else if( t[ i ] == ')' ){
      if( wt.empty() ) return false;
      pr[ wt.back() ] = i;
      wt.pop_back();
    }
  if( not wt.empty() ) return false;
  flag = true;
  LL lv = cal( 0 , mid - 1 );
  LL rv = cal( mid + 1 , len - 1 );
  if( lv != rv ) flag = false;
  return flag;
}
void gogo( int now ){
  if( now == (int)cand.size() ){
    for( int i = 0 ; i < len ; i ++ )
      if( isalpha( c[ i ] ) )
        t[ i ] = to[ (int)c[ i ] ];
      else
        t[ i ] = c[ i ];
    if( eval() ){
    //puts( t );
      ans ++;
    }
    return;
  }
  for( int i = 0 ; i < 8 ; i ++ ){
    if( used[ i ] ) continue;
    to[ (int)cand[ now ] ] = opc[ i ];
    used[ i ] = true;
    gogo( now + 1 );
    used[ i ] = false;
  }
}
int main(){
  scanf( "%s" , c );
  len = strlen( c );
  for( int i = 0 ; c[ i ] ; i ++  )
    if( isalpha( c[ i ] ) )
      cand.push_back( c[ i ] );
  sort( cand.begin() , cand.end() );
  cand.resize( unique( cand.begin() , cand.end() ) - cand.begin() );
  gogo( 0 );
  printf( "%d\n" , ans );
}
