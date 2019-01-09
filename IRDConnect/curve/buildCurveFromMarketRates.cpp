#include "buildCurveFromMarketRates.h"
#include "date.h"
#include <fstream>
#include "curve.h"
#include "moneymkt.h"
#include "mmfuture.h"
#include "calendarUtil.h"
//#include "instrumentTypeCd.h"
#include "swap.h"
#include <iomanip>
#include "marchingConv.h"
#include <algorithm>
#include <fstream>
#include "secant.h"
#include "bisection.h"
#include "curveDef.h"
namespace IRDConnect {

  class SwapCouponEntry {
  public:
    SwapCouponEntry (const Date & startDate , const Date & endDate , const Date & instrEndDate,
		     double fixedCouponDcf ,double floatCouponDcf, double instrDcf,
		     double indexStartZcdf ,
		     double indexEndZcdf, double couponZcdf , bool unknownCoupon ) :
      startDate_ ( startDate ),
      endDate_ ( endDate ) ,
      instrEndDate_ ( instrEndDate),
      fixedCouponDcf_ ( fixedCouponDcf),
      floatCouponDcf_ ( floatCouponDcf),
      instrDcf_ ( instrDcf),
      indexStartZcdf_ ( indexStartZcdf ),
      indexEndZcdf_ ( indexEndZcdf),
      couponZcdf_  ( couponZcdf),
      unknownCoupon_ ( unknownCoupon) {
    }
    Date startDate_ ;
    Date endDate_ ;
    Date instrEndDate_ ;
    double fixedCouponDcf_ ;
    double floatCouponDcf_ ;
    double instrDcf_ ;
    double indexStartZcdf_ ;
    double indexEndZcdf_ ;
    double couponZcdf_ ;
    bool unknownCoupon_ ;

    double fixedPV ( double swapRate  ) const    {
      return swapRate * fixedCouponDcf_ * couponZcdf_ ;
    }

    double floatPV ( ) const {
      double rate = ( indexStartZcdf_ / indexEndZcdf_ - 1 )/ instrDcf_  ;
      return ( rate * floatCouponDcf_ * couponZcdf_  ) ;
    }
    void print () {
      	cout << setprecision(10) << "Coupon Start : "
		<< "Coupon End : "
		<< "Instr End : "
		<< "Fix Coupon Dcf : "
		<< "Float Coupon Dcf : "
		<< "Instr Dcf  : "
		<< "Start Zcdf : "
		<< "End Zcdf : "
		<< "Coupon Zcdf : "
		<< "Unknown Coupon : "
		<< endl ;

      cout << setprecision(16)  << startDate_
	   << " : "   << endDate_
	   << " : " << instrEndDate_
	   << " : "   << fixedCouponDcf_
	   << " : "   << floatCouponDcf_
	   << " : "   << instrDcf_
	   << " : "   << indexStartZcdf_
	   << " : "     << indexEndZcdf_
	   << " : "  << couponZcdf_
	   << " : " << unknownCoupon_ ;


     if (!unknownCoupon_)
		cout << " : " << (( indexStartZcdf_/indexEndZcdf_ - 1 ) / instrDcf_) ;  // RAM commented this
    else
		cout << " : " << 0 ;

   cout 		 << endl ;

      /*	cout << setprecision(10) << "Coupon Start : "  << startDate_
		<< " : Coupon End : "   << endDate_
		<< " : Instr End : " << instrEndDate_
		<< " : Fix Coupon Dcf : "   << fixedCouponDcf_
		<< " : Float Coupon Dcf : "   << floatCouponDcf_
		<< " : Instr Dcf  : "   << instrDcf_
		<< " : Start Zcdf : "   << indexStartZcdf_
		<< " : End Zcdf : "     << indexEndZcdf_
		<< " : Coupon Zcdf : "  << couponZcdf_
		<< " : Unknown Coupon : " << unknownCoupon_
		<< endl ; */
    }
  };
  class pvYtm {
  private :
    double partialPv_ ;
    SwapCouponEntry  sce_ ;
    Date lastTenorDate_ ;
    double lastTenorZcdf_ ;
    double ytm_ ;
    Date refDate_ ;
  public :
    pvYtm ( double partialPv,  const SwapCouponEntry & sce,
	    const Date & lastTenorDate, const double & lastTenorZcdf,
	    const double & ytm, const Date & refDate )
      : partialPv_ ( partialPv ),sce_(sce),lastTenorDate_(lastTenorDate),
	lastTenorZcdf_(lastTenorZcdf), ytm_(ytm ), refDate_ ( refDate) {}
    double operator () ( double zcdf ) {
      boost::shared_ptr<Curve>  tmpCurve ( new Curve ( refDate_)) ;
      tmpCurve->addCurvePoint(lastTenorDate_, lastTenorZcdf_) ;
      if ( sce_.instrEndDate_ > sce_.endDate_ )
	{
	  tmpCurve->addCurvePoint(sce_.instrEndDate_, zcdf) ;
	  sce_.couponZcdf_ = tmpCurve->getZcdf (sce_.endDate_) ;
	  sce_.indexEndZcdf_ = zcdf ;
	}
      else
	{
	  tmpCurve->addCurvePoint(sce_.endDate_, zcdf) ;
	  sce_.indexEndZcdf_ = tmpCurve->getZcdf (sce_.instrEndDate_) ;
	  sce_.couponZcdf_ = zcdf ;
	}
      /*     cout << "SCE : " << setprecision (10 )
	     << lastTenorDate_  << " : "
	     << sce_.instrEndDate_  << " : "
	     << lastTenorZcdf_ << " : "
	     << zcdf << " : "
	     << sce_.couponZcdf_  << " : "
	     << sce_.indexEndZcdf_ << endl  ; */
      /* if ( sce_.instrEndDate_ > sce_.endDate_ )
	 {
	 sce_.indexEndZcdf_ =  zcdf ;

	 std::vector<Date> dates ;
	 std::vector<double> zcdfs ;
	 dates.push_back ( sce_.startDate_ ) ;
	 dates.push_back ( sce_.instrEndDate_   ) ;
	 zcdfs.push_back ( sce_.indexStartZcdf_ ) ;
	 zcdfs.push_back ( zcdf ) ;
	 }*/

      return ( partialPv_ + sce_.fixedPV(ytm_) - sce_.floatPV() ) ;
    }
  };

