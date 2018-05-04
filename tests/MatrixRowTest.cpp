//
// Created by mathew on 5/3/18.
//

#include <Linear/Matrix.h>
#include <Linear/Guassian.h>

int main()
{
	Matrix m1 = Matrix(6,3);

	m1.set_element(0,0,0);
	m1.set_element(0,1,1);
	m1.set_element(0,2,1);

	m1.set_element(1,0,1);
	m1.set_element(1,1,3);
	m1.set_element(1,2,0);

	m1.set_element(2,0,3);
	m1.set_element(2,1,3);
	m1.set_element(2,2,0);

	std::cout << m1 << std::endl;

	return 0;
}
