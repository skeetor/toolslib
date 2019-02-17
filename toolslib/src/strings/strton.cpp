#include <limits.h>

#include "toolslib/toolslib_api.h"
#include "toolslib/strings/numbers.h"

namespace toolslib
{
	namespace strings
	{
		// ******************************************************************************
		int8_t TOOLSLIB_API strto8(const char *nptr, const char *end, const char **endptr, register int base)
		{
			return strton<int8_t>(nptr, end, endptr, base);
		}

		int16_t TOOLSLIB_API strto16(const char *nptr, const char *end, const char **endptr, register int base)
		{
			return strton<int16_t>(nptr, end, endptr, base);
		}

		int32_t TOOLSLIB_API strto32(const char *nptr, const char *end, const char **endptr, register int base)
		{
			return strton<int32_t>(nptr, end, endptr, base);
		}

		int64_t TOOLSLIB_API strto64(const char *nptr, const char *end, const char **endptr, register int base)
		{
			return strton<int64_t>(nptr, end, endptr, base);
		}

		// ******************************************************************************
		int8_t TOOLSLIB_API fromDecimal<int8_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto8(str, end, pScanned, 10);
		}

		int16_t TOOLSLIB_API fromDecimal<int16_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto16(str, end, pScanned, 10);
		}

		int32_t TOOLSLIB_API fromDecimal<int32_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto32(str, end, pScanned, 10);
		}

		int64_t TOOLSLIB_API fromDecimal<int64_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto64(str, end, pScanned, 10);
		}

		// ******************************************************************************
		uint8_t TOOLSLIB_API strtou8(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative)
		{
			return strtoun<uint8_t>(nptr, end, endptr, base, acceptNegative);
		}

		uint16_t TOOLSLIB_API strtou16(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative)
		{
			return strtoun<uint16_t>(nptr, end, endptr, base, acceptNegative);
		}

		uint32_t TOOLSLIB_API strtou32(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative)
		{
			return strtoun<uint32_t>(nptr, end, endptr, base, acceptNegative);
		}

		uint64_t TOOLSLIB_API strtou64(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative)
		{
			return strtoun<uint64_t>(nptr, end, endptr, base, acceptNegative);
		}

		// ******************************************************************************
		uint8_t TOOLSLIB_API fromDecimal<uint8_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou8(str, end, pScanned, 10, true);
		}

		uint16_t TOOLSLIB_API fromDecimal<uint16_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou16(str, end, pScanned, 10, true);
		}

		uint32_t TOOLSLIB_API fromDecimal<uint32_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou32(str, end, pScanned, 10, true);
		}

		uint64_t TOOLSLIB_API fromDecimal<uint64_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou64(str, end, pScanned, 10, true);
		}

		uint8_t TOOLSLIB_API fromUnsignedDecimal<uint8_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou8(str, end, pScanned, 10, false);
		}

		uint16_t TOOLSLIB_API fromUnsignedDecimal<uint16_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou16(str, end, pScanned, 10, false);
		}

		uint32_t TOOLSLIB_API fromUnsignedDecimal<uint32_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou32(str, end, pScanned, 10, false);
		}

		uint64_t TOOLSLIB_API fromUnsignedDecimal<uint64_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou64(str, end, pScanned, 10, false);
		}

		// ******************************************************************************
		int8_t TOOLSLIB_API fromHex<int8_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto8(str, end, pScanned, 16);
		}

		int16_t TOOLSLIB_API fromHex<int16_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto16(str, end, pScanned, 16);
		}

		int32_t TOOLSLIB_API fromHex<int32_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto32(str, end, pScanned, 16);
		}

		int64_t TOOLSLIB_API fromHex<int64_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto64(str, end, pScanned, 16);
		}

		// ******************************************************************************
		uint8_t TOOLSLIB_API fromHex<uint8_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou8(str, end, pScanned, 16, true);
		}

		uint16_t TOOLSLIB_API fromHex<uint16_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou16(str, end, pScanned, 16, true);
		}

		uint32_t TOOLSLIB_API fromHex<uint32_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou32(str, end, pScanned, 16, true);
		}

		uint64_t TOOLSLIB_API fromHex<uint64_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou64(str, end, pScanned, 16, true);
		}

		// ******************************************************************************
		int8_t TOOLSLIB_API fromBinary<int8_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto8(str, end, pScanned, 2);
		}

		int16_t TOOLSLIB_API fromBinary<int16_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto16(str, end, pScanned, 2);
		}

		int32_t TOOLSLIB_API fromBinary<int32_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto32(str, end, pScanned, 2);
		}

		int64_t TOOLSLIB_API fromBinary<int64_t>(const char *str, const char *end, const char **pScanned)
		{
			return strto64(str, end, pScanned, 2);
		}

		// ******************************************************************************
		uint8_t TOOLSLIB_API fromBinary<uint8_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou8(str, end, pScanned, 2, true);
		}

		uint16_t TOOLSLIB_API fromBinary<uint16_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou16(str, end, pScanned, 2, true);
		}

		uint32_t TOOLSLIB_API fromBinary<uint32_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou32(str, end, pScanned, 2, true);
		}

		uint64_t TOOLSLIB_API fromBinary<uint64_t>(const char *str, const char *end, const char **pScanned)
		{
			return strtou64(str, end, pScanned, 2, true);
		}
	}
}
