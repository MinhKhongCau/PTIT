#ifndef IMAGES_H
#define IMAGES_H

#include <Arduino.h>
#include <pgmspace.h> // Bắt buộc phải có để nhận diện PROGMEM

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_LARGE_CONST
#define LV_ATTRIBUTE_LARGE_CONST
#endif

// Khai báo extern các mảng ảnh nằm ở 5 file 1.c đến 5.c
extern const uint8_t img1_map[] PROGMEM;
extern const uint8_t img2_map[] PROGMEM;
extern const uint8_t img3_map[] PROGMEM;
extern const uint8_t img4_map[] PROGMEM;
extern const uint8_t img5_map[] PROGMEM;

// Mảng con trỏ tổng hợp để gọi trong code chính (.ino)
extern const uint8_t* const bg_images[5] PROGMEM;

#endif