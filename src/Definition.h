#pragma once
#include "Buffer.h"

#include <cstdint>
#include <iostream>
#include <vector>
#include <Eigen/Eigen>

class Configuration
{
public:
	static constexpr const char* WindowTitle = "CPU renderer";
	static constexpr int32_t WindowBeginPositionX = 600;
	static constexpr int32_t WindowBeginPositionY = 600;
	static constexpr int32_t DisplayWidth = 800;
	static constexpr int32_t DisplayHeight = 600;
	static constexpr int32_t DisplayPixelCount = DisplayWidth * DisplayHeight;
};

class ConsoleLog
{
public:
	static void Print(const char* log)
	{
		std::cout << log << std::endl;
	}
};

using Mat4f = Eigen::Matrix4f;
using Mat3f = Eigen::Matrix3f;
using Vec4f = Eigen::Vector4f;
using Vec3f = Eigen::Vector3f;
using Vec2f = Eigen::Vector2f;
using Vec2i = Eigen::Vector2i;
using Quaternion = Eigen::Quaternionf;

using ColorBuffer = Buffer<uint32_t, Configuration::DisplayPixelCount>;
using DepthBuffer = Buffer<float, Configuration::DisplayPixelCount>;
