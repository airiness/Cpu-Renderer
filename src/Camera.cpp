#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(const Vec3f& position, const Vec3f& target, const Vec3f& up,
	float fovy, float near, float far, float aspect)
	: mPosition(position)
	, mTarget(target)
	, mUp(up)
	, mFovy(Math::ToRadian(fovy))
	, mNear(near)
	, mFar(far)
	, mAspectRatio(aspect)
{
}

Mat4f Camera::GetViewMatrix()
{
	Vec3f forward = mPosition - mTarget;
	forward.normalize();
	Vec3f left = mUp.cross(forward);
	left.normalize();
	Vec3f up = forward.cross(left);

	Mat4f viewMat;
	viewMat <<
		left.x(), left.y(), left.z(), -left.dot(mPosition),
		up.x(), up.y(), up.z(), -up.dot(mPosition),
		forward.x(), forward.y(), forward.z(), -forward.dot(mPosition),
		0, 0, 0, 1;

	return viewMat;
}

Mat4f Camera::GetOrthoProjMatrix()
{
	auto ortho = Mat4f::Identity();

	return ortho;
}

Mat4f Camera::GetPerspProjMatrix()
{
	Mat4f perspProjMat;
	const auto zRange = mFar - mNear;
	const auto mat11 = 1.0f / std::tan(mFovy * 0.5f);
	perspProjMat <<
		(mat11 / mAspectRatio), 0.0f, 0.0f, 0.0f,
		0.0f, mat11, 0.0f, 0.0f,
		0.0f, 0.0f, ((-mNear - mFar) / zRange), (-2.0f * mFar * mNear / zRange),
		0.0f, 0.0f, -1.0f, 0.0f;

	return perspProjMat;
}
