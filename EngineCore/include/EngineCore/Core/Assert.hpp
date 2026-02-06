#pragma once
#include <iostream>
#include <cassert>
#include "EngineCore/Core/BuildConfig.hpp"

#if defined(ENGINE_DEBUG)

	#define ENGINE_ASSERT(cond) \
		do { \
			if (!(cond)) { \
				std::cerr << "ASSERT FAILED: " #cond \
						  << " (" << __FILE__ << ":" << __LINE__ << ")\n"; \
				assert(false); \
			} \
		} while (0)

	#define ENGINE_ASSERT_MSG(cond, msg) \
		do { \
			if (!(cond)) { \
				std::cerr << "ASSERT FAILED: " #cond \
						  << " (" << __FILE__ << ":" << __LINE__ << "): " << msg << "\n"; \
				assert(false); \
			} \
		} while (0)

#else

	#define ENGINE_ASSERT(cond) do {} while (0)
	#define ENGINE_ASSERT_MSG(cond, msg) do {} while (0)

#endif