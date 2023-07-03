#include <algorithm>
#include <iostream>
#include <regex>

#include "solver.h"
#include "utils.h"

static bool check(const std::string& text);
static void normalize(std::string& text);

int main() {
  std::string text;

  init();

  std::cout << "Enter the word: ";
  std::cin >> text;

  if (!check(text)) {
    std::cout << "Invalid word" << std::endl;
    return EXIT_FAILURE;
  }
  normalize(text);

  start_timer();
  auto wordlist = findall(text);

  auto duration = stop_timer();
  std::cout << "Found " << wordlist.size() << " words in " << duration.count()
            << " ms" << std::endl;

  std::sort(wordlist.begin(), wordlist.end(),
            [](const std::string& first, const std::string& second) {
              if (first.size() != second.size())
                return first.size() < second.size();
              else
                return first < second;
            });

  for (auto& word : wordlist) {
    std::cout << word << std::endl;
  }

  system("pause");

  return EXIT_SUCCESS;
}

static bool check(const std::string& text) {
  if (text.length() != 6) {
    return false;
  }
  if (!std::regex_match(text, std::regex("^[A-Za-z]+$"))) {
    return false;
  }
  return true;
}

void normalize(std::string& text) {
  std::transform(text.begin(), text.end(), text.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}
