/*
 * curveBuilder.h
 *
 *  Created on: 27-Oct-2010
 *      Author: vishist
 */

#ifndef CURVEBUILDER_H_
#define CURVEBUILDER_H_

#include "boost/shared_ptr.hpp"
namespace IRDConnect {

class Curve;
class CurveBuilder {
public:
	virtual boost::shared_ptr <Curve>  build () =0 ;
	virtual ~CurveBuilder () {};
};
}
#endif /* CURVEBUILDER_H_ */
