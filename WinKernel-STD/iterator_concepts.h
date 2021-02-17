#pragma once
#include "concepts.h"
namespace kstd
{
	template<class I>

	concept __LegacyIterator =
		requires(I i) {
			{   *i } -> is_referenceable;
			{  ++i } -> kstd::same_as<I&>;
			{ *i++ } -> is_referenceable;
	}&& kstd::copyable<I>;




}