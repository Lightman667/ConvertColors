#include "Convertation.h"
#include <iostream>

/**
 * @brief Получить структуру rgb из hsv
 * @param in_s16Hue - значение H
 * @param in_s8Saturation - значение S
 * @param in_s8Value - значение V
 * @return структура rgb
 */
rgb_struct GetRGBfromHSV(s16 in_s16Hue, s8 in_s8Saturation, s8 in_s8Value) {
  if (in_s16Hue >= 0 && in_s8Saturation >= 0 && in_s8Value >= 0) {
    const f32 l_f32Saturation = in_s8Saturation * 0.01;
    f32 l_f32Value = in_s8Value * 0.01;
    const f32 l_f32HueValue = in_s16Hue / 360.0;
    l_f32Value = round(l_f32Value * 255);
    const u32 i = floor(l_f32HueValue * 6);
    const f32 f = l_f32HueValue * 6 - i;
    const f32 l_f32Result1 = round(l_f32Value * (1 - l_f32Saturation));
    const f32 l_f32Result2 = round(l_f32Value * (1 - f * l_f32Saturation));
    const f32 l_f32Result3 =
        round(l_f32Value * (1 - (1 - f) * l_f32Saturation));

    switch (i % 6) {
      case 0:
        return {l_f32Value, l_f32Result3, l_f32Result1};
      case 1:
        return {l_f32Result2, l_f32Value, l_f32Result1};
      case 2:
        return {l_f32Result1, l_f32Value, l_f32Result3};
      case 3:
        return {l_f32Result1, l_f32Result2, l_f32Value};
      case 4:
        return {l_f32Result3, l_f32Result1, l_f32Value};
      case 5:
        return {l_f32Value, l_f32Result1, l_f32Result2};
      default:
        return {};
    }
  }
  return {};
}

/**
 * @brief Получить структуру HSV из комплексного числа
 * @param in_s32ComplexColor - комплексное число
 * @return структура hsv
 */
hsv_struct GetHSVfromComplex(s32 in_s32ComplexColor) {
  if (in_s32ComplexColor >= 0) {
    const f32 l_f32Hue = in_s32ComplexColor >> 16 & 0xFFFF;
    const f32 l_f32Saturation = in_s32ComplexColor >> 8 & 0xFF;
    const f32 l_f32Bright = in_s32ComplexColor & 0xFF;

    return {l_f32Hue, l_f32Saturation, l_f32Bright};
  }
  return {};
}

/**
 * @brief Конвертация RGB в HEX
 * @param in_u16Red - красный цвет (R)
 * @param in_u16Green - зеленый цвет (G)
 * @param in_u16Blue - синий цвет (B)
 * @return строка с HEX кодом
 */
//std::string ConvertRGBtoHex(u16 in_u16Red, u16 in_u16Green, u16 in_u16Blue) {
//  if (in_u16Red <= 255 && in_u16Green <= 255 && in_u16Blue <= 255) {
//    const u32 l_u32Color = (in_u16Red << 16) | (in_u16Green << 8) | in_u16Blue;
//    std::stringstream l_sHexCode;
//    l_sHexCode << std::hex << std::uppercase << std::setfill('0')
//               << std::setw(6) << l_u32Color;
//    return l_sHexCode.str();
//  }
//  return "FFFFFF";
//}

/**
 * @brief Конвертация RGB в HSV
 * @param in_u16Red - красный цвет (R)
 * @param in_u16Green - зеленый цвет (G)
 * @param in_u16Blue - синий цвет (B)
 * @return структура hsv
 */
hsv_struct ConvertRGBtoHSV(u16 in_u16Red, u16 in_u16Green, u16 in_u16Blue) {
  if (in_u16Red <= 255 && in_u16Green <= 255 && in_u16Blue <= 255) {
    const f32 l_f32Red = in_u16Red / 100.0;
    const f32 l_f32Green = in_u16Green / 100.0;
    const f32 l_f32Blue = in_u16Blue / 100.0;

    f32 l_f32Max = l_f32Red;
    if (l_f32Max < l_f32Green) l_f32Max = l_f32Green;
    if (l_f32Max < l_f32Blue) l_f32Max = l_f32Blue;

    f32 l_f32Min = l_f32Red;
    if (l_f32Min > l_f32Green) l_f32Min = l_f32Green;
    if (l_f32Min > l_f32Blue) l_f32Min = l_f32Blue;

    f32 l_f32Value = l_f32Max;
    f32 l_f32Saturation;
    f32 l_f32Hue = 0;

    if (l_f32Max == 0)
      l_f32Saturation = 0;
    else
      l_f32Saturation = 1.0 - (l_f32Min / l_f32Max);

    if (l_f32Max == l_f32Min)
      l_f32Hue = 0;
    else if (l_f32Max == l_f32Red && l_f32Green >= l_f32Blue)
      l_f32Hue = 60.0 * ((l_f32Green - l_f32Blue) / (l_f32Max - l_f32Min));
    else if (l_f32Max == l_f32Red && l_f32Green < l_f32Blue)
      l_f32Hue =
          60.0 * ((l_f32Green - l_f32Blue) / (l_f32Max - l_f32Min)) + 360.0;
    else if (l_f32Max == l_f32Green)
      l_f32Hue =
          60.0 * ((l_f32Blue - l_f32Red) / (l_f32Max - l_f32Min)) + 120.0;
    else if (l_f32Max == l_f32Blue)
      l_f32Hue =
          60.0 * ((l_f32Red - l_f32Green) / (l_f32Max - l_f32Min)) + 240.0;

    l_f32Value = (l_f32Value * 100.0) / 2.55;
    l_f32Saturation = l_f32Saturation * 100.0;

    return {l_f32Hue, l_f32Saturation, l_f32Value};
  }
  return {};
}

/**
 * @brief Конвертировать HSV в комплексное число
 * @param in_u16Hue - H (2 байта)
 * @param in_u8Saturation - S (1 байт)
 * @param in_u8Bright - V (1 байт)
 * @return комплексное число
 */
u32 ConvertHSVtoComplex(u16 in_u16Hue, u8 in_u8Saturation, u8 in_u8Bright) {
  if (in_u16Hue <= 360 && in_u8Saturation <= 100 && in_u8Bright <= 100)
    return (in_u16Hue << 16) | (in_u8Saturation << 8) | (in_u8Bright << 0);
  return {};
}
