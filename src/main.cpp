#include "Diffie_Hellman.h"


// An execution example
int main()
{
	// Initialize with Base, Prime, and the preferred SM algorithm flavor
	Diffie_Hellman dh(233, 1861, SM_Type::NAIVE);
	dh.print();

	// Define simulated private keys for Alice and Bob
	uint64_t usrA_private = 101;
	uint64_t usrB_private = 37;

	// -------------------------------------------

	// 1. Users generate their public interchange keys
	uint64_t usrA_inter = dh.get_interchange_key(usrA_private);
	uint64_t usrB_inter = dh.get_interchange_key(usrB_private);

	std::cout << "user A's public key to interchange with user B = " << usrA_inter << '\n';
	std::cout << "user B's public key to interchange with user A = " << usrB_inter << '\n';

	// 2. Users generate the COMMON shared secret key using their partner's public key
	uint64_t usrA_common = dh.get_common_key(usrB_inter, usrA_private);
	uint64_t usrB_common = dh.get_common_key(usrA_inter, usrB_private);

	std::cout << "user A's common key = " << usrA_common << '\n';
	std::cout << "user B's common key = " << usrB_common << '\n';

	return 0;
}
