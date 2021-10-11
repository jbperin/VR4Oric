#include "config.h"

.bss
* = $400
_texture_PANO .dsb 32768 ;; 256*128

_adrTextureHigh .dsb 256
_adrTextureLow .dsb 256

_borderTables .dsb 1014 ;; 13*78
_diffimg       .dsb 8672

.text


