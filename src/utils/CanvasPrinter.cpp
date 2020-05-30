//
// Created by damian on 30.05.2020.
//

#include "CanvasPrinter.h"
#include <fstream>
#include <sstream>
void util::CanvasPrinter::printToPPM(const std::filesystem::path &path, const util::Canvas &canvas) const
{
  std::ofstream file(path, std::ios::trunc);
  std::stringstream buffer;
  buffer << "P3\n";
  buffer << canvas.width() << '\n'
         << canvas.height() << '\n';
  buffer << "255\n";
  int counter = 0;
  for (const auto &pixel : canvas) {
    buffer << convertColor(pixel.r) << " " << convertColor(pixel.g) << " " << convertColor(pixel.b);
    counter+=12;
    if (counter >= 58) {
      buffer << '\n';
      counter = 0;
    } else {
      buffer << ' ';
    }
  }
  auto conetent = buffer.str();
  conetent.pop_back();
  conetent.push_back('\n');
  file << conetent;
}
