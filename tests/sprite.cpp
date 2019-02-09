#include "catch.hpp"
#include "FayEngine/FayEngine.h"

TEST_CASE( "Sprite positioning", "[sprite/affine_transform]" ) {
	using namespace FE;

	SpritePtr spr = Sprite::create();

	SECTION("alloc") {
		REQUIRE(spr);
	}
	
	SECTION("child") {
		SpritePtr spr2 = Sprite::create();
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

