//
// Created by User on 11/15/2022.
//

#include "Restoring.h"
#include <iostream>

Result restoringMethod(const TestElement & element)
{
  long EAQ = element.dividend;
  long EBbitMask = (1<<(element.divisorLength+1)) - 1;
  long EB2sComp = (((~element.divisor + 1) & EBbitMask) << element.divisorLength);
  long Bshifted = element.divisor << element.divisorLength;
  std::cout << "EAQ: " << EAQ << " mask: " << EBbitMask << " 2scomp" << EB2sComp << " b shifted: " << Bshifted << std::endl;

  long AbitMask = ((1<<(element.divisorLength)) - 1) << element.divisorLength;
  const long originalA = ((EAQ & AbitMask) >> element.divisorLength);
  std::cout << "A: " << originalA << std::endl;
  if (originalA >= element.divisor) {
    std::cout << "overflow" << std::endl;
    return {-1, 0, 0, 0, 0};
  }
  for(int i = 0; i < element.divisorLength; i++)
  {
    EAQ <<= 1;
    EAQ += EB2sComp;
    if((1<<(element.divisorLength*2))&EAQ) // E == 1
    {
      EAQ &= ~1; // set LSB to 0
      EAQ += Bshifted;
    } else {
      EAQ |= 1; // set LSB to 1
    }
  }
  std::cout << "now EAQ: " << EAQ << std::endl;
  long QbitMask = ((1<<(element.divisorLength)) - 1);
  return {EAQ & QbitMask, (EAQ & AbitMask) >> element.divisorLength, 0, 0, 0};
}
