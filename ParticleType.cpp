#include "ParticleType.hpp"

class ParticleType {
 private:
  const char* fName{};
  const double fMass{};
  const int fCharge{};

 public:
  ParticleType(const char* parName, const double parMass, const int parCharge)
      : fName(parName), fMass(parMass), fCharge(parCharge){};
  const char* get_ParticleName() { return fName; };
  const double get_ParticleMass() { return fMass; };
  const int get_ParticleCharge() { return fCharge; };
  void print() {
    std::cout << "Name: " << ParticleType::get_ParticleName() << std::endl
              << "Mass: " << ParticleType::get_ParticleMass() << std::endl
              << "Charge: " << ParticleType::get_ParticleCharge() << std::endl;
  };
};
