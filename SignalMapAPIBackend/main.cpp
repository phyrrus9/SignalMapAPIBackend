//
//  main.cpp
//  SignalMapAPIBackend
//
//  Created by Ethan Laur on 10/17/15.
//  Copyright © 2015 Ethan Laur. All rights reserved.
//

#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>
#include <libsocket/libsocket.h>
#include <pthread.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

struct signalData
{
	float latitude;
	float longitude;
	std::string carrier;
	int service;
	float signal;
};

int main(int argc, const char * argv[])
{
	Poco::Data::SQLite::Connector::registerConnector();
	Session session("SQLite", "/Users/phyrrus9/SignalMap.db");
	
	signalData d;
	Statement select(session);
	select << "SELECT DISTINCT latitude, longitude, carrier, service, signal FROM signalData",
	into(d.latitude),
	into(d.longitude),
	into(d.carrier),
	into(d.service),
	into(d.signal),
	range(0, 1);
	
	while (!select.done())
	{
		select.execute();
		printf("(%.4f, %.4f) [%s : %d] %.2f%%\n", d.latitude, d.longitude, d.carrier.c_str(), d.service, d.signal);
	}
	
}
