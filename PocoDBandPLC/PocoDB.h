#pragma once

#include <Poco/BasicEvent.h>
#include <Poco/ActiveMethod.h>
#include "Poco/Data/Session.h"
#include "Poco/Data/ODBC/Connector.h"
#include "Poco/Data/SessionPool.h"
#include "Poco/DateTime.h"
#include "Poco/Data/Extraction.h"
#include <string>

using namespace Poco::Data;
using namespace Poco::Data::Keywords;
using namespace std;

//테이블 구조체


class CPocoDB
{

private:
	bool m_Connected;

public:
	SessionPool* sessionPool;

	CPocoDB();
	~CPocoDB();

	bool IsConnected() { return m_Connected; }

	std::string m_connectionString;

	void Connect();
	void DisConnect();

	// Insert문
	bool InsertPLC();

	// Select문
	bool ReadPLCAddress(std::vector<st_plc_address>* vt_data);
	bool SelectSch(std::vector<string>* vt_data);

};

