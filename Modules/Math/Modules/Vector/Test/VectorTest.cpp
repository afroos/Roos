#include "catch.hpp"
#include <Roos/Math/Vector/Vector.hpp>

using namespace Roos::Math;

// TODO: reduce class size caused by Roos::Math::Operators.
//TEST_CASE("Vector storage is minimum") 
//{
//	REQUIRE(sizeof(Vector3d) == 3 * sizeof(double));
//	REQUIRE(sizeof(Vector<int, 10>) == 10 * sizeof(int));
//}

TEST_CASE("Vector constructors") 
{
	Vector2d a;
	Vector2d b{};
	Vector2d c{0.0, 0.0};
	Vector<double, 5> d{-3.0, -1.5, 0.0, 1.5, 3.0};
	Vector<double, 5> e(-3.0, -1.5, 0.0, 1.5, 3.0);
	Vector<double, 5> f({-3.0, -1.5, 0.0, 1.5, 3.0});
	Vector<double, 5> g = {-3.0, -1.5, 0.0, 1.5, 3.0};
	Vector3i h{-1, 0, 1};
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

TEST_CASE("Vector assignment")
{
	Vector2f a{-1.0f, -1.0f};
	Vector2f b{0.0f, 1.0f};
	a = b;
	b = {2.0f, 3.0f};

	REQUIRE(a == Vector2f{0.0f, 1.0f});
	REQUIRE(b == Vector2f{2.0f, 3.0f});
}

TEST_CASE("Vector acessors")
{
	Vector4d a{1.0, 1.0, 1.0, 1.0};
	Vector4d b{2.0, 2.0, 2.0, 2.0};
	Vector4d c{3.0, 3.0, 3.0, 3.0};
	Vector4d d{4.0, 4.0, 4.0, 4.0};

	a[0] = -1.0;
	a[1] = -0.5;
	a[2] = 0.0;
	a[3] = 0.5;

	b(0) = a[0];
	b(1) = a[1];
	b(2) = a[2];
	b(3) = a[3];

	c.x() = b(0);
	c.y() = b(1);
	c.z() = b(2);
	c.w() = b(3);

	d[0] = c.x();
	d[1] = c.y();
	d[2] = c.z();
	d[3] = c.w();

	REQUIRE(a == Vector4d{-1.0, -0.5, 0.0, 0.5});
	REQUIRE(b == a);
	REQUIRE(c == b);
	REQUIRE(d == c);
}

TEST_CASE("Vector arithmetic operators")
{
	Vector3d a{-1.0, -2.0, 3.0};
	Vector3d b{1.0, 1.0, 1.0};
	Vector3d c;
	
	c = +a;
	REQUIRE(c == a);

	c = -a;
	REQUIRE(c == Vector3d{1.0, 2.0, -3.0});

	c += Vector3d{-1.0, -1.0, 1.0};
	REQUIRE(c == Vector3d{0.0, 1.0, -2.0});

	c -= Vector3d{0.5, 0.5, 0.5};
	REQUIRE(c == Vector3d{-0.5, 0.5, -2.5});

	c *= Vector3d{-1.0, 2.0, 3.0};
	REQUIRE(c == Vector3d{0.5, 1.0, -7.5});

	c /= Vector3d{0.5, 1.0, -2.5};
	REQUIRE(c == Vector3d{1.0, 1.0, 3.0});

	c *= 3.0;
	REQUIRE(c == Vector3d{3.0, 3.0, 9.0});

	c /= -1.5;
	REQUIRE(c == Vector3d{-2.0, -2.0, -6.0});

	c = a + b;
	REQUIRE(c == Vector3d{ 0.0, -1.0, 4.0});

	c = a - b;
	REQUIRE(c == Vector3d{-2.0, -3.0, 2.0});

	c = a * 1.5;
	REQUIRE(c == Vector3d{-1.5, -3.0, 4.5});

	c = -1.5 * a;
	REQUIRE(c == Vector3d{1.5, 3.0, -4.5});

	c = b / 0.5;
	REQUIRE(c == Vector3d{2.0, 2.0, 2.0});
}

TEST_CASE("Vector comparison operators")
{
	Vector3d a{-1.0, -2.0, 3.0};
	Vector3d b{-1.0, -2.0, 3.0};
	Vector3d c{-1.0, -3.0, 3.0};

	REQUIRE(b == a);
	REQUIRE(c != a);
	REQUIRE(c < b);
	REQUIRE(b > c);
	REQUIRE(a <= b);
	REQUIRE(a >= b);
}

TEST_CASE("Vector dot product")
{
	Vector3i a{1, 0, 0};
	Vector3i b{0, 1, 0};
	Vector3i c{-1, 0, 0};
	Vector3i d{0, -1, 0};
	Vector3i e{1, 2, 3};
	Vector3i f{4, 5, 6};

	REQUIRE(dot(a, a) == 1);
	REQUIRE(dot(a, b) == 0);
	REQUIRE(dot(a, c) == -1);
	REQUIRE(dot(a, d) == 0);
	REQUIRE(dot(e, f) == 32);
}

