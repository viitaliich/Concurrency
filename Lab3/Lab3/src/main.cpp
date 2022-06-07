#include <iostream>
#include <thread>
#include <vector>

class Unit
{
private:
	int mPosition = 0;

public:
	void Move(int* array, int p);

};

void Unit::Move(int* array, int p)
{
	int P = rand() % 100;
	
	array[mPosition]--;
	if (P < p)
	{
		mPosition--;
	}
	else
	{
		mPosition++;
	}
	array[mPosition]++;
}

void Log(int* array, int length, int iter)
{
	printf("Iteration %d: ", iter);
	for(int i = 0; i < length; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}
void Update(int* array, Unit& unit, int p, int N, int iter)
{

	unit.Move(array, p);

}

int main()
{
	const int N = 10;
	const int K = 5;
	
	int array[N];
	array[0] = K;

	int p = 30;

	int iter = 0;

	std::vector<std::thread> threads;

	while(iter < 10)
	{
		for (int i = 0; i < K; ++i)
			threads.push_back(std::thread(Update, array, new Unit, p, N, iter));

		//Update(array, NULL, p, N, iter);

		for (auto& t : threads)
			t.join();
		
		Log(array, N, iter);
		iter++;
	}


	std::cout << "Hello\n";
	return 0;
}