#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 100
char c[ 3 ][ N ];
int len , nxt[ 3 ][ 2 ];
vector<string> _name = {"Pre", "In", "Post"};
bool got;
struct Nd{
  char r;
  Nd *tl , *tr;
  Nd(){
    tl = tr = NULL;
  }
};

void pre_go2( Nd* ret , string& ss );
void in_go2( Nd* ret , string& ss );
void post_go2( Nd* ret , string& ss );
void pre_go2( Nd* ret , string& ss ){
  if( !ret ) return;
  ss += ret->r;
  if( nxt[ 0 ][ 0 ] == 0 )
    pre_go2( ret->tl , ss );
  if( nxt[ 0 ][ 0 ] == 1 )
    in_go2( ret->tl , ss );
  if( nxt[ 0 ][ 0 ] == 2 )
    post_go2( ret->tl , ss );
  if( nxt[ 0 ][ 1 ] == 0 )
    pre_go2( ret->tr , ss );
  if( nxt[ 0 ][ 1 ] == 1 )
    in_go2( ret->tr , ss );
  if( nxt[ 0 ][ 1 ] == 2 )
    post_go2( ret->tr , ss );
}
void in_go2( Nd* ret , string& ss ){
  if( !ret ) return;
  if( nxt[ 1 ][ 0 ] == 0 )
    pre_go2( ret->tl , ss );
  if( nxt[ 1 ][ 0 ] == 1 )
    in_go2( ret->tl , ss );
  if( nxt[ 1 ][ 0 ] == 2 )
    post_go2( ret->tl , ss );
  ss += ret->r;
  if( nxt[ 1 ][ 1 ] == 0 )
    pre_go2( ret->tr , ss );
  if( nxt[ 1 ][ 1 ] == 1 )
    in_go2( ret->tr , ss );
  if( nxt[ 1 ][ 1 ] == 2 )
    post_go2( ret->tr , ss );
}
void post_go2( Nd* ret , string& ss ){
  if( !ret ) return;
  if( nxt[ 2 ][ 0 ] == 0 )
    pre_go2( ret->tl , ss );
  if( nxt[ 2 ][ 0 ] == 1 )
    in_go2( ret->tl , ss );
  if( nxt[ 2 ][ 0 ] == 2 )
    post_go2( ret->tl , ss );
  if( nxt[ 2 ][ 1 ] == 0 )
    pre_go2( ret->tr , ss );
  if( nxt[ 2 ][ 1 ] == 1 )
    in_go2( ret->tr , ss );
  if( nxt[ 2 ][ 1 ] == 2 )
    post_go2( ret->tr , ss );
  ss += ret->r;
}

