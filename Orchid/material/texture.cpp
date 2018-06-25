#include "texture.h"

namespace Orchid
{
	Texture::Texture(const char * filename)
	{
	}
	Vector3d Texture::get_pixel(unsigned x, unsigned y) const
	{
		return Vector3d();
	}
	Vector3d Texture::get_pixel(double u, double v) const
	{
		return Vector3d();
	}
	bool Texture::is_loaded() const
	{
		return false;
	}
}
