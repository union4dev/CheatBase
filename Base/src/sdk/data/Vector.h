#pragma once
#include <algorithm>
#include <cmath>

class Vector2D
{
public:
	float x, y;

	constexpr Vector2D(float x = 0.f, float y = 0.f) : x(x), y(y) { }

	bool operator==(const Vector2D& vec)
	{
		return this->IsEqual(vec);
	}

	bool operator!=(const Vector2D& vec) const
	{
		return !this->IsEqual(vec);
	}

	constexpr Vector2D& operator=(const Vector2D& vec)
	{
		this->x = vec.x; this->y = vec.y;
		return *this;
	}

	constexpr Vector2D& operator+=(const Vector2D& vec)
	{
		this->x += vec.x; this->y += vec.y;
		return *this;
	}

	constexpr Vector2D& operator-=(const Vector2D& vec)
	{
		this->x -= vec.x; this->y -= vec.y;
		return *this;
	}

	constexpr Vector2D& operator*=(const Vector2D& vec)
	{
		this->x *= vec.x; this->y *= vec.y;
		return *this;
	}

	constexpr Vector2D& operator/=(const Vector2D& vec)
	{
		this->x /= vec.x; this->y /= vec.y;
		return *this;
	}

	constexpr Vector2D& operator+=(const float add)
	{
		this->x += add; this->y += add;
		return *this;
	}

	constexpr Vector2D& operator-=(const float subtract)
	{
		this->x -= subtract; this->y -= subtract;
		return *this;
	}

	constexpr Vector2D& operator*=(const float multiply)
	{
		this->x *= multiply; this->y *= multiply;
		return *this;
	}

	constexpr Vector2D& operator/=(const float divide)
	{
		this->x /= divide; this->y /= divide;
		return *this;
	}

	Vector2D operator+(const Vector2D& add) const
	{
		return Vector2D(this->x + add.x, this->y + add.y);
	}

	Vector2D operator-(const Vector2D& subtract) const
	{
		return Vector2D(this->x - subtract.x, this->y - subtract.y);
	}

	Vector2D operator*(const Vector2D& multiply) const
	{
		return Vector2D(this->x * multiply.x, this->y * multiply.y);
	}

	Vector2D operator/(const Vector2D& divide) const
	{
		return Vector2D(this->x / divide.x, this->y / divide.y);
	}

	Vector2D operator+(const float add) const
	{
		return Vector2D(this->x + add, this->y + add);
	}

	Vector2D operator-(const float subtract) const
	{
		return Vector2D(this->x - subtract, this->y - subtract);
	}

	Vector2D operator*(const float multiply) const
	{
		return Vector2D(this->x * multiply, this->y * multiply);
	}

	Vector2D operator/(const float divide) const
	{
		return Vector2D(this->x / divide, this->y / divide);
	}

	bool IsZero() const noexcept
	{
		return (std::fpclassify(this->x) == FP_ZERO &&
			std::fpclassify(this->y) == FP_ZERO);
	}

	bool IsEqual(const Vector2D& equal, const float errorMargin = std::numeric_limits<float>::epsilon()) const
	{
		return (std::fabsf(this->x - equal.x) < errorMargin && std::fabsf(this->y - equal.y) < errorMargin);
	}

	float length() const noexcept
	{
		return std::sqrt(x * x + y * y);
	}

	float distance(const Vector2D& vec2d) const noexcept
	{
		return (*this - vec2d).length();
	}

	Vector2D& normalize() noexcept
	{
		x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
		y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
		return *this;
	}
};

class Vector
{
public:
	float x, y, z;

	constexpr Vector(float x = 0.f, float y = 0.f, float z = 0.f) : x(x), y(y), z(z) { }

	constexpr Vector(const float* vec) : x(vec[0]), y(vec[1]), z(vec[2]) { }

	constexpr Vector(const Vector& vec, float z = 0.f) : x(vec.x), y(vec.y), z(z) { }

	float* data()
	{
		return reinterpret_cast<float*>(this);
	}

	const float* data() const
	{
		return reinterpret_cast<float*>(const_cast<Vector*>(this));
	}

