//
// Created by mathew on 5/3/18.
//

#include <Linear/Matrix.h>
#include <Linear/SquareMatrix.h>

int main()
{
	SquareMatrix m1 = SquareMatrix(4);
	SquareMatrix m2 = SquareMatrix(4);

	m1.set_identity();

	Matrix::row_operation_swap(m1, 0, 3, m2);

	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;

	return 0;
}