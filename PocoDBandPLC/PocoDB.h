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

//���̺� ����ü


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

	// Insert��
	bool InsertPLC();

	// Select��
	bool ReadPLCAddress(std::vector<st_plc_address>* vt_data);
	bool SelectSch(std::vector<string>* vt_data);

};

