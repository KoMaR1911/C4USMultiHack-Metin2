#pragma once
#include <string>
#include <Windows.h>
#include <stdint.h>
#include <string>


// https://www.unknowncheats.me/forum/counterstrike-global-offensive/209624-fast-easy-netvar-manager.html
// https://stackoverflow.com/questions/15858141/conveniently-declaring-compile-time-strings-in-c
// This is used to XOR the strings so der cant be easily found in a debugger

typedef uint32_t fnv_t;
class CFnvHash
{
	static constexpr fnv_t FNV_PRIME = 16777619u;
	static constexpr fnv_t OFFSET_BASIS = 2166136261u;

	template <unsigned int N>
	static constexpr fnv_t fnvHashConst(const char(&str)[N], unsigned int I = N)
	{
		return static_cast<fnv_t>(1ULL * (I == 1 ? (OFFSET_BASIS ^ str[0]) : (fnvHashConst(str, I - 1) ^ str[I - 1])) * FNV_PRIME);
	}

	static __forceinline fnv_t fnvHash(const char* str)
	{
		const auto length = strlen(str) + 1;
		auto hash = OFFSET_BASIS;
		for (std::size_t i = 0; i < length; ++i)
		{
			hash ^= *str++;
			hash *= FNV_PRIME;
		}
		return hash;
	}

	struct Wrapper
	{
		Wrapper(const char* str) : str(str) { }
		const char* str;
	};

	fnv_t hash_value;
public:
	CFnvHash(Wrapper wrapper) : hash_value(fnvHash(wrapper.str)) { }

	template <unsigned int N>
	constexpr CFnvHash(const char(&str)[N]) : hash_value(fnvHashConst(str)) { }

	constexpr operator fnv_t() const { return this->hash_value; }
};

namespace NXorStringFuncs
{
	constexpr static const unsigned seed = CFnvHash(__DATE__ __TIME__);

	constexpr unsigned LinearCongruentGenerator(int Rounds, unsigned Seed = seed)
	{
		return static_cast<unsigned>(1013904223ULL + 1664525ULL * (Rounds > 0 ? LinearCongruentGenerator(Rounds - 1) : Seed));
	}

	constexpr unsigned RandomRounds(int rounds)
	{
		return LinearCongruentGenerator(rounds);
	}

	constexpr unsigned Random()
	{
		return RandomRounds(10);
	}

	constexpr unsigned RandomNumber(int min, int max)
	{
		return min + Random() % (max - min + 1);
	}

	namespace variadic_toolbox
	{
		template <unsigned count,
			template<unsigned...> class meta_functor, unsigned... indices>
		struct apply_range
		{
			typedef typename apply_range<count - 1, meta_functor, count - 1, indices...>::result result;
		};

		template <template<unsigned...> class meta_functor, unsigned... indices>
		struct apply_range<0, meta_functor, indices...>
		{
			typedef typename meta_functor<indices...>::result result;
		};
	}

	namespace compile_time
	{
		constexpr unsigned char get_key(unsigned index, unsigned value)
		{
			return 0xFF & RandomRounds(10 + index + value);
		}

		constexpr unsigned short encrypt_string(const char* str, unsigned idx)
		{
			return static_cast<unsigned short>(0UL + (get_key(idx, str[idx]) << 8) + (str[idx] ^ get_key(idx, str[idx])));
		}

		template <unsigned short... str>
		struct string
		{
			static constexpr const unsigned short chars[sizeof...(str)] = { str... };
		};

		template <unsigned short... str>
		constexpr const unsigned short string<str...>::chars[sizeof...(str)];

		template <typename lambda_str_type>
		struct string_builder
		{
			template <unsigned... indices>
			struct produce
			{
				typedef string < encrypt_string(lambda_str_type{}.chars, indices)... > result;
			};
		};
	}
}

class CXString
{
public:
	constexpr CXString(std::size_t uiSize, const WORD* c_pwEncrypted) :
		m_uiSize((NXorStringFuncs::RandomRounds(10 + uiSize) << 16) + ((uiSize ^ NXorStringFuncs::RandomRounds(10 + uiSize)) & 0xFFFF)),
		m_pwEncrypted(c_pwEncrypted)
	{
	}

	void DecryptData(char* pDestData) const
	{
		WORD wSize = (m_uiSize & 0xFFFF) ^ (m_uiSize >> 16);

		for (std::size_t i = 0; i < wSize; ++i)
			pDestData[i] = (m_pwEncrypted[i] & 0xFF) ^ (m_pwEncrypted[i] >> 8);
	}

	std::string DecryptString() const
	{
		WORD wSize = (m_uiSize & 0xFFFF) ^ (m_uiSize >> 16);

		std::string szOutputString;
		szOutputString.resize(wSize);

		DecryptData(const_cast<char*>(szOutputString.data()));

		return szOutputString;
	}

private:
	std::size_t  m_uiSize;
	const WORD* m_pwEncrypted;
};


#define XOR(szInput)																					\
    CXString(sizeof(szInput), []{																		\
        struct  constexpr_string_type { const char * chars = szInput; };								\
        return  NXorStringFuncs::variadic_toolbox::apply_range<sizeof(szInput),							\
            NXorStringFuncs::compile_time::string_builder<constexpr_string_type>::produce>::result{};	\
    }().chars).DecryptString().c_str()