  BuildCurveFromMarketRates::BuildCurveFromMarketRates(const Date &date,
						       Dominance curveDom ,
                                                      boost::shared_ptr<CurveDef> &curveDef, 
                                                       const std::map<std::string, double> &rates ) : 
    curveDate_ ( date ) , curveDominance_(curveDom),curveDef_(curveDef),rates_(rates) {

    // curveDef_ = boost::shared_ptr<CurveDef> ( new CurveDef ( "/home/vishist/indir/gbp.xml"));
  }

  void BuildCurveFromMarketRates::genSwapCoupon ( std::vector <SwapCouponEntry> &couponList, const Curve * curve,
						  boost::shared_ptr<Swap> swapPtr, const Date &curveEndDate )  {
    Date curveDate = curve->getRefDate () ;
    std::list<Date> cDates = swapPtr->generateSchedule ( curveDate ) ;
    std::list<Date>::const_iterator iterEvent = cDates.begin () ;
    std::list<Date>::const_iterator iterEnd = cDates.end () ;

    if ( iterEvent != iterEnd ) {
      Date prevCouponDate = *iterEvent ;
      double prevZcdf = curve->getZcdf ( prevCouponDate ) ;
      iterEvent++ ;
      const DayCountConv * dcc = swapPtr->getDayCountConv() ;
      const DayCountConv * instrDcc = swapPtr->getInstrDayCountConv() ;
      for ( ; iterEvent != iterEnd ; iterEvent++ ) {
	Date couponDate = *iterEvent ;
	double fixDcf = dcc->getFraction(prevCouponDate,couponDate) ;
	double floatDcf = instrDcc->getFraction(prevCouponDate,couponDate) ;
	Date instrEndDate = swapPtr->getInstrEndDate ( prevCouponDate ) ;
	double instrDcf = instrDcc->getFraction(prevCouponDate,instrEndDate) ;

	double couponZcdf = 0.0 ;
	bool unknownCoupon = false ;
	if ( couponDate <= ( curveEndDate + 14  )  )
	  couponZcdf = curve->getZcdf ( couponDate ) ;

	if ( couponDate > curveEndDate || instrEndDate > curveEndDate )
	  unknownCoupon = true;

	double instrEndZcdf = 0.0 ;
	if ( instrEndDate <= ( curveEndDate + 14 ) )
	  instrEndZcdf = curve->getZcdf ( instrEndDate ) ;

	couponList.push_back ( SwapCouponEntry ( prevCouponDate, couponDate,instrEndDate,fixDcf,floatDcf,instrDcf,prevZcdf,instrEndZcdf,couponZcdf,unknownCoupon)) ;
	prevCouponDate = couponDate ;
	prevZcdf = couponZcdf ;
      }
    }
  }
  double BuildCurveFromMarketRates::getRate (const std::string & instr_id )
  {
    std::map<std::string,double>::const_iterator it ;  
    it=rates_.find(instr_id);
    if ( it == rates_.end() )
      throw std::string("Invalid Quote " + instr_id); 

    return it->second ;
  }
     
