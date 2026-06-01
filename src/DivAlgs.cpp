#include "DivAlgs.h"


/**
 * @brief Calculates all common divisors (ACD) of two natural numbers a and b and returns them as an ascendingly sorted set of divisors
 * @param a a natural number
 * @param b a natural number
 * @return the set of all common divisors a and b
 */
std::set<uint64_t> DivAlgs::get_ACD(uint64_t a, uint64_t b)
{
	std::set<uint64_t> setA;
	std::set<uint64_t> setB;
	std::set<uint64_t> result;

	if (a > 0 && b > 0)
	{
		setA = get_setOfDividers(a);
		setB = get_setOfDividers(b);
	}

	std::set_intersection(setA.begin(), setA.end(),
		setB.begin(), setB.end(),
		std::inserter(result, result.end()));

	return result;
}

/**
 * @brief Calculates the greatest common divisor (GCD) of two natural numbers a and b, and returns its numerical value
 * @param a a natural number
 * @param b a natural number
 * @return the greatest common divisor (GCD) of the passed natural numbers a and b.
 */
uint64_t DivAlgs::get_GCD(uint64_t a, uint64_t b)
{
	std::set <uint64_t> set = get_ACD(a, b);
	return *set.rbegin();
}

/**
 * @brief Calculates the greatest common divisor of two natural numbers using the Euclidean algorithm
 * @param a a natural number
 * @param b a natural number
 * @return the greatest common divisor (GCD) of the passed natural numbers a and b.
 */
uint64_t DivAlgs::euclidean_GCD(uint64_t a, uint64_t b)
{
	uint64_t potGCD = 0;
	if (a > 0 && b > 0)
	{
		uint64_t num = a > b ? a : b;
		uint64_t denom = a == num ? b : a;
		potGCD = denom;
		uint64_t rest = 1;
		while (rest > 0)
		{
			rest = num % denom;
			if (rest > 0)
			{
				num = denom;
				potGCD = denom = rest;
			}
		}
	}
	return potGCD;
}

/**
 * @brief Calculates — based on Euler's totient function (Phi(n)) — all numbers coprime to n and returns their count
 * @param n the natural number to be checked
 * @return the number of all coprime numbers to n
 */
uint64_t DivAlgs::eulerian_Phi(uint64_t n)
{
	uint64_t count = 0;
	if (n > 0)
	{
		for (uint64_t i = 1; i <= n; i++)
			if (get_GCD(i, n) == 1) count++;
	}
	return count;
}

/**
 * @brief Returns a set with all divisors of the passed natural number x
 * @param x the natural number to be divided
 * @return a set containing all natural number divisors of x
 */
std::set<uint64_t> DivAlgs::get_setOfDividers(uint64_t n)
{
	std::set<uint64_t> setX;
	double xDbl = n + 0.0;
	double tmp;

	for (uint64_t i = 1; i <= n; i++)
	{
		tmp = xDbl / i;
		if ((tmp - (uint64_t)tmp) == 0)
			setX.insert(n / i);
	}

	return setX;
}

/**
 * @brief Square & Multiply (intuitive / naive approach):
 *
 * The exponent is converted into a string using `std::bitset`, leading zeros are stripped using `std::regex`,
 * and the bits are evaluated via a character loop. This approach is excellently suited for gaining a visual understanding of the algorithm.
 * For production-critical hot loops, this approach was later optimized — to eliminate the string overhead — by replacing it with the bit-based
 * variants (`_L2R` and `_R2L`).
 *
 * @note This was the very first custom implementation from the early days (2024/2025).
 * It precisely replicates the procedure one would use to calculate it manually on paper.
 *
 * @param base the base
 * @param exp the exponent
 * @param n the modulo element
 * @return base^(exponent) mod n
 */
uint64_t DivAlgs::square_n_multiply_NAIVE(uint64_t base, uint64_t exp, uint64_t n)
{
	std::string bits = std::bitset<64>(exp).to_string();

	std::regex reg("^0*");
	bits = regex_replace(bits.data(), reg, "");

	uint64_t tmp = 1;
	for (char bit : bits)
	{
		tmp = (tmp * tmp) % n;			// square

		if (bit == '1')		// & multiply
			tmp = (tmp * base) % n;

		//tmp %= n;
	}

	return tmp;
}

/**
 * @brief Square & Multiply L2R (Modern C++20 Approach):
 *
 * This approach scans the exponent from left (MSB) to right (LSB). It utilizes `std::countl_zero` to ignore
 * leading zeros directly at the CPU level, and `static_cast` to 128 bits to nip mathematical overflows during
 * multiplication — prior to the modulo step — in the bud.
 *
 * Procedure: For each bit, the current result is squared. If the bit is 1, it is additionally multiplied by the base.
 *
 * @param base the base
 * @param exp the exponent
 * @param n the modulo element
 * @return base^(exponent) mod n
 */
uint64_t DivAlgs::square_n_multiply_L2R(uint64_t base, uint64_t exp, uint64_t n)
{
	if (n == 0) return 0;
	if (exp == 0) return 1;

	uint64_t res = 1;
	base = base % n;

	// finding the highest set MSB (skipping unnecessary loops)
	int lead_zeros = std::countl_zero(exp);
	int hi_bit_idx = 63 - lead_zeros;

	// from MSB --> LSB
	for (int i = hi_bit_idx; i >= 0; --i)
	{
		res = (static_cast<unsigned __int128>(res) * res) % n;			// square

		if ((exp >> i) & 1)
			res = (static_cast<unsigned __int128>(res) * base) % n;		// &  multiply
	}

	return res;
}

/**
 * @brief Square & Multiply R2L (Classic Hardware-friendly Approach):
 *
 * This approach scans the exponent from right (LSB) to left (MSB) using simple bit-shifting (exp >> 1).
 * It is the indestructible classic, often utilized in embedded systems (crypto-chips) because it does not require pre-counting of bits.
 *
 * Procedure: The base is squared in each step. Only if the current bit is 1, the currently exponentiated base is included in the final result.
 *
 * @param base the base
 * @param exp the exponent
 * @param n the modulo element
 * @return base^(exponent) mod n
 */
uint64_t DivAlgs::square_n_multiply_R2L(uint64_t base, uint64_t exp, uint64_t n)
{
	if (n == 0) return 0;

	uint64_t res = 1;
	base = base % n;

	while (exp > 0)
	{
		if (exp & 1)
			res = (static_cast<unsigned __int128>(res) * base) % n;	// curr LSB = 1 ? ==> multiply in the curr base

		exp = exp >> 1;

		base = (static_cast<unsigned __int128>(base) * base) % n;	// square the base for the next step
	}

	return res;
}

/**
 * @brief Returns whether the given natural number is a prime number
 * @param n the natural number to be checked
 * @return bool
 */
bool DivAlgs::isPrime(uint64_t n)
{
	std::set<uint64_t> set;
	set = get_setOfDividers(n);
	if (set.size() == 2)
		return true;

	return false;
}
