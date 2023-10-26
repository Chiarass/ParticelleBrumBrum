#ifndef PARTICLE
#define PARTICLE
#include <array>
#include <iostream>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

class Particle {
 private:
  ParticleType particletype;
  const char* f_Name = particletype.get_ParticleName();
  static const int fMaxNumParticleType = 10;
  static ParticleType* fParticleType[fMaxNumParticleType];
  static int fNParticleType;
  int fIndex;
  double fPx;
  double fPy;
  double fPz;
  int FindParticle(const char* Name) {
    for (int i; i < fMaxNumParticleType; ++i) {
      if (fParticleType[i]->get_ParticleName() == Name) {
        return i;
      } else {
        std::cout << "No correspondence, sorry";
      }
    }
  };

 public:
  Particle(const char* parName, int Index, double Px, double Py, double Pz)
      : f_Name(parName),
        fIndex(Index = FindParticle(parName)),
        fPx(Px = 0),
        fPy(Py = 0),
        fPz(Pz = 0){};
};
#endif