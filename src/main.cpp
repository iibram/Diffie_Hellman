// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Diffie_Hellman.h"

int main()
{
	Diffie_Hellman dh(2, 11, SM_Type::R2L);
	dh.print();

	uint64_t usrA_private = 3;
	uint64_t usrB_private = 4;

	uint64_t usrA_inter = dh.get_interchange_key(usrA_private);
	uint64_t usrB_inter = dh.get_interchange_key(usrB_private);

	std::cout << "userA interchange = " << usrA_inter << std::endl;
	std::cout << "userB interchange = " << usrB_inter << std::endl;

	uint64_t usrA_common = dh.get_common_key(usrB_inter, usrA_private);
	uint64_t usrB_common = dh.get_common_key(usrA_inter, usrB_private);

	std::cout << "userA common = " << usrA_common << std::endl;
	std::cout << "userB common = " << usrB_common << std::endl;
}
