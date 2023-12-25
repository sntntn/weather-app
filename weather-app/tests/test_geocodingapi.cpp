#include "catch.hpp"
#include "geocodingapi.h"

TEST_CASE("Testiranje geocoding funkcionalnosti", "[geocoding]") {
    GeocodingAPI geocodingApi;

    SECTION("Testiranje geocodeCity funkcije") {
        geocodingApi.geocodeCity("Beograd");
        // Dodajte provere za rezultate poziva funkcije
    }


}
