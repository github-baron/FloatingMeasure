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

#include <Utils/Utils.h>
#include <iostream>
double Round2Precision(const DF_VALUE_TYPE dValue,const int nPrecision)
{
    double dFactor = pow(10.,nPrecision);
    bool bPos = dValue >0;
    return double ( (long)(dValue*dFactor + (bPos ? 1 : -1)*(0.5)) )/dFactor; 
}

string Bool2String(const bool bBool)
{
    return bBool ? "true" : "false";
}

string Double2String(const DF_VALUE_TYPE& dValue)
{   
    ostringstream oss;
    oss << scientific << dValue;
    return oss.str();
}

string  TrimLeft(const string& str2Trim, const string strTrim )
{
//     cout << "str2Trim = \"" << str2Trim << "\"" << std::endl
//     << " strTrim = \"" << strTrim << "\"" << std::endl; 
    int nPosTrim = 0;
    int nPosTrimOld = 0;
    while( (nPosTrim = str2Trim.find(strTrim,nPosTrimOld)) == nPosTrimOld)
    {
//         cout << "npos " << nPosTrim << endl;
        nPosTrimOld = nPosTrim +  strTrim.length();
    }
    
     return str2Trim.substr(nPosTrimOld, str2Trim.length()-nPosTrimOld);
}

string  TrimRight(const string& str2Trim, const string strTrim )
{
//     cout << "str2Trim = \"" << str2Trim << "\"" << std::endl
//     << " strTrim = \"" << strTrim << "\"" << std::endl; 
    int nPosTrimOld = str2Trim.length() -strTrim.length();
    int nPosTrim = -1;
    while( (nPosTrim = str2Trim.find(strTrim,nPosTrimOld)) == nPosTrimOld)
    {
//         cout << "npos " << nPosTrim << endl;
        nPosTrimOld  -= strTrim.length();
    }
    
    // increment nPosTrimOld for correct substring 
    nPosTrimOld += strTrim.length();
    
     return str2Trim.substr(0, nPosTrimOld);
}

string  Trim(const string& str2Trim, const string strTrim )
{
    return TrimLeft(TrimRight(str2Trim,strTrim),strTrim);
}

vector<string> Tokenize(const string& strTotal, const string& strSep, bool bTrim)
{
    // initialize result
    vector<string> vstrResult;
 
    // if separator is not given return empty vector
    if(strSep == "")
        return vstrResult;
    
    int nPos = 0;
    int nOldPos = 0;
    while((nPos = strTotal.find(strSep,nOldPos)) != string::npos)
    {
        string str = strTotal.substr(nOldPos, nPos-nOldPos);
//         std::cout << "substring (old=" << nOldPos << ", new=" << nPos << ") = " << str << std::endl;
        // push back if not empty
        if(str.length() > 0)
            vstrResult.push_back(bTrim ? Trim(str, " ") : str);
        
        // setting old position to actual pos. + leng(separator)
        nOldPos = nPos+strSep.length();
        
    }
    
    // add last element
    if(nOldPos < strTotal.length()-1)
    {
        string str = strTotal.substr(nOldPos, strTotal.length()-nOldPos);
//         std::cout << "substring (old=" << nOldPos << ", new=" << strTotal.length() << ") = " << str << std::endl;
        // push back if not empty
        if(str.length() > 0)
            vstrResult.push_back(str);
    }
    
    // no empty vector will be returned: if token does not exist
    // return whole string
    if(vstrResult.size() == 0)
        vstrResult.push_back(strTotal);
    
    return vstrResult;
}

string Concat(vector<string> vstr2Print, string strSep)
{
    string strTotal;
    for(int istr=0; istr<vstr2Print.size(); istr++)
    {
        // add to concatenated string
        strTotal+=vstr2Print[istr];
        
        // add separator except for last element
        if(istr < vstr2Print.size()-1)
            strTotal += strSep;
    }
    
    return strTotal;
}
