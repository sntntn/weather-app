#include "catch.hpp"
#include "GeoLocationData.h"

TEST_CASE("GeoLocationData Construction") {
    SECTION("Default Constructor") {
        GeoLocationData location;
        REQUIRE(location.getDetailedPlace().isEmpty());
        REQUIRE(location.getRenamedPlace().isEmpty());
        REQUIRE(location.getCoordinates() == QGeoCoordinate());
        REQUIRE(location.getCountry().isEmpty());
    }

    SECTION("Parameterized Constructor") {
        GeoLocationData location("Belgrade", "Belgrade City", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        REQUIRE(location.getDetailedPlace() == "Belgrade");
        REQUIRE(location.getRenamedPlace() == "Belgrade City");
        REQUIRE(location.getCoordinates() == QGeoCoordinate(44.8125, 20.4375));
        REQUIRE(location.getCountry() == "Serbia");
    }
}

TEST_CASE("GeoLocationData Equality Operator") {
    GeoLocationData location1("Belgrade", "Belgrade City", QGeoCoordinate(44.8125, 20.4375), "Serbia");
    GeoLocationData location2("Belgrade", "Belgrade City", QGeoCoordinate(44.8125, 20.4375), "Serbia");
    GeoLocationData location3("New York", "NYC", QGeoCoordinate(40.7128, -74.0060), "USA");

    REQUIRE(location1 == location2);
    REQUIRE_FALSE(location1 == location3);
}

TEST_CASE("GeoLocationData QVariant Conversion") {
    GeoLocationData original("Belgrade", "Belgrade City", QGeoCoordinate(44.8125, 20.4375), "Serbia");

    QVariant variant = original.toVariant();
    GeoLocationData converted;
    converted.fromVariant(variant);

    REQUIRE(original == converted);
}

TEST_CASE("GeoLocationData fromVariantMap") {
    QVariantMap map{
        {"place", "Belgrade"},
        {"renamedPlace", "Belgrade City"},
        {"latitude", 44.8125},
        {"longitude", 20.4375},
        {"country", "Serbia"}
    };

    GeoLocationData location = GeoLocationData::fromVariantMap(map);

    REQUIRE(location.getDetailedPlace() == "Belgrade");
    REQUIRE(location.getRenamedPlace() == "Belgrade City");
    REQUIRE(location.getCoordinates() == QGeoCoordinate(44.8125, 20.4375));
    REQUIRE(location.getCountry() == "Serbia");
}
