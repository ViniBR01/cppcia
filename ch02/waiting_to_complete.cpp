#include <chrono>
#include <iostream>
#include <thread>

int do_something(int id) {
  int new_id = id+1;
  return new_id;
}

struct func {
  int& id;
  func(int& id_):id(id_){}
  // int id; //save as a local variable instead
  // func(int id_):id(id_){}
  void operator()() {
    for (unsigned j=0; j<1000000; ++j) {
      if (id % 100000 == 0) {
        std::cout << id << std::endl;
      }
      id = do_something(id);
    }
    std::cout << id << std::endl;
  }
};

void oops() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach(); //Thread will live, but local state will be destroyed
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::cout << "local_state before destruction = "
            << some_local_state << std::endl;
}

class thread_guard {
  std::thread& t;
public:
  explicit thread_guard(std::thread& t_):t(t_){}
  ~thread_guard() {
    if(t.joinable()) {
      t.join();
    }
  }
  thread_guard(thread_guard const&)=delete;
  thread_guard& operator=(thread_guard const&)=delete;
};

void this_one_works() {
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  thread_guard my_guard(my_thread);
  //do something quick in this thread;
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  std::cout << "Exiting function that works" << std::endl;
}

int main() {
  // std::cout << "Thread pointing to variable after its destruction"
  //           << std::endl;
  // oops(); //undefined behavior
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // std::cout << std::endl;

  std::cout << "Joining a thread with thread_guard" << std::endl;
  this_one_works();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
