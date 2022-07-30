#include "Matrix.hpp"
#include "Vector.hpp"
#include <iostream>



template<class T, int N, int M>
 Matrix<T, N, M> Matrix<T, N, M>::transpose()	 const
{
	 Matrix<T, N, M> mat;
	 for (int i = 0;i < N;++i)
	 {
		 for (int j = 0;j < M;++j)
		 {
			 mat[i][j] = raw[j][i];
		 }
	 }
	 return mat;
}

template<class T, int N, int M>
 Matrix<T, N, M> Matrix<T, N, M>::inverse()const
{
	return Matrix<T, N>();
}


