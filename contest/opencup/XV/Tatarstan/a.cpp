#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const double eps = 1e-8;
const double pi = acosl( -1. );
struct Pt{ double X , Y , Z; };
Pt operator^( const Pt& p1 , const Pt& p2 ){
  return { p1.Y * p2.Z - p1.Z * p2.Y ,
           p1.Z * p2.X - p1.X * p2.Z ,
           p1.X * p2.Y - p1.Y * p2.X };
}
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X ,
           p1.Y + p2.Y ,
           p1.Z + p2.Z };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X ,
           p1.Y - p2.Y ,
           p1.Z - p2.Z };
}
Pt operator*( const Pt& pp , double kk ){
  return { pp.X * kk ,
           pp.Y * kk ,
           pp.Z * kk };
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X +
         p1.Y * p2.Y +
         p1.Z * p2.Z;
}
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
double norm2( const Pt& pp ){
  return pp * pp;
}
void print( const Pt& pp ){
  printf( "(%.6f, %.6f, %.6f)\n" , pp.X , pp.Y , pp.Z );
}
double R , r;
double dist( const Pt& p1 , const Pt& p2 ){
  if( norm( p1 - p2 ) < eps ) return 0;
  double theta = acosl( max( -1. , min( 1. , (p1 * p2) / norm( p1 ) / norm( p2 ) ) ) );
  return theta * R;
}
inline Pt read(){
  double la , lo;
  cin >> la >> lo;
  la = (la / 180.) * pi;
  lo = (lo / 180.) * pi;
  return { (double)(cosl( lo ) * cosl( la )) ,
           (double)(sinl( lo ) * cosl( la )) ,
           (double)(sinl( la )) };
}
#define K 120
// min dist from po to line pa, pb
double min_dist( const Pt& pa , const Pt& pb , const Pt& po ){
  if( dist( pa , pb ) < eps ) return dist( pa , po );
  double bl = 0 , br = 1;
  for( int i = 0 ; i < K ; i ++ ){
    double mid1 = (bl + bl + br) / 3;
    double mid2 = (bl + br + br) / 3;
    Pt tmp = pa * mid1 + pb * (1. - mid1);
    tmp = tmp * (R / norm(tmp));
    double td1 = dist( tmp , po );
       tmp = pa * mid2 + pb * (1. - mid2);
    tmp = tmp * (R / norm(tmp));
    double td2 = dist( tmp , po );
    if( td1 < td2 ) br = mid2;
    else bl = mid1;
  }
  Pt tmp = pa * bl + pb * (1. - bl);
  tmp = tmp * (R / norm(tmp));
  return dist( tmp , po );
}

Pt a , b , o;
inline Pt perp( const Pt& pp ){
  if( fabs( pp.X ) > eps or fabs( pp.Y ) > eps )
    return { -pp.Y , pp.X , pp.Z };
  return { pp.X , -pp.Z , pp.Y };
}

double cir_dist( const vector<Pt>& v1 ,
                 const vector<Pt>& v2 ){
  double ret = (pi + pi) * R;
  double tlen = (v1[ 0 ] * o) / norm( o );
  Pt fake_ori = o * (tlen / norm(o));
  double real_r = norm(fake_ori - v1[ 0 ]);
  for( auto p1 : v1 )
    for( auto p2 : v2 ){
      double ne = ((p1 - fake_ori) * (p2 - fake_ori))
                  / norm(p1 - fake_ori)
                  / norm(p2 - fake_ori);
      double theta = acosl( max( -1. , min( 1. , ne ) ) );
      ret = min( ret , theta * real_r );
    }
  return ret;
}

Pt mirror( const Pt& pa , const Pt& pb , const Pt& pc ){
  Pt pl = pa ^ pb;
  pl = pl * (1. / norm(pl));
  double dst = fabs( (pl * pa) - (pl * pc) );
  if( pl * pc > pl * pa )
    return pc - pl * (dst + dst);
  else
    return pc + pl * (dst + dst);
}

