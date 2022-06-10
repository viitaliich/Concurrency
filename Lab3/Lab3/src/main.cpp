#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <chrono>
#include <random>

void Log(std::vector<int>& array, int length, int iter)
{
	printf("Iteration %d: ", iter);
	for (int i = 0; i < length; i++)
	{
		printf("[%d] ", array[i]);
	}
	printf("\n");
}

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

Unit::Unit(int p) { P = p; }

void Unit::SetP(int p) { P = p; }

void Unit::Move(std::vector<int>* array, int p, int N)
{
	CRITICAL_SECTION m_CriticalSection;
	InitializeCriticalSection(&m_CriticalSection);
	EnterCriticalSection(&m_CriticalSection);
	((*array)[mPosition])--;
	LeaveCriticalSection(&m_CriticalSection);
	DeleteCriticalSection(&m_CriticalSection);

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
}

void Update(std::vector<int>* array, Unit* unit, int p, int N)
{
	unit->Move(array, p, N);
}

int main()
{
	const int N = 10;
	const int K = 500;
	const int p = 30;

	const bool mode = 1;	// 0 - iterations, 1 - time
	const int iter_num = 5;
	const int time = 10000;	// ms
	const int delay = 10;	// ms
	
	std::vector<std::thread> threads;
	std::vector<Unit*> units(K);
	std::vector<int> array(N);
	array[0] = K;

	for (int j = 0; j < K; j++)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::minstd_rand0 generator(seed);
		int random_variable = generator() % 100;

		units[j] = new Unit(random_variable);
	}

	int iter = 0;
	if(mode == 0)
	{
		while (iter < iter_num)
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
			printf("\n");
			iter++;
		}
	}
	else if (mode == 1)
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> startPoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(startPoint).time_since_epoch().count();
		std::chrono::time_point<std::chrono::high_resolution_clock> endPoint = std::chrono::high_resolution_clock::now();;
		auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endPoint).time_since_epoch().count();

		while (end - start < time)
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
			printf("\n");
			iter++;

			std::this_thread::sleep_for(std::chrono::milliseconds(delay));

			endPoint = std::chrono::high_resolution_clock::now();
			end = std::chrono::time_point_cast<std::chrono::milliseconds>(endPoint).time_since_epoch().count();
		}
	}

	return 0;
}