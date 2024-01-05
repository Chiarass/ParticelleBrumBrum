#include "../include/Map.hpp"

#include "../include/Headers.hpp"
#include "../include/Particle.hpp"
#include "../include/ParticleType.hpp"
#include "../include/ResonanceType.hpp"

// Constructor: Initializes the particle map upon object creation
particle_Info::particle_Info() {
  // Initialize the map when the object is created
  InitializeMap();
}

// Destructor: Performs cleanup if necessary
particle_Info::~particle_Info() {
  // Destructor code, if needed
}

// Function to initialize the map with desired values and associated
// probabilities
void particle_Info::InitializeMap() {
  particle_Map[0] = std::make_pair("Pion+", 0.4);
  particle_Map[1] = std::make_pair("Pion-", 0.4);
  particle_Map[2] = std::make_pair("Kaon+", 0.05);
  particle_Map[3] = std::make_pair("Kaon-", 0.05);
  particle_Map[4] = std::make_pair("Proton+", 0.045);
  particle_Map[5] = std::make_pair("Proton-", 0.045);
  particle_Map[6] = std::make_pair("Kaon*", 0.01);
  // ... add other particle types if needed
}

// Function to get the particle type based on a random value
std::string particle_Info::GetParticleType(double random) const {
  double cumulativeProbability = 0.0;

  // Loop through the map to find the particle type associated with the random
  // value
  for (const auto& entry : particle_Map) {
    cumulativeProbability += entry.second.second;

    if (random < cumulativeProbability) {
      return entry.second.first;
    }
  }

  // If no type is found, return an empty string
  return "";
}

// Function to get the particle index (fIndex) based on the particle type
int particle_Info::GetParticleFIndex(const std::string& particleType) const {
  for (const auto& entry : particle_Map) {
    // Loop through the map to find the index associated with the particle type
    if (entry.second.first == particleType) {
      return entry.first;
    }
  }

  return -1;  // o un altro valore significativo
}

// Function to set the particle index (fIndex) associated with a particle type
void particle_Info::SetParticleFIndex(int fIndex,
                                      const std::string& particleType) {
  // Set the index associated with the particle type in the map
  particle_Map[fIndex].first = particleType;
}
