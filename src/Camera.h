#pragma once
#include "Definition.h"
#include "Math.h"

class Camera
{
public:
	Camera();
	Camera(const Vec3f& position, const Vec3f& target, const Vec3f& up,
		float fovy, float near, float far, float aspect);
	~Camera() = default;

	float GetNear() const { return mNear; }
	float GetFar() const { return mFar; }

	Mat4f GetViewMatrix();
	Mat4f GetOrthoProjMatrix();
	Mat4f GetPerspProjMatrix();

private:
	Vec3f mPosition = Vec3f(0.0f, 3.0f, 8.0f);
	Vec3f mTarget = Vec3f::Zero();
	Vec3f mUp = Vec3f::UnitY();
	float mFovy = Math::ToRadian(60.0f);
	float mNear = 0.1f;
	float mFar = 100.0f;
	float mAspectRatio = static_cast<float>(Configuration::DisplayWidth) / Configuration::DisplayHeight;
};