/*
 * MIT License
 * 
 * Copyright (c) 2020 Michael von Mengershausen
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UTILS_H
#define UTILS_H

#include<string>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<assert.h>
#include<ostream>

using namespace std;
using namespace __gnu_cxx;

///////////////////////////////////////////////////
// definitions
///////////////////////////////////////////////////

#define myNAN               nan("1")
#define GREEK_SMALL_MU      "\u00b5"
#define GREEK_CAPITAL_OMEGA "\u03a9"
#define UNKNOWN_SHORT       "n.a."
#define UNKNOWN_LONG        "unknown"
#define UNKNOWN_INDEX       -1
#define UNKNOWN_VALUE       myNAN
#define INVALID_EXPONENT    -666

#define mu string(GREEK_SMALL_MU)
#define Omega string(GREEK_CAPITAL_OMEGA)
#define pm string("\u00B1")

// need to derive machine epsilon for double
/**
 * @brief union for calculation of numerical error of a 64 bit double
 * 
 */
union dbl_64{
    /**
     * @brief 64 bit integer representation
     * 
     */
    long long i64;
    /**
     * @brief 64 bit double representation
     * 
     */
    double d64;
};



///////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////

/**
 * @brief calculates the numerical error for a given double 
 * 
 * @param dValue: double which error is calculated
 * @return double
 */
double DoubleMachineEpsilon (double dValue) ;

/**
 * @brief cuts double according to precision 
 * - example positive precision: value= 100.00234, precision = 3 --> 100.002 
 * - example negative precision: value 1023404.234, precision = -2 --> 1023400
 * 
 * @param dValue: value to be cut
 * @param nPrecision: the wanted precision
 * @return double
 */
double Round2Precision(const double dValue, const int nPrecision);
/**
 * @brief returns "true" or "false" as string
 * 
 * @param bBool: bool to convert to string
 * @return string
 */
string Bool2String(const bool bBool);


///////////////////////////////////////////////////
// classes
///////////////////////////////////////////////////

 /**
  * @brief a Singleton class for a generic SingletonObject
  * 
  */
 template <typename SingletonObject>
 class CSingleton
 {
 public:
     /**
      * @brief allocates instance for member CSingleton< SingletonObject >::_instance
      * 
      * @return SingletonObject*
      */
     static SingletonObject* instance ()
    {
       if (!_instance)
          _instance = new SingletonObject ();
       return _instance;
    }
    
    /**
     * @brief virtual destructor
     * 
     */
    virtual ~CSingleton ()
    {
       _instance = 0;
    }
 protected:
     /**
      * @brief protected default constructor: <br>
      * avoids allocation like "SingletonObject MySingleton"
      * 
      */
     CSingleton () { }
 
     
 private:
     /**
      * @brief private "reflexive" pointer of SingletonObject:<br>
      * will be instantiated by #CSingleton::instance()
      * 
      */
     static SingletonObject* _instance;
};

 /**
  * @brief global definition and initialization of #CSingleton::_instance
  * 
  */
 template<typename SingletonObject> SingletonObject* CSingleton<SingletonObject>::_instance = nullptr;
   
///////////////////////////////////////////////////
// template functions
///////////////////////////////////////////////////

/**
 * @brief returns the index of an element within a vector
 * 
 * @tparam T: template type 
 * @param Value: value to find  in the vector
 * @param Vec: the vector where the element will be searched
 * @param nDefaultIndex: the index returned in case the element is not found in the vector
 * @return int
 */
template< typename T >
int FindElementInVectorGetIndex(const T& Value, const vector<T>&  Vec, int nDefaultIndex )
{
    int nResultIndex = nDefaultIndex;
    
    // find a corresponding factor
    typename vector<T>::const_iterator it = find(Vec.begin(), Vec.end(), Value);
    
    // if found: hand over the corresponding index 
    if(it != Vec.end() )
        nResultIndex = (int)(it-Vec.begin());
    
    // tell the caller if something was found and changed
    return nResultIndex;
}

/**
 * @brief returns the index of an element within a vector
 * 
 * @tparam T: template type 
 * @param Vec: the vector where the element will be searched
 * @param uiIndex: the index of the value returned, in case it exceeds the 
 *                         vector size, the last element of the vector is returned
 * @return int
 */
template< typename T >
const T& GetElementFromVectorByIndex(const vector<T>&  Vec, const unsigned int uiIndex )
{
    return uiIndex < Vec.size() ? 
            Vec[uiIndex] : Vec.back();
}
  
/**
 * @brief safely deletes pointers to objects of type T:<br>
 * "safely" holds only if unused pointers are initialized with nullptr
 * 
 * @tparam T:object Type
 * @param pt: pointer
 */
template< typename T>
void SecureDeleteObjectPointer( T* &pt)
{
    if( pt!=nullptr )
        delete pt;
    pt = nullptr;
}
 
/**
 * @brief safely deletes vectors / arrays of type T
 * "safely" holds only if unused pointers are initialized with nullptr
 * 
 * @tparam T: object type
 * @param pt: pointer of vector / array
 */
template< typename T>
void SecureDeleteVectorPointer( T* &pt)
{
    if( pt!=nullptr )
        delete[] pt;
    pt = nullptr;
}

#endif // UTILS_H
