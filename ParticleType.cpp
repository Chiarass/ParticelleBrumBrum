#include "ParticleType.hpp"

ParticleType::ParticleType(const char* parName, const double parMass,
                           const int parCharge)
    : fName(parName), fMass(parMass), fCharge(parCharge){};
const char* ParticleType::get_ParticleName() { return fName; };
const double ParticleType::get_ParticleMass() { return fMass; };
const int ParticleType::get_ParticleCharge() { return fCharge; };
void ParticleType::print() {
  std::cout << "Name: " << ParticleType::get_ParticleName() << std::endl
            << "Mass: " << ParticleType::get_ParticleMass() << std::endl
            << "Charge: " << ParticleType::get_ParticleCharge() << std::endl;
};
