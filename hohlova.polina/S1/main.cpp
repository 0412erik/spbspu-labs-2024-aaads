#include "list.hpp"

int main()
{
  hohlova::List<std::pair<std::string, std::vector<int>>> numbers;
  std::vector<std::pair<std::string, std::vector<std::string>>> tempData;
  std::string line;
  bool hasData = false;
  std::string temp;

  while (std::getline(std::cin, line) && !line.empty())
  {
    std::istringstream iss(line);
    std::string word;
    iss >> word;
    temp = word;

    std::vector<std::string> nums;
    std::string numStr;
    while (iss >> numStr)
    {
      nums.push_back(numStr);
    }

    tempData.push_back(std::make_pair(word, nums));
    if (!nums.empty())
      hasData = true;
  }

  if (!hasData && !tempData.empty())
  {
    std::cout << temp << std::endl
      << "0";
    return 0;
  }

  if (tempData.empty())
  {
    std::cout << "0" << std::endl;
    return 0;
  }

  for (const auto &entry : tempData)
  {
    std::vector<int> nums;
    for (const auto &numStr : entry.second)
    {
      try
      {
        nums.push_back(std::stoi(numStr));
      }
      catch (const std::out_of_range &oor)
      {
        std::cerr << "Out of range input: " << numStr << std::endl;
        return 1;
      }
    }
    numbers.push_back(std::make_pair(entry.first, nums));
  }

  for (auto it = numbers.begin(); it != numbers.end(); ++it)
  {
    std::cout << (*it).first;
    auto nextIt = it;
    ++nextIt;
    if (nextIt != numbers.end())
    {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  std::cout << numbers;

  size_t max_length = 0;
  for (auto it = numbers.begin(); it != numbers.end(); ++it)
  {
    max_length = std::max(max_length, (*it).second.size());
  }

  for (size_t i = 0; i < max_length; ++i)
  {
    int sum = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
      if (i < (*it).second.size())
        sum += (*it).second[i];
    }
    std::cout << sum;
    if (i < max_length - 1)
      std::cout << " ";
  }
  std::cout << std::endl;
  return 0;
}

