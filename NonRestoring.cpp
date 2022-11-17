
#include "NonRestoring.h"

Result nonRestoringMethod(const TestElement & element)
{
  long iterations = 0;
  long additions = 0;
  long subtractions = 0;
  long EAQ = element.dividend;
  const long EBbitMask = (1 << (element.divisorLength + 1)) - 1; // the bitmask of the length of EB. This has (divisorLength + 1) 1s. So a divisor length of 4 would give a 0b11111 mask
  const long EB2sComp = ((~element.divisor + 1) & EBbitMask) << element.divisorLength; // This is the 2's compliment of the divisor shifted into the position it needs to be in so that adding it to EAQ is like subtracting B from EA
  const long Bshifted = element.divisor << element.divisorLength; // This is B, but shifted so that adding Bshifted to EAQ is like adding B to EA
  const long AbitMask = ((1 << element.divisorLength) - 1) << element.divisorLength; // This bitmask, when AND'd with EAQ, will give the value of A. After ANDing, you must shift right.
  const long originalA = (EAQ & AbitMask) >> element.divisorLength; // This equation extracts A from EAQ.
  if (originalA >= element.divisor) { // divide overflow
    return {-1, 0, 0, 0, 0};
  }
  for(int i = 0; i < element.divisorLength; i++) // for divisorLength iterations
  {
    if((1 << (element.divisorLength * 2)) & EAQ) // E == 1
    {
      EAQ <<= 1; // shift left
      EAQ += Bshifted; // add
      additions++; // increment number of additions
    } else {
      EAQ <<= 1; // shift left
      EAQ += EB2sComp; // subtract divisor
      subtractions++;
    }
    if((1 << (element.divisorLength * 2)) & EAQ) // E == 1
    {
      EAQ &= ~1; // set LSB to 0
    } else {
      EAQ |= 1; // set LSB to 1
    }
    iterations++; // increment number of iterations
  }
  if((1 << (element.divisorLength * 2)) & EAQ) // E == 1
  {
    EAQ += Bshifted; // add
    additions++; // increment number of additions
  }
  long QbitMask = (1 << element.divisorLength) - 1; // The bitmask, that when AND'd with EAQ, will extract Q
  return {EAQ & QbitMask, (EAQ & AbitMask) >> element.divisorLength, iterations, additions, subtractions};
}
