#include "Diffie_Hellman.h"


/**
 * @brief Custom constructor:
 * @param base the base
 * @param n the modulo element
 * @param type the type of the "Square & Multiply" (SM) algorithm preferred by the user to use in this session
 */
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

/**
 * @brief Invokes the execution of the preselected SM algorithm for calculating the interchangable public key and returns the result
 * @param p_key private key
 * @return the public key to interchange with the partner
 */
uint64_t Diffie_Hellman::get_interchange_key(uint64_t p_key) const
{
	return base != 0 ? execute_sm(base, p_key, n) : INVALID_BASE;
}

/**
 * @brief Invokes the execution of the preselected SM algorithm for calculating the common key and returns the result
 * @param interchanged_key the interchanged key of the partner
 * @param p_key private key
 * @return
 */
uint64_t Diffie_Hellman::get_common_key(uint64_t interchanged_key, uint64_t p_key) const
{
	return base != 0 ? execute_sm(interchanged_key, p_key, n) : INVALID_BASE;
}

/**
 * @brief Getter
 * @return the base
 */
uint64_t Diffie_Hellman::get_base() const { return base; }

/**
 * @brief Prints the public key to the console
 */
void Diffie_Hellman::print() const { std::cout << public_key << std::endl; }

/**
 * @brief Helper function: selector of the type of the "Square & Multiply" (SM) algorithm preferred by the user to use in this session
 * @param base the base
 * @param exp the exponent
 * @param n the modulo element
 * @return the result of the preferred type of the "Square & Multiply Algorithm"
 */
uint64_t Diffie_Hellman::execute_sm(uint64_t base, uint64_t exp, uint64_t n) const
{
	switch (type)
	{
		case SM_Type::NAIVE:	return Square_n_Multiply::NAIVE(base, exp, n);
		case SM_Type::R2L:		return Square_n_Multiply::R2L(base, exp, n);
		case SM_Type::L2R:
		default:				return Square_n_Multiply::L2R(base, exp, n);
	}
}
