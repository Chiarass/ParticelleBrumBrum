#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../include/Headers.hpp"
#include "../include/Particle.hpp"
#include "../include/ParticleType.hpp"
#include "../include/ResonanceType.hpp"
#include "TApplication.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TRint.h"
#include "TStyle.h"

// Adding main for shell compilation
int main3(int argc, char **argv) {
// Object ownership setup
#ifdef PROGRAM_USE_LOCAL_OWNERSHIP
  // Disable automatic ownership transfer to ROOT directories
  TDirectory::AddDirectory(kFALSE);
#endif

  // Create a ROOT application
  APP_TYPE app(APP_NAME, &argc, argv);

  // Run the ROOT application
  app.Run();
  std::cout << "hello";
  // Close the ROOT application
  gApplication->Terminate(0);

  return 0;
}
