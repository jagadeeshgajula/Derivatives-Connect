/*
 * buildCurveFromZcdf.h
 *
 *  Created on: 30-Oct-2010
 *      Author: vishist
 */

#ifndef BUILDCURVEFROMZCDF_H_
#define BUILDCURVEFROMZCDF_H_
#include "boost/shared_ptr.hpp"
#include "curveBuilder.h"
namespace IRDConnect {

class Curve;
class BuildCurveFromZcdf : public CurveBuilder {
public:
	boost::shared_ptr <Curve>  build () ;
};
}

#endif /* BUILDCURVEFROMZCDF_H_ */
