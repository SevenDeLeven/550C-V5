#ifndef SDL_CLASSES_H
#define SDL_CLASSES_H


/*
I know, I know...

This isn't just classes, but rather a subset of vars.h for organization
*/

#include "sdlapi/event.hpp"

typedef struct _lv_obj_t lv_obj_t;

#ifdef __cplusplus
extern "C" {
#endif

namespace sdl {

struct AutonConfig {
	float turnOffset;
	bool park;
};

} //Namespace SDL

extern void loadConfiguration(const char* file);
extern void writeConfiguration(const char* file);

#ifdef __cplusplus
}
#endif

#endif
