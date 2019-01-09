#ifndef CURVECACHE_H
#define CURVECACHE_H 
#include "singleton.h"
#include "boost/shared_ptr.hpp"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include "date.h"

namespace IRDConnect { 
  class Curve;
  class CurveDef ;
  struct curveKey {
    Date date_ ;
    std::string curveName_ ;
  curveKey(const Date & date, const std::string & curveName ) : date_ ( date ) , curveName_ ( curveName ){        }
  };

  struct curveScenKey {
    Date date_ ;
    std::string curveName_ ;
    std::string bumpTenor_ ;
    double bumpSize_ ;
    curveScenKey(const Date & date,
                 const std::string & curveName,
                 const std::string & bumpTenor,
                 double bumpSize ) :
                                     date_ ( date ) ,
				     curveName_ ( curveName),
				     bumpTenor_ ( bumpTenor ),
				     bumpSize_(bumpSize) { }
  };

  bool operator < (const curveScenKey &k1, const curveScenKey &k2 );
  bool operator < (const curveKey &k1, const curveKey &k2 );

  class CurveCache : private Singleton<CurveCache> {

  public :
    friend class Singleton<CurveCache> ;
    using Singleton<CurveCache>::instance ;
    boost::shared_ptr<Curve> find ( const Date & date, const std::string & curveName );
    boost::shared_ptr<Curve> find ( const Date & date, const std::string & curveName,
				    const std::string & bumpTenor, double bumpSize );
  private :
    CurveCache();
    boost::shared_ptr<Curve> loadCurve ( const Date & curveDate, const std::string & curveName ) ;
    boost::shared_ptr<Curve> loadBumpCurve ( const Date & curveDate, const std::string & curveName,
					     const std::string & bumpTenor, double bumpSize) ;
    void loadRates ( const std::string & rates_filename );
    ~CurveCache(){};
    std::map<curveKey, boost::shared_ptr<Curve> > curveMap_ ;
    std::map<curveScenKey, boost::shared_ptr<Curve> > curveScenMap_ ;
    //std::map<std::string, boost::shared_ptr<CurveDef> > curveDefMap_ ;
    std::map<std::string,std::string > curveDefMap_ ;
    std::map<std::string,double> ratesMap_ ;
  };

}
#endif
