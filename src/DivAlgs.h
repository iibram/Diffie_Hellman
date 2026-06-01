// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#include <cstdint>
#include <bitset>
#include <regex>
#include <bit>
#include <set>


/**
 * @brief Provides various divisibility functions based on the Euclidean and Eulerian algorithms
 *
 * @author Ibrahim Ibram
 * @date year 2024/2025
 */
namespace DivAlgs
{
	std::set<uint64_t> get_ACD(uint64_t a, uint64_t b);
	uint64_t get_GCD(uint64_t a, uint64_t b);
	uint64_t euklidic_GCD(uint64_t a, uint64_t b);
	uint64_t euleric_Phi(uint64_t n);
	std::set<uint64_t> get_setOfDividers(uint64_t x);
	uint64_t square_n_multiply_L2R(uint64_t base, uint64_t exp, uint64_t n);
	uint64_t square_n_multiply_R2L(uint64_t base, uint64_t exp, uint64_t n);
	uint64_t square_n_multiply_NAIVE(uint64_t base, uint64_t exp, uint64_t n);
	bool isPrime(uint64_t x);
}
