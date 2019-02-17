#ifndef _STRING_STRTON_H
#define _STRING_STRTON_H

		/*-
		 * Copyright (c) 1990 The Regents of the University of California.
		 * All rights reserved.
		 *
		 * Redistribution and use in source and binary forms, with or without
		 * modification, are permitted provided that the following conditions
		 * are met:
		 * 1. Redistributions of source code must retain the above copyright
		 *    notice, this list of conditions and the following disclaimer.
		 * 2. Redistributions in binary form must reproduce the above copyright
		 *    notice, this list of conditions and the following disclaimer in the
		 *    documentation and/or other materials provided with the distribution.
		 * 3. [rescinded 22 July 1999]
		 * 4. Neither the name of the University nor the names of its contributors
		 *    may be used to endorse or promote products derived from this software
		 *    without specific prior written permission.
		 *
		 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
		 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
		 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
		 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
		 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
		 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
		 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
		 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
		 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
		 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		 * SUCH DAMAGE.
		 */

		 /*
		 Source: https://github.com/gcc-mirror/gcc/blob/master/libiberty/strtol.c

		 @deftypefn Supplemental {long int} strtol (const char *@var{string}, @
		   char **@var{endptr}, int @var{base})
		 @deftypefnx Supplemental {unsigned long int} strtoul (const char *@var{string}, @
		   char **@var{endptr}, int @var{base})

		 The @code{strtol} function converts the string in @var{string} to a
		 long integer value according to the given @var{base}, which must be
		 between 2 and 36 inclusive, or be the special value 0.  If @var{base}
		 is 0, @code{strtol} will look for the prefixes @code{0} and @code{0x}
		 to indicate bases 8 and 16, respectively, else default to base 10.
		 When the base is 16 (either explicitly or implicitly), a prefix of
		 @code{0x} is allowed.  The handling of @var{endptr} is as that of
		 @code{strtod} above.  The @code{strtoul} function is the same, except
		 that the converted value is unsigned.

		 @end deftypefn

		 */
#include <cctype>
#include <string>
#include <limits>
#include <exception>
#include <type_traits>

#include "toolslib/toolslib_api.h"
#include "toolslib/toolslib_def.h"

#pragma warning (push)
#pragma warning(disable : 4146 4706 4244)

#ifdef _STRTON_NO_EXCEPTIONS

#define _STRTON_ERROR_RETURN(s, x)  errno = x; return 0;

#else

#define _STRTON_ERROR_RETURN(s, x)  throw std::invalid_argument(std::string(TOOLSLIB_DEFINE_TO_STRING(x))+":"+s)

#endif

#ifndef ISSPACE
#define ISSPACE(c) isspace(c)
#endif

#ifndef ISUPPER
#define ISUPPER(c) isupper(c)
#endif

#ifndef ISDIGIT
#define ISDIGIT(c) isdigit(c)
#endif

#ifndef ISALPHA
#define ISALPHA(c) isalpha(c)
#endif

#ifdef min
#define _redefine_min
#undef min
#endif

#ifdef max
#define _redefine_max
#undef max
#endif

namespace toolslib
{
	namespace strings
	{
		template <typename T>
		T strton(const char *nptr, const char *end, const char **endptr, register int base)
		{
			typedef typename std::make_unsigned<T>::type unsignedType;
			typedef typename std::make_signed<T>::type signedType;

			register const char *s = nptr;
			register unsignedType acc;
			register int c;
			register unsignedType cutoff;
			register int neg = 0, any, cutlim;

			// Since we only modify end when we are done we can safely reuse this pointer
			// as a safeguard.
			if (endptr == nullptr)
				endptr = &end;

			/*
			 * Skip white space and pick up leading +/- sign if any.
			 * If base is 0, allow 0x for hex and 0 for octal, else
			 * assume decimal; if base is already 16, allow 0x.
			 */
			do
			{
				c = *s++;
			} while (ISSPACE(c) && s < end);

			if (s >= end)
			{
				*endptr = end;
				_STRTON_ERROR_RETURN(std::string(nptr, end-nptr), EINVAL);
			}

			if (c == '-')
			{
				neg = 1;
				c = *s++;
			}
			else if (c == '+')
				c = *s++;

			if (s > end)
			{
				*endptr = end;
				_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), EINVAL);
			}

			if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X'))
			{
				c = s[1];
				s += 2;
				base = 16;
			}

