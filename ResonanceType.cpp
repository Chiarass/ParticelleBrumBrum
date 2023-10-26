#include "ResonanceType.hpp"

#include "ParticleType.hpp"

ResonanceType::ResonanceType(const char* parName, const double parMass,
                             const int parCharge, const double resWidth)
    : ParticleType(parName, parMass, parCharge), fWidth(resWidth){};
const double ResonanceType::get_ResonanceWidth() { return fWidth; };
void ResonanceType::print() {
  std::cout << "Name: " << ParticleType::get_ParticleName() << ", "
            << "Mass: " << ParticleType::get_ParticleMass() << ", "
            << "Charge: " << ParticleType::get_ParticleCharge() << ", "
            << "Resonance Width: " << ResonanceType::get_ResonanceWidth();
}