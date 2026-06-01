// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

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
uint64_t DivAlgs::euklidic_GCD(uint64_t a, uint64_t b)
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
uint64_t DivAlgs::euleric_Phi(uint64_t n)
{
	long count = 0;
	if (n > 0)
	{
		for (uint64_t i = 1; i <= n; i++)
		{
			if (get_GCD(i, n) == 1) count++;
		}
	}
	return count;
}

/**
 * @brief Returns a set with all divisors of the passed natural number x
 * @param x the natural number to be divided
 * @return a set containing all natural number divisors of x
 */
std::set<uint64_t> DivAlgs::get_setOfDividers(uint64_t x)
{
	std::set<uint64_t> setX;
	double xDbl = x + 0.0;
	double tmp;

	for (uint64_t i = 1; i <= x; i++)
	{
		tmp = xDbl / i;
		if ((tmp - (uint64_t)tmp) == 0)
			setX.insert(x / i);
	}

	return setX;
}

/**
 * @brief Calculates the modulo of the provided values ​​in a highly efficient manner, capable of handling very large exponents
 * @param base the base
 * @param exp the exponent
 * @param n the modulo element
 * @return base^(exponent) mod n
 */

/**
 * @brief Square-and-Multiply (Intuitiver / Naiver Ansatz)
 * @note Evolutionärer Meilenstein: Dies war die allererste eigene Implementierung aus der Anfangszeit (2024/2025).
 * Sie bildet exakt das Verfahren nach, wie man es manuell auf dem Papier berechnen würde.
 * @details Ansatz: Der Exponent wird über std::bitset in einen String gewandelt, führende Nullen werden per
 * std::regex rasiert und die Bits als Char-Schleife evaluiert. Hervorragend geeignet, um den Algorithmus visuell zu verstehen.
 * Für produktive Hot-Loops wurde dieser Ansatz später durch die bitbasierten Varianten (_L2R und _R2L) wegen des String-Overheads optimiert.
 *
 * @param base the base
 * @param exp the exponent
 * @param n the modulo element
 * @return base^(exponent) mod n
 */
uint64_t DivAlgs::square_n_multiply_NAIVE(uint64_t base, uint64_t exp, uint64_t n)
{
	std::string bits = std::bitset<32>(exp).to_string();

	std::regex reg("^0*");
	bits = regex_replace(bits.data(), reg, "");

	uint64_t tmp = 1;
	for (char bit : bits)
	{
		tmp *= tmp;			// square

		if (bit == '1')		// & multiply
			tmp *= base;

		tmp %= n;
	}

	return tmp;
}

/**
 * @brief Left-to-Right Square-and-Multiply (Modern C++20 Approach).
 * Dieser Ansatz scannt den Exponenten von links (MSB) nach rechts (LSB). Er nutzt std::countl_zero,
 * um führende Nullen direkt auf CPU-Ebene zu ignorieren, und static_cast auf 128-Bit, um mathematische
 * Overflows bei der Multiplikation vor dem Modulo-Schritt im Keim zu ersticken.
 *
 * Ansatz: Für jedes Bit wird das aktuelle Ergebnis quadriert. Ist das Bit 1, wird zusätzlich mit der Basis multipliziert.
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

	// Finde das höchste gesetzte Bit, um unnötige Schleifendurchläufe zu sparen
	int leading_zeros = std::countl_zero(exp);
	int highest_bit_index = 63 - leading_zeros;

	// Von links (MSB) nach rechts (LSB) wandern
	for (int i = highest_bit_index; i >= 0; --i)
	{
		// 1. Immer quadrieren (und sofort Modulo anwenden)
		res = (static_cast<unsigned __int128>(res) * res) % n;

		// 2. Wenn das aktuelle Bit 1 ist: Multiplizieren
		if ((exp >> i) & 1)
		{
			res = (static_cast<unsigned __int128>(res) * base) % n;
		}
	}
	return res;
}

/**
 * @brief Right-to-Left Square-and-Multiply (Classic Hardware-friendly Approach).
 * Dieser Ansatz scannt den Exponenten von rechts (LSB) nach links (MSB) mittels einfachem Bit-Shifting (exp >> 1).
 * Er ist der unzerstörbare Klassiker, der oft in eingebetteten Systemen (Krypto-Chips) genutzt wird, da er keine
 * Bit-Zählung im Voraus benötigt.
 *
 * Ansatz: Die Basis wird in jedem Schritt quadriert. Nur wenn das aktuelle Bit 1 ist, wird die aktuell
 * hochpotenzierte Basis in das Endergebnis eingerechnet.
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
		// Wenn das niedrigste Bit aktuell 1 ist, multipliziere die aktuelle Basis hinein
		if (exp & 1)
		{
			res = (static_cast<unsigned __int128>(res) * base) % n;
		}

		// Exponent nach rechts schieben (Halbierung)
		exp = exp >> 1;

		// Basis für den nächsten Schritt quadrieren (base^1 -> base^2 -> base^4 ...)
		base = (static_cast<unsigned __int128>(base) * base) % n;
	}

	return res;
}

/**
 * @brief Returns whether the given natural number is a prime number
 * @param x the natural number to be checked
 * @return
 */
bool DivAlgs::isPrime(uint64_t x)
{
	std::set<uint64_t> set;
	set = get_setOfDividers(x);
	if (set.size() == 2)
		return true;

	return false;
}
