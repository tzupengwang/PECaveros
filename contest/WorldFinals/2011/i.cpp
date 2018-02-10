#include<bits/stdc++.h>
using namespace std;

#define N 101010

typedef pair<int, int> ii;
typedef pair<ii, ii> sq;
int n;
vector<ii> v;
vector<sq> s;

#define mid ((l+r)>>1)
struct Nd{
  int mn , tg;
  Nd *tl , *tr;
  Nd(){
    mn = tg = 0;
    tl = tr = NULL;
  }
};
int Mn( Nd* now ){ return now ? now->mn : 0; }
void push( Nd* now , int l , int r ){
  if( !now->tg ) return;
  if( !now->tl ) now->tl = new Nd();
  if( !now->tr ) now->tr = new Nd();
  now->tl->mn += now->tg;
  now->tl->tg += now->tg;
  now->tr->mn += now->tg;
  now->tr->tg += now->tg;
  now->tg = 0;
}
void modify( Nd* now , int l , int r , int ql , int qr , int d ){
  if( r < ql or l > qr ) return;
  if( ql <= l and r <= qr ){
    now->mn += d;
    now->tg += d;
    return;
  }
  push( now , l , r );
  if( ql <= mid and !now->tl ) now->tl = new Nd();
  if( mid < qr  and !now->tr ) now->tr = new Nd();
  modify( now->tl , l , mid , ql , qr , d );
  modify( now->tr , mid + 1 , r , ql , qr , d );
  now->mn = min( Mn( now->tl ) , Mn( now->tr ) );
}
void bye( Nd* now ){
  if( !now ) return;
  bye( now->tl );
  bye( now->tr );
  delete now;
}


bool has_blank( int t ){
  vector< pair< int , tuple<int,int,int> > > evet;
  for( auto i : s ){
    int lx = i.first.first;
    int rx = i.first.second;
    int ly = i.second.first;
    int ry = i.second.second;
    evet.push_back( { lx     , make_tuple( ly , ry , +1 ) } );
    evet.push_back( { rx + 1 , make_tuple( ly , ry , -1 ) } );
  }
  sort( evet.begin() , evet.end() );
  if( evet.empty() ) return true;
  if( evet[ 0 ].first > -t ) return true;
  if( evet.back().first < t ) return true;
  Nd *root = new Nd();
  bool got = false;
  for( size_t il = 0 , ir = 0 ; il < evet.size() ; il = ir ){
    while( ir < evet.size() and evet[ il ].first == evet[ ir ].first ) ir ++;
    for( size_t i = il ; i < ir ; i ++ )
      modify( root , -t , t , get<0>( evet[ i ].second ) ,
                              get<1>( evet[ i ].second ) ,
                              get<2>( evet[ i ].second ) );
    if( evet[ il ].first > t ) break;
    if( Mn( root ) == 0 ){
      got = true;
      break;
    }
  }
  bye( root );
  return got;
}

bool okay(int t) {
  s.clear();
  //printf("%d\n", t);
  for (int i = 0; i < n; i ++) {
    int x = v[i].first;
    int y = v[i].second;

    if (x < -(2 * t + 1) || x > (2 * t + 1)) continue;
    if (y < -(2 * t + 1) || y > (2 * t + 1)) continue;

    ii xs, ys;

    if (x < 0) xs = ii(-t, x + t);
    else if (x > 0) xs = ii(x - t, t);
    else xs = ii(-t, t);

    if (y < 0) ys = ii(-t, y + t);
    else if (y > 0) ys = ii(y - t, t);
    else ys = ii(-t, t);

    s.push_back(sq(xs, ys));
    //printf("(%d, %d) <-> (%d, %d)\n", xs.first, xs.second, ys.first, ys.second);
  }

  if (has_blank(t)) {
    //puts("true");
    return true;
  } else return false;
  //return has_blank(t);
}

int main() {
  int cs = 1;
  while (scanf("%d", &n) && n != -1) {
    v.clear();

    for (int i = 0; i < n; i ++) {
      int x, y;
      scanf("%d%d", &x, &y);
      v.push_back(ii(x, y));
    }

    int l = 0, r = 10000000;
    //int l = 0, r = 20;
    while (l < r) {
      int md = (l + r + 1) / 2;
      if (okay(md)) l = md;
      else r = md - 1;
    }

    if (l < 10000000) printf("Case %d: %d\n", cs ++, l + 1);
    else printf("Case %d: never\n", cs ++);
  }
}
