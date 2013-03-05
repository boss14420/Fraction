/*
 * =====================================================================================
 *
 *       Filename:  fraction.cpp
 *
 *    Description:  Fraction class
 *
 *        Version:  1.0
 *        Created:  01/21/2012 10:54:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BOSS14420 (boss14420), boss14420@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

//#include "disable_builtins_atomic.h"

#include "fraction.hh"

#include <sstream>
#include <iostream>
#include <deque>
#include <map>
#include <iterator>
#include <utility>
#include <algorithm>
#include <cmath>

#ifdef _TEST
    #include <cstdlib>
    #include <ctime>
#endif

#if (__cplusplus >= 201103L)
#include <unordered_map>
using std::unordered_map;
#else
#include <tr1/unordered_map>
using std::tr1::unordered_map;
#endif

namespace boss14420 {

    Fraction& Fraction::operator+=(Fraction const& f) {
        long long n = static_cast<long long>(numerator) * f.denominator
            + static_cast<long long>(denominator) * f.numerator;
        long long d = static_cast<long long>(denominator) * f.denominator;
        simplify(n,d);
        numerator = n;
        denominator = d;
        return *this;
    }

    Fraction& Fraction::operator-=(Fraction const& f) {
        if(&f != this) {
            long long n = static_cast<long long>(numerator) * f.denominator
                - static_cast<long long>(denominator) * f.numerator;
            long long d = static_cast<long long>(denominator) * f.denominator;
            simplify(n,d);
            numerator = n;
            denominator = d;
        } else {
            numerator = 0;
            denominator = 1;
        }
        return *this;
    }

    Fraction& Fraction::operator*=(Fraction const& f) {
        long long n = static_cast<long long>(numerator) * f.numerator;
        long long d = static_cast<long long>(denominator) * f.denominator;
        simplify(n,d);
        numerator = n;
        denominator = d;

        return *this;
    }

    Fraction& Fraction::operator/=(Fraction const& f) {
        long long n = static_cast<long long>(numerator) * f.denominator;
        long long d = static_cast<long long>(denominator) * f.numerator;
        simplify(n,d);
        numerator = n;
        denominator = d;

        return *this;
    }

    std::ostream& operator<< (std::ostream& os, Fraction const& f) {
        return os << f.numerator << " / " << f.denominator;
    }

    std::istream& operator>> (std::istream& is, Fraction& f) {
        is >> f.numerator >> f.denominator;
        f.simplify();

        return is;
    }

    void Fraction::decimalization(std::string& non_sequence, std::string& sequence) const {

        non_sequence.resize(0), sequence.resize(0);

        register int p = numerator, q = denominator;

        q = abs(q);
        p = abs(p);

        p %= q;

        if(p) { // N¿u chia d°, tính ph§n th­p phân
#ifdef _TEST
        std::clock_t start, end;
        start = std::clock();
#endif

            int g = gcd(p,q);
            p /= g, q /= g;

            std::map<int, int> remain; // Lưu các số dư
            std::deque<char> dec;    // Lưu các chữ số phần thập phân
            remain[p] = 0;

//            remain.reserve(q);
            std::map<int, int>::iterator ri = remain.end();     
            register int k = 1;
            register unsigned long long pp;
            const unsigned long long TEN = 10ULL;
            while(p) {
                pp = p*TEN; dec.push_back(pp/q+'0'); p = pp%q;
                
                // Tìm xem phần dư hiện tại có lặp lại hay không
                ri = remain.find(p);        

                if(ri == remain.end())
                    // Nếu không thì tiếp tục
                    remain[p] = k++;
                else {
                    // Nếu có thì kết thúc phần tuần hoàn
                    break;
                }
            }
#ifdef _TEST
            end = std::clock();
            std::cerr << "time : " << (end-start)/(double)CLOCKS_PER_SEC 
                << " s" << std::endl;
#endif

            std::deque<char>::iterator begin_sequence = dec.begin() 
                + ((ri != remain.end()) ? ri->second : k - 1);

            // Phần không tuần hoàn
            non_sequence.resize(begin_sequence-dec.begin());
            std::copy(dec.begin(), begin_sequence, non_sequence.begin());

            // Phần tuần hoàn
            sequence.resize(dec.end()-begin_sequence);
            std::copy(begin_sequence, dec.end(), sequence.begin());
        }
    }

    std::string Fraction::toString(size_t sz) const {
        std::string sequence, non_sequence;
        decimalization(non_sequence, sequence);
        size_t nlen = non_sequence.length(), slen = sequence.length();

        std::stringstream ss(std::stringstream::out);
        if(numerator < 0)
            ss << '-';
        ss << numerator/denominator;

        std::string res = ss.str();

        if(nlen || slen) {
            res.push_back('.');

            if(slen == 0) {
                sz = std::max(nlen, sz);
                res.reserve(res.length() + sz);
                res.append(non_sequence.begin(), non_sequence.begin() + sz);
            } else {
                res.reserve(res.length() + sz);
                res += non_sequence;

                size_t remain = sz - nlen;
                size_t times = remain / slen;
                while(times--) {
                    res += sequence;
                    remain -= slen;
                }
                res.append(sequence.begin(), sequence.begin()+remain);
            } 
        }

        return res;
    }

    std::string Fraction::toString() const {
        std::string sequence, non_sequence;
        decimalization(non_sequence, sequence);
        size_t nlen = non_sequence.length(), slen = sequence.length();

        std::stringstream ss(std::stringstream::out);
        if(numerator < 0)
            ss << '-';
        ss << numerator / denominator;
        std::string res = ss.str();

        if(nlen > 0 || slen > 0) {
            res.push_back('.');
            if(slen > 0) {
                res.reserve(res.length() + nlen + slen + 2);
                res += non_sequence;
                res += '(';
                res += sequence;
                res += ')';
            } else {
                res.reserve(res.length() + non_sequence.size());
                res += non_sequence;
            }
            
        }
        return res;
    }

    template<class T>
        T Fraction::gcd(T a, T b) {
            a = abs(a);
            b = abs(b);

            // Ensure a >= b; can save a useless MOD
            if (b > a) { std::swap(a, b); }

            // Main loop of algorithm
            T temp;
            while (b > 0) {
                temp = b;
                b = a % b;
                a = temp;
            } // end while
            return a;
        }

    template int Fraction::gcd<int>(int,int);
    template long long Fraction::gcd<long long>(long long, long long);
    template void Fraction::simplify<int>(int&, int&);
    template void Fraction::simplify<long long>(long long&, long long&);

}
