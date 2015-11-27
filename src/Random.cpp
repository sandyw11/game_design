#include "Random.hpp"
#include <cstdlib>

namespace lava
{
	long Equilikely(long a, long b)
	{
		return (a + (long)((b - a + 1) * rand() / RAND_MAX));
	}
}
