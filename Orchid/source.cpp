#include "source.h"

Orchid::Source::Source()
{
}

Orchid::Source::Source(Vector3d p, Vector3d n, Vector3d e) :_position(p), _normal(n), _emit(e)
{
}
