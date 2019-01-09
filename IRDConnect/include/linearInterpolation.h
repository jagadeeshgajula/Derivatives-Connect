/*
 * LinearInterpolation.h
 *
 *  Created on: 10-Oct-2010
 *      Author: vishist
 */

#ifndef lINEARINTERPOLATION_H_
#define lINEARINTERPOLATION_H_
#include <vector>
#include <iostream>

template <typename X, typename Y>

class LinearInterpolationIRD
{
public :
	LinearInterpolationIRD (const std::vector<X> &xVals, const std::vector<Y> &yVals ) :
		xVals_(xVals), yVals_(yVals ) {}
	Y operator () (X xCoord )
	{
		//std::cout << xCoord << ","  << xCoord.serialNumber()  << std::endl ;

		if ( xCoord <= xVals_[0])
			return yVals_[0] ;

		if ( xCoord >= xVals_[ xVals_.size() -1 ] )
			return yVals_[xVals_.size() -1] ;

		for ( size_t i=0; i< xVals_.size() ; i++ )
		{
			if ( xCoord == xVals_[i])
				return yVals_[i] ;

			if ( xCoord > xVals_[i] )
			    continue ;
		//	std::cout << xCoord << ","  << xCoord.serialNumber() <<  std::endl ;
		//	std::cout << i << "," << xVals_[i] << ","  << xVals_[i].serialNumber() <<  std::endl ;

			double slope = ( yVals_[i] - yVals_[i-1]) / ( xVals_ [i] - xVals_ [i-1] ) ;
		//	std::cout << yVals_ [ i ] << "," << yVals_ [i+1] << ","  << i << std::endl ;
			return ( yVals_[i-1] + slope * ( xCoord - xVals_[i-1]) ) ;


		}
		return Y(0);

	}
	const std::vector<X> & getXVals () {
		return xVals_ ;
	}
	const std::vector<Y> & getYVals () {
			return yVals_ ;
		}


private :


	const std::vector<X> xVals_ ;
	const std::vector<Y> yVals_ ;
};
#endif /* lINEARINTERPOLATION_H_ */
