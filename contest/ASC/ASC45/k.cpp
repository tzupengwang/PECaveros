#include<bits/stdc++.h>
using namespace std;

#define PB push_back
#define _x first
#define _y second

const int MXL = 5000;
const double EPS = 1e-9;
const double eps = 1e-9;

typedef pair<double, double> pdd;
typedef pair<pdd, pdd> Line;
typedef double D;

pdd operator + (const pdd p1, const pdd p2){
	return pdd(p1._x + p2._x, p1._y + p2._y);
}
pdd operator - (const pdd p1, const pdd p2){
	return pdd(p1._x - p2._x, p1._y - p2._y);
}
pdd operator * (const double c, const pdd p){
	return pdd(p._x * c, p._y * c);
}
double operator % (const pdd p1, const pdd p2){
	return p1._x * p2._y - p2._x * p1._y;
}
double operator * ( const pdd p1 , const pdd p2 ){
  return p1._x * p2._x + p1._y * p2._y;
}

vector<Line> lnlst;
double atn[MXL];

bool lncmp(int l1, int l2){
	return atn[l1] < atn[l2];	
}

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2){
	double f1 = (p2 - p1) % (q1 - p1);
	double f2 = (p2 - p1) % (p1 - q2);
	double f = (f1 + f2);

	if(fabs(f) < EPS) return pdd(nan(""), nan(""));

	return (f2 / f) * q1 + (f1 / f) * q2;
}

deque<Line> dq;

void halfPlaneInter(){
  dq.clear();
	int n = lnlst.size();
	vector<int> stlst;
	for(int i=0; i<n; i++){
		stlst.PB(i);
		pdd d = lnlst[i].second - lnlst[i].first;
		atn[i] = atan2(d._y, d._x);
	}
	sort(stlst.begin(), stlst.end(), lncmp);
	vector<Line> lst;

	for(int i=0; i<n; i++){
		if(i) {
			int j = i-1;
			Line li = lnlst[stlst[i]];
			Line lj = lnlst[stlst[j]];
			pdd di = li.second - li.first;
			pdd dj = lj.second - lj.first;
			if(fabs(di%dj) < EPS){
				if(di % (lj.second - li.second) < 0) {
					lst.pop_back();
				}else continue;
			}
		}
		lst.PB(lnlst[stlst[i]]);
	}

	dq.PB(lst[0]);
	dq.PB(lst[1]);
	for(int i=2; i<n; i++){
		int dsz = dq.size();
		Line l = lst[i];
		while(dsz >= 2){
			Line l1 = dq[dsz-1];
			Line l2 = dq[dsz-2];

			pdd it12 = interPnt(l1.first, l1.second, l2.first, l2.second);

			if((l.second - l.first) % (it12 - l.first) < 0){
				dq.pop_back();
				dsz --;
			} else break;
		}

		while(dsz >= 2){
			Line l1 = dq[0];
			Line l2 = dq[1];

			pdd it12 = interPnt(l1.first, l1.second, l2.first, l2.second);

			if((l.second - l.first) % (it12 - l.first) < 0){
				dq.pop_front();
				dsz --;
			} else break;
		}

		Line l1 = dq[dsz - 1];
		if(!std::isnan(interPnt(l.first, l.second, l1.first,  l1.second)._x)){
			dq.PB(l);
		}

	}

	int dsz = dq.size();
	while(dsz >= 2){
		Line l1 = dq[dsz - 1];
		Line l2 = dq[dsz - 2];
		Line l = dq[0];
		pdd it12 = interPnt(l1.first, l1.second, l2.first, l2.second);
		if(std::isnan(it12._x)) {
			dq.pop_back();
			dq.pop_back();
			dsz -= 2;
		} else if((l.second - l.first) % (it12 - l.first) < 0){
			dq.pop_back();
			dsz --;
		} else break;
	}
}

int n;
pdd p[ 222 ] , ap[ 2 ];
inline void init(){
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lf%lf" , &p[ i ]._x , &p[ i ]._y );
}
inline bool okay( double r ){
  lnlst.clear();
	for( int i = 0 ; i < n ; i ++ ){
    pdd l1 = p[ ( i + 1 ) % n ] - p[ i ];
    pdd n1 = { -l1._y , l1._x };
    D len1 = sqrt( n1 * n1 );
    n1 = ( r / len1 ) * n1;
    lnlst.PB( { p[ i ] + n1 , p[ ( i + 1 ) % n ] + n1 } );
	}
 
	halfPlaneInter();

	int dsz = dq.size();
  if( dsz < 3 ) return false;
  vector< pdd > posp;
	for(int i=0; i<dsz; i++){
		int j = (i+1) % dsz;
		pdd it = interPnt(dq[i].first, dq[i].second, dq[j].first, dq[j].second);
    posp.push_back( it );
	}
  // printf( "%.12f\n" , r );
  // for( auto it : posp )
    // printf( "%.6f %.6f\n" , it.first , it.second );
  for( size_t i = 0 ; i < posp.size() ; i ++ )
    for( size_t j = i + 1 ; j < posp.size() ; j ++ ){
      D len = sqrt( ( posp[ i ] - posp[ j ] ) *
                    ( posp[ i ] - posp[ j ] ) );
      if( len + eps > r + r ){
        ap[ 0 ] = posp[ i ];
        ap[ 1 ] = posp[ j ];
        return true;
      }
    }
  return false;
}
inline void solve(){
  D l = 0.0 , r = 1e5 , mid , ans = 0.0;
  for( int i = 0 ; i < 50 ; i ++ ){
    mid = ( l + r ) * 0.5;
    if( okay( mid ) ) ans = mid , l = mid;
    else r = mid;
  }
  printf( "%.12f\n" , ans );
  for( int i = 0 ; i < 2 ; i ++ )
    printf( "%.12f %.12f\n" , ap[ i ]._x , ap[ i ]._y );
}
int main(){
  freopen( "kabbalah.in" , "r" , stdin );
  freopen( "kabbalah.out" , "w" , stdout );
  while( scanf( "%d" , &n ) == 1 ){
    if( n == 0 ) break;
    init();
    solve();
  }
}

