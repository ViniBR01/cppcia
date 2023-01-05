#include <iostream>
#include <thread>

void do_some_work() {
  std::cout << "This thread is doing some work." << std::endl;
}

class background_task {
public:
  void operator()() const {
    do_some_work();
  }
};

int main() {
  std::thread thread_from_function(do_some_work);
  thread_from_function.join();

  background_task obj_with_function_call_operator;
  std::thread thread_from_object(obj_with_function_call_operator);
  thread_from_object.join();

  std::thread thread_from_unnamed_object{background_task()};
  thread_from_unnamed_object.join();

  std::thread thread_from_lambda_function([]{
                                            do_some_work();
                                          });
  thread_from_lambda_function.join();
}
