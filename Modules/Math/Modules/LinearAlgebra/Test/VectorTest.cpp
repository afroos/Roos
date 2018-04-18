#include "catch.hpp"
#include <Roos/Math/LinearAlgebra/Vector.hpp>

using namespace Roos::Math;

TEST_CASE("Vector storage is minimum") 
{
	REQUIRE(sizeof(Vector3d) == 3 * sizeof(double));
	REQUIRE(sizeof(Vector<int, 10>) == 10 * sizeof(int));
}

TEST_CASE("Vector constructors") 
{
	Vector2d a;
	Vector2d b{};
	Vector2d c{0.0, 0.0};
	Vector<double, 5> d{-3.0, -1.5, 0.0, 1.5, 3.0};
	Vector<double, 5> e(-3.0, -1.5, 0.0, 1.5, 3.0);
	Vector<double, 5> f({-3.0, -1.5, 0.0, 1.5, 3.0});
	Vector<double, 5> g = {-3.0, -1.5, 0.0, 1.5, 3.0};
	Vector3i h{-1, -0, 1};
	auto i{h};
	auto j{std::move(i)};

	REQUIRE(a == b);
	REQUIRE(b == c);
	REQUIRE(d == e);
	REQUIRE(e == f);
	REQUIRE(f == g);
	REQUIRE(h == i);
	REQUIRE(h == j);
}

TEST_CASE("Vector constants") 
{
	auto a = Vector4i::Zero();
	auto b = Vector4i::UnitX();
	auto c = Vector4i::UnitY();
	auto d = Vector4i::UnitZ();
	auto e = Vector4i::UnitW();
	auto f = Vector<int, 5>::Unit(4);
	Vector4i g{0, 0, 0, 0};
	Vector4i h{1, 0, 0, 0};
	Vector4i i{0, 1, 0, 0};
	Vector4i j{0, 0, 1, 0};
	Vector4i k{0, 0, 0, 1};
	Vector<int, 5> l{0, 0, 0, 0, 1};

	REQUIRE(a == g);
	REQUIRE(b == h);
	REQUIRE(c == i);
	REQUIRE(d == j);
	REQUIRE(e == k);
	REQUIRE(f == l);
}