	float& operator[](const std::size_t i)
	{
		return this->data()[i];
	}

	const float& operator[](const std::size_t i) const
	{
		return this->data()[i];
	}

	bool operator==(const Vector& vec)
	{
		return this->IsEqual(vec);
	}

	bool operator!=(const Vector& vec) const
	{
		return !this->IsEqual(vec);
	}

	constexpr Vector& operator=(const Vector& vec)
	{
		this->x = vec.x; this->y = vec.y;
		return *this;
	}

	constexpr Vector& operator+=(const Vector& vec)
	{
		this->x += vec.x; this->y += vec.y;
		return *this;
	}

	constexpr Vector& operator-=(const Vector& vec)
	{
		this->x -= vec.x; this->y -= vec.y;
		return *this;
	}

	constexpr Vector& operator*=(const Vector& vec)
	{
		this->x *= vec.x; this->y *= vec.y;
		return *this;
	}

	constexpr Vector& operator/=(const Vector& vec)
	{
		this->x /= vec.x; this->y /= vec.y;
		return *this;
	}

	constexpr Vector& operator+=(const float add)
	{
		this->x += add; this->y += add;
		return *this;
	}

	constexpr Vector& operator-=(const float subtract)
	{
		this->x -= subtract; this->y -= subtract;
		return *this;
	}

	constexpr Vector& operator*=(const float multiply)
	{
		this->x *= multiply; this->y *= multiply;
		return *this;
	}

	constexpr Vector& operator/=(const float divide)
	{
		this->x /= divide; this->y /= divide;
		return *this;
	}

	Vector operator+(const Vector& add) const
	{
		return Vector(this->x + add.x, this->y + add.y);
	}

	Vector operator-(const Vector& subtract) const
	{
		return Vector(this->x - subtract.x, this->y - subtract.y);
	}

	Vector operator*(const Vector& multiply) const
	{
		return Vector(this->x * multiply.x, this->y * multiply.y);
	}

	Vector operator/(const Vector& divide) const
	{
		return Vector(this->x / divide.x, this->y / divide.y);
	}

	Vector operator+(const float add) const
	{
		return Vector(this->x + add, this->y + add);
	}

	Vector operator-(const float subtract) const
	{
		return Vector(this->x - subtract, this->y - subtract);
	}

	Vector operator*(const float multiply) const
	{
		return Vector(this->x * multiply, this->y * multiply);
	}

	Vector operator/(const float divide) const
	{
		return Vector(this->x / divide, this->y / divide);
	}

	float distance(Vector vec) const noexcept
	{
		(*this - vec).length();
	}

	bool IsEqual(const Vector& equal, const float errorMargin = std::numeric_limits<float>::epsilon()) const
	{
		return (std::fabsf(this->x - equal.x) < errorMargin &&
			std::fabsf(this->y - equal.y) < errorMargin &&
			std::fabsf(this->z - equal.z) < errorMargin);
	}

	Vector& normalize() noexcept
	{
		x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
		y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
		z = 0.0f;
		return *this;
	}

	float length() const noexcept
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	float length2D() const noexcept
	{
		return std::sqrt(x * x + y * y);
	}

	constexpr float LengthSqr() const
	{
		return DotProduct(*this);
	}

	constexpr float DotProduct(const Vector& dot) const
	{
		return (this->x * dot.x + this->y * dot.y + this->z * dot.z);
	}

	constexpr float squareLength() const noexcept
	{
		return x * x + y * y + z * z;
	}
};

class Vector4D
{
public:
	float x, y, z, w;

	constexpr Vector4D(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) :
		x(x), y(y), z(z), w(w) { }
};

class __declspec(align(16)) VectorAligned : public Vector
{
public:
	float w;

	VectorAligned() = default;

	explicit VectorAligned(const Vector& base)
	{
		this->x = base.x; this->y = base.y; this->z = base.z; this->w = 0.f;
	}

	constexpr VectorAligned& operator=(const Vector& base)
	{
		this->x = base.x; this->y = base.y; this->z = base.z; this->w = 0.f;
		return *this;
	}
};