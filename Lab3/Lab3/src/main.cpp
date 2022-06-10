#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <random>

#define RAND_MAX 100

void Log(std::vector<int>& array, int length, int iter);

class Unit
{
private:
	int mPosition = 0;
	int P;

public:
	Unit(int p);
	void Move(std::vector<int>* array, int p, int N);
	void SetP(int p);

};

Unit::Unit(int p)
{
	P = p;
}

void Unit::SetP(int p)
{
	P = p;
}

void Unit::Move(std::vector<int>* array, int p, int N)
{
	//printf("\n@@@ = %d", P);
	
		CRITICAL_SECTION m_CriticalSection;
		InitializeCriticalSection(&m_CriticalSection);
		EnterCriticalSection(&m_CriticalSection);
		((*array)[mPosition])--;
		LeaveCriticalSection(&m_CriticalSection);
		DeleteCriticalSection(&m_CriticalSection);
		//Log(*array, N, 99);

		//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=%d", P);

		if ((P <= p || mPosition == N-1) && mPosition-1 >= 0)
		{
			mPosition--;
		}
		else if((P > p || mPosition == 0) && mPosition+1 < N)
		{
			mPosition++;
		}
		CRITICAL_SECTION m_CriticalSection1;
		InitializeCriticalSection(&m_CriticalSection1);
		EnterCriticalSection(&m_CriticalSection1);
		((*array)[mPosition])++;
		LeaveCriticalSection(&m_CriticalSection1);
		DeleteCriticalSection(&m_CriticalSection);
		//Log(*array, N, 99);



}

void Log(std::vector<int>& array, int length, int iter)
{
	printf("Iteration %d: ", iter);
	for(int i = 0; i < length; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}
void Update(std::vector<int>* array, Unit* unit, int p, int N)
{

	unit->Move(array, p, N);

}

int main()
{
	const int N = 10;
	const int K = 5;
	
	std::vector<int> array(N);
	array[0] = K;

	int p = 30;


	std::vector<std::thread> threads;
	std::vector<Unit*> units(K);
	for (int j = 0; j < K; j++)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::minstd_rand0 generator(seed);
		int random_variable = generator() % 100;

		units[j] = new Unit(random_variable);
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	int iter = 0;
	while (iter < 5)
	{
		for (int i = 0; i < K; i++)
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::minstd_rand0 generator(seed);
			int random_variable = generator() % 100;
			units[i]->SetP(random_variable);

			threads.push_back(std::thread(Update, &array, units[i], p, N));
		}

		for (auto& t : threads)
			if (t.joinable())
				t.join();
		
		Log(array, N, iter);
		printf("\n***\n");
		iter++;
	}


	std::cout << "Hello\n";
	return 0;
}