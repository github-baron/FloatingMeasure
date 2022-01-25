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

// global includes
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<unordered_map>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<assert.h>
#include<ostream>

// DEBUG
#include <iostream>

// local includes 
#include "Singleton.h"
#include "CommonUtils.h"

// deal with log4cplus include 
#ifdef LOG4CPLUS_ENABLED

#include "Log4cplusWrapper.h"
#include "LoggingStrings.h"
#else
// define empty log to commens

#define LOGTRACE(lg,msg);    
#define LOGDEBUG(lg,msg);    
#define LOGINFO(lg,msg);
#define LOGWARN(lg,msg);
#define LOGERROR(lg,msg);
#define LOGFATAL(lg,msg);

#endif




#define DF_VALUE_TYPE       long double //double
#define DF_INT_TYPE         __int128 // long long 
#define myNAN               nan("1")
#define GREEK_SMALL_MU      "\u00b5"
#define GREEK_CAPITAL_OMEGA "\u03a9"
#define UNKNOWN_SHORT       "n.a."
#define UNKNOWN_LONG        "unknown"
#define UNKNOWN_INDEX       -1
#define UNKNOWN_VALUE       myNAN
#define INVALID_EXPONENT    -666

#ifdef _WIN32
#undef  GREEK_CAPITAL_OMEGA    
#define  GREEK_CAPITAL_OMEGA    "ohm"
#endif


#define mu string(GREEK_SMALL_MU)
#define Omega string(GREEK_CAPITAL_OMEGA)
#define plmi string("\u00B1")

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
    DF_INT_TYPE intRep;
    /**
     * @brief 64 bit double representation
     * 
     */
    DF_VALUE_TYPE dRep;
};


///////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////

/**
 * @brief cuts double according to precision 
 * - example positive precision: value= 100.00234, precision = 3 --> 100.002 
 * - example negative precision: value 1023404.234, precision = -2 --> 1023400
 * 
 * @param dValue: value to be cut
 * @param nPrecision: the wanted precision
 * @return double
 */
double 
#ifdef _WIN32
_WIN_DLL_API
#endif
 Round2Precision(const DF_VALUE_TYPE dValue, const int nPrecision);
 
/**
 * @brief returns "true" or "false" as string
 * 
 * @param bBool: bool to convert to string
 * @return string
 */
string 
#ifdef _WIN32
_WIN_DLL_API
#endif
 Bool2String(const bool bBool);
 
/**
 * @brief prints double with a given precision
 * 
 * @param[in] dValue double to convert to string
 * @param[in] nPrecision int setting precision used for conversion
 * @return string
 */
string 
#ifdef _WIN32
_WIN_DLL_API
#endif
 Double2String(const DF_VALUE_TYPE& dValue);
 
/**
 * @brief removes consecutive white spaces from the left side of a string
 * 
 * @param[in] str2Trim string to remove white spaces from
 * @param[in] strTrim string 2 be removed (default space)
 * @return string without white space character on the left
 */
string 
#ifdef _WIN32
_WIN_DLL_API
#endif
 TrimLeft(const string& str2Trim, const string strTrim = " ");
 
/**
 * @brief removes consecutive white spaces from the right side of a string
 * 
 * @param[in] str2Trim string to remove white spaces from
 * @param[in] strWhiteSpace white space character (default space)
 * @return string without white space character on the right
 */
string 
#ifdef _WIN32
_WIN_DLL_API
#endif
 TrimRight(const string& str2Trim, const string strWhiteSpace = " ");
 
 
/**
 * @brief removes consecutive white spaces from the leading and trailing end of a string
 * 
 * @param[in] str2Trim string to remove white spaces from
 * @param[in] strWhiteSpace white space character (default space)
 * @return string without white space character on the leading and trailing end
 */
string 
#ifdef _WIN32
_WIN_DLL_API
#endif
 Trim(const string& str2Trim, const string strWhiteSpace = " ");
 
/**
 * @brief prints double with a given precision
 * 
 * @param[in] dValue double to convert to string
 * @param[in] nPrecision int setting precision used for conversion
 * @return string
 */
 vector<string>
#ifdef _WIN32
_WIN_DLL_API
#endif 
Tokenize(const string& strTotal, const string& strSep, bool bTrim = false);
    
/**
 * @brief concatenates elements of a vector of strings separated by the user given string
 * 
 * @param[in] vstrTotal vector of strings to print
 * @param[in] strSep separator string
 * @return string
 */
 string
#ifdef _WIN32
_WIN_DLL_API
#endif 
Concat(vector<string> vstr2Print, string strSep = "\n");

/**
 * @brief checks for a numeric character (0-9)
 * 
 * @param[in] c character to check
 * @return true if numeric
 */
