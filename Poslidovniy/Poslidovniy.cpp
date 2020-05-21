#include <iostream>
#include <iostream>
#include <omp.h>
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
	long long total_sln = 0;

	long long down = (argc > 1) ? atol(argv[1]) : 300;
	long long up = (argc > 2) ? atol(argv[2]) : 90000000;

	double tm = omp_get_wtime();

	for (int p = down; p < up; p++) {
		if (CheckPalindrome(p)) {
			total_sln++;
		}
	}

	tm = omp_get_wtime() - tm;
	std::cout << "Kilkist rozvyazkiv: " << total_sln << ".\nChas roboty programy: " << tm << "sek.\n";
	
	return 0;
}