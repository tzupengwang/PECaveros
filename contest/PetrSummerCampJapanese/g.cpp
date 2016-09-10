#include <bits/stdc++.h>
using namespace std;
#define N 32769
typedef long long LL;
LL sq[ N ];
vector< LL > pset;
bool p[ N ];
inline LL sqr( LL v ){
  if( v == 0 ) return 1;
  if( v < N ) return sq[ v ];
  LL tk = 1;
  for( LL tp : pset )
    while( v % ( tp * tp ) == 0 ){
      tk *= tp;
      v /= ( tp * tp );
    }
  return tk;
}
struct frac{
  LL p , q;
  frac(){
    p = 0; q = 1;
  }
  frac( LL x ){
    p = x; q = 1;
  }
  frac( LL u , LL v ){
    p = u; q = v;
    reduce();
  }
  frac operator+( const frac& tf ) const{
    LL up = p * tf.q + q * tf.p;
    LL dn = q * tf.q;
    return frac( up , dn );
  }
  frac operator-( const frac& tf ) const{
    LL up = p * tf.q - q * tf.p;
    LL dn = q * tf.q;
    return frac( up , dn );
  }
  frac operator*( const frac& tf ) const{
    LL up = p * tf.p;
    LL dn = q * tf.q;
    return frac( up , dn );
  }
  frac operator/( const frac& tf ) const{
    LL up = p * tf.q;
    LL dn = q * tf.p;
    return frac( up , dn );
  }
  void reduce(){
    LL tg = __gcd( p , q );
    p /= tg; q /= tg;
    if( q < 0 ){
      p *= -1;
      q *= -1;
    }
  }
  void print( LL rrr ){
    if( rrr == 1 ){
      printf( "%lld" , p );
      if( q > 1 ) printf( "/%lld" , q );
    }else{
      if( q == 1 && abs( p ) == 1 ){
        if( p == -1 ) putchar( '-' );
        return;
      }
      printf( "%lld" , p );
      if( q > 1 ) printf( "/%lld" , q );
    }
  }
};
bool cmp( pair<frac,LL> p1 , pair<frac,LL> p2 ){
  return p1.second < p2.second;
}
struct Xstar{
  vector< pair<frac,LL> > coe;
  Xstar(){ coe.clear(); }
  Xstar( LL v ){
    coe.clear();
    if( v != 0 )
      coe.push_back( { frac( v ) , 1 } );
  }
  Xstar( frac v , LL u ){
    coe.clear();
    if( v.p != 0 )
      coe.push_back( { v , u } );
  }
  Xstar sqrt() const{
    if( coe.empty() ) return *this;
    LL tp = coe[ 0 ].first.p;
    LL tq = coe[ 0 ].first.q;
    LL sqrtp = sqr( tp );
    LL sqrtq = sqr( tq );
    LL ta = sqrtp , tb = tp / ( sqrtp * sqrtp );
    LL tc = sqrtq , td = tq / ( sqrtq * sqrtq );
    tc *= td;
    td *= tb; 
    LL ff = sqr( td );
    ta *= ff;
    td /= ff * ff;
    return Xstar( frac( ta , tc ) , td );
  }
  Xstar operator/( const Xstar& tx ) const{
    Xstar txx;
    frac cc = tx.coe[ 0 ].first;
    LL dd = tx.coe[ 0 ].second;
    for( pair<frac,LL> tp : coe ){
      frac aa = tp.first;
      LL bb = tp.second;
      frac tmp = aa / cc;
      tmp = tmp / frac( dd );
      LL tq = bb * dd;
      LL ff = sqr( tq );
      tmp = tmp * frac( ff );
      tq /= ( ff * ff );
      txx.coe.push_back( { tmp , tq } );
    }
    sort( txx.coe.begin() , txx.coe.end() , cmp );
    if( txx.coe.empty() ) return txx;
    size_t sz = 1;
    for( size_t i = 1 ; i < txx.coe.size() ; i ++ ){
      if( txx.coe[ i ].second == txx.coe[ sz - 1 ].second )
        txx.coe[ sz - 1 ].first = txx.coe[ sz - 1 ].first + 
                                  txx.coe[ i ].first;
      else
        txx.coe[ sz ++ ] = txx.coe[ i ];
    }
    txx.coe.resize( sz );
    sz = 0;
    for( size_t i = 0 ; i < txx.coe.size() ; i ++ ){
      if( txx.coe[ i ].first.p == 0 ) continue;
      txx.coe[ sz ++ ] = txx.coe[ i ];
    }
    txx.coe.resize( sz );
    return txx;
  }
  Xstar operator+( const Xstar& tx ) const{
    Xstar res;
    int sz1 = (int)coe.size() , ptr1 = 0;
    int sz2 = (int)tx.coe.size() , ptr2 = 0;
    while( ptr1 < sz1 && ptr2 < sz2 ){
      if( coe[ ptr1 ].second == tx.coe[ ptr2 ].second ){
        frac rres = coe[ ptr1 ].first + tx.coe[ ptr2 ].first;
        if( rres.p )
          res.coe.push_back( { rres , coe[ ptr1 ].second } );
        ptr1 ++; ptr2 ++;
      }else if( coe[ ptr1 ].second < tx.coe[ ptr2 ].second ){
        res.coe.push_back( { coe[ ptr1 ].first , coe[ ptr1 ].second } );
        ptr1 ++;
      }else{
        res.coe.push_back( { tx.coe[ ptr2 ].first , tx.coe[ ptr2 ].second } );
        ptr2 ++;
      }
    }
    while( ptr1 < sz1 ) res.coe.push_back( coe[ ptr1 ++ ] );
    while( ptr2 < sz2 ) res.coe.push_back( tx.coe[ ptr2 ++ ] );
    return res;
  }
  Xstar operator-( const Xstar& tx ) const{
    Xstar res;
    int sz1 = (int)coe.size() , ptr1 = 0;
    int sz2 = (int)tx.coe.size() , ptr2 = 0;
    while( ptr1 < sz1 && ptr2 < sz2 ){
      if( coe[ ptr1 ].second == tx.coe[ ptr2 ].second ){
        frac rres = coe[ ptr1 ].first - tx.coe[ ptr2 ].first;
        if( rres.p )
          res.coe.push_back( { rres , coe[ ptr1 ].second } );
        ptr1 ++; ptr2 ++;
      }else if( coe[ ptr1 ].second < tx.coe[ ptr2 ].second ){
        res.coe.push_back( { coe[ ptr1 ].first , coe[ ptr1 ].second } );
        ptr1 ++;
      }else{
        res.coe.push_back( { tx.coe[ ptr2 ].first * frac( -1 ) ,
                             tx.coe[ ptr2 ].second } );
        ptr2 ++;
      }
    }
    while( ptr1 < sz1 ) res.coe.push_back( coe[ ptr1 ++ ] );
    while( ptr2 < sz2 ){
      res.coe.push_back( { tx.coe[ ptr2 ].first * frac( -1 ) ,
                           tx.coe[ ptr2 ].second } );
      ptr2 ++;
    }
    return res;
  }
  Xstar operator*( const Xstar& tx ) const{
    Xstar res;
    for( size_t i = 0 ; i < coe.size() ; i ++ )
      for( size_t j = 0 ; j < tx.coe.size() ; j ++ ){
        frac ta = coe[ i ].first * tx.coe[ j ].first;
        LL tv = coe[ i ].second * tx.coe[ j ].second;
        LL ff = sqr( tv );
        ta = ta * frac( ff );
        tv /= ( ff * ff );
        res.coe.push_back( { ta , tv } );
      }
    sort( res.coe.begin() , res.coe.end() , cmp );
    if( res.coe.empty() ) return res;
    size_t sz = 1;
    for( size_t i = 1 ; i < res.coe.size() ; i ++ ){
      if( res.coe[ i ].second == res.coe[ sz - 1 ].second )
        res.coe[ sz - 1 ].first = res.coe[ sz - 1 ].first + 
                                  res.coe[ i ].first;
      else
        res.coe[ sz ++ ] = res.coe[ i ];
    }
    res.coe.resize( sz );
    sz = 0;
    for( size_t i = 0 ; i < res.coe.size() ; i ++ ){
      if( res.coe[ i ].first.p == 0 ) continue;
      res.coe[ sz ++ ] = res.coe[ i ];
    }
    res.coe.resize( sz );
    return res;
  }
  void print(){
    if( coe.empty() ){
      puts( "0" );
      return;
    }
    for( size_t i = 0 ; i < coe.size() ; i ++ ){
      if( i ) printf( " + " );
      coe[ i ].first.print( coe[ i ].second );
      if( coe[ i ].second > 1 ){
        if( coe[ i ].first.q != 1 || abs( coe[ i ].first.p ) != 1 )
          putchar( '*' );
        printf( "sqrt(%lld)" , coe[ i ].second );
      }
    }
    puts( "" );
  }
};
void build(){
  for( LL i = 1 ; i < N ; i ++ ){
    sq[ i ] = 1;
    for( LL j = 2 ; j * j <= i ; j ++ )
      if( i % ( j * j ) == 0 )
        sq[ i ] = j;
  }
  for( LL i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
    pset.push_back( i );
    for( LL j = i ; j < N ; j += i )
      p[ j ] = true;
  }
}
char cmd[ 10101 ];
vector< Xstar > stk;
int main(){
  build();
  while( scanf( "%s" , cmd ) == 1 ){
    if( !strcmp( cmd , "stop" ) ) break;
    if( !strcmp( cmd , "disp" ) ){
      stk.back().print();
      stk.pop_back();
      continue;
    }
    if( !strcmp( cmd , "push" ) ){
      LL x; scanf( "%lld" , &x );
      stk.push_back( Xstar( x ) );
      continue;
    }
    if( !strcmp( cmd , "add" ) ){
      int sz = (int)stk.size();
      stk[ sz - 2 ] = stk[ sz - 2 ] + stk[ sz - 1 ];
      stk.pop_back();
      continue;
    }
    if( !strcmp( cmd , "sub" ) ){
      int sz = (int)stk.size();
      stk[ sz - 2 ] = stk[ sz - 2 ] - stk[ sz - 1 ];
      stk.pop_back();
      continue;
    }
    if( !strcmp( cmd , "mul" ) ){
      int sz = (int)stk.size();
      stk[ sz - 2 ] = stk[ sz - 2 ] * stk[ sz - 1 ];
      stk.pop_back();
      continue;
    }
    if( !strcmp( cmd , "div" ) ){
      int sz = (int)stk.size();
      stk[ sz - 2 ] = stk[ sz - 2 ] / stk[ sz - 1 ];
      stk.pop_back();
      continue;
    }
    if( !strcmp( cmd , "sqrt" ) ){
      stk.back() = stk.back().sqrt();
      continue;
    } 
  }
}
