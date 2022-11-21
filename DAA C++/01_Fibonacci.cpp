#include<iostream>
using namespace std;

int fibonacci(int count)
{
	if(count < 2) return count;
	int f1 = 0, f2 = 1, sum = 0;

	for (int i = 2; i <= count; i++){
		sum = f1 + f2;
		f1 = f2;
		f2 = sum;
	}
	return sum;
}

int fibonacci_recursive(int count)
{
	if (count <= 1)
		return count;
	else
		return fibonacci_recursive(count - 1) + fibonacci_recursive(count -2);
}

int main(int argc, char* argv[])
{
	cout << fibonacci(20) << "\n";
	cout << fibonacci_recursive(20);
	return 0;
}
