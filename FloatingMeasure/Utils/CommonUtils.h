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

#ifndef COMMONUTILS_H
#define COMMONUTILS_H


///////////////////////////////////////////////////
// namespaces
///////////////////////////////////////////////////
using namespace std;
#ifdef __linux__
using namespace __gnu_cxx;
#endif

///////////////////////////////////////////////////
// macro definitions
///////////////////////////////////////////////////
#ifdef _WIN32
#define _WIN_DLL_API __declspec(dllexport) 
#endif

///////////////////////////////////////////////////
// compile switches
///////////////////////////////////////////////////
#ifdef LONGNUMBER
    #ifdef _WIN32
        #define DF_VALUE_TYPE       long double //double
        #define DF_INT_TYPE         long long 
        #define STR2INT             stol
        #define STR2DBL             stold
    #endif
    #ifdef __linux__
        #define DF_VALUE_TYPE       long double //double
        #define DF_INT_TYPE         __int128 // long long 
    #endif
#else
    #define DF_VALUE_TYPE       double
    #define DF_INT_TYPE         int
    #define STR2INT             stoi
    #define STR2DBL             stod
#endif



#endif
