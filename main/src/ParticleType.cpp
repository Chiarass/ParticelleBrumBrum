#include "ParticleType.hpp"

// Default constructor
ParticleType::ParticleType(){};

// Parameterized constructor
ParticleType::ParticleType(const char *parName, const double parMass,
                           const int parCharge)
    : fName(parName), fMass(parMass), fCharge(parCharge){};

// Getter function for particle name
const char *ParticleType::get_ParticleName() { return fName; };

// Getter function for particle mass
const double ParticleType::get_ParticleMass() { return fMass; };

// Getter function for particle charge
const int ParticleType::get_ParticleCharge() { return fCharge; };

// Getter function for particle width (always returns 0 for this implementation)
const double ParticleType::get_ParticleWidth() { return 0; };

// Print function to display particle information
void ParticleType::print() {
  std::cout << "Name: " << ParticleType::get_ParticleName() << ", "
            << "Mass: " << ParticleType::get_ParticleMass() << ", "
            << "Charge: " << ParticleType::get_ParticleCharge();
};
