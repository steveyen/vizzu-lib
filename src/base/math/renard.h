#ifndef MATH_RENARD
#define MATH_RENARD

#include <span>

namespace Math
{

class Renard
{
public:
	static Renard R3();
	static Renard R5();
	explicit Renard(std::span<const double> const &numbers) :
	    numbers(numbers)
	{}
	[[nodiscard]] double ceil(double value) const;
	[[nodiscard]] double floor(double value) const;

private:
	std::span<const double> numbers;
};

}

#endif
