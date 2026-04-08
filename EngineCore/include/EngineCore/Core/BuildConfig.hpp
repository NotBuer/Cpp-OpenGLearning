#pragma once

#if !defined(ENGINE_DEBUG) && (defined(DEBUG) || defined(_DEBUG))
	#define ENGINE_DEBUG
	#pragma message("Running in DEBUG mode")
#endif