#pragma once
#include <array>
#include <memory>

template<typename T, size_t Size>
class Buffer
{
public:
	using BufferArray = std::array<T, Size>;
	using BufferPtr = std::unique_ptr<BufferArray>;

public:
	Buffer(int width, int height);
	~Buffer() = default;

	T& operator()(int32_t x, int32_t y);

	void SetPixelData(int32_t x, int32_t y, T value);

	const T* GetBufferPointer() const;

	size_t GetBufferSize() const;

	void Clear(T value);

private:
	int32_t mWidth = 0;
	int32_t mHeight = 0;

	BufferPtr mBuffer;
};

template<typename T, size_t Size>
inline Buffer<T, Size>::Buffer(int width, int height)
	: mWidth(width)
	, mHeight(height)
	, mBuffer(std::make_unique<BufferArray>())
{
}

template<typename T, size_t Size>
inline T& Buffer<T, Size>::operator()(int32_t x, int32_t y)
{
	return mBuffer->at((mHeight - y - 1) * mWidth + x);
}

template<typename T, size_t Size>
inline void Buffer<T, Size>::SetPixelData(int32_t x, int32_t y, T value)
{
	mBuffer->at((mHeight - y - 1) * mWidth + x) = value;
}

template<typename T, size_t Size>
inline const T* Buffer<T, Size>::GetBufferPointer() const
{
	return mBuffer->data();
}

template<typename T, size_t Size>
inline size_t Buffer<T, Size>::GetBufferSize() const
{
	return sizeof(T) * Size;
}

template<typename T, size_t Size>
inline void Buffer<T, Size>::Clear(T value)
{
	std::fill(mBuffer->begin(), mBuffer->end(), value);
}
