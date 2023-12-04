#include "minirt_base.h"

#include <math.h>

minirt_f minirt_f_sqrt(minirt_f f) {
#if MINIRT_PRECISION == 1
	return sqrtf(f);
#elif MINIRT_PRECISION == 2
	return sqrt(f);
#elif MINIRT_PRECISION == 3
	return sqrtl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_pow(minirt_f f, minirt_f exp) {
#if MINIRT_PRECISION == 1
	return powf(f, exp);
#elif MINIRT_PRECISION == 2
	return pow(f, exp);
#elif MINIRT_PRECISION == 3
	return powl(f, exp);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_ln(minirt_f f) {
#if MINIRT_PRECISION == 1
	return logf(f);
#elif MINIRT_PRECISION == 2
	return log(f);
#elif MINIRT_PRECISION == 3
	return logl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_log(minirt_f f, minirt_f base) {
#if MINIRT_PRECISION == 1
	return logf(f) / logf(base);
#elif MINIRT_PRECISION == 2
	return log(f) / log(base);
#elif MINIRT_PRECISION == 3
	return logl(f) / logl(base);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_sin(minirt_f f) {
#if MINIRT_PRECISION == 1
	return sinf(f);
#elif MINIRT_PRECISION == 2
	return sin(f);
#elif MINIRT_PRECISION == 3
	return sinl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_cos(minirt_f f) {
#if MINIRT_PRECISION == 1
	return cosf(f);
#elif MINIRT_PRECISION == 2
	return cos(f);
#elif MINIRT_PRECISION == 3
	return cosl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_tan(minirt_f f) {
#if MINIRT_PRECISION == 1
	return tanf(f);
#elif MINIRT_PRECISION == 2
	return tan(f);
#elif MINIRT_PRECISION == 3
	return tanl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_cot(minirt_f f) {
	return 1 / minirt_f_tan(f);
}

minirt_f minirt_f_sec(minirt_f f) {
	return 1 / minirt_f_cos(f);
}

minirt_f minirt_f_csc(minirt_f f) {
	return 1 / minirt_f_sin(f);
}

minirt_f minirt_f_sinh(minirt_f f) {
#if MINIRT_PRECISION == 1
	return sinhf(f);
#elif MINIRT_PRECISION == 2
	return sinh(f);
#elif MINIRT_PRECISION == 3
	return sinhl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_cosh(minirt_f f) {
#if MINIRT_PRECISION == 1
	return coshf(f);
#elif MINIRT_PRECISION == 2
	return cosh(f);
#elif MINIRT_PRECISION == 3
	return coshl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_tanh(minirt_f f) {
#if MINIRT_PRECISION == 1
	return tanhf(f);
#elif MINIRT_PRECISION == 2
	return tanh(f);
#elif MINIRT_PRECISION == 3
	return tanhl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_coth(minirt_f f) {
	return 1 / minirt_f_tanh(f);
}

minirt_f minirt_f_sech(minirt_f f) {
	return 1 / minirt_f_cosh(f);
}

minirt_f minirt_f_csch(minirt_f f) {
	return 1 / minirt_f_sinh(f);
}

minirt_f minirt_f_asin(minirt_f f) {
#if MINIRT_PRECISION == 1
	return asinf(f);
#elif MINIRT_PRECISION == 2
	return asin(f);
#elif MINIRT_PRECISION == 3
	return asinl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_acos(minirt_f f) {
#if MINIRT_PRECISION == 1
	return acosf(f);
#elif MINIRT_PRECISION == 2
	return acos(f);
#elif MINIRT_PRECISION == 3
	return acosl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_atan(minirt_f f) {
#if MINIRT_PRECISION == 1
	return atanf(f);
#elif MINIRT_PRECISION == 2
	return atan(f);
#elif MINIRT_PRECISION == 3
	return atanl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

#if MINIRT_PRECISION == 1
# define MINIRT_PI_2 ((minirt_f)1.57079632679f)
#elif MINIRT_PRECISION == 2
# define MINIRT_PI_2 ((minirt_f)1.5707963267948966)
#elif MINIRT_PRECISION == 3
# define MINIRT_PI_2 ((minirt_f)1.5707963267948966192313216916398L)
#else
# error Unrecognized MINIRT_PRECISION value
#endif

minirt_f minirt_f_acot(minirt_f f) {
	return MINIRT_PI_2 - minirt_f_atan(f);
}

minirt_f minirt_f_asec(minirt_f f) {
	return acos(1 / f);
}

minirt_f minirt_f_acsc(minirt_f f) {
	return asin(1 / f);
}

minirt_f minirt_f_asinh(minirt_f f) {
#if MINIRT_PRECISION == 1
	return asinhf(f);
#elif MINIRT_PRECISION == 2
	return asinh(f);
#elif MINIRT_PRECISION == 3
	return asinhl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_acosh(minirt_f f) {
#if MINIRT_PRECISION == 1
	return acoshf(f);
#elif MINIRT_PRECISION == 2
	return acosh(f);
#elif MINIRT_PRECISION == 3
	return acoshl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_atanh(minirt_f f) {
#if MINIRT_PRECISION == 1
	return atanhf(f);
#elif MINIRT_PRECISION == 2
	return atanh(f);
#elif MINIRT_PRECISION == 3
	return atanhl(f);
#else
# error Unrecognized MINIRT_PRECISION value
#endif
}

minirt_f minirt_f_acoth(minirt_f f) {
	return 0.5 * minirt_f_ln((f + 1) / (f - 1));
}

minirt_f minirt_f_asech(minirt_f f) {
	return acosh(1 / f);
}

minirt_f minirt_f_acsch(minirt_f f) {
	return asinh(1 / f);
}
