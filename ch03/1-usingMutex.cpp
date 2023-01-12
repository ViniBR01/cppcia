#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>

void add_to_list(std::mutex& some_mutex, std::list<int>& some_list, int new_value) {
  std::lock_guard<std::mutex> guard(some_mutex);
  some_list.push_back(new_value);
}

bool list_contains(std::mutex& some_mutex, std::list<int>& some_list, int value_to_find) {
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main() {
  std::list<int> some_list;
  std::mutex some_mutex;
  add_to_list(some_mutex, some_list, 1);
  std::cout << list_contains(some_mutex, some_list, 2) << std::endl;
  add_to_list(some_mutex, some_list, 2);
  std::cout << list_contains(some_mutex, some_list, 2) << std::endl;

  return 0;
}