void pre_go( Nd* ret , string& ss ){
  if( !ret ) return;
  ss += ret->r;
  pre_go( ret->tl , ss );
  pre_go( ret->tr , ss );
}
void in_go( Nd* ret , string& ss ){
  if( !ret ) return;
  in_go( ret->tl , ss );
  ss += ret->r;
  in_go( ret->tr , ss );
}
void post_go( Nd* ret , string& ss ){
  if( !ret ) return;
  post_go( ret->tl , ss );
  post_go( ret->tr , ss );
  ss += ret->r;
}
#define ID first.first
#define KD first.second
#define L second.first
#define R second.second
typedef pair< pair<int,int> , pair<int,int> > dat;
Nd* bst[ 3 ][ N ][ N ];
int gt[ 3 ][ N ][ N ] , stmp;
Nd* Bst( int kd , int l , int r ){
  if( l > r ) return NULL;
  if( gt[ kd ][ l ][ r ] == stmp )
    return bst[ kd ][ l ][ r ];
  gt[ kd ][ l ][ r ] = stmp;
  if( l == r ){
    bst[ kd ][ l ][ r ] = new Nd();
    bst[ kd ][ l ][ r ]->r = c[ 0 ][ l ];
    return bst[ kd ][ l ][ r ];
  }
  bool found = false;
  Nd* ret = NULL;
  string pp = "" , ii = "";
  if( kd == 0 ){ // pre
    Nd* tmp = new Nd();
    tmp->r = c[ 0 ][ l ];
    
    for( int i = l + 1 ; i <= r ; i ++ ){
      Nd *lft = Bst( nxt[ 0 ][ 0 ] , l + 1 , i );
      Nd *rgt = Bst( nxt[ 0 ][ 1 ] , i + 1 , r );
      tmp->tl = lft;
      tmp->tr = rgt;

      string np = "" , ni = "";
      pre_go( tmp , np );
      in_go( tmp , ni );
      if( not found or make_pair(np, ni) < make_pair(pp, ii) ){
        ret = new Nd();
        ret->r = c[ 0 ][ l ];
        ret->tl = lft;
        ret->tr = rgt;
        pp = np;
        ii = ni;
      }
    }
  }
  if( kd == 1 ){ // in   
    for( int i = l ; i <= r ; i ++ ){
      Nd* tmp = new Nd();
      tmp->r = c[ 0 ][ i ];
      Nd *lft = Bst( nxt[ 1 ][ 0 ] , l , i - 1 );
      Nd *rgt = Bst( nxt[ 1 ][ 1 ] , i + 1 , r );
      tmp->tl = lft;
      tmp->tr = rgt;

      string np = "" , ni = "";
      pre_go( tmp , np );
      in_go( tmp , ni );
      if( not found or make_pair(np, ni) < make_pair(pp, ii) ){
        ret = new Nd();
        ret->r = c[ 0 ][ i ];
        ret->tl = lft;
        ret->tr = rgt;
        pp = np;
        ii = ni;
      }
    }
  }
  if( kd == 2 ){ // post
    Nd* tmp = new Nd();
    tmp->r = c[ 0 ][ r ];
    for( int i = l ; i < r ; i ++ ){
      Nd *lft = Bst( nxt[ 2 ][ 0 ] , l , i );
      Nd *rgt = Bst( nxt[ 2 ][ 1 ] , i + 1 , r - 1 );
      tmp->tl = lft;
      tmp->tr = rgt;

      string np = "" , ni = "";
      pre_go( tmp , np );
      in_go( tmp , ni );
      if( not found or make_pair(np, ni) < make_pair(pp, ii) ){
        ret = new Nd();
        ret->r = c[ 0 ][ r ];
        ret->tl = lft;
        ret->tr = rgt;
        pp = np;
        ii = ni;
      }
    }
  }
  return bst[ kd ][ l ][ r ] = ret;
}
bool cmp( dat d1 , dat d2 ){
  return d1.KD < d2.KD;
}
bool ggwp( const vector<dat>& vv ){
  int msk[ 3 ] = {};
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = vv[ i ].L ; j <= vv[ i ].R ; j ++ )
      msk[ i ] |= (1 << (c[ vv[ i ].ID ][ j ] - 'A'));
  return msk[ 0 ] != msk[ 1 ] or
         msk[ 0 ] != msk[ 2 ];
}
Nd* go( vector< dat >& v , bool& ok ){
  ok = true;
  if( ggwp( v ) ){
    ok = false;
    return NULL;
  }
  sort( v.begin() , v.end() , cmp );
  if( v[ 0 ].L > v[ 0 ].R )
    return NULL;
  if( v[ 0 ].L == v[ 0 ].R ){
    for( int i = 1 ; i < 3 ; i ++ )
      if( c[ v[ 0 ].ID ][ v[ 0 ].L ] !=
          c[ v[ i ].ID ][ v[ i ].L ] )
        ok = false;
    if( not ok ) return NULL;
    Nd* ret = new Nd();
    ret->r = c[ v[ 0 ].ID ][ v[ 0 ].L ];
    return ret;
  }
  if( v[ 0 ].KD == v.back().KD ){
    ok = true;
    for( int i = 0 ; i < 3 ; i ++ )
      if( v[ i ].ID == 0 )
        return Bst( v[ i ].KD , v[ i ].L , v[ i ].R );
    assert( false );
    ok = false;
    return NULL;
  }
  for( int i = 0 ; i < 3 ; i ++ )
    if( v[ i ].KD == 1 ){
      for( int j = 0 ; j < 3 ; j ++ ){
        if( v[ j ].KD == 0 or v[ j ].KD == 2 ){
          Nd* ret = new Nd();
          if( v[ j ].KD == 0 )
            ret->r = c[ v[ j ].ID ][ v[ j ].L ];
          else
            ret->r = c[ v[ j ].ID ][ v[ j ].R ];
          char goal = ret->r;
          int at = -1;
          for( int k = v[ i ].L ; k <= v[ i ].R ; k ++ )
            if( c[ v[ i ].ID ][ k ] == ret->r ){
              at = k;
              break;
            }
          if( at == -1 ){
            ok = false;
            return NULL;
          }
          int llen = at - v[ i ].L;
          {
            bool okl , okr , cur = true;
            vector< dat > vl , vr;
            for( int k = 0 ; k < 3 ; k ++ )
              if( v[ k ].KD == 0 ){
                if( c[ v[ k ].ID ][ v[ k ].L ] != goal )
                  cur = false;
                vl.push_back( { { v[ k ].ID , nxt[ 0 ][ 0 ] } ,
                                { v[ k ].L + 1 , v[ k ].L + llen } } );
                vr.push_back( { { v[ k ].ID , nxt[ 0 ][ 1 ] } ,
                                { v[ k ].L + llen + 1 , v[ k ].R } } );
              }else if( v[ k ].KD == 1 ){
                if( c[ v[ k ].ID ][ v[ k ].L + llen ] != goal )
                  cur = false;
                vl.push_back( { { v[ k ].ID , nxt[ 1 ][ 0 ] } ,
                                { v[ k ].L , v[ k ].L + llen - 1 } } );
                vr.push_back( { { v[ k ].ID , nxt[ 1 ][ 1 ] } ,
                                { v[ k ].L + llen + 1 , v[ k ].R } } );
              }else if( v[ k ].KD == 2 ){
                if( c[ v[ k ].ID ][ v[ k ].R ] != goal )
                  cur = false;
                vl.push_back( { { v[ k ].ID , nxt[ 2 ][ 0 ] } ,
                                { v[ k ].L , v[ k ].L + llen - 1 } } );
                vr.push_back( { { v[ k ].ID , nxt[ 2 ][ 1 ] } ,
                                { v[ k ].L + llen , v[ k ].R - 1 } } );
              }
            if( !cur ){
              ok = false;
              return NULL;
            }
            ret->tl = go( vl , okl );
            if( !okl ){
              ok = false;
              return NULL;
            }
            ret->tr = go( vr , okr );
            if( !okr ){
              ok = false;
              return NULL;
            }
          }
          ok = true;
          return ret;
        }
      }
    }
  for( int i = 0 ; i < 3 ; i ++ )
    if( v[ i ].KD == 0 )
      for( int j = 0 ; j < 3 ; j ++ ){
        if( v[ j ].KD == 2 ){ // i pre , j post
          bool found = false;
          Nd *ret = NULL;
          string pp , ii;
    
          int res = v[ i ].R - v[ i ].L;

          for( int llen = 0 ; llen <= res ; llen ++ ){

            Nd* nret = new Nd();
 
            nret->r = c[ v[ i ].ID ][ v[ i ].L ];

            char goal = nret -> r;

            bool okl = true , okr = true , cur = true;
            vector< dat > vl , vr;
            for( int k = 0 ; k < 3 ; k ++ )
              if( v[ k ].KD == 0 ){
                if( c[ v[ k ].ID ][ v[ k ].L ] != goal )
                  cur = false;
                vl.push_back( { { v[ k ].ID , nxt[ 0 ][ 0 ] } ,
                                { v[ k ].L + 1 , v[ k ].L + llen } } );
                vr.push_back( { { v[ k ].ID , nxt[ 0 ][ 1 ] } ,
                                { v[ k ].L + llen + 1 , v[ k ].R } } );
              }else if( v[ k ].KD == 1 ){
                if( c[ v[ k ].ID ][ v[ k ].L + llen ] != goal )
                  cur = false;
                vl.push_back( { { v[ k ].ID , nxt[ 1 ][ 0 ] } ,
                                { v[ k ].L , v[ k ].L + llen - 1 } } );
                vr.push_back( { { v[ k ].ID , nxt[ 1 ][ 1 ] } ,
                                { v[ k ].L + llen + 1 , v[ k ].R } } );
              }else if( v[ k ].KD == 2 ){
                if( c[ v[ k ].ID ][ v[ k ].R ] != goal )
                  cur = false;
                vl.push_back( { { v[ k ].ID , nxt[ 2 ][ 0 ] } ,
                                { v[ k ].L , v[ k ].L + llen - 1 } } );
                vr.push_back( { { v[ k ].ID , nxt[ 2 ][ 1 ] } ,
                                { v[ k ].L + llen , v[ k ].R - 1 } } );
              }
            if( !cur ) continue;
            nret->tl = go( vl , okl );
            if( !okl ) continue;
            nret->tr = go( vr , okr );
            if( !okr ) continue;

            string np = "" , ni = "";
            pre_go( nret , np );
            in_go( nret , ni );
            if( not found or
                make_pair( np , ni ) < make_pair( pp , ii ) ){
              found = true;
              ret = nret;
              pp = np;
              ii = ni;
            }
          }
          ok = found;
          return ret;
        }
      }
  assert( false );
  return NULL;
}
vector<int> ord;
void solve(){
  ++ stmp;
  bool ok;
  vector< dat > v;
  for( int i = 0 ; i < 3 ; i ++ )
    v.push_back( { { i , i } , {0 , len - 1} } );
  Nd* ret = go( v , ok );
  if( not ok ) return;

  {
    string o = "";
    pre_go2( ret , o );
    if( o != string( c[ 0 ] ) )
      return;
  }
  {
    string o = "";
    in_go2( ret , o );
    if( o != string( c[ 1 ] ) )
      return;
  }
  {
    string o = "";
    post_go2( ret , o );
    if( o != string( c[ 2 ] ) )
      return;
  }

  if( got ) puts( "" );
  got = true;
  for( int i = 0 ; i < 6 ; i ++ )
    cout << _name[ ord[ i ] ] << " \n"[ i + 1 == 6 ];

  {
    string o = "";
    pre_go( ret , o );
    printf( "%s\n" , o.c_str() );
  }
  {
    string o = "";
    in_go( ret , o );
    printf( "%s\n" , o.c_str() );
  }
  {
    string o = "";
    post_go( ret , o );
    printf( "%s\n" , o.c_str() );
  }
}
int main(){
  for( int i = 0 ; i < 3 ; i ++ )
    scanf( "%s" , c[ i ] );
  len = strlen( c[ 0 ] );
  ord = {0, 0, 1, 1, 2, 2};
  do{
    for( int i = 0 ; i < 6 ; i ++ )
      nxt[ i >> 1 ][ i & 1 ] = ord[ i ];
    solve();
  }while( next_permutation( ord.begin() , ord.end() ) );
}
