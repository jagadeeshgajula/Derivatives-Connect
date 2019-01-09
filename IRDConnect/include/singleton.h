#ifndef SINGLETON_H
#define SINGLETON_H 
#include <boost/utility.hpp>

namespace IRDConnect { 
  
  template <typename T> 
  class Singleton : private boost::noncopyable {
  public : 
    static T & instance ();
  protected :
    Singleton(){};
    ~Singleton(){};
  };
  template <typename T>
    T& Singleton<T>::instance(){
    static T sInstance  ;
    return sInstance ; 
  }

}
#endif 
