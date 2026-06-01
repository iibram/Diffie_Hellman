// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Diffie_Hellman.h"



Diffie_Hellman::Diffie_Hellman(uint64_t base, uint64_t n, SM_Type type) : n(n), type(type)
{
	if (n <= 1)
		throw std::invalid_argument("Modulus n must be greater than 1 for Diffie-Hellman!");

	while (base >= n)
	{
		std::cout << "invalid base for Diffie-Hellman !!!\nplease enter a base < " << n << ": ";
		std::cin >> base;

		if (std::cin.fail())
		{
			std::cin.clear();																		// reset fail flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	 // clear the junk
			base = n;																				// provide the loop to proceed
		}
	}
	this->base = base;
	public_key = std::format("({}, {})", base, n);

	std::cout << "base is succesfully set!" << std::endl;
}

uint64_t Diffie_Hellman::get_interchange_key(uint64_t p_key) const
{
	return base != 0 ? execute_sm(base, p_key, n) : INVALID_BASE;
}

uint64_t Diffie_Hellman::get_common_key(uint64_t interchanged_key, uint64_t p_key) const
{
	return base != 0 ? execute_sm(interchanged_key, p_key, n) : INVALID_BASE;
}

uint64_t Diffie_Hellman::get_base() const { return base; }

void Diffie_Hellman::print() const { std::cout << public_key << std::endl; }


// Eine private Hilfsmethode spart dir doppelten Code in den Key-Funktionen!
uint64_t Diffie_Hellman::execute_sm(uint64_t base, uint64_t exp, uint64_t n) const
{
	switch (type)
	{
		case SM_Type::NAIVE:	return DivAlgs::square_n_multiply_NAIVE(base, exp, n);
		case SM_Type::R2L:		return DivAlgs::square_n_multiply_R2L(base, exp, n);
		case SM_Type::L2R:
		default:				return DivAlgs::square_n_multiply_L2R(base, exp, n);
	}
}
