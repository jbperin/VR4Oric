#include "config.h"

.bss
* = $400

;; Equirectangular translated image (256*128)
;; adr of pixel (l,c) in texture_PANO is texture_PANO + c*128 + l
_texture_PANO       .dsb 32768 ;; 256*128

;; Precomputed mulitply by 128 tables used to compute address in texture
;; For a given column c these tables gives a pointer to the beginning of 
;; this column in the texture:
;; adr + 128*c = adrTextureHigh [c] << 8 | adrTextureLow[c]
_adrTextureHigh     .dsb 256
_adrTextureLow      .dsb 256

;; 
_borderTables       .dsb 1014 ;; 13*78

;; Image Diff Table
_diffimg            .dsb 8672
;; 0                : nb_diff = N
;; 1                : nb_point_in_diff0 = N0
;; 2, 3, 4          : X, Y, color
;; 5, 6, 7          : X, Y, color
;;  ... 
;; (N0-1)*3+2, (N0-1)*3+3, (N0-1)*3+4   : X, Y, color
;; (N0-1)*3+4 + 5   :nb_point_in_diff1
;;                  : X, Y, color
;;                  : X, Y, color
;;  ... 

.text


