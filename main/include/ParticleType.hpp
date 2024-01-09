#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>

class ParticleType {
 private:
  const char* fName{};   // Name of the particle
  const double fMass{};  // Mass of the particle
  const int fCharge{};   // Charge of the particle

 public:
  // Constructors
  ParticleType();
  ParticleType(const char* parName, const double parMass, const int parCharge);

  // Methods to retrieve information about the particle
  virtual const char* get_ParticleName() const;
  virtual double get_ParticleMass() const;
  virtual int get_ParticleCharge() const;
  virtual double get_ParticleWidth() const;

  // Method to print information about the particle
  virtual void print();
};

#endif
