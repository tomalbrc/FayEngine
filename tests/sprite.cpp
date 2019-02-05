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
	}
	
	SECTION("rotation") {
		const auto &child = spr->getChildren()[1];
		spr->setZRotation(DegreesToRadians(90.0));
		
		
	}
}

