#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <iostream>
#include <string>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "doctest.h"

ParticleType* parArray[2];

TEST_CASE("Testing ParticleType class") {
  ParticleType p("K", 5, 2);
  SUBCASE("Testing getters") {
    CHECK(p.get_ParticleName() == "K");
    CHECK(p.get_ParticleMass() == 5);
    CHECK(p.get_ParticleCharge() == 2);
  }
  SUBCASE("Testing print method") {
    std::ostringstream outputBuffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    p.print();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput = "Name: K, Mass: 5, Charge: 2";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
};

TEST_CASE("Testing ResonanceType class") {
  ResonanceType r("K", 5, 2, 7);
  SUBCASE("Testing getters") {
    CHECK(r.get_ParticleName() == "K");
    CHECK(r.get_ParticleMass() == 5);
    CHECK(r.get_ParticleCharge() == 2);
    CHECK(r.get_ResonanceWidth() == 7);
  }
  SUBCASE("Testing print method") {
    std::ostringstream outputBuffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());
    r.print();
    std::cout.rdbuf(oldCoutBuffer);
    const std::string ExpectedOutput =
        "Name: K, Mass: 5, Charge: 2, Resonance Width: 7";
    CHECK(outputBuffer.str() == ExpectedOutput);
  }
}