  boost::shared_ptr <Curve> BuildCurveFromMarketRates::build ()
  {

    typedef boost::shared_ptr<Moneymkt> MoneymktPtr ;
    const std::vector < MoneymktPtr > & cashTenors = curveDef_->getCashTenors() ;

    Curve * curve  = new Curve (curveDate_);
    curve->addCurvePoint ( curveDate_ , 1.0 ) ;
    typedef std::vector < MoneymktPtr >::const_iterator cashTenors_Iter ;

    for ( cashTenors_Iter  iter = cashTenors.begin() ; iter != cashTenors.end () ; ++iter ) {
      //		cout << "CASHDATE = " << (*iter)->getMaturityDate ( refDate )
      //				<< "," << std::setprecision(15) << 1/ ( (*iter)->getFwdAmount ( refDate,1)) << endl ;
      double settleZcdf = curve->getZcdf( (*iter)->getSettlementDate ( curveDate_) ) ;
      if ( iter == cashTenors.begin()) {
	settleZcdf = 1 ;
	//   curve->addCurvePoint( (*iter)->getMaturityDate ( curveDate_ ), 0.999980620265 );
      }
      curve->addCurvePoint( (*iter)->getMaturityDate ( curveDate_ ), settleZcdf / ( (*iter)->getFwdAmount ( curveDate_,getRate((*iter)->getId()) ) ));
    }

    typedef boost::shared_ptr<MMFuture> MMFuturePtr ;
    const std::vector < MMFuturePtr > & futureTenors = curveDef_->getFutureTenors() ;
    typedef std::vector < MMFuturePtr >::const_iterator futureTenors_Iter ;

    Date cEndDate = curve->getCurveEndDate() ;

    if ( futureTenors.begin() != futureTenors.end () ) {
      Date firstFutDate = (*futureTenors.begin())->getExpiryDate ( ) ;
      //cout << firstFutDate << endl ; // NO NEED TO PRINT THIS - RAM
      if ( curveDominance_ == none || curveDominance_ == future )
	curve->addCurvePoint( firstFutDate, curve->getZcdf( firstFutDate ) );
      //  if ( curveDominance_ == future )
      //	  curve->removeCurvePointsGtDate ( firstFutDate ) ;

    }
    for ( futureTenors_Iter  iter = futureTenors.begin() ; iter != futureTenors.end () ; ++iter ) {
      //		cout << "CASHDATE = " << (*iter)->getMaturityDate ( refDate )
      //				<< "," << std::setprecision(15) << 1/ ( (*iter)->getFwdAmount ( refDate,1)) << endl ;
      Date settleDate = (*iter)->getExpiryDate ( ) ;
      curve->addCurvePoint( (*iter)->getEndDate ( ), curve->getZcdf( settleDate ) / ( (*iter)->getFwdPrice ( settleDate,getRate((*iter)->getId()) )) );
    }

    typedef boost::shared_ptr<Swap> SwapPtr ;
    const std::vector < SwapPtr > & swapInstr = curveDef_->getSwapTenors() ;

    SwapPtr prevSwapPt ;
    double prevSwapRate ; 
    for ( size_t i=0; i<swapInstr.size(); i++ ) {
      SwapPtr swapPt = swapInstr[i] ;

      
      double swapRate = getRate( swapPt->getId()) ;
      const double swapRate_p = swapRate ; 
      typedef std::vector <SwapCouponEntry> CouponList ;
      typedef CouponList::iterator CouponList_iter ;
      CouponList couponList ;
      Date curveEndDate = curve->getCurveEndDate() ;
      genSwapCoupon ( couponList, curve ,swapPt,curveEndDate ) ;

      /* DEBUG INFO - NOT NEEDED TO PRINT
      std::string tenor ("GBPLIBORSWAP_11Y");

      if ( swapPt->getId()== tenor )
      {
    	  std::for_each ( couponList.begin() , couponList.end() , mem_fun_ref(&SwapCouponEntry::print)) ;
      }

       */

      double fixedPv = 0 ;
      double floatPv = 0 ;


      for ( CouponList_iter iter = couponList.begin () ; iter != couponList.end() ; iter++  )	{
	if ( iter->unknownCoupon_)  {
	  double couponZcdf ;
	  if ( iter->endDate_ > curveEndDate && iter->endDate_ <= (curveEndDate + 14 ) )
	    couponZcdf = curve->getZcdf ( iter->endDate_) ;
	  else {
	    if ( i> 0 ) {
	      swapRate = LinearlyInterpolate (prevSwapPt->getTerminationDate (), swapPt->getTerminationDate (),
					      prevSwapRate, swapRate_p, iter->endDate_  ) ;
/*

	      if ( swapPt->getId()== tenor)
	    	  cout << setprecision(15) << "SWAP RATE " << swapRate
	    	        << "," << prevSwapPt->getTerminationDate ()
	    	       << "," << swapPt->getTerminationDate () << "," << prevSwapRate << "," << swapRate_p
	    	       << "," <<iter->endDate_ << endl ;
					      //  prevSwapPt->getSwapRate(), swapPt->getSwapRate(), iter->endDate_  ) ;
	   // NO NEED TO PRINT - RAM

	    */
	    }    // i> 0


	    double floatDcfRatio = iter->floatCouponDcf_ / iter->instrDcf_;
	    couponZcdf = ( iter->indexStartZcdf_  * floatDcfRatio - (fixedPv * swapRate) + floatPv ) /
	      ( floatDcfRatio + swapRate * iter->fixedCouponDcf_ );
	  }

	  iter->unknownCoupon_ = false ;
	  iter->indexEndZcdf_ = couponZcdf;
	  iter->couponZcdf_ = couponZcdf ;

	  if ( iter->endDate_ == iter->instrEndDate_ ) {
	    curve->addCurvePoint (iter->endDate_,couponZcdf );
	    //if ( swapPt->getId()== tenor)
	    	//    std::for_each ( couponList.begin() , couponList.end() , mem_fun_ref(&SwapCouponEntry::print)) ;
	  }
	  else {
	    curveEndDate = curve->getCurveEndDate() ;
	    curve->addCurvePoint(iter->endDate_,couponZcdf)  ;
	    //  cout << "INTERP " << iter->endDate_ << iter->instrEndDate_ << setprecision(20 ) << fixedPv * swapRate - floatPv  << endl ;
	    iter->indexEndZcdf_ = curve->getZcdf(iter->instrEndDate_) ;
	    pvYtm pvy ( fixedPv * swapRate - floatPv, *iter,curveEndDate, curve->getZcdf(curveEndDate),swapRate,curveDate_) ;
	     Secant<pvYtm,30> sec ( couponZcdf, iter->indexEndZcdf_, pvy ) ;
	    // Bisection<pvYtm> sec (  iter->indexEndZcdf_, couponZcdf,pvy,iter->instrDcf_ ) ;
	    double z = sec () ;
	    curve->removeCurvePoint(iter->endDate_);
	    curve->addCurvePoint ( iter->instrEndDate_,z) ;
	    iter->couponZcdf_ = curve->getZcdf (iter->endDate_) ;
	    iter->indexEndZcdf_ = z ;
	  //  if ( swapPt->getId()== tenor)
	    //std::for_each ( couponList.begin() , couponList.end() , mem_fun_ref(&SwapCouponEntry::print)) ;
	  }
	  if ( iter+1 != couponList.end())
	    (iter+1)->indexStartZcdf_ = iter->couponZcdf_ ;
	}   // unknown coupon
	fixedPv += iter->fixedPV(1.0) ;
	floatPv += iter->floatPV() ;
      }  // coupon list

      prevSwapPt = swapPt ;
      prevSwapRate = swapRate_p ;
    }   /// swap instr

    //    for ( size_t s =0; s< dates.size(); s++)
    //    	cout << s << "," << dates [s] << "," << zcdfs[s]  << endl ;
    return boost::shared_ptr<Curve>(curve ) ;
  }
}
