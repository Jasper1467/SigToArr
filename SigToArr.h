#pragma once

#include <array>

#ifdef SIGTOARR_USE_LOOKUP_TABLE
namespace details
{
	namespace SigToArr
	{
		inline constexpr int ASCIIHexToInt[] =
		{
			// ASCII
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

			// 0x80-FF (Omit this if you don't need to check for non-ASCII)
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
			-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		};
	} // namespace SigToArr

} // details
#endif

template <char... Chars>
class CSigToArr
{
	template <unsigned char Char>
	struct HexStringToInteger
	{
#ifdef SIGTOARR_USE_LOOKUP_TABLE
		static constexpr int m_nValue = details::SigToArr::ASCIIHexToInt[static_cast<int>(Char)];
#else
		static constexpr int m_nValue =
			(Char == '?') ? -1 : ((Char >= '0' && Char <= '9') ? (Char - '0') : (10 + (Char & 0x0F)));
#endif
	};

	template <char... Ch>
	struct HexStringToIntegerArray
	{
		static constexpr std::array<int, sizeof...(Ch)> m_arrValue = { HexStringToInteger<Ch>::m_nValue... };
	};

public:
	static constexpr std::array<int, sizeof...(Chars)> m_arrValue = { HexStringToIntegerArray<Chars>::m_arrValue... };

	constexpr auto Get() const
	{
		return m_arrValue;
	}
};
