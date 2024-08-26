#ifndef GEOLOCATIONDATA_H
#define GEOLOCATIONDATA_H

#include "Data.h"
#include "Serializable.h"

#include <QGeoCoordinate>

class GeoLocationData : public Data, public Serializable
{
public:
  GeoLocationData()								= default;
  ~GeoLocationData() override = default;
  GeoLocationData(const GeoLocationData &other) = default;
  GeoLocationData(QString place, QString renamedPlace, QGeoCoordinate coordinates, QString country);
  GeoLocationData(QString renamedPlace, QGeoCoordinate coordinates);

  [[nodiscard]] inline auto getDetailedPlace() const -> QString { return m_place; }

  [[nodiscard]] inline auto getRenamedPlace() const -> QString { return m_renamedPlace; }

  [[nodiscard]] inline auto getCountry() const -> QString { return m_country; }

  [[nodiscard]] inline auto getCoordinates() const -> QGeoCoordinate { return m_coordinates; }

  inline void setRenamedPlace(QString &renamedPlace)
  {
	m_renamedPlace = renamedPlace;
  }

  [[nodiscard]] auto toVariant() const -> QVariant override;
  void					 fromVariant(const QVariant &variant) override;
  static auto fromVariantMap(const QVariantMap &geoLocation) -> GeoLocationData;

  auto operator=(const GeoLocationData &other) -> GeoLocationData & = default;
  auto operator==(const GeoLocationData &other) const -> bool;

  private:
  QString		 m_place;
  QString		 m_renamedPlace;
  QGeoCoordinate m_coordinates;
  QString		 m_country;
};
Q_DECLARE_METATYPE(GeoLocationData)

#endif // GEOLOCATIONDATA_H
