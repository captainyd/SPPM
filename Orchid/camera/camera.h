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

#ifndef _CAMERAH_
#define _CAMERAH_
//#include "../3rdParty/rand48/erand48.h"
#include "../math/vector3d.h"
#include "../ray/ray.h"


namespace Orchid
{
	class Camera
	{
	private:
		int _imageW;
		int _imageH;

		double _nearPlaneDistance = 0.1;
		double _aspectRatio = 0;
		double _cameraVerticalFOV = 40.0f *PI / 180.0f;
		double _cameraHorizFOV;
		double _windowTop;
		double _windowRight;

		Vector3d _position;
		Vector3d _cameraFwd;
		Vector3d _cameraRight;
		Vector3d _cameraUp;
		Vector3d _up;
	public:
		Camera(Vector3d position, Vector3d target, Vector3d up,
			int width, int height,
			double nearPalneDistance, double fov);
		inline  Vector3d center()    const { return _position; }
		inline  Vector3d direction() const { return _cameraFwd; }
		inline  Vector3d up() const { return _up; }
		inline int imageW() const { return _imageW; }
		inline int imageH() const { return _imageH; }
		Ray get_ray(int x, int y);

	};
}



#endif // !_CAMERAH_
