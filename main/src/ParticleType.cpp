#include "../include/ParticleType.hpp"

// Default constructor
ParticleType::ParticleType(){};

// Parameterized constructor
ParticleType::ParticleType(const char *parName, const double parMass,
                           const int parCharge)
    : fName(parName), fMass(parMass), fCharge(parCharge){};

// Getter function for particle name
const char *ParticleType::get_ParticleName() const { return fName; };

// Getter function for particle mass
double ParticleType::get_ParticleMass() const { return fMass; };

// Getter function for particle charge
int ParticleType::get_ParticleCharge() const { return fCharge; };

// Getter function for particle width (always returns 0 for this implementation)
double ParticleType::get_ParticleWidth() const { return 0; };

// Print function to display particle information
void ParticleType::print() {
  std::cout << "Name: " << ParticleType::get_ParticleName() << ", "
            << "Mass: " << ParticleType::get_ParticleMass() << ", "
            << "Charge: " << ParticleType::get_ParticleCharge();
};
