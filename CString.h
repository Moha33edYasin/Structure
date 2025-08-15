#ifndef CSTRING_H
#define CSTRING_H

#include <string>
using std::string;

unsigned int cut_out_neg(int __n)
{
    if (__n < 0)
        return 0;
    return __n;
}

bool is_empty_str(const string __str, const char empty_char = ' ')
{
    for(char c : __str)
    {
        if(c != empty_char)
            return false;
    }
    return true;
}
bool is_empty_str(const string __str, const string empty_char = " ")
{
    for(char _char : __str)
    {
        for(char _e_char : empty_char)
        {
            if(_char != _e_char)
                return false;
        }
    }
    return true;
}

string multiple_str(const string __str, const size_t __n)
{
    string m_str;
    for(int _ns=0; _ns<__n; _ns++)
        m_str += __str;
    return m_str;
}

#endif // CSTRING_H