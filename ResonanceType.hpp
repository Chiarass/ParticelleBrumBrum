#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP
#include "ParticleType.hpp"

class ResonanceType : public ParticleType {
 private:
  const double fWidth;

 public:
  ResonanceType();
  ResonanceType(const char* parName, const double parMass, const int parCharge,
                const double resWidth);
  virtual const double get_Width();
  virtual void print() override;
};

#endif