/*
Orchid source code is Copyright(c) 2018
Li Wei.
This file is part of Orchid.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _VECTORH_
#define _VECTORH_


#include <iostream>
#include <array>


#include <iomanip>
#include <sstream>
#include <algorithm>
#include "../core/common.h"

namespace Orchid
{
	template<typename T>
	class Vector3_
	{
	public:
		//Vector3_() :_x{ 0 }, _y{ 0 }, _z{ 0 } {}
		Vector3_(T x = T(0), T y = T(0), T z = T(0)) :_x{ x }, _y{ y }, _z{ z } {}
		template<typename otherType>
		Vector3_(const Vector3_<otherType> &v)
		{
			_x = T(v.x());
			_y = T(v.y());
			_z = T(v.z());
		}

		~Vector3_() {}
		T x() const { return _x; }
		T y() const { return _y; }
		T z() const { return _z; }

		T& xRef() { return _x; }
		T& yRef() { return _y; }
		T& zRef() { return _z; }

		T &operator[](unsigned i)
		{
			return (&_x)[i];
		}
		const T &operator[](unsigned i)const
		{
			return (&_x)[i];
		}

		Vector3_& operator = (const Vector3_& v)
		{
			this->_x = v._x;
			this->_y = v._y;
			this->_z = v._z;
			return *this;
		}

		Vector3_& operator+=(const Vector3_& v)
		{
			this->_x += v._x;
			this->_y += v._y;
			this->_z += v._z;
			return *this;
		}
		Vector3_ operator + (const Vector3_& v)
		{
			//return Vector3_(_x + v.x, _y + v._y, _z + v._z);
			Vector3_ temp(*this);
			return temp += v;
		}

		Vector3_& operator+=(const T &v)
		{
			this->_x += v;
			this->_y += v;
			this->_z += v;
			return *this;
		}
		Vector3_ operator + (const T &v)
		{
			Vector3_ temp(*this);
			return temp += v;
		}
		Vector3_& operator-=(const Vector3_& v)
		{
			this->_x -= v._x;
			this->_y -= v._y;
			this->_z -= v._z;
			return *this;
		}
		Vector3_ operator - (const Vector3_& v)
		{
			Vector3_ temp(*this);
			return temp -= v;
		}

		Vector3_& operator-=(const T &v)
		{
			this->_x -= v;
			this->_y -= v;
			this->_z -= v;
			return *this;
		}
		Vector3_ operator - (const T &v)
		{
			Vector3_ temp(*this);
			return temp -= v;
		}

		Vector3_ operator - () const
		{
			return Vector3_(-this->_x, -this->_y, -this->_z);
		}

		/** Element-wise multiplication.
		*/
		Vector3_& operator*=(const Vector3_&v)
		{
			this->_x *= v._x;
			this->_y *= v._y;
			this->_z *= v._z;
			return *this;
		}
		Vector3_ operator*(const Vector3_&v)
		{
			Vector3_ temp(*this);
			return temp *= v;
		}
		Vector3_& operator*=(const T&v)
		{
			this->_x *= v;
			this->_y *= v;
			this->_z *= v;
			return *this;
		}
		Vector3_ operator*(const T&v)
		{
			Vector3_ temp(*this);
			return temp *= v;
		}
		/** Element-wise division *  @param v multiplied vector*/
		Vector3_& operator /=(const Vector3_&v)
		{
			Assertion(v._x != 0 && v._y != 0 && v._z != 0, "Zero division");
			this->_x /= v;
			this->_y /= v;
			this->_z /= v;
			return *this;
		}
		Vector3_ operator /(const Vector3_&v)
		{
			Vector3_ temp(*this);
			return temp /= v;
		}
		Vector3_& operator/=(const T&v)
		{
			Assertion(v != 0, "Zero division");
			this->_x /= v;
			this->_y /= v;
			this->_z /= v;
			return *this;
		}
		Vector3_ operator/(const T&v)
		{
			Vector3_ temp(*this);
			return temp /= v;
		}

		bool operator == (const Vector3_& v) const
		{
			return (this->_x == v._x && this->_y == v._y && this->_z == v._z);
		}
		bool operator != (const Vector3_& v) const
		{
			return !this->operator==(v);
		}

		T dot(const Vector3_ &v)const
		{
			return this->_x * v._x + this->_y * v._y + this->_z * v._z;
		}
		static T dot(const Vector3_&v1, const Vector3_&v2)
		{
			return v1.dot(v2);
		}

		Vector3_ cross(const Vector3_& v)const
		{
			T x = this->_y * v._z - this->_z * v._y;
			T y = this->_z * v._x - this->_x * v._z;
			T z = this->_x * v._y - this->_y * v._x;
			return Vector3_(x, y, z);
		}
		static Vector3_ cross(const Vector3_&v1, const Vector3_&v2)
		{
			return v1.cross(v2);
		}

		T norm()const
		{
			return ::sqrt(this->squaredNorm());
		}
		T squaredNorm() const
		{
			return this->dot(*this);
		}
		Vector3_ normalized() const
		{
			Vector3_<T> ret = *this;
			ret /= ret.norm();
			return ret;
		}
		Vector3_ normalize(const Vector3_ &v) const
		{
			return v.normalized();
		}
		Vector3_ multiply(const Vector3_&v)const
		{
			Vector3_ temp(*this);
			return temp *= v;
		}
		static Vector3_ minimum(const Vector3_& v1, const Vector3_& v2)
		{
			T x = std::min(v1._x, v2._x);
			T y = std::min(v1._y, v2._y);
			T z = std::min(v1._z, v2._z);
			return{ x, y, z };
		}
		static Vector3_ maximum(const Vector3_& v1, const Vector3_& v2)
		{
			T x = std::max(v1._x, v2._x);
			T y = std::max(v1._y, v2._y);
			T z = std::max(v1._z, v2._z);
			return{ x, y, z };
		}
		static Vector3_ reflect(const Vector3_& v, const Vector3_& n)
		{
			return (v - n * T(2) * n.dot(v));
		}


		std::string toString() const {
			std::stringstream ss;
			ss << std::fixed;
			ss << std::setprecision(8);
			ss << "(" << _x << ", " << _y << ", " << _z << ")";
			return std::move(ss.str());
		}

		friend std::ostream &operator<< (std::ostream &stream, const Vector3_ &v)
		{
			/*		stream << '(';
			stream << v._x << (0 ? ')' : ',');
			stream << v._y << (0 ? ')' : ',');
			stream << v._z << (1 ? ')' : ',');*/
			stream << v.toString();
			return stream;
		}
	protected:
		T _x, _y, _z;
	};

	typedef Vector3_<float> Vector3f;
	typedef Vector3_<double> Vector3d;
	typedef Vector3_<int> Vector3i;

	template <typename T>
	Vector3_<T>	operator+(const Vector3_<T>& v1, const Vector3_<T>& v2)
	{
		Vector3_<T> ret = v1;
		ret += v2;
		return ret;
	}
	template <typename T>
	Vector3_<T>	operator-(const Vector3_<T>& v1, const Vector3_<T>& v2)
	{
		Vector3_<T> ret = v1;
		ret -= v2;
		return ret;
	}
	template <typename T>
	Vector3_<T>	operator+(const Vector3_<T>& v1, const T& x)
	{
		Vector3_<T> ret = v1;
		ret += x;
		return ret;
	}
	template <typename T>
	Vector3_<T>	operator+(const T& x, const Vector3_<T>& v1)
	{
		return{ x + v1.x(),x + v1.y(),x + v1.z() };


	}
	template <typename T>
	Vector3_<T>	operator-(const Vector3_<T>& v1, const T& x)
	{
		return v1 + (-x);
	}

	template <typename T>
	Vector3_<T>	operator-(const T& x, const Vector3_<T>& v1)
	{
		return{ x - v1.x(),x - v1.y(),x - v1.z() };
	}

	template <typename T>
	Vector3_<T>	operator*(const T& x, const Vector3_<T>& v1)
	{
		return{ x * v1.x(),x * v1.y(),x * v1.z() };

	}

	template <typename T>
	Vector3_<T>	operator*(const Vector3_<T>& v1, const T& x)
	{
		return{ x * v1.x(),x * v1.y(),x * v1.z() };

	}

	template <typename T>
	Vector3_<T>	operator/(const T& x, const Vector3_<T>& v1)
	{
		Assertion(v1.x() != 0 && v1.y() != 0 && v1.z() != 0, "Zero division");

		return{ x / v1.x(),x / v1.y(),x / v1.z() };

	}

}



#endif