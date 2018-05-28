//
// Created by mathew on 5/28/18.
//

#include <Transforms/PerspectiveTransform.h>
#include <cmath>


PerspectiveTransform::PerspectiveTransform()
{
	mark_for_update();

}

PerspectiveTransform::PerspectiveTransform(float aspect_ratio, float near, float far, float fov) :
		aspect_ratio(aspect_ratio),
		near(near),
		far(far),
		fov(fov)
{
	mark_for_update();
}

void PerspectiveTransform::set_view_frustum(float aspect_ratio, float near, float far, float fov)
{
	mark_for_update();
	this->aspect_ratio = aspect_ratio;
	this->near = near;
	this->far = far;
	this->fov = fov;
}

void PerspectiveTransform::calculate_matrix(Matrix4f& dest)
{
	dest.set_identity();
	dest.set_element(0, 0, 1.0 / tan(fov / 2.0) * aspect_ratio);
	dest.set_element(1, 1, 1.0 / tan(fov / 2.0));
	dest.set_element(2, 2, -((far+near) / (far - near)));
	dest.set_element(3, 2, -((2 * near * far) / (far - near)));
	dest.set_element(3, 3, 0);
	dest.set_element(2, 3, -1);
}

void PerspectiveTransform::calculate_matrix_inverse(Matrix4f& dest)
{
	// Meh, Later TODO

}
