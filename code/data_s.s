.bss
* = $400
_texture_PANO .dsb 32768 ;; 256*128

_adrTextureHigh .dsb 256
_adrTextureLow .dsb 256

_borderTables .dsb 1014 ;; 13*78

.text

.zero
_wrtAdr .dsb 2

;; #include "image_s.s"
;; #include "tabEquiRect_s.s"
