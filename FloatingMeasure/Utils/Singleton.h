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


#ifndef CSINGLETON_H
#define CSINGLETON_H

 /**
  * @brief a Singleton class for a generic SingletonObject
  * 
  */
 template <typename SingletonObject>
 class 
#ifdef _WIN32
_WIN_DLL_API
#endif
 CSingleton
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
   
#endif
