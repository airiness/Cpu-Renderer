#include "Renderer.h"

#include "Display.h"
#include "Engine.h"

Renderer::Renderer()
{
}

bool Renderer::Initialize()
{
	return true;
}

void Renderer::Destroy()
{

}

void Renderer::ClearBuffer()
{
	mFrameBuffer.ClearColorBuffer(mClearColor);
	mFrameBuffer.ClearDepthBuffer();
}

void Renderer::SwapBuffer()
{
	Engine::Instance().GetDisplay().SwapBuffer(&mFrameBuffer.GetColorBuffer());
}

void Renderer::DrawTriangle(const TriangleColorVertex& t, FillMode fillmode)
{
	// mvp matrix
	Mat4f mvp = mProjectionMatrix * mViewMatrix * mModelMatrix;

	// eye->clip
	std::array<Vec4f, 3> vertices;
	for (size_t i = 0; i < 3; i++)
	{
		const ColorVertex p = t.at(i);
		vertices.at(i) = mvp * Vec4f(p.mPosition.x(), p.mPosition.y(), p.mPosition.z(), 1.0f);
	}

	// clip->ndc
	for (auto& v : vertices)
	{
		v /= v.w();
	}

	// ndc->screen coordinate
	std::array<Vec2f, 3> screenCoords;
	std::array<Color, 3> vertexColor = { t.at(0).mColor,t.at(1).mColor, t.at(2).mColor };
	std::array<float, 3> screenDepths = {};
	for (size_t i = 0; i < 3; i++)
	{
		const auto& v = vertices.at(i);
		screenCoords.at(i) = Vec2f(mWidth * 0.5f * (v.x() + 1.0f), mHeight * 0.5f * (v.y() + 1.0f));
		screenDepths.at(i) = 0.5f * (v.z() + 1.0f);
	}

	auto& colorBuffer = mFrameBuffer.GetColorBuffer();
	auto& depthBuffer = mFrameBuffer.GetDepthBuffer();

	if (fillmode == FillMode::Wireframe)
	{
		const auto& a = screenCoords.at(0);
		const auto& b = screenCoords.at(1);
		const auto& c = screenCoords.at(2);

		DrawLine2D(a, b, vertexColor.at(0), &colorBuffer);
		DrawLine2D(b, c, vertexColor.at(1), &colorBuffer);
		DrawLine2D(c, a, vertexColor.at(2), &colorBuffer);

		return;
	}

	// back face culling
	if (IsBackFace(screenCoords))
	{
		return;
	}

	// get boundingbox of triangle
	BoundingBox bb = GetTriangleBoundingBox(screenCoords);

	for (int32_t x = bb.mMin.x(); x <= bb.mMax.x(); x++)
	{
		for (int32_t y = bb.mMin.y(); y <= bb.mMax.y(); y++)
		{
			// to pixel center
			Vec2f point = Vec2f(0.5f + x, 0.5f + y);
			// barycentric weight
			Vec3f weight = CalculateWeight(screenCoords, point);

			if (weight.x() >= 0 && weight.y() >= 0 && weight.z() >= 0)
			{
				float depthInter = DepthInterpolate(screenDepths, weight);
				Color colorInter = ColorInterpolate(vertexColor, weight);
				if (depthInter < depthBuffer(x, y))
				{
					depthBuffer.SetPixelData(x, y, depthInter);
					colorBuffer.SetPixelData(x, y, colorInter.Data());
				}
			}
		}
	}
}

void Renderer::DrawPoint2D(const Vec2f& pos, Color color, ColorBuffer* buffer)
{
	buffer->SetPixelData(static_cast<int32_t>(pos.x()), static_cast<int32_t>(pos.y()), color.Data());
}

void Renderer::DrawLine2D(const Vec2f& begin, const Vec2f& end, Color color, ColorBuffer* buffer)
{
	auto x0 = begin.x();
	auto y0 = begin.y();
	auto x1 = end.x();
	auto y1 = end.y();

	auto isSteep = false;
	if (std::abs(x1 - x0) < std::abs(y1 - y0))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		isSteep = true;
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	if (x0 == x1)
	{
		for (int32_t y = y0; y <= y1; ++y)
		{
			DrawPoint2D(Vec2f(x0, y), color, buffer);
		}
		return;
	}

	for (int32_t x = x0; x <= x1; ++x)
	{
		float t = (x - x0) / static_cast<float>(x1 - x0);
		int32_t y = static_cast<int32_t>(t * y1 + (1.0f - t) * y0);

		isSteep ?
			DrawPoint2D(Vec2f(y, x), color, buffer) :
			DrawPoint2D(Vec2f(x, y), color, buffer);
	}
}

