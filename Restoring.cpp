//
// Created by User on 11/15/2022.
//

#include "Restoring.h"

Result restoringMethod(const TestElement & element)
{
  long EAQ = element.dividend;
  long bitMask = (1<<(element.divisorLength+1)) - 1;
  long B2sComp = (((~element.divisor + 1) & bitMask) << element.divisorLength);

  for(int i = 0; i < element.divisorLength; i++)
  {
    EAQ <<= 1;
    EAQ -= B2sComp;
  }
}
