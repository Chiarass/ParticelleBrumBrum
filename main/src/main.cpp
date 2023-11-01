#include <iostream>

#include "Headers.hpp"
#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "TApplication.h"
#include "TDirectory.h"
#include "TRint.h"

int main(int argc, char** argv) {
// object ownership setup
#ifdef PROGRAM_USE_LOCAL_OWNERSHIP
  TDirectory::AddDirectory(kFALSE);
#endif
  // create root application
  APP_TYPE app(APP_NAME, &argc, argv);

  // create the logic objects

  // do stuff

  // run application
  app.Run();
  Particle::DeallocateMemory();
  return 0;
}
