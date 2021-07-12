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

#ifndef CLOG4CPLUSWRAPPER_H
#define CLOG4CPLUSWRAPPER_H


///////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/loggingmacros.h>
#include "Singleton.h"
#include "CommonUtils.h"

///////////////////////////////////////////////////
// macros
///////////////////////////////////////////////////
#ifndef LOG4CPLUS_CONFIG_PATH
#define LOG4CPLUS_CONFIG_PATH   "log4cplus.config"
#endif


///////////////////////////////////////////////////
// forward declarations
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// namespaces
///////////////////////////////////////////////////
using namespace log4cplus;

/**
 * @brief CLog4cplusWrapper: a class for wrapping the log4cplus::Logger to use it as a singleton
 */
class 
#ifdef _WIN32
_WIN_DLL_API
#endif
CLog4cplusWrapper
{
public:
    
    ///////////////////////////////////////////////////
    // constructors / destructor
    ///////////////////////////////////////////////////
    /**
     * @brief Default constructor: initializes logging with log4cplus
     */
    CLog4cplusWrapper();
    /**
     * @brief destructor: 
     */
    ~CLog4cplusWrapper();
    
    ///////////////////////////////////////////////////
    // public variables
    ///////////////////////////////////////////////////
    Logger m_Logger;

    
};

/**
 * @brief a singleton instance of the wrapper class for Logger (log4cplus)
 * 
 */
typedef CSingleton<CLog4cplusWrapper> CLog4cplusWrapperSingleton;

/**
 * @brief Short cut to the singleton instance of log4cplus Logger class for 
 *        all different logging levels. e.g.:
 *        LOGTRACE("ConfigurableLoggerName","logging text 4 u")
 * 
 */
#define LOGTRACE(lg,msg)    LOG4CPLUS_TRACE( CLog4cplusWrapperSingleton::instance()->m_Logger.getInstance(LOG4CPLUS_TEXT(lg)),LOG4CPLUS_TEXT(msg));
#define LOGDEBUG(lg,msg)    LOG4CPLUS_DEBUG( CLog4cplusWrapperSingleton::instance()->m_Logger.getInstance(LOG4CPLUS_TEXT(lg)),LOG4CPLUS_TEXT(msg));
#define LOGINFO(lg,msg)    LOG4CPLUS_INFO( CLog4cplusWrapperSingleton::instance()->m_Logger.getInstance(LOG4CPLUS_TEXT(lg)),LOG4CPLUS_TEXT(msg));
#define LOGWARN(lg,msg)    LOG4CPLUS_WARN( CLog4cplusWrapperSingleton::instance()->m_Logger.getInstance(LOG4CPLUS_TEXT(lg)),LOG4CPLUS_TEXT(msg));
#define LOGIERROR(lg,msg)    LOG4CPLUS_ERROR( CLog4cplusWrapperSingleton::instance()->m_Logger.getInstance(LOG4CPLUS_TEXT(lg)),LOG4CPLUS_TEXT(msg));
#define LOGFATAL(lg,msg)    LOG4CPLUS_FATAL( CLog4cplusWrapperSingleton::instance()->m_Logger.getInstance(LOG4CPLUS_TEXT(lg)),LOG4CPLUS_TEXT(msg));


#endif
