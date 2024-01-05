#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <string>
#include <unordered_map>

#include "Headers.hpp"
#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

class particle_Info {
 private:
  // Unordered map to store particle information
  static std::unordered_map<int, std::pair<std::string, double>> particle_Map;

 public:
  // Constructor and Destructor
  particle_Info();
  ~particle_Info();

  // Method to initialize the particle map
  static void InitializeMap();

  // Method to get the particle type based on a random value
  std::string GetParticleType(double random) const;

  // Method to get the fIndex of a particle type
  int GetParticleFIndex(const std::string& particleType) const;

  // Method to set the fIndex for a particle type
  void SetParticleFIndex(int fIndex, const std::string& particleType);

  // Additional methods (commented out, uncomment if needed)
  // void AddParticleMap(const Particle&, double probability);
  // double GetProbability(const Particle& particle) const;
};

#endif
