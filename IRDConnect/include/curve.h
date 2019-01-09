/*
 * curve.h
 *
 *  Created on: 24-Oct-2010
 *      Author: vishist
 */

#ifndef CURVE_H_
#define CURVE_H_
//#include "LinearInterpolation.h"
#include "curveInterp.h"

namespace IRDConnect {

class Date ;
class Curve {

public :
	Curve ( const Date & refDate ) ;
	Curve ( const Date & refDate , const std::vector<Date> & dates,const std::vector<double>  &zcdfs) ;
	double getZcdf ( const Date & ) const;
        double getForwardRate ( const Date & indexStart, const Date & indexEnd, double dcf ) ; 
	void addCurvePoint ( const Date & date, double zcdf );
	void removeCurvePoint ( const Date &date ) ;
	void removeCurvePointsGtDate ( const Date &date ) ;
	const Date & getCurveEndDate ( ) { return curvePoints_[curvePoints_.size() -1].first; };
	~Curve () ;
	void print () ;
	const Date & getRefDate () const { return refDate_ ; }  ;

private :
	Date refDate_ ;
	//std::vector<Date> dates_ ;
	//std::vector<double> zcdfs_ ;
	std::vector<std::pair<Date,double> > curvePoints_ ;
	CurveInterp * interpolator_ ;


	// LinearInterpolation<Date,double> interpolator_ ;
};
}

#endif /* CURVE_H_ */
