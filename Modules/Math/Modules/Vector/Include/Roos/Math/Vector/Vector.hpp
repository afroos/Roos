#ifndef ROOS_MATH_VECTOR_VECTOR_HPP
#define ROOS_MATH_VECTOR_VECTOR_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <Roos/Math/Operators.hpp>

namespace Roos::Math {

template <typename Real, std::size_t Dimension>
class Vector :
	Operators::EqualityComparable<Vector<Real, Dimension>>,
	Operators::LessThanComparable<Vector<Real, Dimension>>,
	Operators::Addable<Vector<Real, Dimension>>,
	Operators::Subtractable<Vector<Real, Dimension>>,
	Operators::CommutativeMultipliable<Vector<Real, Dimension>, Real>,
	Operators::Dividable<Vector<Real, Dimension>, Real>
{
public:

	static_assert(Dimension > 0, "Dimension must be greater than 0.");
	static_assert(std::is_arithmetic_v<Real>, "Coordinate type must be arithmetic.");

	using SizeType = std::size_t;
	using Reference = Real&;
	using ConstReference = const Real&;
	using Iterator = typename std::array<Real, Dimension>::iterator;
	using ConstIterator = typename std::array<Real, Dimension>::const_iterator;
	
	constexpr Vector() noexcept = default;

	template<typename ...Args, 
		typename = std::enable_if_t<sizeof...(Args) == Dimension && 
			!(sizeof...(Args) == 1 && std::is_same_v<std::common_type_t<Args...>, Vector<Real, Dimension>>)>>
	constexpr Vector(Args&&... coordinates) noexcept :
		tuple{{coordinates...}} 
	{
	}

	static constexpr Vector Zero() noexcept
	{
		return Vector();
	}

	static constexpr Vector Unit(SizeType unitaryIndex) noexcept
	{
		Vector p;
		p[unitaryIndex] = Real{ 1 };
		return p;
	}

	static constexpr Vector UnitX() noexcept { return Unit(0); }

	template<typename = std::enable_if_t<(Dimension > 1)>>
	static constexpr Vector UnitY() noexcept { return Unit(1); }

	template<typename = std::enable_if_t<(Dimension > 2)>>
	static constexpr Vector UnitZ() noexcept { return Unit(2); }

	template<typename = std::enable_if_t<(Dimension > 3)>>
	static constexpr Vector UnitW() noexcept { return Unit(3); }

	constexpr ConstReference operator[](SizeType index) const noexcept
	{ 
		assert(0 <= index && index < Dimension);
		return tuple[index];
	}

	constexpr Reference operator[](SizeType index) noexcept
	{
		return const_cast<Reference>(std::as_const(*this).operator[](index));
	}

	constexpr ConstReference operator()(SizeType index) const noexcept
	{
		return (*this).operator[](index);
	}

	constexpr Reference operator()(SizeType index) noexcept
	{
		return (*this).operator[](index);
	}

	constexpr ConstReference x() const noexcept { return (*this)[0]; }
	constexpr Reference x() noexcept { return (*this)[0]; }

	template<typename = std::enable_if_t<(Dimension > 1)>>
	constexpr ConstReference y() const noexcept { return (*this)[1]; }

	template<typename = std::enable_if_t<(Dimension > 1)>>
	constexpr Reference y() noexcept
	{
		return const_cast<Real&>(std::as_const(*this).y());
	}

	template<typename = std::enable_if_t<(Dimension > 2)>>
	constexpr ConstReference z() const noexcept { return (*this)[2]; }

	template<typename = std::enable_if_t<(Dimension > 2), int>>
	constexpr Reference z() noexcept
	{
		return const_cast<Real&>(std::as_const(*this).z());
	}

	template<typename = std::enable_if_t<(Dimension > 3)>>
	constexpr ConstReference w() const noexcept { return (*this)[3]; }

	template<typename = std::enable_if_t<(Dimension > 3), int>>
	constexpr Reference w() noexcept
	{
		return const_cast<Real&>(std::as_const(*this).w());
	}
	
	ConstIterator begin() const noexcept { return tuple.begin(); }
	Iterator begin() noexcept { return tuple.begin(); }

	ConstIterator end() const noexcept { return tuple.end(); }
	Iterator end() noexcept { return tuple.end(); }

	constexpr Vector& operator+=(const Vector& v) noexcept
	{
		std::transform(begin(), end(), v.begin(), begin(), std::plus<Real>());
		return *this;
	}

	constexpr Vector& operator-=(const Vector& v) noexcept
	{
		std::transform(begin(), end(), v.begin(), begin(), std::minus<Real>());
		return *this;
	}

	constexpr Vector& operator*=(const Vector& v) noexcept
	{
		std::transform(begin(), end(), v.begin(), begin(), std::multiplies<Real>());
		return *this;
	}

	constexpr Vector& operator/=(const Vector& v) noexcept
	{
		std::transform(begin(), end(), v.begin(), begin(), std::divides<Real>());
		return *this;
	}

	constexpr Vector& operator*=(const Real& s) noexcept
	{
		for (auto& coordinate : tuple) { coordinate *= s; }
		return *this;
	}

	constexpr Vector& operator/=(const Real& s) noexcept
	{
		for (auto& coordinate : tuple) { coordinate /= s; }
		return *this;
	}

private:
	std::array<Real, Dimension> tuple{};
};

template <typename Real, std::size_t Dimension>
inline constexpr bool operator==(const Vector<Real, Dimension>& a, const Vector<Real, Dimension>& b)
{
	return std::equal(a.begin(), a.end(), b.begin());
}

template <typename Real, std::size_t Dimension>
inline constexpr bool operator<(const Vector<Real, Dimension>& a, const Vector<Real, Dimension>& b)
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template <typename Real, std::size_t Dimension>
inline constexpr Vector<Real, Dimension> operator+(const Vector<Real, Dimension>& v)
{
	return v;
}

template <typename Real, std::size_t Dimension>
inline constexpr Vector<Real, Dimension> operator-(const Vector<Real, Dimension>& v)
{
	Vector<Real, Dimension> result;
	std::transform(v.begin(), v.end(), result.begin(), std::negate<Real>());
	return result;
}

template <typename Real, std::size_t Dimension>
std::ostream& operator<<(std::ostream& os, const Vector<Real, Dimension>& v)
{
	os << '(';
	std::copy(v.begin(), v.end(), std::ostream_iterator<Real>(os, ", "));
	os << "\b\b)";
	return os;
}

template <typename Real, std::size_t Dimension>
inline constexpr Real dot(const Vector<Real, Dimension>& a, const Vector<Real, Dimension>& b)
{
	return static_cast<Real>(std::inner_product(a.begin(), a.end(), b.begin(), 0.0));
}

template <typename Real, std::size_t Dimension>
inline constexpr Real normSquared(const Vector<Real, Dimension>& v)
{
	return dot(v, v);
}

template <typename Real, std::size_t Dimension>
inline constexpr Real norm(const Vector<Real, Dimension>& v)
{
	return std::sqrt(normSquared(v));
}

template <typename Real>
using Vector2 = Vector<Real, 2>;
template <typename Real>
using Vector3 = Vector<Real, 3>;
template <typename Real>
using Vector4 = Vector<Real, 4>;

using Vector2i = Vector<int, 2>;
using Vector2f = Vector<float, 2>;
using Vector2d = Vector<double, 2>;

using Vector3i = Vector<int, 3>;
using Vector3f = Vector<float, 3>;
using Vector3d = Vector<double, 3>;

using Vector4i = Vector<int, 4>;
using Vector4f = Vector<float, 4>;
using Vector4d = Vector<double, 4>;

}

#endif