#include <functional>
#include <iostream>

#include <spdlog/spdlog.h>
#include <Tuple.h>
struct Projectile {
  util::Tuple position = util::Tuple::point(0,1,0);
  util::Tuple velocity = util::Tuple::vector(1,1,0).normalize();
};
struct Environment {
  util::Tuple gravity = util::Tuple::vector(0,-0.1,0);
  util::Tuple wind = util::Tuple::vector(-0.01,0,0);
};

void tick(const Environment &env, Projectile &p) {
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
  while (projectile.position.y > 0 ) {
    std::cout<<projectile.position<<'\n';
 //     spdlog::info("Position: {}!", projectile.position);
      tick(environment,projectile);
  }

 // fmt::print("Hello, from {}\n", "{fmt}");
}
