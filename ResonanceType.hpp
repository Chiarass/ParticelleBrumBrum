#ifndef RESONANCETYPE
#define RESONANCETYPE
#include "ParticleType.hpp"

class ResonanceType : public ParticleType {
 private:
  const double fWidth;

 public:
  ResonanceType();
  ResonanceType(const char* parName, const double parMass, const int parCharge,
                const double resWidth);
  const double get_ResonanceWidth();
  void print();
};

#endif