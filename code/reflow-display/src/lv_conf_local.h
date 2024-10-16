#ifndef LV_CONF_H
#	error	"Don't include this file directly, use 'lv_conf.h' instead!"
#endif

// Maximal resolutions
#define LV_HOR_RES_MAX  240
#define LV_VER_RES_MAX  320
#define LV_DPI          200

/* Color depth:
 * - 1:  1 byte per pixel
 * - 8:  RGB332
 * - 16: RGB565
 * - 32: ARGB8888
 */
#define LV_COLOR_DEPTH  16

// Enable logging at INFO level
#define LV_USE_LOG    1
#define LV_LOG_LEVEL  LV_LOG_LEVEL_INFO