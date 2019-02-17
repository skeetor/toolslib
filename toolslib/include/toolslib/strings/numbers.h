#ifndef _STRING_NUMBERS_H
#define _STRING_NUMBERS_H

#include <cctype>
#include <string>

#include "toolslib/toolslib_api.h"
#include "toolslib/toolslib_def.h"
#include "toolslib/strings/strton.h"

namespace toolslib
{
	namespace strings
	{
		// These functions throw an invalid_argument exception in case of an error

		int8_t TOOLSLIB_API strto8(const char *nptr, const char *end, const char **endptr, register int base);
		int16_t TOOLSLIB_API strto16(const char *nptr, const char *end, const char **endptr, register int base);
		int32_t TOOLSLIB_API strto32(const char *nptr, const char *end, const char **endptr, register int base);
		int64_t TOOLSLIB_API strto64(const char *nptr, const char *end, const char **endptr, register int base);

		uint8_t TOOLSLIB_API strtou8(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative = true);
		uint16_t TOOLSLIB_API strtou16(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative = true);
		uint32_t TOOLSLIB_API strtou32(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative = true);
		uint64_t TOOLSLIB_API strtou64(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative = true);

		template <typename T>
		T fromDecimal(const char *str, const char *end, const char **pScanned)
		{
			static_assert(false, "Unspported type!");
		}

		// ******************************************************************************
		template<> int8_t TOOLSLIB_API fromDecimal<int8_t>(const char *str, const char *end, const char **pScanned);
		template<> int16_t TOOLSLIB_API fromDecimal<int16_t>(const char *str, const char *end, const char **pScanned);
		template<> int32_t TOOLSLIB_API fromDecimal<int32_t>(const char *str, const char *end, const char **pScanned);
		template<> int64_t TOOLSLIB_API fromDecimal<int64_t>(const char *str, const char *end, const char **pScanned);

		// Even though these are unsigned types a negaitve input will be converted.
		template<> uint8_t TOOLSLIB_API fromDecimal<uint8_t>(const char *str, const char *end, const char **pScanned);
		template<> uint16_t TOOLSLIB_API fromDecimal<uint16_t>(const char *str, const char *end, const char **pScanned);
		template<> uint32_t TOOLSLIB_API fromDecimal<uint32_t>(const char *str, const char *end, const char **pScanned);
		template<> uint64_t TOOLSLIB_API fromDecimal<uint64_t>(const char *str, const char *end, const char **pScanned);

		template <typename T>
		T fromUnsignedDecimal(const char *str, const char *end, const char **pScanned)
		{
			static_assert(false, "Unspported type!");
		}

		// These are unsigned types and a negaitve input will cause an error.
		template<> uint8_t TOOLSLIB_API fromUnsignedDecimal<uint8_t>(const char *str, const char *end, const char **pScanned);
		template<> uint16_t TOOLSLIB_API fromUnsignedDecimal<uint16_t>(const char *str, const char *end, const char **pScanned);
		template<> uint32_t TOOLSLIB_API fromUnsignedDecimal<uint32_t>(const char *str, const char *end, const char **pScanned);
		template<> uint64_t TOOLSLIB_API fromUnsignedDecimal<uint64_t>(const char *str, const char *end, const char **pScanned);

		// ******************************************************************************
		template <typename T>
		T fromHex(const char *str, const char *end, const char **pScanned)
		{
			static_assert(false, "Unspported type!");
		}

		template<> int8_t TOOLSLIB_API fromHex<int8_t>(const char *str, const char *end, const char **pScanned);
		template<> int16_t TOOLSLIB_API fromHex<int16_t>(const char *str, const char *end, const char **pScanned);
		template<> int32_t TOOLSLIB_API fromHex<int32_t>(const char *str, const char *end, const char **pScanned);
		template<> int64_t TOOLSLIB_API fromHex<int64_t>(const char *str, const char *end, const char **pScanned);
		template<> uint8_t TOOLSLIB_API fromHex<uint8_t>(const char *str, const char *end, const char **pScanned);
		template<> uint16_t TOOLSLIB_API fromHex<uint16_t>(const char *str, const char *end, const char **pScanned);
		template<> uint32_t TOOLSLIB_API fromHex<uint32_t>(const char *str, const char *end, const char **pScanned);
		template<> uint64_t TOOLSLIB_API fromHex<uint64_t>(const char *str, const char *end, const char **pScanned);

		// ******************************************************************************
		template <typename T>
		T fromBinary(const char *str, const char *end, const char **pScanned)
		{
			static_assert(false, "Unspported type!");
		}

		template<> int8_t TOOLSLIB_API fromBinary<int8_t>(const char *str, const char *end, const char **pScanned);
		template<> int16_t TOOLSLIB_API fromBinary<int16_t>(const char *str, const char *end, const char **pScanned);
		template<> int32_t TOOLSLIB_API fromBinary<int32_t>(const char *str, const char *end, const char **pScanned);
		template<> int64_t TOOLSLIB_API fromBinary<int64_t>(const char *str, const char *end, const char **pScanned);
		template<> uint8_t TOOLSLIB_API fromBinary<uint8_t>(const char *str, const char *end, const char **pScanned);
		template<> uint16_t TOOLSLIB_API fromBinary<uint16_t>(const char *str, const char *end, const char **pScanned);
		template<> uint32_t TOOLSLIB_API fromBinary<uint32_t>(const char *str, const char *end, const char **pScanned);
		template<> uint64_t TOOLSLIB_API fromBinary<uint64_t>(const char *str, const char *end, const char **pScanned);
	}
}

#endif // _STRING_HELPERS_H
