#ifndef PARTICLETYPE
#define PARTICLETYPE
#include <iostream>

class ParticleType {
 private:
  const char* fName{};
  const double fMass{};
  const int fCharge{};

 public:
  ParticleType(const char* parName, const double parMass, const int parCharge);
  const char* get_ParticleName();
  const double get_ParticleMass();
  const int get_ParticleCharge();
  virtual void print();
};

#endif
