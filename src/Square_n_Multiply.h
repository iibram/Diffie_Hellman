#pragma once

#include <cstdint>
#include <bitset>
#include <regex>
#include <bit>


/**
 * @brief Provides a few different approaches for the "Square and Multiply" algorithm.
 *
 * @author Ibrahim Ibram
 * @date 2024 (2025 refactored: added additional "Square and Multiply" variants beside the NAIVE approach)
 */
namespace Square_n_Multiply
{
	/**
	 * @brief Square & Multiply (intuitive / naive approach):
	 *
	 * The exponent is converted into a string using `std::bitset`, leading zeros are stripped using `std::regex`,
	 * and the bits are evaluated via a character loop. This approach is excellently suited for gaining a visual understanding of the algorithm.
	 * For production-critical hot loops, this approach was later optimized — to eliminate the string overhead — by replacing it with the bit-based
	 * variants (`L2R` and `R2L`).
	 *
	 * @note This was the very first custom implementation from the early days (2024).
	 * It precisely replicates the procedure one would use to calculate it manually on paper.
	 *
	 * @param base the base
	 * @param exp the exponent
	 * @param n the modulo element
	 * @return base^(exponent) mod n
	 */
	inline uint64_t NAIVE(uint64_t base, uint64_t exp, uint64_t n)
	{
		std::string bits = std::bitset<64>(exp).to_string();

		std::regex reg("^0*");
		bits = regex_replace(bits.data(), reg, "");

		uint64_t tmp = 1;
		for (char bit : bits)
		{
			tmp = (tmp * tmp) % n;			// square

			if (bit == '1')
				tmp = (tmp * base) % n;		// & multiply
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
	inline uint64_t L2R(uint64_t base, uint64_t exp, uint64_t n)
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
	inline uint64_t R2L(uint64_t base, uint64_t exp, uint64_t n)
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
}
