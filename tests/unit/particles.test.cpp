#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <iostream>
#include <string>

#include "../../main/include/Particle.hpp"
#include "../../main/include/ParticleType.hpp"
#include "../../main/include/ResonanceType.hpp"
#include "doctest.h"

TEST_CASE("Testing ParticleType class") {
  ParticleType p("Kaon+", 0.49367, 1);
  SUBCASE("Testing getters") {
    CHECK(p.get_ParticleName() == "Kaon+");
    CHECK(p.get_ParticleMass() == 0.49367);
    CHECK(p.get_ParticleCharge() == 1);
    CHECK(p.get_ParticleWidth() == 0);
  }
  SUBCASE("Testing print method") {
    std::ostringstream outputBuffer;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    p.print();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput = "Name: Kaon+, Mass: 0.49367, Charge: 1";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
};

TEST_CASE("Testing ResonanceType class") {
  ResonanceType r("Kaon*", 0.89166, 0, 0.050);
  SUBCASE("Testing getters") {
    CHECK(r.get_ParticleName() == "Kaon*");
    CHECK(r.get_ParticleMass() == 0.89166);
    CHECK(r.get_ParticleCharge() == 0);
    CHECK(r.get_ParticleWidth() == 0.050);
  }
  SUBCASE("Testing print method") {
    std::ostringstream outputBuffer;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    r.print();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput = "Name: Kaon*, Mass: 0.89166, Charge: 0, Resonance Width: 0.05";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
}
TEST_CASE("Testing ParticleClass") {
  ResonanceType r("Kaon*", 0.89166, 0, 0.050);
  ParticleType p("Proton+", 0.93827, 1);
  ParticleType h("Pion-", 0.13957, -1);
  Particle::AddParticleType(r.get_ParticleName(), r.get_ParticleMass(), r.get_ParticleCharge(), r.get_ParticleWidth());
  Particle::AddParticleType(p.get_ParticleName(), p.get_ParticleMass(), p.get_ParticleCharge(), 0);
  Particle::AddParticleType(h.get_ParticleName(), h.get_ParticleMass(), h.get_ParticleCharge(), 0);
  Particle c(r.get_ParticleName(), 0.89166, 0, 0.050);
  Particle d(p.get_ParticleName(), 0.93827, 1, 0);
  Particle e(h.get_ParticleName(), 0.13957, -1, 0);
  // Testing Findparticle method while testing getters
  SUBCASE("Testing getters") {
    CHECK(c.get_Mass() == 0.89166);
    CHECK(c.get_Charge() == 0);
    // CHECK get_specificMass
    CHECK(c.get_specificMass(0.89166, "Kaon*") == true);
    CHECK(d.get_specificMass(0.93827, "Proton+") == true);
    CHECK(e.get_specificMass(8, "Kaon*") == false);
    CHECK(e.get_specificMass(8, "Proton+") == false);
    CHECK_THROWS_AS(c.get_specificMass(10, "NonExistentParticle"), std::runtime_error);
  }

  SUBCASE("Testing AddParticleType") {
    std::ostringstream outputBuffer;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    Particle::ArrayStatus();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput =
        "Name: Kaon*, Mass: 0.89166, Charge: 0, Resonance Width: 0.05\nName: Proton+, Mass: 0.93827, Charge: 1\nName: "
        "Pion-, Mass: 0.13957, Charge: -1\n";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
  SUBCASE("Testing Momentum Setter") {
    c.set_P(3, 4, 5);
    CHECK(c.get_Xmomentum() == 3);
    CHECK(c.get_Ymomentum() == 4);
    CHECK(c.get_Zmomentum() == 5);
  }

  SUBCASE("Testing Indexsetter with an integer parameter") {
    c.set_fIndex(6);
    CHECK(c.get_fIndex() == 0);
  }

  SUBCASE("Testing Indexsetter with a char parameter") {
    c.set_fIndex("Pion+");
    CHECK(c.get_fIndex() == 0);
  }

  SUBCASE("Testing ParticleEnergy method") {
    c.set_P(3, 4, 5);
    d.set_P(1.5, 2, 10.5);
    CHECK(c.ParticleEnergy() == doctest::Approx(7.12707).epsilon(0.01));
    CHECK(d.ParticleEnergy() == doctest::Approx(10.8340).epsilon(0.01));
    CHECK(e.ParticleEnergy() == doctest::Approx(0.13957).epsilon(0.01));
  }

  SUBCASE("Testing InvMass method") {
    c.set_P(3, 4, 5);
    d.set_P(1.5, 2, 10.5);
    e.set_P(0.7, 9.1, 3);
    c.ParticleEnergy();
    d.ParticleEnergy();
    e.ParticleEnergy();
    CHECK(c.InvMass(d) == doctest::Approx(5.1088).epsilon(0.1));
    CHECK(c.InvMass(e) == doctest::Approx(5.5473).epsilon(0.1));
    CHECK(d.InvMass(e) == doctest::Approx(10.3729).epsilon(0.1));
  }
}