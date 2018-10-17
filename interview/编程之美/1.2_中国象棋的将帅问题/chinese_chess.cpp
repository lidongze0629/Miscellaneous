#include <iostream>

#define HALF_BITS_LENGTH 4
#define FULLMASK 255
// 11110000
// 00001111
#define LMASK (FULLMASK << HALF_BITS_LENGTH)
#define RMASK (FULLMASK >> HALF_BITS_LENGTH)

#define LSET(b, n) (b = (((b) & RMASK) | ((n) << HALF_BITS_LENGTH)))
#define RSET(b, n) (b = (((b) & LMASK) | (n)))
#define LGET(b) (((b) & LMASK) >> HALF_BITS_LENGTH)
#define RGET(b) ((b) & RMASK)

// 九宫格的宽度
#define RANGE 3

int main() {
    unsigned char bits;
    // Test 1
    for (LSET(bits, 1); LGET(bits) <= RANGE * RANGE; LSET(bits, LGET(bits) + 1)) {
        for (RSET(bits, 1); RGET(bits) <= RANGE * RANGE; RSET(bits, RGET(bits) + 1)) {
            if ((LGET(bits) % 3) != (RGET(bits) % 3)) {
                std::cout << LGET(bits) << ", " << RGET(bits) << std::endl;
            }
        }
    }
    
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    // Test 2
    unsigned char bits2 = 81;
    while (bits2--) {
        if ((bits2 % 9 % 3)  != (bits2 / 9 % 3)) {
            std::cout << bits2 / 9 + 1 << ", " << bits2 % 9 + 1 << std::endl;
        }
    }

    
}
