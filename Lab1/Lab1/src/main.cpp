#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

#define NUM 1000000000

// CPU-bound

// Function foo() doea some complex calculations sequentially
size_t foo(int num)
{
	size_t result = 1;
	int i = 1;
	while(i < num)
	{
		result = result * i;
		result = std::sqrt(result);
		result = 0;
		i++;
	}
	
	return result;
}

// Function foo_c does same calculations as foo() but in 8 threads.
int foo_c(int num)
{
	const int num_threads = 8;
	std::thread array_t[num_threads];
	
	std::thread t1(foo, num / 8);
	std::thread t2(foo, num / 8);
	std::thread t3(foo, num / 8);
	std::thread t4(foo, num / 8);
	std::thread t5(foo, num / 8);
	std::thread t6(foo, num / 8);
	std::thread t7(foo, num / 8);
	std::thread t8(foo, num / 8);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	
	return 0;

}

int main()
{
	uint64_t ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "result1 = " << foo(NUM) << std::endl;
	uint64_t ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << ms2 - ms1 << std::endl;

	uint64_t ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "result2 = " << foo_c(NUM) << std::endl;
	uint64_t ms4 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << ms4 - ms3 << std::endl;

	return 0;
}