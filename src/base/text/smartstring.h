#ifndef TEXT_SMARTSTRING
#define TEXT_SMARTSTRING

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "base/conv/tostring.h"

#include "numberscale.h"

namespace Text
{

enum class NumberFormat : std::uint8_t { none, grouped, prefixed };

namespace SmartString
{
template <class T>
concept PlusAssignableToString =
    requires(std::string &str, const T &t) {
	    { str += t } -> std::same_as<std::string &>;
    };

template <char... separators> constexpr std::string join(auto &&il)
{
	std::string res;
	for (auto &&sl : il) {
		if (!res.empty()) {
			static const std::array sep{separators...};
			static_assert(sep.size() == 1 || sep.size() == 2);
			res += sep[0];
			if constexpr (sep.size() > 1) res += sep[1];
		}

		if constexpr (PlusAssignableToString<decltype(sl)>)
			res += sl;
		else
			res += Conv::toString(sl);
	}
	return res;
}

[[nodiscard]] std::vector<std::string> split(const std::string &str,
    char delim,
    bool ignoreEmpty = false,
    const char *parens = nullptr);

std::string_view trim_view(const std::string_view &string);

void trim(std::string &string);

[[nodiscard]] std::string fromPhysicalValue(double value,
    NumberFormat format,
    size_t maxFractionDigits,
    const NumberScale &numberScale,
    const std::string &unit);
}

}

#endif
