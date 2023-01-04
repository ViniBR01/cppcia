#include <iostream>
#include <string>
#include <thread>
#include <vector>

void hello() {
  std::thread::id thread_id = std::this_thread::get_id();
  unsigned int thread_id_as_int = *static_cast<unsigned int*>(static_cast<void*>(&thread_id));
  std::string thread_id_as_str = std::to_string(thread_id_as_int);
  std::string message = "Hello Concurrent World: thread_id=" + thread_id_as_str + "\n";
  std::cout << message;
}

int main () {
  unsigned long const num_threads = std::thread::hardware_concurrency();
  std::cout << "Max threads in this HW: " << num_threads << std::endl;
  std::vector<std::thread>  threads(num_threads-1);
  for(unsigned long i=0;i<(num_threads-1);++i) {
    threads[i]=std::thread(hello);                         
  }
  for(auto& entry: threads) {
    entry.join();
  }
}
