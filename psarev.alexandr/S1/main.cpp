#include <utility>
#include <cmath>
#include "utilityFuncs.hpp"

int main()
{
  using namespace psarev;

  List< int > testList;
  testList.pushBack(10);
  testList.pushBack(10);
  testList.pushBack(11);
  testList.pushBack(10);
  std::cout << testList.getSize() << '\n';
  testList.remove(11);
  std::cout << testList.getSize() << '\n';

  List< std::pair< std::string, List< unsigned long long > > > lines;
  Iterator< std::pair< std::string, List< unsigned long long > > > iterLine;
  std::string line = "";
  size_t maxDigits = 0;
  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string ord = psarev::getOrd(line);
      lines.pushBack({ ord, {} });
      iterLine = lines.begin();
      for (size_t i = 0; i < (lines.getSize() - 1); i++)
      {
        iterLine++;
      }
      size_t cntDigits = 0;
      while (line.size() != 0)
      {
        unsigned long long digit = psarev::getDigit(line);
        (*iterLine).second.pushBack(digit);
        cntDigits++;
      }
      maxDigits = fmax(maxDigits, cntDigits);
    }
  }

  outOrds< unsigned long long >(lines);
  bool isOverflow = false;
  List< unsigned long long > sums = outDigits(lines, maxDigits, isOverflow);
  if (isOverflow)
  {
    std::cerr << "Error: Value overflow during counting the sum!\n";
    return 1;
  }
  outSums< unsigned long long >(sums);
  return 0;
}
