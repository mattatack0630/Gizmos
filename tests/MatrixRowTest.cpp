//
// Created by mathew on 5/3/18.
//


#include <vector>

struct Matrix{
	std::vector<std::vector<float>> elements;
	int height;
	int width;

	Matrix(int w, int h)
	{
		width = w;
		height = h;

		for (int i = 0; i < height; i++) {
			elements.push_back(std::vector<float>());

			for (int j = 0; j < width; j++) {
				elements[i].emplace_back(0.0f);
			}
		}
	}

	float get_element(int x, int y) const { return elements[y][x]; }

	void set_element(int x, int y, float value) { elements[y][x] = value; }
};

void dot(Matrix const& left, Matrix const& right, Matrix& dest)
{
	float t_elements[right.width][left.height];

	for (int i = 0; i < left.height; i++) {
		for (int j = 0; j < right.width; j++) {
			float elementVal = 0;

			for (int k = 0; k < left.width; k++)
				elementVal += (left.get_element(k, i) * right.get_element(j, k));

			t_elements[j][i] = elementVal;
		}
	}

	for (int i = 0; i < dest.width; i++)
		for (int j = 0; j < dest.height; j++)
			dest.set_element(i, j, t_elements[i][j]);
}

/*int main()
{
	Matrix m1 = Matrix(3,3);
	Matrix m2 = Matrix(3,3);
	Matrix m3 = Matrix(3,3);

	dot(m1, m2, m3);

	return 0;
}*/
