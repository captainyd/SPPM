#pragma once
#include <random>

namespace Orchid
{
	static std::mt19937_64 rng = std::mt19937_64(std::random_device()());
}