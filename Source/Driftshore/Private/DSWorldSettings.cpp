// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSWorldSettings.h"

ADSWorldSettings::ADSWorldSettings()
{
	DefaultTrafficDensity.ProfileId = TEXT("marina_tourist");
	DefaultTrafficDensity.VehiclePerKm = 4.f;
	DefaultTrafficDensity.PedestrianPer100m2 = 0.35f;
	DefaultTrafficDensity.BoatIdleSlots = 6;
	DefaultTrafficDensity.PatrolStubCount = 1;
}
