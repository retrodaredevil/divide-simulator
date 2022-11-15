#include <iostream>
#include "TestElement.h"

const TestElement TEST_DATA[] {
        TestElement{0b111100001, 0b01111, 9, 5},
        TestElement{0b001001101, 0b11011, 9, 5},
        TestElement{0b000010101, 0b10011, 9, 5},
        TestElement{0b100001101, 0b01101, 9, 5},

        TestElement{0b1111111000001, 0b1111111, 13, 7},
        TestElement{0b0010110110010, 0b1011011, 13, 7},
        TestElement{0b1000010111101, 0b1000111, 13, 7},
        TestElement{0b1100111100010, 0b1110111, 13, 7},

        TestElement{0b01111111000000001, 0b011111111, 17, 9},
        TestElement{0b10001011110110101, 0b000110011, 17, 9},
        TestElement{0b00011011111001000, 0b001110111, 17, 9},
        TestElement{0b00000101001001011, 0b101010101, 17, 9},

        TestElement{0b111111111100000000001, 0b11111111111, 21, 11},
        TestElement{0b100000111000101101100, 0b10000111101, 21, 11},
        TestElement{0b100011100011000111001, 0b00101010101, 21, 11},
        TestElement{0b000010101100000010000, 0b00001111000, 21, 11},
};

int main() {
    // TODO split dividend in half to AC and Q
    std::cout << "Hello, World!" << std::endl;
    return 0;
}