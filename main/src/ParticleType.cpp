#include "ParticleType.hpp"

ParticleType::ParticleType(){};
ParticleType::ParticleType(const char *parName, const double parMass,
                           const int parCharge)
    : fName(parName), fMass(parMass), fCharge(parCharge){};

const char *ParticleType::get_ParticleName() { return fName; };

const double ParticleType::get_ParticleMass() { return fMass; };

const int ParticleType::get_ParticleCharge() { return fCharge; };

void ParticleType::print() {
  std::cout << "Name: " << ParticleType::get_ParticleName() << ", "
            << "Mass: " << ParticleType::get_ParticleMass() << ", "
            << "Charge: " << ParticleType::get_ParticleCharge();
};
