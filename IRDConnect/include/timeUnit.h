/*
 * timeUnit.h
 *
 *  Created on: 05-Sep-2010
 *      Author: vishist
 */

#ifndef IRDTIMEUNIT_H_
#define IRDTIMEUNIT_H_
#include <ostream>

using namespace std;

namespace IRDConnect {

 enum TimeUnit { Days,
                    Weeks,
                    Months,
                    Years
    };

    /*! \relates TimeUnit */
   std::ostream& operator<<(std::ostream&,
                            const TimeUnit&);

}
#endif /* IRDTIMEUNIT_H_ */
