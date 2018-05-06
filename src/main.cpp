/*

bool verify_add(Matrix m1, Matrix m2, Matrix m3)
{
	bool result = true;

	Matrix m4 = m3-m2;
	result &= (m4 == m1);

	Matrix m5 = m3-m1;
	result &= (m5 == m2);

	return result;
}

bool verify_sub(Matrix m1, Matrix m2, Matrix m3)
{
	bool result = true;

	Matrix m4 = m3+m2;
	result &= m4 == m1;

	return result;
}
*/
/*

int main()
{
	SquareMatrix m1 = SquareMatrix(3);
	SquareMatrix m2 = SquareMatrix(3);

	SquareMatrix dot_result = SquareMatrix(3);
	SquareMatrix add_result = SquareMatrix(3);
	SquareMatrix sub_result = SquareMatrix(3);

	m1.setElement(0, 0, 1);
	m1.setElement(0, 1, 2);
	m1.setElement(2, 0, 3);
	m1.setElement(2, 2, 1);

	m2.setElement(1, 0, 1);
	m2.setElement(0, 2, 2);
	m2.set_element(0, 1, 3);
	m2.set_element(2, 2, 1);

	std::cout << (verify_add(m1, m2, m1+m2)) << std::endl;
	std::cout << (verify_sub(m1, m2, m1-m2)) << std::endl;

	Matrix::dot(m1, m2, dot_result);
	Matrix::sub(m1, m2, sub_result);
	Matrix::add(m1, m2, add_result);

	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;
	std::cout << dot_result << std::endl;
	std::cout << sub_result << std::endl;
	std::cout << add_result << std::endl;

	return 0;
}*/
