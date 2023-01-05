#include <iostream>
#include <string>
#include <thread>

void fun(int id, std::string const& message) {
  std::cout << id << ": " << message << std::endl;
}

void spawn_threads_with_functions() {
  std::cout << "Threads receving function with argument" << std::endl;
  std::thread thread_with_function(fun, 1, "hello");
  std::string message = "goodbye";
  std::thread another_thread_with_function(fun, 2, std::string(message));
  std::thread yet_another_thread_with_function(fun, 3, std::ref(message));
  thread_with_function.join();
  another_thread_with_function.join();
  yet_another_thread_with_function.join();
  std::cout << message << std::endl;
}

int main() {
  spawn_threads_with_functions();
}
