#ifndef SECANT_H_
#define SECANT_H_
namespace IRDConnect { 
  template<typename F, int MAX_ITERATION=30>
  class Secant {

  public:
	Secant ( const double & x1 , const double & x2 , F & f)
	: x1_ ( x1 ) , x2_ ( x2) , f_(f){}

	double operator() () {
            double y1 = f_ ( x1_ ) ;
            double y2 = f_ ( x2_ ) ;

           // cout << x1_ << ", " << x2_  << ", " << y1 << ", " << y2 << endl << endl ;

            if ( fabs( y1 ) < fabs( y2 ) ) {
        	double xtemp = x1_ ;
        	x1_ = x2_ ;
        	x2_ = xtemp ;
		double yTemp = y1;
		y1 = y2;
		y2 = yTemp;
            }

    	    for ( int idx = 1; idx <= MAX_ITERATION; idx++ ) {

    		if ( fabs( y2 - y1 ) < MIN_ACCURACY )
    			break;

    		double change = ( x1_ - x2_ ) * y2 / ( y2 - y1 );
    	//	cout << "ALL" << x1_ << ", " << x2_  << ", " << y1 << ", " << y2 << "," << change << endl ;
    		x1_ = x2_;
    		y1 = y2;
    		x2_ += change;
    		y2 = f_( x2_ );

    		if ( fabs( change ) < MIN_ACCURACY || y2 == 0.0 )
    			break;
    	}
    //    cout << "Y1 = " << y1 << "Y2 = " << y2 << endl ;

    	return x2_;
	  
	  //	  return 0;
	}

private :
  	static const double MIN_ACCURACY = 0.0000000001 ;
  //	static const int MAX_ITERATION = 30 ;
	double x1_ ;
	double x2_ ;
	F & f_ ;
};
     
}
#endif 
