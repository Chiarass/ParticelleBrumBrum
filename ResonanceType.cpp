#include "ResonanceType.hpp"

ResonanceType::ResonanceType(const char* parName, const double parMass,
                             const int parCharge, const double resWidth)
    : ParticleType(parName, parMass, parCharge), fWidth(resWidth){};
const double ResonanceType::get_ResonanceWidth() { return fWidth; };
void ResonanceType::print() {
  std::cout << "Name: " << ParticleType::get_ParticleName() << std::endl
            << "Mass: " << ParticleType::get_ParticleMass() << std::endl
            << "Charge: " << ParticleType::get_ParticleCharge() << std::endl
            << "Resonance Width: " << ResonanceType::get_ResonanceWidth()
            << std::endl;
}