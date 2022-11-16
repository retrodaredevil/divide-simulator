#include <iostream>
#include "TestElement.h"
#include "Result.h"
#include "Restoring.h"
#include "NonRestoring.h"

const TestElement TEST_DATA[] {
        TestElement{0b111100001, 0b01111, 9, 6}, // changing divisor length from 5 to 6 to avoid overflow
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

        TestElement{0b0111111111110000000000001, 0b0111111111111, 25, 13},
        TestElement{0b1000111000110111000111001, 0b1010101010101, 25, 13},
        TestElement{0b1000000111110001100011001, 0b1000011111111, 25, 13},
        TestElement{0b1000011100001000100100000, 0b0000011100000, 25, 13},
};
const size_t TEST_DATA_SIZE = 20;

int main() {
    std::cout << "Divisor Length,Dividend,Divisor,Quotient,Remainder,Restoring Iterations,Restoring Additions,Restoring Subtracts,Non-Restoring Iterations,Non-Restoring Additions,Non-Restoring Subtracts" << std::endl;
    for (const auto & element : TEST_DATA) {
        Result restoringResult = restoringMethod(element);
        Result nonRestoringResult = nonRestoringMethod(element);
        bool anyError = false;
        long correctQuotient = element.dividend / element.divisor;
        long correctRemainder = element.dividend % element.divisor;
        if (restoringResult.quotient < 0) { // indicates overflow
            std::cerr << "Overflow for restoring method with dividend: " << element.dividend << " and divisor: " << element.divisor << std::endl;
            anyError = true;
        } else {
            if (restoringResult.quotient != correctQuotient || correctRemainder != restoringResult.remainder) {
                std::cerr << "Incorrect result for restoring method with dividend: " << element.dividend << " and divisor: " << element.divisor
                          << std::endl << "\tRestoring: Quotient: " << restoringResult.quotient << " Remainder: " << restoringResult.remainder
                          << std::endl << "\tShould be: Quotient: " << restoringResult.quotient << " Remainder: " << restoringResult.remainder
                          << std::endl;
                anyError = true;
            }
        }
        if (nonRestoringResult.quotient < 0) { // indicates overflow
            std::cerr << "Overflow for non-restoring method with dividend: " << element.dividend << " and divisor: " << element.divisor << std::endl;
            anyError = true;
        } else {
            if (nonRestoringResult.quotient != correctQuotient || correctRemainder != nonRestoringResult.remainder) {
                std::cerr << "Incorrect result for non-restoring method with dividend: " << element.dividend << " and divisor: " << element.divisor
                          << std::endl << "\tNon-Restoring: Quotient: " << nonRestoringResult.quotient << " Remainder: " << nonRestoringResult.remainder
                          << std::endl << "\tShould be: Quotient: " << nonRestoringResult.quotient << " Remainder: " << nonRestoringResult.remainder
                          << std::endl;
                anyError = true;
            }
        }

        if (restoringResult.quotient >= 0 && nonRestoringResult.quotient >= 0) { // no overflow for either method
            if (restoringResult.quotient != nonRestoringResult.quotient || restoringResult.remainder != nonRestoringResult.remainder) {
                std::cerr << "Different results for dividend: " << element.dividend << " and divisor: " << element.divisor
                          << std::endl << "\tRestoring: Quotient: " << restoringResult.quotient << " Remainder: " << restoringResult.remainder
                          << std::endl << "\tNon-Restoring: Quotient: " << nonRestoringResult.quotient << " Remainder: " << nonRestoringResult.remainder << std::endl;
                anyError = true;
            }
        }
        if (anyError) {
            std::cerr << std::endl;
        }
        std::cout << element.divisorLength << "," << element.dividend << "," << element.divisor
                << "," << restoringResult.quotient << "," << restoringResult.remainder
                << "," << restoringResult.numIts << "," << restoringResult.numAdditions << "," << restoringResult.numSubtractions
                << "," << nonRestoringResult.numIts << "," << nonRestoringResult.numAdditions << "," << nonRestoringResult.numSubtractions
                << std::endl;
                ;
    }
    Result restoringResult = restoringMethod(TEST_DATA[0]);
    std::cout << restoringResult.quotient << std::endl << restoringResult.remainder << std::endl;
    Result num = nonRestoringMethod(TEST_DATA[0]);
    std::cout << num.quotient << std::endl << num.remainder << std::endl << num.numIts << std::endl << num.numAdditions << std::endl << num.numSubtractions << std::endl;
    return 0;
}
