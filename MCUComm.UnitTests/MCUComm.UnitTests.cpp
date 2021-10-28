#include "pch.h"
#include "CppUnitTest.h"
#include "../MCUComm/Device.h"
#include "..//MCUComm/Device.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MCUCommUnitTests
{
	//test device class
	TEST_CLASS(DeviceTests)
	{
	public:
		
		//test convert method
		TEST_METHOD(Convert__ValIsValid_ReturnEqual)
		{
			//arrange
			Device Pot(0xFE, "Volts", 2.0, 2.4, 3.3);
			unsigned char Value = 0xF0;
			double Result = 0.0;

			//act
			Result = Pot.Convert(Value);

			//assert
			Assert::AreEqual(Result, 480.0);

		}

		//test evaluate method
		TEST_METHOD(Evaluate_ValIsValid_ReturnTrue)
		{
			//arrange
			Device Pot(0xFE, "Volts", 2.0, 2.4, 3.3);
			double Value = 3.0;
			bool Result = false;

			//act
			Result = Pot.Evaluate(Value);

			//assert
			Assert::IsTrue(Result);
		}

		//test evaluate method
		TEST_METHOD(Evaluate_ValIsLessThanMin_ReturnFalse)
		{
			//arrange
			Device Pot(0xFE, "Volts", 2.0, 2.4, 3.3);
			double Value = 2.0;
			bool Result = false;

			//act
			Result = Pot.Evaluate(Value);

			//assert
			Assert::IsFalse(Result);
		}

		//test evaluate method
		TEST_METHOD(Evaluate_ValIsGreaterThanMax_ReturnFalse)
		{
			//arrange
			Device Pot(0xFE, "Volts", 2.0, 2.4, 3.3);
			double Value = 4.0;
			bool Result = false;

			//act
			Result = Pot.Evaluate(Value);

			//assert
			Assert::IsFalse(Result);
		}
	};
}
