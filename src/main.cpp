#include <functional>
#include <iostream>

#include <spdlog/spdlog.h>
#include <Tuple.h>
#include <Canvas.h>
#include <CanvasPrinter.h>
struct Projectile
{
  util::Tuple position = util::Tuple::point(0, 1, 0);
  util::Tuple velocity = util::Tuple::vector(1, 1.8, 0).normalize() * 11.25;
};
struct Environment
{
  util::Tuple gravity = util::Tuple::vector(0, -0.1, 0);
  util::Tuple wind = util::Tuple::vector(-0.01, 0, 0);
};

void tick(const Environment &env, Projectile &p)
{
  p.position = p.position + p.velocity;
  p.velocity = p.velocity + env.gravity + env.wind;
}

int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;
  //Use the default logger (stdout, multi-threaded, colored)
  Projectile projectile;
  Environment environment;
  util::Canvas canvas(900, 550);
  while (projectile.position.y > 0) {
    std::cout << projectile.position << '\n';
    unsigned int x = static_cast<unsigned int>(projectile.position.x);
    unsigned int y = canvas.height() - static_cast<unsigned int>(projectile.position.y);
    tick(environment, projectile);
    if (x <= canvas.width() && y <= canvas.height())
      canvas(x, y) = util::Color(1, 0, 0);
  }
  auto printer = util::CanvasPrinter();
  printer.printToPPM(std::filesystem::current_path() / "ak.ppm", canvas);
}
