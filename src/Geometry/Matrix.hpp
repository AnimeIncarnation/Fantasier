#pragma once
#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "Vector.hpp"
#include <vector>
#include <initializer_list>


/*2022.7.18备注：
*	1. 以初始化列表为参数的构造器 ClassName(const std::initializer_list<T>& list)........必须在头文件中书写实现，且不用写inline。若分文件编写则报链接错误。
*	2. 带模板的operator必须在头文件中书写实现，且不用写inline。若分文件编写则报链接错误。
*	3. 类的operator[]一般是一定要重载一份const和一份无const
*/






template<class T, int N,int M>
class Matrix
{
private:
	std::vector< Vector<T,M>> raw;
	unsigned int rows{ N }, columns{ M };


public:
	Matrix():raw(N) {};
	Matrix(const std::initializer_list<T>& list);
	Matrix(const Matrix<T,N,M>& m):raw(m.raw){};

	Matrix<T,N,M> operator+ (const Matrix<T,N,M>& m) const ;
	Matrix<T,N,M> operator- (const Matrix<T,N,M>& m) const ;
	Vector<T,N>   operator* (const Vector<T,M>& m) const ;
	Matrix<T,N,M> operator* (const float x) const ;
	Vector<T,N>&  operator[](const int i) { return raw.at(i); }
	const Vector<T, N>& operator[](const int i)const { return raw.at(i); }
	Matrix<T,N,M> transpose()const ;
	Matrix<T,N,M> inverse()const ;
	unsigned int GetRows() const { return rows; }
	unsigned int GetColumns() const { return columns; }

};		

typedef Matrix<int,   2,2> Matrix2i;
typedef Matrix<float, 2,2> Matrix2f;
typedef Matrix<int,   3,3> Matrix3i;
typedef Matrix<float, 3,3> Matrix3f;
typedef Matrix<int,   4,4> Matrix4i;
typedef Matrix<float, 4,4> Matrix4f;



template<class T, int N, int M>
Matrix<T,N,M>::Matrix(const std::initializer_list<T>& list) :raw(N)
{
	int count = 0;
	for (auto arg : list)
	{
		if (count / N >= N)
		{
			std::cout << "Warning: Too much params for Matrix Initialization in file " << __FILE__ << " at line: " << __LINE__ << std::endl;
			break;
		}
		raw[count / M][count % M] = arg;
		++count;
	}
}

template<class T, int N, int M>
Matrix<T, N, M> Matrix<T, N, M>::operator+(const Matrix<T, N, M>& m)	const 
{
	Matrix<T, N, M> sum;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < M;j++)
		{
			sum[i][j] = raw[i][j] + m.raw[i][j];
		}
	}
	return sum;
}

template<class T, int N, int M>
Matrix<T, N, M> Matrix<T, N, M>::operator-(const Matrix<T, N, M>& m) const
{
	Matrix<T, N, M> sub;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < M;j++)
		{
			sub[i][j] = raw[i][j] - m.raw[i][j];
		}
	}
	return sub;
}

template<class T, int N, int M, int K>
Matrix<T, N, K> operator*(const Matrix<T, N, M>& m1, const Matrix<T, M, K>& m2)
{
	Matrix<T, N, K> mul;
	for (int n = 0;n < N;n++)
	{
		for (int k = 0;k < K;k++)
		{
			for (int iter = 0;iter < M;iter++)
			{
				mul[n][k] += m1[n][iter] * m2[iter][k];
			}
		}
	}
	return mul;
}

template<class T, int N, int M>
Vector<T, N> Matrix<T, N, M>::operator*(const Vector<T, M>& v) const
{
	Vector<T, N> mul;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < M;j++)
		{
			mul[i] += raw[i][j] * v[j];
		}
	}
	return mul;
}

template<class T, int N, int M>
Matrix<T, N, M> Matrix<T, N, M>::operator*(const float x)	const
{
	Matrix<T, N, M> mul;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < M;j++)
		{
			mul[i][j] = raw[i][j] * x;
		}
	}
	return mul;
}

template<class T, int N, int M>
Vector<T, M> operator*(const Vector<T, N>& v,const Matrix<T, N, M>& m)	
{
	Vector<T, M> mul;
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
		{
			mul[i] +=  v[j] * m[j][i] ;
		}
	}
	return mul;
}

template <class T, int N, int M>	inline
std::ostream& operator<<(std::ostream& s, const  Matrix<T, N,M>& m)	
{
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < M;j++)
		{
			s << m[i][j] << " ";
		}
		s << std::endl;
	}

	return s;
}






#endif 

