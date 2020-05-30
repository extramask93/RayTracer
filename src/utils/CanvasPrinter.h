//
// Created by damian on 30.05.2020.
//

#ifndef MYPROJECT_CANVASPRINTER_H
#define MYPROJECT_CANVASPRINTER_H
#include <filesystem>
#include <Canvas.h>
namespace util {

class CanvasPrinter
{
public:
  void printToPPM(const std::filesystem::path &path, const Canvas &canvas) const;
private:
  std::string convertColor(double c) const {
    c = c * 255;
    if(c>255) {
      c = 255;
    }
    if(c<0) {
      c = 0.0;
    }
    return std::to_string(static_cast<unsigned char>(ceil(c)));
  }
};

}


#endif//MYPROJECT_CANVASPRINTER_H