double solve(){
  double td = dist( a , b );
  if( td < eps ) return td;
  if( fabs( td - pi * R ) < eps ) return td;
  if( min_dist( a , b , o ) > r - eps ) return td;
  Pt ro = perp( o );
  Pt rro = o ^ ro;
  double lp = 0;

  //ro = ro * (R / norm(ro));
  //rro = rro * (R / norm(rro));

  ro = a - o * ((a * o) / norm2(o));
  rro = o ^ ro;
  ro = ro * (R / norm(ro));
  rro = rro * (R / norm(rro));


  {
    double bl = 0 , br = 1;
    for( int i = 0 ; i < K ; i ++ ){
      double mid = (bl + br) * .5;
      Pt tmp = o * mid + ro * (1. - mid);
      tmp = tmp * (R / norm(tmp));
      if( dist( tmp , o ) > r ) bl = mid;
      else br = mid;
    }
    lp = bl;
  }

  Pt bst1 , bst2;
  double tbst1 = -1 , tbst2 = -1;
  for( int i = -1 ; i <= 1 ; i += 2 )
    for( int j = -1 ; j <= 1 ; j += 2 ){
      Pt p1 = ro * i;
      Pt p2 = rro * j;
      {
        double bl = 0 , br = 1;
        for( int _ = 0 ; _ < K ; _ ++ ){
          double bmid1 = (bl + bl + br) / 3;
          double bmid2 = (bl + br + br) / 3;
          double mnd1 , mnd2;
          {
            Pt cp = p1 * bmid1 + p2 * (1. - bmid1);
            cp = cp * (R / norm(cp));

            Pt rr = o * lp + cp * (1. - lp);
            rr = rr * (R / norm(rr));
            {
              mnd1 = min_dist( a , rr , o );
              mnd1 = min( mnd1 , min_dist( a , rr * -1 , o ) );
              mnd1 = min( mnd1 , min_dist( a * -1 , rr , o ) );
              mnd1 = min( mnd1 , min_dist( a * -1 , rr * -1 , o ) );
            }
          }
          {
            Pt cp = p1 * bmid2 + p2 * (1. - bmid2);
            cp = cp * (R / norm(cp));

            Pt rr = o * lp + cp * (1. - lp);
            rr = rr * (R / norm(rr));
            {
              mnd2 = min_dist( a , rr , o );
              mnd2 = min( mnd2 , min_dist( a , rr * -1 , o ) );
              mnd2 = min( mnd2 , min_dist( a * -1 , rr , o ) );
              mnd2 = min( mnd2 , min_dist( a * -1 , rr * -1 , o ) );
            }
          }
          if( mnd1 > mnd2 )
            br = bmid2;
          else
            bl = bmid1;
        }
        Pt cp = p1 * bl + p2 * (1. - bl);
        cp = cp * (R / norm(cp));

        Pt rr = o * lp + cp * (1. - lp);
        rr = rr * (R / norm(rr));
        double mnd;
        {
          mnd = min_dist( a , rr , o );
          mnd = min( mnd , min_dist( a , rr * -1 , o ) );
          mnd = min( mnd , min_dist( a * -1 , rr , o ) );
          mnd = min( mnd , min_dist( a * -1 , rr * -1 , o ) );
        }
        //printf( "%.12f " , mnd );
        //print( rr );
        if( mnd > tbst1 - eps ){
          tbst1 = mnd;
          bst1 = rr;
        }
      }
      //{
        //double bl = 0 , br = 1;
        //for( int _ = 0 ; _ < K ; _ ++ ){
          //double bmid1 = (bl + bl + br) / 3;
          //double bmid2 = (bl + br + br) / 3;
          //double mnd1 , mnd2;
          //{
            //Pt cp = p1 * bmid1 + p2 * (1. - bmid1);
            //cp = cp * (R / norm(cp));

            //Pt rr = o * lp + cp * (1. - lp);
            //rr = rr * (R / norm(rr));
            //{
              //mnd1 = min_dist( b , rr , o );
              //mnd1 = min( mnd1 , min_dist( b , rr * -1 , o ) );
              //mnd1 = min( mnd1 , min_dist( b * -1 , rr , o ) );
              //mnd1 = min( mnd1 , min_dist( b * -1 , rr * -1 , o ) );
            //}
          //}
          //{
            //Pt cp = p1 * bmid2 + p2 * (1. - bmid2);
            //cp = cp * (R / norm(cp));

            //Pt rr = o * lp + cp * (1. - lp);
            //rr = rr * (R / norm(rr));
            //{
              //mnd2 = min_dist( b , rr , o );
              //mnd2 = min( mnd2 , min_dist( b , rr * -1 , o ) );
              //mnd2 = min( mnd2 , min_dist( b * -1 , rr , o ) );
              //mnd2 = min( mnd2 , min_dist( b * -1 , rr * -1 , o ) );
            //}
          //}
          //if( mnd1 > mnd2 )
            //br = bmid2;
          //else
            //bl = bmid1;
        //}
        //Pt cp = p1 * bl + p2 * (1. - bl);
        //cp = cp * (R / norm(cp));

        //Pt rr = o * lp + cp * (1. - lp);
        //rr = rr * (R / norm(rr));
        //double mnd;
        //{
          //mnd = min_dist( b , rr , o );
          //mnd = min( mnd , min_dist( b , rr * -1 , o ) );
          //mnd = min( mnd , min_dist( b * -1 , rr , o ) );
          //mnd = min( mnd , min_dist( b * -1 , rr * -1 , o ) );
        //}
        //if( mnd > tbst2 - eps ){
          //tbst2 = mnd;
          //bst2 = rr;
        //}
      //}
    }


  ro = b - o * ((b * o) / norm2(o));
  rro = o ^ ro;
  ro = ro * (R / norm(ro));
  rro = rro * (R / norm(rro));

  for( int i = -1 ; i <= 1 ; i += 2 )
    for( int j = -1 ; j <= 1 ; j += 2 ){
      Pt p1 = ro * i;
      Pt p2 = rro * j;
      //{
        //double bl = 0 , br = 1;
        //for( int _ = 0 ; _ < K ; _ ++ ){
          //double bmid1 = (bl + bl + br) / 3;
          //double bmid2 = (bl + br + br) / 3;
          //double mnd1 , mnd2;
          //{
            //Pt cp = p1 * bmid1 + p2 * (1. - bmid1);
            //cp = cp * (R / norm(cp));

            //Pt rr = o * lp + cp * (1. - lp);
            //rr = rr * (R / norm(rr));
            //{
              //mnd1 = min_dist( a , rr , o );
              //mnd1 = min( mnd1 , min_dist( a , rr * -1 , o ) );
              //mnd1 = min( mnd1 , min_dist( a * -1 , rr , o ) );
              //mnd1 = min( mnd1 , min_dist( a * -1 , rr * -1 , o ) );
            //}
          //}
          //{
            //Pt cp = p1 * bmid2 + p2 * (1. - bmid2);
            //cp = cp * (R / norm(cp));

            //Pt rr = o * lp + cp * (1. - lp);
            //rr = rr * (R / norm(rr));
            //{
              //mnd2 = min_dist( a , rr , o );
              //mnd2 = min( mnd2 , min_dist( a , rr * -1 , o ) );
              //mnd2 = min( mnd2 , min_dist( a * -1 , rr , o ) );
              //mnd2 = min( mnd2 , min_dist( a * -1 , rr * -1 , o ) );
            //}
          //}
          //if( mnd1 > mnd2 )
            //br = bmid2;
          //else
            //bl = bmid1;
        //}
        //Pt cp = p1 * bl + p2 * (1. - bl);
        //cp = cp * (R / norm(cp));

        //Pt rr = o * lp + cp * (1. - lp);
        //rr = rr * (R / norm(rr));
        //double mnd;
        //{
          //mnd = min_dist( a , rr , o );
          //mnd = min( mnd , min_dist( a , rr * -1 , o ) );
          //mnd = min( mnd , min_dist( a * -1 , rr , o ) );
          //mnd = min( mnd , min_dist( a * -1 , rr * -1 , o ) );
        //}
        ////printf( "%.12f " , mnd );
        ////print( rr );
        //if( mnd > tbst1 - eps ){
          //tbst1 = mnd;
          //bst1 = rr;
        //}
      //}
      {
        double bl = 0 , br = 1;
        for( int _ = 0 ; _ < K ; _ ++ ){
          double bmid1 = (bl + bl + br) / 3;
          double bmid2 = (bl + br + br) / 3;
          double mnd1 , mnd2;
          {
            Pt cp = p1 * bmid1 + p2 * (1. - bmid1);
            cp = cp * (R / norm(cp));

            Pt rr = o * lp + cp * (1. - lp);
            rr = rr * (R / norm(rr));
            {
              mnd1 = min_dist( b , rr , o );
              mnd1 = min( mnd1 , min_dist( b , rr * -1 , o ) );
              mnd1 = min( mnd1 , min_dist( b * -1 , rr , o ) );
              mnd1 = min( mnd1 , min_dist( b * -1 , rr * -1 , o ) );
            }
          }
          {
            Pt cp = p1 * bmid2 + p2 * (1. - bmid2);
            cp = cp * (R / norm(cp));

            Pt rr = o * lp + cp * (1. - lp);
            rr = rr * (R / norm(rr));
            {
              mnd2 = min_dist( b , rr , o );
              mnd2 = min( mnd2 , min_dist( b , rr * -1 , o ) );
              mnd2 = min( mnd2 , min_dist( b * -1 , rr , o ) );
              mnd2 = min( mnd2 , min_dist( b * -1 , rr * -1 , o ) );
            }
          }
          if( mnd1 > mnd2 )
            br = bmid2;
          else
            bl = bmid1;
        }
        Pt cp = p1 * bl + p2 * (1. - bl);
        cp = cp * (R / norm(cp));

        Pt rr = o * lp + cp * (1. - lp);
        rr = rr * (R / norm(rr));
        double mnd;
        {
          mnd = min_dist( b , rr , o );
          mnd = min( mnd , min_dist( b , rr * -1 , o ) );
          mnd = min( mnd , min_dist( b * -1 , rr , o ) );
          mnd = min( mnd , min_dist( b * -1 , rr * -1 , o ) );
        }
        if( mnd > tbst2 - eps ){
          tbst2 = mnd;
          bst2 = rr;
        }
      }
    }


  return dist( a , bst1 ) + dist( b , bst2 ) +
    cir_dist( { bst1 , mirror( a , o , bst1 ) } ,
              { bst2 , mirror( b , o , bst2 ) } );
}

int main(){
  a = read();
  b = read();
  o = read();
  cin >> r >> R;
  a = a * R;
  b = b * R;
  o = o * R;
  //print( a );
  //print( b );
  //print( o );
  printf( "%.12f\n" , solve() );
}
