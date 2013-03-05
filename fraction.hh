/*
 * =====================================================================================
 *
 *       Filename:  fraction.hh
 *
 *    Description:  Fraction class header
 *
 *        Version:  1.0
 *        Created:  01/21/2012 11:20:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BOSS14420 (boss14420), boss14420@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __FRACTION_HH__
#define __FRACTION_HH__

#include <iosfwd>
#include <string>

namespace boss14420 {
    class Fraction {
        int numerator, denominator;

    public:
        Fraction(int a = 1, int b = 1) : numerator(a), denominator(b) { simplify(); }

        bool operator==(Fraction const& f) const {
            return numerator == f.numerator && denominator == f.denominator;
        }
        bool operator!=(Fraction const& f) const {
            return numerator != f.numerator || denominator != f.denominator;
        }
        bool operator>(Fraction const& f) const {
            return static_cast<long long>(numerator) * f.denominator
                    > static_cast<long long>(denominator) * f.numerator;
        }
        bool operator>=(Fraction const& f) const {
            return static_cast<long long>(numerator) * f.denominator
                    >= static_cast<long long>(denominator) * f.numerator;
        }
        bool operator<(Fraction const& f) const {
            return static_cast<long long>(numerator) * f.denominator
                    < static_cast<long long>(denominator) * f.numerator;
        }
        bool operator<=(Fraction const& f) const {
            return static_cast<long long>(numerator) * f.denominator
                    <= static_cast<long long>(denominator) * f.numerator;
        }

        Fraction& operator+=(Fraction const& f);
        Fraction& operator-=(Fraction const& f);
        Fraction& operator*=(Fraction const& f);
        Fraction& operator/=(Fraction const& f);

        Fraction operator+(Fraction const& f) const {
            Fraction tmp = *this;
            tmp += f;
            return tmp;
        }
        Fraction operator-(Fraction const& f) const {
            Fraction tmp = *this;
            tmp -= f;
            return tmp;
        }
        Fraction operator*(Fraction const& f) const {
            Fraction tmp = *this;
            tmp *= f;
            return tmp;
        }
        Fraction operator/(Fraction const& f) const {
            Fraction tmp = *this;
            tmp /= f;
            return tmp;
        }
        
//        operator int () const { return numerator/denominator;}

        std::string toString() const;
        std::string toString(size_t) const;

        friend std::istream& operator>>(std::istream&, Fraction& f);
        friend std::ostream& operator<<(std::ostream&, Fraction const& f);

        void decimalization(std::string&, std::string&) const;

    private:
        void simplify() {
            simplify(numerator, denominator);
        }

        template<class T> static T gcd(T,T);
        template<class T> static void simplify(T& a, T& b) {
            if(b < 0)
                b = -b, a = -a;
            T g = gcd(a,b);
            a /= g;
            b /= g;
        }
    };
}

#endif
