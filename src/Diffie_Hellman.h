// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#include "DivAlgs.h"
#include <iostream>
#include <string>
#include <format>
#include <limits>


/**
 * @brief Pre-Selection for the target "Square And Multiply" Algorithm type
 */
enum class SM_Type { L2R, R2L, NAIVE };

const uint64_t INVALID_BASE = std::numeric_limits<uint64_t>::max();

/**
 * This class is representing a C++ solution for "The Diffie-Hellman" key exchange
 * @author Ibrahim Ibram
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
