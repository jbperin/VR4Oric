#ifndef CONFIG_H
#define CONFIG_H

#include "constants.h"
#define DEFAULT_BASE_ADRESS (HIRES_SCREEN_ADDRESS + 40*((VIEWPORT_START_LINE<<1) + VIEWPORT_START_LINE) + (VIEWPORT_START_COLUMN>>1))


#ifdef __GNUC__

#define __USE_C_DDA__
#define __USE_PURE_C_RENDER__

#undef __USE_C_ASM_RENDER__
#undef __USE_PURE_ASM_RENDER__

#else
// #define __USE_CLEAR_VIEWPORT__
// #define __USE_SLOW_TEXEL__
#undef __USE_C_DDA__
#undef __USE_PURE_C_RENDER__

#undef __USE_C_ASM_RENDER__
#define __USE_PURE_ASM_RENDER__

#endif // __GNUC__

#endif // CONFIG_H