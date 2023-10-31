#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP
#include <iostream>

class ParticleType {
 private:
  const char* fName{};
  const double fMass{};
  const int fCharge{};

 public:
  ParticleType();
  ParticleType(const char* parName, const double parMass, const int parCharge);

  virtual const char* get_ParticleName();
  virtual const double get_ParticleMass();
  virtual const int get_ParticleCharge();

  virtual void print();
};

#endif
