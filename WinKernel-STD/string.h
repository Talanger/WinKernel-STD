#pragma once
namespace kstd {
	struct string
	{
		string(const char* str) {
			for (int i{ 0 }; str[i] != '\0';++i)
			{
				continue; // TODO
			}
		}
	};
}