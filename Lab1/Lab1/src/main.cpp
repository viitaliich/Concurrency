#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <math.h>

#define NUM 100

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

int recursive_Fibonacci(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	return recursive_Fibonacci(n - 1) + recursive_Fibonacci(n - 2);
}

std::atomic<int> shared_value;

void recursive_Fibonacci_c(int n, int num_t)
{
	if (n == 0)
	{
		shared_value += 0; return;
	}
	if (n == 1)
	{
		shared_value += 1; return;
	}
	if(num_t > 0)
	{
		num_t-=2;
		std::thread t1(recursive_Fibonacci_c, n - 1, num_t);
		std::thread t2(recursive_Fibonacci_c, n - 2, num_t);
		t1.join();
		t2.join();
	}
	else
	{
		shared_value += recursive_Fibonacci(n - 1);
		shared_value += recursive_Fibonacci(n - 2);
	}
}

int main()
{
	int threads_num = std::thread::hardware_concurrency();
	// Memory-bound

	// Sequential Fibonacci sequence
	const int F = 40;
	uint64_t ms5 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	recursive_Fibonacci(F);
	uint64_t ms6 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "F1 " << ms6 - ms5 << std::endl;
	
	// Concurrent Fibonacci sequence
	uint64_t ms7 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	recursive_Fibonacci_c(F, threads_num);
	int result = shared_value;
	uint64_t ms8 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "F2 " << ms8 - ms7 << std::endl;

	// CPU-bound

	// Function foo() does some complex calculations sequentially
	uint64_t ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "result1 = " << foo(NUM) << std::endl;
	uint64_t ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << ms2 - ms1 << std::endl;

	// Function foo_c does same calculations as foo() but in 8 threads.
	uint64_t ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "result2 = " << foo_c(NUM) << std::endl;
	uint64_t ms4 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << ms4 - ms3 << std::endl;

	return 0;
}