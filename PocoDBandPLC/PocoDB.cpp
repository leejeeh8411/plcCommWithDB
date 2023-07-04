#include "stdafx.h"
#include "PocoDB.h"



CPocoDB::CPocoDB()
{
	m_Connected = false;
}


CPocoDB::~CPocoDB()
{
	DisConnect();
}

void CPocoDB::Connect()
{
	if (m_Connected == true)
		return;

	Poco::Data::ODBC::Connector::registerConnector();

	std::string strConnection = 
		//"DRIVER={ODBC Driver 17 for SQL Server};Server=DESKTOP-4NUMLB1;Database=MasterNew;Trusted_Connection=Yes;";
		"DRIVER={ODBC Driver 17 for SQL Server};Server=DESKTOP-86U7OKN;Database=MasterNew;Trusted_Connection=Yes;";
	
	m_connectionString = strConnection;
	sessionPool = new Poco::Data::SessionPool("ODBC", strConnection);

	m_Connected = true;
}

void CPocoDB::DisConnect()
{
	if (m_Connected == false)
		return;

	m_Connected = false;
}

bool CPocoDB::InsertPLC()
{
	int nValue = 0;

	//Session session(sessionPool->get());
	//Statement stmt(session);
	//stmt << std::fixed << std::setprecision(2); // 부동소수점 2자리로 설정
	//stmt << "INSERT INTO LotInfo (start_time, lot_id, lot_index, rcp_id";
	//stmt << ") VALUES (";
	//stmt << "'" << nValue << "'";
	//stmt << ",'" << nValue << "'";
	//stmt << ",'" << nValue << "'";
	//stmt << ",'" << nValue << "'";
	//stmt << ")";

	//// execute query
	//while (!stmt.done()){
	//	try{
	//		stmt.execute();
	//	}
	//	catch (Poco::Exception& e){
	//		return false;
	//	}
	//}
	return true;
}

bool CPocoDB::ReadPLCAddress(std::vector<st_plc_address>* vt_data)
{
	st_plc_address plcAddress;

	std::string strAddress;
	std::string strDataType;
	std::string strSyncType;
	std::string strComment;

	// prepare query
	Session session(sessionPool->get());
	Statement stmt(session);
	stmt << "SELECT idx, TRIM(address), blocksize, TRIM(datatype), TRIM(synctype), TRIM(comment)";
	stmt << " FROM PLCaddress";

	stmt, into(plcAddress.blockID);
	stmt, into(strAddress);
	stmt, into(plcAddress.blockSize);
	stmt, into(strDataType);
	stmt, into(strSyncType);
	stmt, into(strComment);

	stmt, range(0, 1); //  iterate over result set one row at a time

	while (!stmt.done()) {
		try {
			stmt.execute();

			strncpy(plcAddress.cAddress, strAddress.c_str(), 10);
			strncpy(plcAddress.cDataType, strDataType.c_str(), 10);
			strncpy(plcAddress.cSyncType, strSyncType.c_str(), 10);
			strncpy(plcAddress.cComment, strComment.c_str(), 50);
			vt_data->emplace_back(plcAddress);
		}
		catch (Poco::Exception& e) {
			return false;
		}
	}
	return true;
}

bool CPocoDB::ReadPLCSch(std::vector<st_plc_read_sch>* vt_data, int nBlockID)
{
	st_plc_read_sch plcReadSch;

	std::string strDataType;
	std::string strKeyName;
	std::string strDataTypeDB;
	
	// prepare query
	Session session(sessionPool->get());
	Statement stmt(session);
	stmt << "SELECT idx, addressid, idxstt, size, TRIM(datatype), TRIM(keyname), TRIM(datatypedb)";
	stmt << " FROM PLCReadSCH";
	stmt << " WHERE addressid =? ", use(nBlockID) ;

	stmt, into(plcReadSch.idx);
	stmt, into(plcReadSch.addressid);
	stmt, into(plcReadSch.idxstt);
	stmt, into(plcReadSch.size);
	stmt, into(strDataType);
	stmt, into(strKeyName);
	stmt, into(strDataTypeDB);

	stmt, range(0, 1); //  iterate over result set one row at a time

	while (!stmt.done()){
		try{
			stmt.execute();
			strncpy(plcReadSch.cDataType, strDataType.c_str(), 10);
			strncpy(plcReadSch.keyname, strKeyName.c_str(), 20);
			strncpy(plcReadSch.cDataTypeDB, strDataTypeDB.c_str(), 10);
			vt_data->emplace_back(plcReadSch);
		}
		catch (Poco::Exception& e){
			return false;
		}
	}
	return true;
}