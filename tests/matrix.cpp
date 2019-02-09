#include "catch.hpp"
#include "rawket/rawket.h"

TEST_CASE( "Matrix calculations", "[matrix]" ) {
	using namespace fe;
	
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
	
	SECTION("matrix-matrix multiplication (m*scale(2,2))") {
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
        
        SECTION("matrix-vector multiplication (m*vec)") {
            auto vec = Vec2{1,2};
            vec = Vec2ApplyAffineTransform(vec, m);
            
            REQUIRE(vec.x == 2.f);
            REQUIRE(vec.y == 4.f);
        }
	}
}
