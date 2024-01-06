#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <iostream>
#include <string>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "doctest.h"
#include "Particle.hpp"

ParticleType *parArray[2];

TEST_CASE("Testing ParticleType class")
{
  ParticleType p("K", 5, 2);
  SUBCASE("Testing getters")
  {
    CHECK(p.get_ParticleName() == "K");
    CHECK(p.get_ParticleMass() == 5);
    CHECK(p.get_ParticleCharge() == 2);
    CHECK(p.get_Width() == 0);
  }
  SUBCASE("Testing print method")
  {
    std::ostringstream outputBuffer;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    p.print();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput = "Name: K, Mass: 5, Charge: 2";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
};

TEST_CASE("Testing ResonanceType class")
{
  ResonanceType r("K", 5, 2, 7);
  SUBCASE("Testing getters")
  {
    CHECK(r.get_ParticleName() == "K");
    CHECK(r.get_ParticleMass() == 5);
    CHECK(r.get_ParticleCharge() == 2);
    CHECK(r.get_Width() == 7);
  }
  SUBCASE("Testing print method")
  {
    std::ostringstream outputBuffer;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    r.print();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput =
        "Name: K, Mass: 5, Charge: 2, Resonance Width: 7";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
}
TEST_CASE("Testing ParticleClass")
{
  ResonanceType r("K", 5, 2, 7);
  ParticleType p("pi+", 5, 2);
  ParticleType h("p-", 8, 9);
  Particle::AddParticleType(r.get_ParticleName(), r.get_ParticleMass(), r.get_ParticleCharge(), r.get_Width());
  Particle::AddParticleType(p.get_ParticleName(), p.get_ParticleMass(), p.get_ParticleCharge(), 0);
  Particle::AddParticleType(h.get_ParticleName(), h.get_ParticleMass(), h.get_ParticleCharge(), 0);
  Particle c(r.get_ParticleName(), 6., 2, 5.);
  Particle d(p.get_ParticleName(), 300, 8000, 700);
  Particle e(h.get_ParticleName(),500,400,1000);
  //Testing Findparticle method while testing getters
  SUBCASE("Testing getters"){
    CHECK(c.get_Mass() == 5);
    CHECK(c.get_Charge() == 2);
  //CHECK get_specificMass 
    CHECK(c.get_specificMass(5,"K") == true);
    CHECK(d.get_specificMass(5,"pi+") == true);
    CHECK(e.get_specificMass(8,"K+") == false);
    CHECK(e.get_specificMass(8,"pi+") == false);
    CHECK_THROWS_AS(c.get_specificMass(10,"NonExistentParticle"), std::runtime_error);
  
  }


  SUBCASE("Testing AddParticleType")
  {
    std::ostringstream outputBuffer;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    Particle::ArrayStatus();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput =
        "Name: K, Mass: 5, Charge: 2, Resonance Width: 7\nName: pi+, Mass: 5, Charge: 2, Resonance Width: 0\n";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
  SUBCASE("Testing Momentum Setter")
  {
    c.set_P(3, 4, 5);
    CHECK(c.get_Xmomentum() == 3);
    CHECK(c.get_Ymomentum() == 4);
    CHECK(c.get_Zmomentum() == 5);
  }
  
  SUBCASE("Testing Indexsetter with an integer parameter")
  {
    c.set_fIndex(5);
    CHECK(c.get_fIndex() == 5);
  }

  SUBCASE("Testing Indexsetter with a char parameter")
  {
    c.set_fIndex("pi+");
    CHECK(c.get_fIndex() == 1);
  }

  SUBCASE("Testing ParticleEnergy method")
  {
    CHECK(c.ParticleEnergy() == doctest::Approx(9.486833).epsilon(0.001));
    CHECK(d.ParticleEnergy() == doctest::Approx(8036.17).epsilon(0.01));
    CHECK(e.ParticleEnergy() == doctest::Approx(1187.461).epsilon(0.01));
  }

  SUBCASE("Testing InvMass method")
  {
    
    CHECK(c.InvMass(d) == doctest::Approx(12081.67).epsilon(0.1));
    CHECK(c.InvMass(e) == doctest::Approx(2256.6022).epsilon(0.1));
    CHECK(d.InvMass(e) == doctest::Approx(14278.843).epsilon(0.1));

  }
}