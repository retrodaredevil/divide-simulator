//
// Created by User on 11/15/2022.
//

#include "NonRestoring.h"

Result nonRestoringMethod(const TestElement & element)
{
  long iterations = 0;
  long additions = 0;
  long subtractions = 0;
  long EAQ = element.dividend;
  long EBbitMask = (1<<(element.divisorLength+1)) - 1;
  long EB2sComp = (((~element.divisor + 1) & EBbitMask) << element.divisorLength);
  long Bshifted = element.divisor << element.divisorLength;
  long AbitMask = ((1<<(element.divisorLength)) - 1) << element.divisorLength;
  const long originalA = ((EAQ & AbitMask) >> element.divisorLength);
  if (originalA >= element.divisor) { // divide overflow
    return {-1, 0, 0, 0, 0};
  }
  for(int i = 0; i < element.divisorLength; i++) // for divisorLength iterations
  {
    EAQ <<= 1; // shift left
    if((1<<(element.divisorLength*2))&EAQ) // E == 1
    {
      EAQ &= ~1; // set LSB to 0
      EAQ += Bshifted; // add
      additions++; // increment number of additions
    } else {
      EAQ |= 1; // set LSB to 1
      EAQ += EB2sComp; // subtract divisor
      subtractions++;
    }
    iterations++; // increment number of iterations
  }
  long QbitMask = ((1<<(element.divisorLength)) - 1);
  return {EAQ & QbitMask, (EAQ & AbitMask) >> element.divisorLength, iterations, additions, subtractions};
}
