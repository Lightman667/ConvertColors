#pragma once

#include "Types.h"
#include <string>

typedef struct rgb_struct {
  f32 m_f32Red;    // красный цвет (R)
  f32 m_f32Green;  // зеленый цвет (G)
  f32 m_f32Blue;   // синий цвет   (B)
} rgb_struct;

typedef struct hsv_struct {
  f32 m_f32Hue;         // тон (H)
  f32 m_f32Saturation;  // насыщенность (S)
  f32 m_f32Value;       // яркость   (V)
} hsv_struct;

// Конвертация цветов
rgb_struct GetRGBfromHSV(s16 in_s16Hue, s8 in_s8Saturation, s8 in_s8Value);
hsv_struct GetHSVfromComplex(s32 in_s32ComplexColor);
std::string ConvertRGBtoHex(u16 in_u16Red, u16 in_u16Green, u16 in_u16Blue);
hsv_struct ConvertRGBtoHSV(u16 in_u16Red, u16 in_u16Green, u16 in_u16Blue);
u32 ConvertHSVtoComplex(u16 in_u16Hue, u8 in_u8Saturation, u8 in_u8Bright);