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
#ifndef _MATERIALH_
#define _MATERIALH_


#include "../math/vector3d.h"
#include "../ray/ray.h"
#include "texture.h"
namespace Orchid
{
	enum MaterialType { DIFF, SPEC, EMIT ,REFR};
	class Material
	{
	private:
		MaterialType _type;
		Vector3d _colour;
		Vector3d _emission;
		Texture _texture;
	public:
		Material(MaterialType t=DIFF,
			Vector3d colour = { 1,1,1 }, Vector3d emission = {0,0,0},
			Texture texture=Texture());
		Material& operator=(Material m);
		MaterialType getType() const { return _type; }
		Vector3d get_colour() const { return _colour; }
		Vector3d get_emission() const { return _emission; }
		Vector3d get_colour_at(double u, double v) const;
		Ray get_reflected_ray(const Ray &r, Vector3d &p, const Vector3d &n, unsigned short *Xi) const;
	};
		
}

#endif // !_MATERIALH_
