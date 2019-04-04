#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;

template<typename T>
using matrix = vector<vector<T> >;

matrix<uint16_t> A, B;

matrix<uint64_t> Vectors;

template<typename T>
void get(matrix<T>& M)
{
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
		{
			cin >> M[i][j];
		}
	}
}

using BITS = bitset<2>;
template<typename Cast = uint16_t, typename T>
void print(matrix<T>& M)
{
	for(int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
		{
			cout << Cast(M[i][j]) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void preprocessVectors(int length)
{
	uint64_t maxLength = (1LL << length);
	Vectors.resize(maxLength, vector<uint64_t>(maxLength));
	for (int i = 0; i < maxLength; i++)
	{
		for (int j = 0; j < maxLength; j++)
		{
			bitset<sizeof(uint64_t)> v1(i), v2(j);
			uint64_t res = 0;
			for (int m = 0; m < sizeof(uint64_t); m++)
			{
				res += v1[m] & v2[m];
				res = res % 2;
			}
			Vectors[i][j] = res;
		}
	}
}

uint64_t readHorizontalVec(matrix<uint16_t>& M, int row, int column, int length)
{
	uint64_t result = 0;
	for (int i = column; i < column + length; i++)
	{
		result *= 2;
		if (i < M[row].size())
		{
			result += M[row][i];
		}
	}
	return result;
}

uint64_t readVerticalVec(matrix<uint16_t>& M, int row, int column, int length)
{
	uint64_t result = 0;
	for (int i = row; i < row + length; i++)
	{
		result *= 2;
		if (i < M.size())
		{
			result += M[i][column];
		}
	}
	return result;
}

matrix<uint64_t> preprocessMatrix(matrix<uint16_t>& M, int k, bool useLines)
{
	matrix<uint64_t> res;
	if (useLines)
	{
		int newLength = M[0].size() / k + (M[0].size() % k > 0);
		res.resize(M.size(), vector<uint64_t>(newLength));
		for (int i = 0; i < res.size(); i++)
		{
			for (int j = 0; j < res[i].size(); j++)
			{
				res[i][j] = readHorizontalVec(M, i, (j * k), k);
			}
		}
	}
	else
	{
		int newLength = M.size() / k + (M.size() % k > 0);
		res.resize(newLength, vector<uint64_t>(M[0].size()));
		for (int i = 0; i < res.size(); i++)
		{
			for (int j = 0; j < res[i].size(); j++)
			{
				res[i][j] = readVerticalVec(M, (i * k), j, k);
			}
		}
	}
	return res;
}

matrix<uint16_t> multiply(matrix<uint64_t>& A, matrix<uint64_t>& B)
{
	matrix<uint16_t> C(A.size(), vector<uint16_t>(B[0].size(), 0));
	for (int i = 0; i < C.size(); i++)
	{
		for (int j = 0; j < C[i].size(); j++)
		{
			for (int m = 0; m < A[i].size(); m++)
			{
				C[i][j] += Vectors[A[i][m]][B[m][j]];
				C[i][j] = C[i][j] % 2;
			}
		}
	}
	return C;
}

int main()
{
	int N, M, L;
	cin >> M >> N >> L;
	A.resize(M, vector<uint16_t>(N));
	B.resize(N, vector<uint16_t>(L));

	get(A);
	get(B);
	int k = log2(N);
	preprocessVectors(k);

	matrix<uint64_t> newA = preprocessMatrix(A, k, true);
	matrix<uint64_t> newB = preprocessMatrix(B, k, false);

	cout << endl;
	cout << "tranformed A: " << endl;
	print(newA);
	cout << "transformed B: " << endl;
	print(newB);

	matrix<uint16_t> C = multiply(newA, newB);
	
	cout << "result: " << endl;
	print(C);
	system("pause");
	return 0;
}
