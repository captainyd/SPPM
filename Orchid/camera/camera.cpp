#include "camera.h"

namespace Orchid
{
	Camera::Camera
	(
		Vector3d position, Vector3d target, Vector3d up,
		int width, int height,
		double nearPalneDistance, double fov
	) :	_position{ position },
		_up{ up },
		_imageW{ width },
		_imageH{ height },
		_nearPlaneDistance{ nearPalneDistance }
	{
		_cameraVerticalFOV = fov *PI / 180.0f;
		_aspectRatio = (double)_imageW / _imageH;
		_cameraFwd = (target - _position).normalized();
		_cameraRight = _up.cross(_cameraFwd).normalized();
		_cameraUp = _cameraFwd.cross(_cameraRight).normalized()*(-1);///???
		_cameraHorizFOV = _cameraVerticalFOV *_aspectRatio;
		_windowTop = tan(_cameraVerticalFOV / 2.0f)*_nearPlaneDistance;
		_windowRight = tan(_cameraHorizFOV / 2.0f)*_nearPlaneDistance;
	}

	Ray Camera::get_ray(int x, int y)
	{
		Vector3d origin = _position;
		float NDC_x = (x + 0.5) / _imageW;
		float NDC_y = (y + 0.5) / _imageH;

		// [-1, 1]
		float screen_x = 2 * NDC_x - 1;
		float screen_y = 2 * NDC_y - 1;

		Vector3d scene_center = _position + _cameraFwd * _nearPlaneDistance;
		Vector3d x_shift = screen_x * _windowRight*_cameraRight;
		Vector3d y_shift = screen_y * _windowTop*_cameraUp;
		Vector3d direction = (scene_center + x_shift + y_shift - origin).normalized();

		return Ray(origin, direction);
	}

}
