#ifndef UTILITY_HPP
#define UTILITY_HPP

inline int digits_count( int num )
{
    int count = 0;
    while( num != 0 )
    {
        num /= 10;
        ++count;
    }
    return count;
}

#endif /// UTILITY_HPP