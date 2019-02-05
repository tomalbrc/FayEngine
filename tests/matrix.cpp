#include "catch.hpp"
#include "FayEngine/FayEngine.h"

TEST_CASE( "Matrix calculations", "[matrix]" ) {
	using namespace FE;
	
	auto m = AffineTransformIdentity();

	SECTION("correct identity") {
		REQUIRE(m.m11 == 1.f);
		REQUIRE(m.m12 == 0.f);
		REQUIRE(m.m13 == 0.f);

		REQUIRE(m.m21 == 0.f);
		REQUIRE(m.m22 == 1.f);
		REQUIRE(m.m23 == 0.f);

		REQUIRE(m.m31 == 0.f);
		REQUIRE(m.m32 == 0.f);
		REQUIRE(m.m33 == 1.f);
	}
	
	SECTION("correct multiplication (m*scale(2,2))") {
		auto s = AffineTransformMakeScale(2,2);
		m = AffineTransformMultiply(m,s);
		
		REQUIRE(m.m11 == 2.f);
		REQUIRE(m.m12 == 0.f);
		REQUIRE(m.m13 == 0.f);

		REQUIRE(m.m21 == 0.f);
		REQUIRE(m.m22 == 2.f);
		REQUIRE(m.m23 == 0.f);

		REQUIRE(m.m31 == 0.f);
		REQUIRE(m.m32 == 0.f);
		REQUIRE(m.m33 == 1.f);
	}
}
