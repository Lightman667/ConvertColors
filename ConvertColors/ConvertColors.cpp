#include <iostream>

#include "Include/Convertation.h"

/**
 * @brief Возьмем за основу цвет Cyan (голубой)
 * HEX: #00FFFF
 * RGB: 0, 255, 255
 * HSV: 180, 100, 100
 * 32-битное число: 11822180
 * @return число
 */
int main() {
  // конвертируем HSV цвет в RGB (структура)
  std::cout << "=== HSV to RGB ==="
            << "\n";
  const auto l_Color = GetRGBfromHSV(180, 100, 100);
  std::cout << "red = " << l_Color.m_f32Red << " green = " << l_Color.m_f32Green
            << " blue = " << l_Color.m_f32Blue << "\n\n";

  // конвертируем 32-битное число в HSV
  std::cout << "=== u32 to HSV ==="
            << "\n";
  const auto l_Complex = GetHSVfromComplex(11822180);
  std::cout << "hue = " << l_Complex.m_f32Hue
            << " saturation = " << l_Complex.m_f32Saturation
            << " value = " << l_Complex.m_f32Value << "\n\n";

  //конвертируем RGB цвет в HEX
  std::cout << "=== RGB to HEX ==="
            << "\n";
  std::cout << ConvertRGBtoHex(0, 255, 255) << "\n\n";

  // конвертируем RGB цвет в HSV
  std::cout << "=== RGB to HSV ==="
            << "\n";
  const auto l_HSVColor = ConvertRGBtoHSV(0, 255, 255);
  std::cout << "hue = " << l_HSVColor.m_f32Hue
            << " saturation = " << l_HSVColor.m_f32Saturation
            << " value = " << l_HSVColor.m_f32Value << "\n\n";

  // конвертируем HSV цвет в 32-битное число
  std::cout << "=== HSV to u32 ==="
            << "\n";
  std::cout << ConvertHSVtoComplex(180, 100, 100) << "\n\n";
}