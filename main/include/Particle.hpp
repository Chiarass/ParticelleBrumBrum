#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <string>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

class Particle {
 private:
  const char *f_Name;
  static const int fMaxNumParticleType = 10;
  static ParticleType *fParticleType[fMaxNumParticleType];
  static int fNParticleType;

  int fIndex;

  double fPx;
  double fPy;
  double fPz;

  static int FindParticle(const char *Name);

  void Boost(double bx, double by, double bz);

 public:
  // Constructors
  Particle();
  Particle(const char *, double, double, double);

  // Getter methods
  int get_fIndex();
  double get_Xmomentum() const;
  double get_Ymomentum() const;
  double get_Zmomentum() const;
  double get_Mass() const;
  double get_Charge() const;
  bool get_specificMass(double, const char *) const;

  // Setter methods
  void set_fIndex(int index);
  void set_fIndex(const char *pname);
  void set_ParticleTypeFromMap(const std::string &particleType);
  void set_P(double px, double py, double pz);

  // Other methods
  double ParticleEnergy() const;
  double InvMass(Particle &p);

  // Static methods
  static void ArrayStatus();
  void ParticleStatus();

  // Static methods for particle type management
  static void AddParticleType(const char *, const double, const int, const double);

  // Decay method
  int Decay2body(Particle &dau1, Particle &dau2) const;
};

#endif
