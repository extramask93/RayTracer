//
// Created by damian on 07.07.2020.
//
#include <Matrix.h>
#include <CanvasPrinter.h>
#include <Canvas.h>
#include <ray/Ray.h>
#include <shapes/Sphere.h>
#include <Intersection.h>
const double wall_z = 10;
const double ray_z = -4;
const unsigned canvas_size = 100;
const double wall_size = 12;
const double pixel_size = wall_size/canvas_size;
const double half = wall_size/2;
int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;
  util::Canvas canvas(canvas_size, canvas_size);
  auto ray_origin = util::Tuple::point(0,0,ray_z);
  auto sphere = rt::Sphere();
  sphere.setTransform(util::Matrixd::rotation_z(M_PI/4)*util::Matrixd::scaling(1,0.5,1));
  for(unsigned y =0 ; y < canvas_size; y++) {
    double world_y = half - pixel_size *y;
    for(unsigned x=0; x < canvas_size;x++) {
      double world_x = -half + pixel_size*x;
      auto position = util::Tuple::point(world_x,world_y,wall_z);
      auto ray = rt::Ray(ray_origin, (position - ray_origin).normalize());
      auto xs = sphere.intersect(ray);
      if(xs.hit().has_value()) {
        canvas(x,y) = util::Color(1,0,0);
      }
    }
  }
  auto printer = util::CanvasPrinter();
  printer.printToPPM(std::filesystem::current_path() / "sphere.ppm", canvas);
}
