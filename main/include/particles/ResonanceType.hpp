#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "ParticleType.hpp"

class ResonanceType : public ParticleType {
 private:
  const double fWidth;  // Width of the resonance

 public:
  // Constructors
  ResonanceType();
  ResonanceType(const char* parName, const double parMass, const int parCharge,
                const double resWidth);

  // Method to retrieve the width of the resonance
  virtual const double get_ResonanceWidth();

  // Method to print information about the resonance
  virtual void print() override;
};

#endif
