#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "responses.h"

class BusManager {
private:
	std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;
public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops);

	BusesForStopResponse GetBusesForStop(const std::string& stop) const;

	StopsForBusResponse GetStopsForBus(const std::string& bus) const;

	AllBusesResponse GetAllBuses() const;
};