void Renderer::DrawTriangle2D(const std::array<Vec2f, 3>& t, Color color, ColorBuffer* buffer)
{
	BoundingBox bb = GetTriangleBoundingBox(t);

	for (int32_t x = bb.mMin.x(); x <= bb.mMax.x(); x++)
	{
		for (int32_t y = bb.mMin.y(); y <= bb.mMax.y(); y++)
		{
			auto bc = CalculateWeight(t, Vec2f(x, y));
			if (bc.x() < 0 || bc.y() < 0 || bc.z() < 0)
			{
				continue;
			}

			DrawPoint2D(Vec2f(x, y), color, buffer);
		}
	}
}

BoundingBox Renderer::GetTriangleBoundingBox(const std::array<Vec2f, 3>& t)
{
	BoundingBox bb;
	auto minmaxX = std::minmax_element(t.begin(), t.end(), [](const Vec2f& lhs, const Vec2f& rhs) { return lhs.x() < rhs.x(); });
	auto minmaxY = std::minmax_element(t.begin(), t.end(), [](const Vec2f& lhs, const Vec2f& rhs) { return lhs.y() < rhs.y(); });
	bb.mMin << static_cast<int32_t>(std::max(minmaxX.first->x(), 0.0f)), static_cast<int32_t>(std::max(minmaxY.first->y(), 0.0f));
	bb.mMax << static_cast<int32_t>(std::min(minmaxX.second->x(), Configuration::DisplayWidth - 1.0f)), static_cast<int32_t>(std::min(minmaxY.second->y(), Configuration::DisplayHeight - 1.0f));
	return bb;
}

Vec3f Renderer::CalculateWeight(const std::array<Vec2f, 3>& vertices, const Vec2f& p)
{
	const auto& a = vertices.at(0);
	const auto& b = vertices.at(1);
	const auto& c = vertices.at(2);

	Vec2f ab = b - a;
	Vec2f ac = c - a;
	Vec2f ap = p - a;

	float denominator = ab.x() * ac.y() - ab.y() * ac.x();
	float s = (ac.y() * ap.x() - ac.x() * ap.y()) / denominator;
	float t = (ab.x() * ap.y() - ab.y() * ap.x()) / denominator;

	return Vec3f(1.0f - s - t, s, t);
}

float Renderer::DepthInterpolate(const std::array<float, 3>& screenDepth, const Vec3f& weight)
{
	return
		screenDepth.at(0) * weight.x() +
		screenDepth.at(1) * weight.y() +
		screenDepth.at(2) * weight.z();
}

Color Renderer::ColorInterpolate(const std::array<Color, 3>& color, const Vec3f& weight)
{
	float r = 0.0f, g = 0.0f, b = 0.0f;

	for (size_t i = 0; i < 3; i++)
	{
		const auto c = color.at(i).Data();
		const auto& w = weight[i];
		r += static_cast<float>(c >> 16 & 0x000000ffu) * w;
		g += static_cast<float>(c >> 8 & 0x000000ffu) * w;
		b += static_cast<float>(c & 0x000000ffu) * w;
	}

	return 0xff000000u | (static_cast<uint32_t>(r) << 16) | (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
}

bool Renderer::IsBackFace(const std::array<Vec2f, 3>& screenCoord)
{
	const auto& a = screenCoord.at(0);
	const auto& b = screenCoord.at(1);
	const auto& c = screenCoord.at(2);

	float area =
		(a.x() * b.y() - b.x() * a.y()) +
		(b.x() * c.y() - c.x() * b.y()) +
		(c.x() * a.y() - a.x() * c.y());

	return area <= 0.0f;
}

FrameBuffer::FrameBuffer()
	: mColorBuffer(Configuration::DisplayWidth, Configuration::DisplayHeight)
	, mDepthBuffer(Configuration::DisplayWidth, Configuration::DisplayHeight)
{
}

void FrameBuffer::ClearColorBuffer(Color color)
{
	mColorBuffer.Clear(color.Data());
}

void FrameBuffer::ClearDepthBuffer()
{
	mDepthBuffer.Clear(std::numeric_limits<float>::max());
}