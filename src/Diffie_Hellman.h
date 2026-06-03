#pragma once

#include "Square_n_Multiply.h"
#include <iostream>
#include <string>
#include <format>
#include <limits>



constexpr uint64_t INVALID_BASE = std::numeric_limits<uint64_t>::max();


/**
 * @brief Pre-Selection for the target "Square & Multiply" algorithm type
 */
enum class SM_Type { L2R, R2L, NAIVE };


/**
 * Implements the "Diffie-Hellman Key Exchange" procedure for demonstration purposes
 *
 * @author Ibrahim Ibram
 * @date 2024/2025
 */
class Diffie_Hellman
{
public:
	Diffie_Hellman(uint64_t base, uint64_t n, SM_Type type = SM_Type::L2R);
	~Diffie_Hellman() = default;

	uint64_t get_interchange_key(uint64_t p_key) const;
	uint64_t get_common_key(uint64_t interchanged_key, uint64_t p_key) const;
	uint64_t get_base() const;
	void print() const;

private:
	std::string public_key;

	uint64_t base = INVALID_BASE;
	uint64_t n;
	SM_Type type;

	uint64_t execute_sm(uint64_t base, uint64_t exp, uint64_t n) const;
};
