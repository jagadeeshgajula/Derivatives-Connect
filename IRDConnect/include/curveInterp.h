/*
 * curveInterp.h
 *
 *  Created on: 24-Oct-2010
 *      Author: vishist
 */

#ifndef CURVEINTERP_H_
#define CURVEINTERP_H_
#include "LinearInterpolation.h"
#include "date.h"
#include "dayCountConv.h"
#include <cmath>
#include <algorithm>

namespace IRDConnect {
	class CurveInterp {
	public :
		virtual ~CurveInterp () {} ;
		virtual double operator () (const Date & d ) = 0 ;
		virtual const std::vector<std::pair<Date,double> >  getPoints () =0 ;

	/*	virtual const std::vector<Date>  getDates () = 0 ;
		virtual std::vector<double>  getZcdfs ()
		{
			std::vector<double> dblvec ;
			return  dblvec;
		}
		virtual std::vector<double>  getZcrs ()
				{
					std::vector<double> dblvec ;
					return  dblvec;
				} */
	};

	class LinearInterpByZcdf : public CurveInterp {
	private :
			typedef std::vector<Date>::const_iterator XI ;
		    typedef std::vector<double>::const_iterator YI ;
	public :
		LinearInterpByZcdf (const std::vector<Date> & dates,const std::vector<double>  &zcdfs )
		{
			for ( size_t s=0; s<dates.size(); s++)
			{
				points_.push_back(make_pair(dates[s], zcdfs[s] )) ;

			}
            interp_ = createLinearInterpolation (points_.begin(),points_.end()) ;
		}
		double operator () (const Date & d )
		{
			return (*interp_)(d) ;
		}
		const std::vector< std::pair<Date,double> > getPoints () {
			return interp_->getXVals () ;
		}


	private :
		typedef std::vector<std::pair<Date,double> >::iterator XYI ;
		LinearInterpolation<XYI> * interp_ ;
		std::vector<std::pair<Date,double> > points_ ;
	};

	class ZcrFromZcdf {
	public :
		ZcrFromZcdf (const Date & refDate, const DayCountConv * dcc  ) : dcc_(dcc), refDate_(refDate ) {


		}
		std::pair<Date,double> operator () (std::pair<Date,double> &point )
		{
			if ( point.first == refDate_ )
				return make_pair(point.first,0 ) ;
			else
			{
			/*	Date tmp ( 1,5,2014) ;
				if ( d >= tmp )
				cout <<"DDDDDD" << d << "," << zcdf << ","
					<<  dcc_->getFraction (refDate_,d)
					<< log(zcdf) << endl ;
*/
				return make_pair ( point.first,( - log(point.second) / dcc_->getFraction (refDate_,point.first) )) ;
			}
		}

	private :

		const DayCountConv * dcc_;
		const Date  refDate_ ;
	};

	class LinearInterpByZcr : public CurveInterp {
	public :
		LinearInterpByZcr (const Date & refDate, const std::vector< std::pair<Date,double> > & points)
							: dcc_(DayCountConv::find ( "_act36525")),refDate_(refDate),points_(points)
		{
		    //zcrs_ = zcdfs ;
			std::transform(points_.begin (),points_.end(),points_.begin(), ZcrFromZcdf(refDate_,dcc_ ) );
			if ( points_.size() >= 2 && points_[0].first == refDate_ )
			    points_[0].second = points_[1].second ;
			/*if (zcdfs.size() == 2 ) {
			cout << endl <<  "-------------------------" << endl ;
			cout << zcrs.size() << "," << zcdfs.size() << endl ;
			for (size_t i=0;i<zcrs.size();i++)
			{
				cout << i << " , " << zcdfs[i] << " : " ;
				cout << i << " , " << zcrs[i] << endl ;
				cout << i << " , " << dates[i] << endl ;
			}
			cout << "-------------------------" << endl ;
			}*/

			/*for ( size_t s=0; s<dates.size(); s++)
			{
				points_.push_back(make_pair(dates[s], zcrs_[s] )) ;

			}*/
			interp_ = createLinearInterpolation (points_.begin(),points_.end() ) ;
			//interp_ = new LinearInterpolation<XI,YI>(dates.begin(),dates.end(),zcrs_.begin()) ;
		}
		double operator () (const Date & d )
		{
		/*	Date tmp ( 10,11,2014) ;
			if ( d>= tmp )
			{
				const std::vector<Date> & dates =  getDates () ;
				cout << endl ;
				for ( size_t i =0 ; i < dates.size() ; i++)
					cout <<  dates[i] << " , ";

					cout << endl ;
			cout << "I" << d << ","<< refDate_ << "," << (*interp_)(d)
			    << dcc_->getFraction(refDate_, d ) << endl ;
			} */
			return exp ( -1 * (*interp_)(d)  * dcc_->getFraction(refDate_, d )) ;
		}
		const std::vector< std::pair<Date,double> > getPoints () {
							return interp_->getXVals () ;
						}
	/*	const std::vector<Date>  getDates () {
			return interp_->getXVals () ;
		}
	   std::vector<double>  getZcrs () {
					return interp_->getYVals () ;
				}
		 std::vector<double>  getZcdfs () {
			std::vector<double> zcdfs(interp_->getYVals ()) ;
			const std::vector<Date> & dates=interp_->getXVals () ;
			cout << zcdfs.size() << "____________________________" << dates.size() << endl ;
			for ( size_t s = 0 ; s< zcdfs.size() ; s++)
			{
				cout << "DATE= " << dates[s].serialNumber() << endl ;
				cout << "ZCR == " << zcdfs[s] << "ZCDF === " << endl;
			    zcdfs[s] = exp ( -1 * zcdfs[s]  * dcc_->getFraction(refDate_, dates[s] ));
				cout << zcdfs[s] << endl ;
			}
							return zcdfs ;
						} */
		private :

			typedef std::vector<std::pair<Date,double> >::iterator XYI ;
			LinearInterpolation<XYI> * interp_ ;
			const DayCountConv * dcc_ ;
			const Date refDate_ ;
			//std::vector<double> zcrs_ ;
			std::vector<std::pair<Date,double> > points_ ;

		};
}

#endif /* CURVEINTERP_H_ */
