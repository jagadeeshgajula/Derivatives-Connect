#ifndef BISECTION_H_
#define BISECTION_H_
namespace IRDConnect { 
  template<typename F, int MAX_ITERATION=100> 
class Bisection {

public:
	Bisection ( const double & x1 , const double & x2 , F & f, const double & instrDcf)
	: x1_ ( x1 ) , x2_ ( x2) , f_(f), instrDcf_(instrDcf){}

	double operator() () {

		double y1 = 1.0;
		double y2 = 1.0;
		double widenFactor;
		double zcr;

		// find bisection bracket
		int idx ;
		for ( idx = 1; idx <= MAX_ITERATION; idx++ ) {
			// determine initial zcdfs and PVs.
			// instrument zcdf used as seed, coupon zcdf will be interpolated.

			y1 = f_( x1_ );
			y2 = f_( x2_);


	/*		cout <<  "Bisecb " << setprecision( 4 ) << idx << ": " <<
					            setprecision( 10 ) << lowerZcdf_ << ", " <<
					            setprecision( 10 ) << lowerPV << ", " <<
					            setprecision( 10 ) << upperZcdf_ << ", " <<
					            setprecision( 10 ) << upperPV << endl; */
			if ( y1 * y2 < 0.0 )
				break;

			zcr = - log( x1_ ) / instrDcf_;
			widenFactor = exp( zcr * 5.0 / 360.0 );
			x2_ *= widenFactor ;
			x1_ /= widenFactor ;
			if ( x2_ > 1.0 )
				x2_ = 1.0 ;

		}

		cout <<  "Bisec " << setprecision( 4 ) << 0 << ": " <<
		            setprecision( 10 ) << x1_ << ", " <<
		            setprecision( 10 ) << y1 << ", " <<
		            setprecision( 10 ) << x2_ << ", " <<
		            setprecision( 10 ) << y2 << endl;

		    if ( y1 * y2 < 0.0 ) {
		        // bisection iteration loop
		        for ( idx = 1; idx <= MAX_ITERATION; idx++ ) {
		            double mid_x = ( x1_ + x2_ ) / 2.0;

		            double mid_y = f_ ( mid_x );

		            double change_x = x2_ - mid_x ;

		            cout << "BISEC " <<  setprecision( 4 ) << idx << ": " <<
		                    setprecision( 10 ) << mid_x << ", " <<
		                    setprecision( 10 ) << mid_y << ", " <<
		                    setprecision( 10 ) << change_x << endl ;

		            // exit condition
		            if ( fabs( change_x ) < MIN_ACCURACY || mid_y == 0.0 )
		                return mid_x ;

		            if ( mid_y * y1 < 0.0 )
		                x2_ = mid_x;
		            else
		                x1_ = mid_x;
		        }
		    }

         return 0 ;

	}

private :
	static const double MIN_ACCURACY = 0.0000000001 ;
//	static const int MAX_ITERATION = 100 ;
	double x1_ ;
	double x2_ ;
	F & f_ ;
        double instrDcf_ ; 
//	SwapCouponEntry sce_ ;
};
     
}
#endif 
