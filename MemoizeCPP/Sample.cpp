#include <iostream>
#include <vector>
#include <algorithm>
#include "Memorize.h"

namespace DP
{
	namespace Lev
	{
		template<typename Ty>
		class Levenshtein : public Memorization::Memorize
		{
		public:
			Levenshtein(Ty src, Ty target) :m_source(src), m_target(target) {}
			size_t operator()()
			{
				return Memoize(&Levenshtein::recurse, this)(m_source.size() - 1, m_target.size() - 1);
			}
		private:
			size_t recurse(int i, int j)
			{
				if (i < 0) return j;
				if (j < 0) return i;
				return std::min(
					Memoize(&Levenshtein::recurse, this)(i - 1, j) + 1,
					std::min(
						Memoize(&Levenshtein::recurse, this)(i, j - 1) + 1,
						Memoize(&Levenshtein::recurse, this)(i - 1, j - 1) + (m_source[i] != m_target[j])));
			}
			Ty m_source, m_target;
		};
	}
}
int main() {
	{
		std::cout << DP::Lev::Levenshtein<std::string>("Abhijit", "Arijit")() << std::endl;
	}
}