# Diffie-Hellman Key Exchange (Educational Demo)

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Purpose](https://img.shields.io/badge/Purpose-Educational%20%2F%20Academic-orange.svg)]()

A clean, console-based demonstration of the classic **Diffie-Hellman Key Exchange**, developed during my Computer Science studies (B.Sc.).

This project was built to hit four birds with one stone:
1. **Continuous Practice:** Keeping my C++ skills sharp and production-ready.
2. **Algorithm Verification:** Translating theoretical textbook math into concrete code to verify my understanding.
3. **Exam Prep Utility:** Creating a reliable "control unit" to double-check hand-calculated exam tasks during intense study phases.
4. **Deep Learning:** Because nothing burns an algorithm into your brain quite like debugging its implementation.

⚠️ **DISCLAIMER:** This project is strictly for **educational and demonstrative purposes**. It is *not* cryptographically secure (no large prime generation, no protection against side-channel attacks, etc.). Do not use this in production.

---

## 🛠️ The 2025 Refactoring (Lessons Learned)

Looking back at my 2024 implementation with more experience, I realized my initial **Square-and-Multiply (SM)** algorithm was quite naive. In 2025, I refactored the codebase to make it more robust and modular:

* **Algorithm Variants:** Added three distinct implementations of the Square-and-Multiply algorithm to compare behavioral nuances.
* **Pre-selection Enum:** Introduced a `uint8_t`-backed `enum` allowing the user to explicitly pre-select the desired SM variant for the session directly via the configuration setup.
* **No Over-Engineering:** Kept the explicit step-by-step method calls in `main` instead of hiding everything inside a fully automated constructor. This keeps the execution flow fully transparent and readable for students or anyone interested in the math.

---

## 🧠 How the Diffie-Hellman Works (The Essence)

The **Diffie-Hellman Key Exchange** is a cornerstone of modern digital cryptography. It addresses a fundamental problem: *How can two parties (Alice and Bob) establish a shared secret key over an insecure public channel (the internet) without an eavesdropper ("Man-in-the-Middle") finding out?*

### The Core Logic:
1. Alice and Bob agree on public parameters: a **Base** ($g$) and a **Prime** ($p$).
2. Both generate their own **Private Keys** (kept strictly secret).
3. They use modular exponentiation to compute their **Public Keys** and exchange them over the internet.
4. By combining the received public key with their own private key, both independently compute the exact same **Shared Secret Key**.

An attacker intercepts only the public keys. Due to the **Discrete Logarithm Problem**, reversing this to find the private keys is computationally infeasible for sufficiently large numbers.

---

## 💻 How to Use

The configuration is deliberately kept simple and human-readable within the `main.cpp`. You can set the public parameters, insert the private keys, and choose your preferred Square-and-Multiply variant.

### Execution Flow Example:

```cpp
#include "Diffie_Hellman.h"

int main()
{
    // Initialize with Base, Prime, and the preferred SM algorithm flavor
    Diffie_Hellman dh(233, 1861, SM_Type::NAIVE);
    dh.print();

    // Define simulated private keys for Alice and Bob
    uint64_t usrA_private = 101;
    uint64_t usrB_private = 37;

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
```

### Console Output

Running the application prints a fully traceable step-by-step breakdown of the exponentiation phases, showing exactly how the math converges to the identical shared secret key on both sides.


## 🚀 Building the Project

This project requires a modern C++ compiler supporting at least **C++20**.
(due to modern type handling and clean syntax).

```bash
# Clone the repository
git clone [https://github.com/iibram/Diffie_Hellman.git](https://github.com/iibram/Diffie_Hellman.git)
cd Diffie_Hellman

# Build using g++ (compile all source files into an executable named 'main')
g++ -std=c++20 -O2 src/*.cpp -o main

# Run the demo
./main
```
