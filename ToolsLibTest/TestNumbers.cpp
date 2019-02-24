#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS

#include <string>

#include "gtest/gtest.h"

#include "toolslib/toolslib_api.h"
#include "toolslib/strings/numbers.h"

#include <iostream>


using namespace std;
using namespace toolslib;
using namespace toolslib::strings;

namespace
{
	TEST(NumberConversion, Decimal8)
	{
		string nr;
		const char *str;
		const char *end;
		const char *scanned;
		int8_t i;
		uint8_t ui;

		// Arbitrary valid value
		nr = "120";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;
		EXPECT_NO_THROW((i = fromDecimal<int8_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint8_t>(str, end, &scanned)));

		EXPECT_EQ(120, i);
		EXPECT_EQ(120u, ui);

		// Arbitrary valid negative value
		nr = "-127";			// 0x81
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		EXPECT_NO_THROW((i = fromDecimal<int8_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint8_t>(str, end, &scanned)));

		// By default the decimal function accepts negative numbers even for unsigned types
		// and covnerts them to their binary representation.
		EXPECT_EQ(-127, i);
		EXPECT_EQ(129u, ui);

		// Dont accept negative numbers for unsigned types as a invalid argument.
		ui = (uint8_t)-1;
		EXPECT_THROW((ui = fromUnsignedDecimal<uint8_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ((uint8_t)-1, ui);

		// Out of bounds for signed but not for unsigned.
		nr = "128";				// 0x80
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint8_t)-1;

		EXPECT_THROW((i = fromDecimal<int8_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint8_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(128u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "-128";			// 0x80
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint8_t)-1;

		EXPECT_THROW((i = fromDecimal<int8_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint8_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(128u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "255";			// 0xff
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint8_t)-1;

		EXPECT_THROW((i = fromDecimal<int8_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint8_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(255u, ui);

		// Out of bounds for signed, and for unsigned
		nr = "256";			// 0x00
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint8_t)-1;

		EXPECT_THROW((i = fromDecimal<int8_t>(str, end, &scanned)), invalid_argument);
		EXPECT_THROW((ui = fromDecimal<uint8_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint8_t)-1, ui);
	}

	TEST(NumberConversion, Decimal16)
	{
		string nr;
		const char *str;
		const char *end;
		const char *scanned;
		int16_t i;
		uint16_t ui;

		// Arbitrary valid value
		nr = "24301";				// 0x5eed
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));

		EXPECT_EQ(24301, i);
		EXPECT_EQ(24301u, ui);

		// Arbitrary valid negative value
		nr = "-24301";				// 0xa113
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));

		EXPECT_EQ(-24301, i);
		EXPECT_EQ(41235u, ui);

		ui = (uint16_t)-1;
		EXPECT_THROW((ui = fromUnsignedDecimal<uint16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ((uint16_t)-1, ui);

		// Out of bounds for signed but not for unsigned.
		nr = "32768";				// 0x8000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;

		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(32768u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "-32768";				// 0x8000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;

		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(32768u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "65535";					// 0xffff
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;

		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(65535u, ui);

		// Out of bounds for signed, and for unsigned
		nr = "65536";					// 0x0000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;

		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint16_t)-1, ui);
	}

	TEST(NumberConversion, Decimal32)
	{
		string nr;
		const char *str;
		const char *end;
		const char *scanned;
		int32_t i;
		uint32_t ui;

		// Arbitrary valid value
		nr = "243010";				// 0x00038542
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;
		EXPECT_NO_THROW((i = fromDecimal<int32_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint32_t>(str, end, &scanned)));

		EXPECT_EQ(243010, i);
		EXPECT_EQ(243010u, ui);

		// Arbitrary valid negative value
		nr = "-243010";				// 0xfffc4aeb
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		EXPECT_NO_THROW((i = fromDecimal<int32_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint32_t>(str, end, &scanned)));

		EXPECT_EQ(-243010, i);
		EXPECT_EQ(4294724286u, ui);

		ui = (uint32_t)-1;
		EXPECT_THROW((ui = fromUnsignedDecimal<uint32_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ((uint32_t)-1, ui);

		// Out of bounds for signed but not for unsigned.
		nr = "2147483648";				// 0x80000000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint32_t)-1;

		EXPECT_THROW((i = fromDecimal<int32_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint32_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(2147483648u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "-2147483648";				// 0x80000000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint32_t)-1;

		EXPECT_THROW((i = fromDecimal<int32_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint32_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(2147483648u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "4294967295";					// 0xffffffff
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint32_t)-1;

		EXPECT_THROW((i = fromDecimal<int32_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint32_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(4294967295u, ui);

		// Out of bounds for signed, and for unsigned
		nr = "4294967296";					// 0x00000000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint32_t)-1;

		EXPECT_THROW((i = fromDecimal<int32_t>(str, end, &scanned)), invalid_argument);
		EXPECT_THROW((ui = fromDecimal<uint32_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint32_t)-1, ui);
	}

	TEST(NumberConversion, Decimal64)
	{
		string nr;
		const char *str;
		const char *end;
		const char *scanned;
		int64_t i;
		uint64_t ui;

		// Arbitrary valid value
		nr = "1152921934105146156";				// 0x1000 0064 0017 f32c
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint64_t)-1;
		EXPECT_NO_THROW((i = fromDecimal<int64_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint64_t>(str, end, &scanned)));

		EXPECT_EQ(1152921934105146156, i);
		EXPECT_EQ(1152921934105146156u, ui);

		// Arbitrary valid negative value
		nr = "-9223090991376364332";				// 0x8000 FF9B FFE8 0CD4
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint64_t)-1;
		EXPECT_NO_THROW((i = fromDecimal<int64_t>(str, end, &scanned)));
		EXPECT_NO_THROW((ui = fromDecimal<uint64_t>(str, end, &scanned)));

		EXPECT_EQ(-9223090991376364332, i);
		EXPECT_EQ( 9223653082333187284u, ui);

		ui = (uint64_t)-1;
		EXPECT_THROW((ui = fromUnsignedDecimal<uint64_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ((uint64_t)-1, ui);

		// Out of bounds for signed but not for unsigned.
		nr = "9223372036854775808";				// 0x8000 0000 0000 0000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint64_t)-1;

		EXPECT_THROW((i = fromDecimal<int64_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint64_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(9223372036854775808u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "-9223372036854775808";			// 0x8000 0000 0000 0000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint64_t)-1;

		EXPECT_THROW((i = fromDecimal<int64_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint64_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(9223372036854775808u, ui);

		// Out of bounds for signed, but not for unsigned
		nr = "18446744073709551615";			// 0xffff ffff ffff ffff
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint64_t)-1;

		EXPECT_THROW((i = fromDecimal<int64_t>(str, end, &scanned)), invalid_argument);
		EXPECT_NO_THROW((ui = fromDecimal<uint64_t>(str, end, &scanned)));
		EXPECT_EQ(-1, i);
		EXPECT_EQ(18446744073709551615u, ui);

		// Out of bounds for signed, and for unsigned
		nr = "18446744073709551616";			// 0x0000 0000 0000 0000
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint64_t)-1;

		EXPECT_THROW((i = fromDecimal<int64_t>(str, end, &scanned)), invalid_argument);
		EXPECT_THROW((ui = fromDecimal<uint64_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint64_t)-1, ui);
	}

	TEST(NumberConversion, InvalidBase)
	{
		string nr;
		const char *str;
		const char *end;
		const char *scanned;
		int16_t i;
		uint16_t ui;

		// Hex value instead of decimal
		nr = "30FA";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;

		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)), invalid_argument);

		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint16_t)-1, ui);
	}

	TEST(NumberConversion, BasicTests)
	{
		string nr;
		const char *str;
		const char *end;
		const char *scanned;
		int16_t i;
		uint16_t ui;

		// Hex value instead of decimal
		nr = "      ";
		str = &nr[0];
		end = &nr[nr.size()]-3;
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;

		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(scanned, end);
		EXPECT_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(scanned, end);

		EXPECT_EQ(end,  &nr[nr.size()] - 3);
		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint16_t)-1, ui);

		nr = "  24301  ";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, nullptr)));
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, nullptr)));

		EXPECT_EQ(24301, i);
		EXPECT_EQ(24301u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "24301";
		str = &nr[0];
		end = &nr[nr.size()-3];
		scanned = nullptr;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(24, i);
		EXPECT_EQ(24u, ui);
		EXPECT_EQ(end, &nr[nr.size()-3]);

		nr = "+24301";
		str = &nr[0];
		end = &nr[nr.size() - 3];
		scanned = nullptr;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(24, i);
		EXPECT_EQ(24u, ui);
		EXPECT_EQ(end, &nr[nr.size() - 3]);

		nr = "+-24301";
		str = &nr[0];
		end = &nr[nr.size() - 3];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ('-', *scanned);
		EXPECT_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ('-', *scanned);

		EXPECT_EQ(end, &nr[nr.size()] - 3);
		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint16_t)-1, ui);

		nr = "-+24301";
		str = &nr[0];
		end = &nr[nr.size() - 3];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ('+', *scanned);
		EXPECT_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ('+', *scanned);

		EXPECT_EQ(end, &nr[nr.size()] - 3);
		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint16_t)-1, ui);

		nr = "+24301-";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_EQ('-', *scanned);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ('-', *scanned);

		EXPECT_EQ(24301, i);
		EXPECT_EQ(24301u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "-24%301";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_EQ('%', *scanned);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ('%', *scanned);

		EXPECT_EQ(end, &nr[nr.size()]);
		EXPECT_EQ(-24, i);
		EXPECT_EQ(65512u, ui);

		nr = "+1";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(1, i);
		EXPECT_EQ(1u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "5";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = fromDecimal<int16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(5, i);
		EXPECT_EQ(5u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_THROW((i = fromDecimal<int16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(end, scanned);
		EXPECT_THROW((ui = fromDecimal<uint16_t>(str, end, &scanned)), invalid_argument);
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint16_t)-1, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "0x";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_THROW((i = strto16(str, end, &scanned, 0)), invalid_argument);
		EXPECT_EQ(end, scanned);
		EXPECT_THROW((i = strtou16(str, end, &scanned, 0)), invalid_argument);
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(-1, i);
		EXPECT_EQ((uint16_t)-1, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "010";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = strto16(str, end, &scanned, 0)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = strtou16(str, end, &scanned, 0)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(8, i);
		EXPECT_EQ(8u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "10";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = strto16(str, end, &scanned, 0)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = strtou16(str, end, &scanned, 0)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(10, i);
		EXPECT_EQ(10u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "0101";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = strto16(str, end, &scanned, 2)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = strtou16(str, end, &scanned, 2)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(5, i);
		EXPECT_EQ(5u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "0101";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = fromBinary<int16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = fromBinary<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(5, i);
		EXPECT_EQ(5u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);

		nr = "6A31";
		str = &nr[0];
		end = &nr[nr.size()];
		scanned = nullptr;

		i = -1;
		ui = (uint16_t)-1;
		EXPECT_NO_THROW((i = fromHex<int16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);
		EXPECT_NO_THROW((ui = fromHex<uint16_t>(str, end, &scanned)));
		EXPECT_EQ(end, scanned);

		EXPECT_EQ(27185, i);
		EXPECT_EQ(27185u, ui);
		EXPECT_EQ(end, &nr[nr.size()]);
	}
}
