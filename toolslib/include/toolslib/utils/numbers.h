#ifndef UTILS_NUMBERS_H
#define UTILS_NUMBERS_H

#include <string>
#include <cstdlib>

namespace toolslib
{
	namespace strings
	{
		template <typename T>
		T fromDecimal(const char *str, const char *end, const char **pScanned = nullptr)
		{
			T val = 0;

			if (str >= end)
			{
				if (pScanned)
					*pScanned = end;

				return val;
			}

			while (str < end)
			{
				char c = *str++ - '0';
				if (c >= 0 && c <= 9)
				{
					val *= 10;
					val += (T)c;
				}
				else
				{
					str--;
					break;
				}
			}

			if (pScanned)
				*pScanned = str;

			return val;
		}

		template <typename T>
		T fromHex(const char *str, const char *end, const char **pScanned = nullptr)
		{
			T val = 0;

			if (str >= end)
			{
				if (pScanned)
					*pScanned = end;

				return val;
			}

			if (pScanned)
				*pScanned = str;

			return val;
		}

		template <typename T>
		T fromBinary(const char *str, const char *end, const char **pScanned = nullptr)
		{
			T val = 0;

			if (str >= end)
			{
				if (pScanned)
					*pScanned = end;

				return val;
			}

			if (pScanned)
				*pScanned = str;

			return val;
		}

		template <typename T>
		T toNumber(const char *str, const char *end, const char **pScanned = nullptr)
		{
			T val = 0;

			if (str >= end)
			{
				if (pScanned)
					*pScanned = end;

				return val;
			}

			if (*end-1 == 'h')
				return fromHex<T>(str, end-1, pScanned);

			switch (*str)
			{
				case '%':
					return fromBinary<T>(str+1, end, pScanned);

				case '0':
				{
					if(str+1 < end && *str+1 == 'x')
						return fromHex<T>(str + 2, end, pScanned);
				}
				break;

				case '$':
					return fromHex<T>(str + 1, end, pScanned);
			}

			return fromDecimal<T>(str, end, pScanned);
		}

		template <typename T>
		T toNumber(const std::string &oNumber, const char **pScanned = nullptr)
		{
			return toNumber<T>(&oNumber[0], &oNumber[oNumber.size()], pScanned);
		}
	}
}

#endif // UTILS_NUMBERS_H
