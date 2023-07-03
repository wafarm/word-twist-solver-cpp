#include "solver.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "resource.h"
#include "utils.h"

static std::unordered_set<std::string> wordlist;

static void remove_duplicates(std::vector<std::string>& list) {
  std::vector<std::string> result;
  for (auto& item : list) {
    if (std::find(result.begin(), result.end(), item) == result.end()) {
      result.push_back(item);
    }
  }
  list = result;
}

static std::vector<std::string> permutations(std::string text) {
  std::vector<std::string> result;
  std::sort(text.begin(), text.end());
  do {
    result.push_back(text);
  } while (std::next_permutation(text.begin(), text.end()));
  remove_duplicates(result);
  return result;
}

static std::vector<std::string> subsets(std::string text) {
  std::vector<std::string> result;
  for (int i = 0; i < (1 << text.length()); i++) {
    std::string subset;
    for (int j = 0; j < text.length(); j++) {
      if (i & (1 << j)) {
        subset += text[j];
      }
    }
    if (subset.length() > 2) result.push_back(subset);
  }
  remove_duplicates(result);
  return result;
}

void init() {
  std::string word;

  start_timer();

  auto file = load_text_resource(IDR_WORDLIST);
  std::istringstream f(file);
  while (std::getline(f, word)) {
    wordlist.insert(word);
  }

  auto duration = stop_timer();
  std::cout << "Loaded " << wordlist.size() << " words in " << duration.count()
            << " ms" << std::endl;
}

std::vector<std::string> findall(const std::string& text) {
  auto subsets = ::subsets(text);
  std::vector<std::string> list;
  for (auto& i : subsets) {
    auto perms = ::permutations(i);
    for (auto& j : perms) {
      if (wordlist.find(j) != wordlist.end()) {
        list.push_back(j);
      }
    }
  }
  remove_duplicates(list);
  return list;
}
