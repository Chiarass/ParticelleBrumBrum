#include "../include/ResonanceType.hpp"

#include "../include/ParticleType.hpp"

// Default constructor for ResonanceType
ResonanceType::ResonanceType() : fWidth(0.0){};

// Parameterized constructor for ResonanceType, invoking the base class
// constructor
ResonanceType::ResonanceType(const char *parName, const double parMass, const int parCharge, const double resWidth)
    : ParticleType(parName, parMass, parCharge), fWidth(resWidth){};

// Getter function for the resonance width
double ResonanceType::get_ParticleWidth() const { return fWidth; };

// Print function to display information about the ResonanceType
void ResonanceType::print() {
  // Invoke the base class print function to display particle information
  ParticleType::print();

  // Display additional information specific to ResonanceType (resonance width)
  std::cout << ", "
            << "Resonance Width: " << ResonanceType::get_ParticleWidth();
}
