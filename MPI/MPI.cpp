#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <string>

using namespace std;

int numLength(int x)
{
	int i = 0;
	while (x != 0)
	{
		x /= 10;
		i++;
	}
	return i;
}

bool CheckPalindrome(int x) {
	int length = numLength(x);
	string num = to_string(x);
	for (int i = 0; i < length / 2; i++) {
		if (num[i] != num[length - i - 1]) return false;
	}
	return true;
}

int main(int argc, char **argv)
{
	int id, p;
	long long solution_part = 0;
	long long total_sln = 0;
	double wtime = 0;

	long long down = (argc > 1) ? atol(argv[1]) : 300;
	long long up = (argc > 2) ? atol(argv[2]) : 90000000;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (id == 0)
	{
		wtime = MPI_Wtime();
	}
	MPI_Bcast(&down, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&up, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = down; i < up; i++) {
		if (i % p == id)
		{
			if (CheckPalindrome(i)) {
				solution_part++;
			}
		}
	}
	MPI_Reduce(&solution_part, &total_sln, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (id == 0)
	{
		wtime = MPI_Wtime() - wtime;
		std::cout << "Kilkist rozvyazkiv: " << total_sln << ".\nChas roboty programy: " << wtime << "sek.\n";
	}

	MPI_Finalize();

	return 0;
}