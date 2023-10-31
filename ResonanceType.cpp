#include "ResonanceType.hpp"

#include "ParticleType.hpp"

ResonanceType::ResonanceType() : fWidth(0.0){};
ResonanceType::ResonanceType(const char *parName, const double parMass,
                             const int parCharge, const double resWidth)
    : ParticleType(parName, parMass, parCharge), fWidth(resWidth){};

const double ResonanceType::get_ResonanceWidth() { return fWidth; };

void ResonanceType::print() {
  ParticleType::print();
  std::cout << "Resonance Width: " << ResonanceType::get_ResonanceWidth()
            << std::endl;
}