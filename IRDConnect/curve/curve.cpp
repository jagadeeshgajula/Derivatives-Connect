/*
 * curve.cpp
 *
 *  Created on: 24-Oct-2010
 *      Author: vishist
 */
#include "curve.h"
#include "date.h"
#include <fstream>
#include <iomanip>

namespace IRDConnect {
typedef std::pair<Date, double> CurvePoint ;
class CurvePointCompare {
public:
	bool operator () ( const CurvePoint & l , const CurvePoint & r )
	{
		return l.first < r.first ;
	}
	bool operator () ( const CurvePoint::first_type &k , const CurvePoint & r )
	{
		return k < r.first ;
	}
	bool operator () ( const CurvePoint & l , const CurvePoint::first_type &k  )
	{
		return l.first < k ;
	}
};

Curve::Curve ( const Date & refDate):
		refDate_(refDate) ,curvePoints_ () {

	interpolator_ = new LinearInterpByZcr (refDate_,curvePoints_) ;
}

Curve::Curve ( const Date & refDate, const std::vector<Date> & dates,const std::vector<double>  &zcdfs):
		refDate_(refDate)  {
	for ( size_t s=0; s<dates.size(); s++) {
			curvePoints_.push_back(make_pair(dates[s], zcdfs[s])) ;
	}
	std::sort(curvePoints_.begin(),curvePoints_.end(),CurvePointCompare()) ;
interpolator_ = new LinearInterpByZcr (refDate_,curvePoints_) ;
}

Curve::~Curve ()
{
	delete interpolator_ ;
	interpolator_ = 0 ;
}
double Curve::getZcdf ( const Date & d ) const
{
	return (*interpolator_) (d) ;
}

double Curve::getForwardRate ( const Date & indexStart, const Date & indexEnd , double dcf ) 
{
	logFile << indexStart << " : " << getZcdf ( indexStart ) << " : " << indexEnd << " : " << getZcdf ( indexEnd ) << endl;

  return ( ( getZcdf ( indexStart ) / getZcdf ( indexEnd ) - 1 ) / dcf ) ;
}


void Curve::addCurvePoint ( const Date & date, double zcdf )
{
//	cout << "CP : " << date << " ZCDF : " << setprecision(15) << zcdf << endl ;
	delete interpolator_ ;
	CurvePointCompare cpCompare ;
	if ( curvePoints_.empty() || cpCompare(curvePoints_[curvePoints_.size()-1] , date ) )
	    curvePoints_.push_back(make_pair(date,zcdf)) ;
	else
	{
		typedef  std::vector<CurvePoint>::iterator CPIter ;
		std::pair<CPIter,CPIter>  p = equal_range(curvePoints_.begin(),curvePoints_.end(),date,cpCompare);
		if ( p.first == p.second  )
		    curvePoints_.insert( p.first, make_pair(date,zcdf));
	}

	interpolator_ = new LinearInterpByZcr (refDate_,curvePoints_) ;

}
void Curve::removeCurvePoint ( const Date &date ) {


	typedef std::vector<CurvePoint>::iterator CPIter ;
	std::pair<CPIter,CPIter>  p = equal_range(curvePoints_.begin(),curvePoints_.end(),date,CurvePointCompare());
	if ( p.first != p.second  )
		curvePoints_.erase( p.first, p.second);
	delete interpolator_ ;
	interpolator_ = new LinearInterpByZcr (refDate_,curvePoints_) ;

}
void Curve::removeCurvePointsGtDate ( const Date &date ) {


	typedef std::vector<CurvePoint>::iterator CPIter ;
	CPIter p = upper_bound(curvePoints_.begin(),curvePoints_.end(),date,CurvePointCompare());
	
        curvePoints_.erase( p, curvePoints_.end());
	delete interpolator_ ;
	interpolator_ = new LinearInterpByZcr (refDate_,curvePoints_) ;

}


void Curve::print ()
{
	const std::vector<std::pair<Date, double> > & dates = interpolator_->getPoints () ;
	Date d = dates[0].first ;
	std::ofstream fout ( "/home/vishist/test.out");
	double z = 2;
	   for ( ;d <= dates[dates.size()-1].first ; d++ )
	   {
		   double z1 = getZcdf (d) ;
		//   if (z1 >= z )
		//	   std::cout << "ERROR" << d << "," << z <<"," <<z1 << std::endl ;
		   z = z1 ;
		   fout << d.serialNumber()  << " Date = " << d
				<< std::setprecision(15) << " ZCDF = " <<  z1 << std::endl  ;
	   }

	   std::ofstream fout1 ( "/home/vishist/testz.out");

	   std::vector<std::pair<Date, double> >::const_iterator it = dates.begin () ;
	   for ( ; it != dates.end() ; it++ )
	   {
		   fout1 << (*it).first.serialNumber()  << " Date = " << (*it).first
		   				<< std::setprecision(15) << " ZCDF = " <<  getZcdf((*it).first)  << std::endl  ;
	   }

	 /*  std::ofstream fout2 ( "/home/vishist/testzn.out");

	   	   std::vector<Date>::const_iterator it1 = dates_.begin () ;
	   	   for ( ; it1 != dates_.end() ; it1++ )
	   	   {
	   		   fout2 << (*it1).serialNumber()  << " Date = " << (*it1)
	   		   				<< std::setprecision(15) << " ZCDF = " <<  getZcdf(*it1)  << std::endl  ;
	   	   } */
}
}