			if (s > end)
			{
				*endptr = end;
				_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), EINVAL);
			}

			if (base == 0)
				base = c == '0' ? 8 : 10;

			/*
			 * Compute the cutoff value between legal numbers and illegal
			 * numbers.  That is the largest legal value, divided by the
			 * base.  An input number that is greater than this value, if
			 * followed by a legal input character, is too big.  One that
			 * is equal to this value may be valid or not; the limit
			 * between valid and invalid numbers is then based on the last
			 * digit.  For instance, if the range for longs is
			 * [-2147483648..2147483647] and the input base is 10,
			 * cutoff will be set to 214748364 and cutlim to either
			 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
			 * a value > 214748364, or equal but the next digit is > 7 (or 8),
			 * the number is too big, and we will return a range error.
			 *
			 * Set any if any `digits' consumed; make it negative to indicate
			 * overflow.
			 */
			cutoff = neg ? -(unsignedType)std::numeric_limits<signedType>::min() : std::numeric_limits<signedType>::max();
			cutlim = cutoff % (unsignedType)base;
			cutoff /= (unsignedType)base;

			for (acc = 0, any = 0;; (c = *s++))
			{
				if (s > end)
					break;

				if (ISDIGIT(c))
					c -= '0';
				else if (ISALPHA(c))
					c -= ISUPPER(c) ? 'A' - 10 : 'a' - 10;
				else
				{
					if (!any)
						any = -1;

					break;
				}

				if (c >= base)
				{
					any = -1;
					break;
				}

				if (any < 0 || acc > cutoff || (acc == cutoff && c >= cutlim))
				{
					any = -1;
					break;
				}
				else
				{
					any = 1;
					acc *= base;
					acc += c;
				}
			}

			if (any < 0)
			{
				*endptr = s-1;
				_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), ERANGE);
			}
			else if (neg)
				acc = -acc;

			*endptr = (char *)(any ? s - 1 : nptr);

			return (T)acc;
		}

		template <typename T>
		T strtoun(const char *nptr, const char *end, const char **endptr, register int base, bool acceptNegative = true)
		{
			typedef typename std::make_unsigned<T>::type unsignedType;
			typedef typename std::make_signed<T>::type signedType;

			register const char *s = nptr;
			register unsignedType acc;
			register int c;
			register unsignedType cutoff;
			register int neg = 0, any, cutlim;

			if (endptr == nullptr)
				endptr = &end;

			/*
			 * See strton for comments as to the logic used.
			 */
			do
			{
				c = *s++;
			} while (ISSPACE(c) && s < end);

			if (s >= end)
			{
				*endptr = end;
				_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), EINVAL);
			}

			if (c == '-')
			{
				if (acceptNegative)
				{
					neg = 1;
					c = *s++;
				}
				else
				{
					*endptr = end;
					_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), EINVAL);
				}
			}
			else if (c == '+')
				c = *s++;

			if (s > end)
			{
				*endptr = end;
				_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), EINVAL);
			}

			if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X'))
			{
				c = s[1];
				s += 2;
				base = 16;
			}

			if (s > end)
			{
				*endptr = end;
				_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), EINVAL);
			}

			if (base == 0)
				base = c == '0' ? 8 : 10;

			cutoff = (unsignedType)std::numeric_limits<unsignedType>::max() / (unsignedType)base;
			cutlim = (unsignedType)std::numeric_limits<unsignedType>::max() % (unsignedType)base;

			for (acc = 0, any = 0;; (c = *s++))
			{
				if (s > end)
					break;

				if (ISDIGIT(c))
					c -= '0';
				else if (ISALPHA(c))
					c -= ISUPPER(c) ? 'A' - 10 : 'a' - 10;
				else
				{
					if (!any)
						any = -1;

					break;
				}

				if (c >= base)
				{
					any = -1;
					break;
				}

				if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
				{
					any = -1;
					break;
				}
				else
				{
					any = 1;
					acc *= base;
					acc += c;
				}
			}

			if (any < 0)
			{
				*endptr = s-1;
				_STRTON_ERROR_RETURN(std::string(nptr, end - nptr), ERANGE);
			}
			else if (neg)
				acc = -acc;

			*endptr = (char *)(any ? s - 1 : nptr);

			return (T)acc;
		}
	}
}

#ifdef _redefine_min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef _redefine_max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#undef _redefine_min
#undef _redefine_max

#pragma warning (pop)

#endif // _STRING_HELPERS_H
