#include "catch.hpp"
#include "rawket.h"

TEST_CASE( "sprite positioning", "[sprite/affine_transform]" ) {
	using namespace rkt;

	sprite_ptr spr = sprite::create();

	SECTION("alloc") {
		REQUIRE(spr);
	}
	
	SECTION("child") {
		sprite_ptr spr2 = sprite::create();
		spr->addChild(spr2);
		
		const auto &clds = spr->getChildren();
        
		REQUIRE(clds.size() == 1);
        
        SECTION("rotation") {
            const auto &child = clds.front();
            spr->setZRotation(DegreesToRadians(90.0));
            auto trans = child->worldToNodeTransform();
            REQUIRE(std::nearbyint(trans.m11) == 0.f); // see below
            REQUIRE(trans.m12 == -1.f);
            REQUIRE(trans.m13 == 0.f);
            
            REQUIRE(trans.m21 == 1.f);
            REQUIRE(std::nearbyint(trans.m11) == 0.f); // odd errors, so use nearest integral
            REQUIRE(trans.m23 == 0.f);
            
            REQUIRE(trans.m31 == 0.f);
            REQUIRE(trans.m32 == 0.f);
            REQUIRE(trans.m33 == 1.f);
        }
        
        
	}
}