bool
#ifdef _WIN32
_WIN_DLL_API
#endif 
IsNumeric(char c);
    

///////////////////////////////////////////////////
// classes
///////////////////////////////////////////////////
///////////////////////////////////////////////////
// template functions
///////////////////////////////////////////////////

/**
 * @brief calculates the numerical error for a given double 
 * 
 * @param dValue: double which error is calculated
 * @return double
 */
template< typename T>
T 
#ifdef _WIN32
_WIN_DLL_API
#endif
 DoubleMachineEpsilon(T dValue)
{ 
    dbl_64 s;
    s.dRep = dValue;
    s.intRep++;
        
    // logging
    LOGTRACE("FloatingMeasure::Utils::DoubleMachineEpsilon ","DoubleMachineEpsilon(" + to_string( dValue ) + ") = " + to_string(fabs(s.dRep - dValue)));
    
    return fabs(s.dRep - dValue);

}

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
 int FindElementInVectorGetIndex(const T& Value, const vector<T>&  Vec, int nDefaultIndex)
 {
     int nResultIndex = nDefaultIndex;

     // find a corresponding factor
     typename vector<T>::const_iterator it = find(Vec.begin(), Vec.end(), Value);

     // if found: hand over the corresponding index 
     if (it != Vec.end())
         nResultIndex = (int)(it - Vec.begin());

     // tell the caller if something was found and changed
     return nResultIndex;
 }

 /**
  * @brief returns the index of an element within a vector
  *
  * @tparam T: template type
  * @param Value: value to find  in the vector
  * @param pVec: the pointer of the vector where the element will be searched
  * @param nDefaultIndex: the index returned in case the element is not found in the vector
  * @return int
  */
 template< typename T >
 int FindElementInVectorGetIndex(const T& Value, const vector<T>*  pVec, int nDefaultIndex)
 {
     return FindElementInVectorGetIndex(Value, (*pVec), nDefaultIndex);
 }

 /**
  * @brief returns the element within a vector by its index. If not found --> last value
  *
  * @tparam T: template type
  * @param Vec: the vector where the element will be searched
  * @param uiIndex: the index of the value returned, in case it exceeds the
  *                         vector size, the last element of the vector is returned
  * @return int
  */
 template< typename T >
 const T& GetElementFromVectorByIndex(const vector<T>&  Vec, const unsigned int uiIndex)
 {
     return uiIndex < Vec.size() ?
         Vec[uiIndex] : Vec.back();
 }

 /**
  * @brief returns the element within a vector by its index. If not found --> last value
  *
  * @tparam T: template type
  * @param pVec: the pointer of the vector where the element will be searched
  * @param uiIndex: the index of the value returned, in case it exceeds the
  *                         vector size, the last element of the vector is returned
  * @return int
  */
 template< typename T >
 const T& GetElementFromVectorByIndex(const vector<T>* pVec, const unsigned int uiIndex)
 {
     return GetElementFromVectorByIndex((*pVec), uiIndex);
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


/**
 * @brief returns pointer address as string
 * 
 * @tparam T: object type 
 * @param pt: the pointer whose address is to be converted into a string
 * @return string
 */
template< class T >
string  Address2String(const T* pt)
{
    ostringstream get_the_address; 
    get_the_address << pt;
    return get_the_address.str();     
}


/**
 * @brief returns optimized calculated difference up to 6th order avoiding higher order differences
 * which results in inaccurate results
 * 
 * @tparam T: object type 
 * @param T& X1 minuend 
 * @param T& X2 subtrahend 
 * @return difference of nth order
 */
template< class T >
T DifferenceNthOrder(const T& X1, const T& X2, unsigned int nthOrder)
{
    T Diff;
    switch(nthOrder)
    {
        case 1:
            Diff = X2-X1;
            break;
        case 2:
            Diff = (X2-X1)*(X2+X1);
            break;
        case 3:
            Diff = (X2-X1)*(X2*X2 + X1*X1 + X1*X2);
            break;
        case 4:
            Diff = (X2-X1)*(X2+X1)*(X1*X1+X2*X2);
            break;
        case 5:
            Diff = (X2-X1)*(pow(X2,nthOrder-1)+pow(X1,nthOrder-1)+(X1*X2)*(X1*X1+ X2*X2+ X1*X2));
            break;
        case 6:
            Diff = (X2-X1)*(X2*X2 + X1*X1 + X1*X2) * (X1*X1*X1+X2*X2*X2);
            break;
        default:
            Diff = pow(X2,nthOrder)-pow(X1,nthOrder);
            break;
    }
    
    return Diff;
}    
#endif // UTILS_H
