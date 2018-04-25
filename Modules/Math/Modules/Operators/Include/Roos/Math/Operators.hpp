#ifndef ROOS_MATH_OPERATORS_HPP
#define ROOS_MATH_OPERATORS_HPP

#define ROOS_OPERATOR(name, op)											\
template<typename T, typename U = T>									\
class name																\
{																		\
	friend constexpr T operator op(const T& a, const U& b) noexcept		\
    {																	\
        T result(a);													\
        result op## = b;												\
        return result;													\
    }																	\
};																		\

#define ROOS_COMMUTATIVE_OPERATOR(name, op)								\
template<typename T, typename U = T>									\
class Commutative##name													\
{																		\
	friend constexpr T operator op(const T& a, const U& b) noexcept		\
    {																	\
        T result(a);													\
        result op## = b;												\
        return result;													\
    }																	\
	friend constexpr T operator op(const U& a, const T& b) noexcept				\
    {																	\
        T result(b);													\
        result op## = a;												\
        return result;													\
    }																	\
};																		\

namespace Roos::Math::Operators {

template<typename T>
class EqualityComparable
{
	friend constexpr bool operator!=(const T& a, const T& b) noexcept
	{
		return !static_cast<bool>(a == b);
	}
};

template<typename T>
class LessThanComparable
{
	friend constexpr bool operator>(const T& a, const T& b) noexcept
	{
		return static_cast<bool>(b < a);
	}

	friend constexpr bool operator<=(const T& a, const T& b) noexcept
	{
		return !static_cast<bool>(b < a);
	}

	friend constexpr bool operator>=(const T& a, const T& b) noexcept
	{
		return !static_cast<bool>(a < b);
	}
};

ROOS_OPERATOR(Addable, +);
ROOS_OPERATOR(Subtractable, -);
ROOS_OPERATOR(Multipliable, *);
ROOS_OPERATOR(Dividable, /);
ROOS_COMMUTATIVE_OPERATOR(Addable, +);
ROOS_COMMUTATIVE_OPERATOR(Multipliable, *);

}

#undef ROOS_OPERATOR
#undef ROOS_COMMUTATIVE_OPERATOR

#endif