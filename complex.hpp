#ifndef COMPLEX_WRAPPER_H
#define COMPLEX_WRAPPER_H

#include <cstdio>

#ifndef USING_QUADMATH

#include <complex>

typedef std::complex<long double> _complex;
typedef long double _float;

#define Re(Z) std::real(Z)
#define Im(Z) std::imag(Z)

const _complex RawComplex_I = _complex(0.0,1.0);

#define Sqrt(Z) std::sqrt(Z)
#define Exp(Z) std::exp(Z)
#define Cos(Z) std::cos(Z)
#define Sin(Z) std::sin(Z)

#else

#include <quadmath.h>

typedef __complex128 _complex;
typedef __float128 _float;

#define Sqrt(Z) csqrtq(Z)
#define Exp(Z) cexpq(Z)
#define Cos(Z) ccosq(Z)
#define Sin(Z) csinq(Z)

const _complex RawComplex_I = csqrtq(1);

#define Re(Z) __real__ Z
#define Im(Z) __imag__ Z

#endif

class Complex
{

	/*
	 * Class to abstract complex arithmetic
	 */

	public:
		_complex raw;

		Complex();
		Complex(_float const&);
		Complex(_float const&, _float const&);
		Complex(_complex const&);

		void print() const;
		void printCompact(FILE*) const;

		_float magsq() const;
		_float mag() const;

		/* Component assignments */
		_float re() const;
		void re(_float const&);
		_float im() const;
		void im(_float const&);

		void operator=  (const Complex&);
		void operator+= (const Complex&);
		void operator-= (const Complex&);
		void operator*= (const Complex&);
		void operator/= (const Complex&);
		void operator^= (const Complex&);

		Complex operator~ (void);

		friend Complex operator+ (const Complex&, const Complex&);
		friend Complex operator- (const Complex&, const Complex&);
		friend Complex operator* (const Complex&, const Complex&);
		friend Complex operator/ (const Complex&, const Complex&);
		friend Complex operator^ (const Complex&, const Complex&);

		friend Complex operator+ (const _complex&, const Complex&);
		friend Complex operator- (const _complex&, const Complex&);
		friend Complex operator* (const _complex&, const Complex&);
		friend Complex operator/ (const _complex&, const Complex&);
		friend Complex operator^ (const _complex&, const Complex&);

};

const Complex Complex_I = Complex(0, 1);

#endif // COMPLEX_WRAPPER_H
