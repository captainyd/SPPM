#include "material.h"

namespace Orchid
{

	Material::Material
	(MaterialType t, Vector3d colour, Vector3d emission, Texture texture)
		:_type{ t }
		, _colour{ colour }
		, _emission{ emission }
		, _texture{ texture }  //nead addd
	{

	}

	Material & Material::operator=(Material  m)
	{
		this->_type = m._type;
		this->_emission = m._emission;
		this->_texture = m._texture;
		this->_colour = m._colour;
		return *this;
	}

	Vector3d Material::get_colour_at(double u, double v) const
	{
		if (_texture.is_loaded())
			return _texture.get_pixel(u, v);
		return _colour;
	}

	Ray Material::get_reflected_ray
	(
		const Ray & r, 
		Vector3d & p, 
		const Vector3d & n,
		unsigned short * Xi
	) const
	{
		
	}
}