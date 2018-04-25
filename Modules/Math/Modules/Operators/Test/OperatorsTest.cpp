#include "catch.hpp"
#include <Roos/Math/Operators.hpp>

using namespace Roos::Math;

class C : 
	Operators::EqualityComparable<C>,
	Operators::LessThanComparable<C>,
	Operators::Addable<C>,
	Operators::CommutativeAddable<C, int>,
	Operators::Subtractable<C>,
	Operators::Subtractable<C, int>,
	Operators::Multipliable<C>,
	Operators::CommutativeMultipliable<C, int>,
	Operators::Dividable<C>,
	Operators::Dividable<C, int>
{
public:
	explicit constexpr C(const int v) noexcept : value(v)
	{
	}

	constexpr C& operator+=(const C& c) noexcept
	{
		value += c.value;
		return *this;
	}

	constexpr C& operator-=(const C& c)
	{
		value -= c.value;
		return *this;
	}

	constexpr C& operator*=(const C& c)
	{
		value *= c.value;
		return *this;
	}

	constexpr C& operator/=(const C& c)
	{
		value /= c.value;
		return *this;
	}

	constexpr C& operator+=(const int v)
	{
		value += v;
		return *this;
	}

	constexpr C& operator-=(const int v)
	{
		value -= v;
		return *this;
	}

	constexpr C& operator*=(const int v)
	{
		value *= v;
		return *this;
	}

	constexpr C& operator/=(const int v)
	{
		value /= v;
		return *this;
	}

	int value;
};

constexpr bool operator==(const C& a, const C& b)
{
	return a.value == b.value;
}

constexpr bool operator<(const C& a, const C& b)
{
	return a.value < b.value;
}

std::ostream& operator<<(std::ostream& os, const C& c)
{
	os << c.value;
	return os;
}


TEST_CASE("Comparison operators")
{
	C c1(1);
	C c2(2);
	C c3(3);

	REQUIRE(c1 == c1);
	REQUIRE(c1 != c2);

	REQUIRE(c1 < c2);
	REQUIRE(c1 <= c2);
	REQUIRE(c2 <= c2);
	REQUIRE(c3 > c2);
	REQUIRE(c3 >= c2);
	REQUIRE(c2 >= c2);
}

TEST_CASE("Arithmetic operators") 
{
	C c1(1);
	C c2(2);
	C c3(3);
	C c4(6);

	REQUIRE(c1 + c2 == c3);
	REQUIRE(1 + c2 == c3);
	REQUIRE(c1 + 2 == c3);

	REQUIRE(c3 - c1 == c2);
	REQUIRE(c3 - 1 == c2);

	REQUIRE(c2 * c3 == c4);
	REQUIRE(c1 * 2 == c2);
	REQUIRE(3 * c1 == c3);

	REQUIRE(c4 / c3 == c2);
	REQUIRE(c2 / 2 == c1);
	REQUIRE((c1 + c3) / 2 == c2);
}