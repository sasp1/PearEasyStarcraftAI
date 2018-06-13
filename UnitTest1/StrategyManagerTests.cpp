#include "stdafx.h"
#include "UnitMock.h"
#include "VultureUnitMock.h"
#include "VultureUnitMockFarAway.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StrategyManagerTests
{
	TEST_CLASS(TANKS) {

		BWAPI::Unitset* unitSet; 

		TEST_METHOD_INITIALIZE(init) {
			unitSet = new Unitset(); 
		}
		TEST_METHOD(shouldBuildTanksIfProtossCanons) {

		}

	}; 
}