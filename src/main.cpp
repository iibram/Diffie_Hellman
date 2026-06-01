#include "Diffie_Hellman.h"


// An execution example
int main()
{
	Diffie_Hellman dh(233, 1861, SM_Type::NAIVE);
	dh.print();

	uint64_t usrA_private = 101;
	uint64_t usrB_private = 37;

	uint64_t usrA_inter = dh.get_interchange_key(usrA_private);
	uint64_t usrB_inter = dh.get_interchange_key(usrB_private);

	std::cout << "user A's public key to interchange with user B = " << usrA_inter << std::endl;
	std::cout << "user B's public key to interchange with user A = " << usrB_inter << std::endl;

	uint64_t usrA_common = dh.get_common_key(usrB_inter, usrA_private);
	uint64_t usrB_common = dh.get_common_key(usrA_inter, usrB_private);

	std::cout << "user A's common key = " << usrA_common << std::endl;
	std::cout << "user B's common key = " << usrB_common << std::endl;
}
