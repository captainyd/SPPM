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


#ifndef _MSC_VER
#pragma once
#endif // !_MSC_VER

#ifndef _TRIANGLEH_
#define _TRIANGLEH_
#include "objetcs.h"
#include "../accel/aabbox.h"
namespace Orchid
{
	class Triangle :public Object 
	{
	private:
		Vector3d _p0, _p1, _p2;
		Material _material;
	public:
		Triangle();
		Triangle(const Vector3d& p0, const Vector3d&p1, const Vector3d&p2, Material material);
		Triangle(const Triangle& tri);
		~Triangle();
		Triangle& operator=(const Triangle& tri);
		Vector3d gravity() const;
		/** Get a vertex with ID in [0, 1, 2]
		*/
		AABBox get_bounding_box();
		bool triangleInBbox();
		Vector3d get(int id) const;
		Vector3d normal() const;
		virtual ObjectIntersection getIntersection(const Ray& ray);
		double area() const ;
	};

}
#endif // !_TRAIANGLEH_
