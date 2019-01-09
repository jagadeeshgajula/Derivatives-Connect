/*
 * buildCurveFromMarketRates.h
 *
 *  Created on: 31-Oct-2010
 *      Author: vishist
 */

#ifndef BUILDCURVEFROMMARKETRATES_H_
#define BUILDCURVEFROMMARKETRATES_H_

#include "boost/shared_ptr.hpp"
#include "curveBuilder.h"
#include <vector>
#include <string>
#include "date.h"
#include <map> 

namespace IRDConnect {

class Curve;
class Moneymkt;
class MMFuture;
class Swap ;
class SwapCouponEntry ;
class Date;
class CurveDef; 

 enum Dominance { none, cash, future } ;
class BuildCurveFromMarketRates : public CurveBuilder {
public:
   BuildCurveFromMarketRates(const Date &date ,Dominance curveDom,boost::shared_ptr<CurveDef> & curveDef, const std::map<std::string,double> & rates ) ;
	boost::shared_ptr <Curve>  build () ;
private:
	void loadCashTenors ( std::vector <boost::shared_ptr<Moneymkt> > & cashTenors );
	void loadFutureTenors ( std::vector <boost::shared_ptr<MMFuture> > & futureTenors );
	void loadSwapTenors ( std::vector <boost::shared_ptr<Swap> > &swapTenors );
	void genSwapCoupon ( std::vector <SwapCouponEntry> &couponList,const Curve * curve,
			                       boost::shared_ptr<Swap> swapPtr, const Date &curveEndDate ) ;
    double getRate( const std::string & instr_id ) ;
	Date curveDate_ ;
    Dominance curveDominance_;
	boost::shared_ptr<CurveDef> curveDef_ ;
	std::map<std::string,double> rates_ ; 
};

}

#endif /* BUILDCURVEFROMMARKETRATES_H_ */
