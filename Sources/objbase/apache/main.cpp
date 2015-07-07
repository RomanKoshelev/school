// Dima Poliakov
// HomeLabs Software. 2000
// TSMC Inc, 2000

#include "sock.h"
#include "String.h"

#pragma comment(lib, "wsock32.lib")

char *host = "www.4me.ru";
int port = 1500;

void main()
{
//	String txt = "BX_RateStats_Site[3][2]VBN[1]1926[2]Concept[2]Indices[1]LH_Visitors[1]LH_Hosts[1]LH_Hits[1]LH_Clicks[1]LH_SuspiciousHits_Prc[1]LH_AnonymousHits_Prc[2]KeyIndex[1]LH_Hosts[2]FirstPos[1]0[2]LastPos[1]4[2]Ascending[1]0[2]WithDescription[1]1[3][2]ObjectsNum[2]RawTable[2]Total[2]SubTotal[2]VBNTotalObjects[2]ReqTotal[2]VBNTotalObjectsAct[2]ReqTotalObjects[2]ReqTotalObjectsAct";
//	String txt = "BX_Site_RateStats[3][2]VBN[1]1234[2]KeyIndex[1]Total_Hits[2]Indices[1]Total_Hits[1]Total_Hosts[3][2]RawTable[2]VBNTotalObjectsAct";
	String txt = "BX_RateStats_Site[3][2]VBN[1]1270[2]Concept[2]Indices[1]LH_Visitors[1]LH_Hosts[1]LH_Hits[1]LH_Clicks[1]LH_SuspiciousHits_Prc[1]LH_AnonymousHits_Prc[2]KeyIndex[1]LH_Hosts[2]FirstPos[1]0[2]LastPos[1]4[2]Ascending[1]0[2]WithDescription[1]1[3][2]ObjectsNum[2]RawTable[2]Total[2]SubTotal[2]VBNTotalObjects[2]ReqTotal[2]VBNTotalObjectsAct[2]ReqTotalObjects[2]ReqTotalObjectsAct";
	

	txt.Replace("[1]", 1);
	txt.Replace("[2]", 2);
	txt.Replace("[3]", 3);

	String query = txt.GetLength();
	query+=",195.91.141.201,MirrorBSD";
	query.SetLength(50);

	WSADATA WSAData;

	int rc = WSAStartup(MAKEWORD(1, 1), &WSAData);

	if(rc)
	{
		printf("Error in WSAStartup");
		return;
	}

	sock s(AF_INET, SOCK_STREAM);
	if(!s.good())
	{
		printf("Error while create socket\n");
		printf("Error string: %s\n", s.error_str.c_str());
		return;
	}

	if(s.connect(host, port) < 0)
	{
		printf("s.connect(host, port) < 0\n");
		printf("Can't connect to: %s (port: %d)\n", host, port);
		printf("Error string: %s\n", s.error_str.c_str());
		return;
	}

	// send query to broker
	if(s.write(query.c_str(), query.GetLength()) < 0)
	{
		printf("Can't write to: %s (port: %d)\n", host, port);
		printf("Error string: %s\n", s.error_str.c_str());
		return;
	}

	// send data to broker
	if(s.write(txt.c_str(), txt.GetLength()) < 0)
	{
		printf("Can't write to: %s (port: %d)\n", host, port);
		printf("Error string: %s\n", s.error_str.c_str());
		return;
	}

	String buf;
	buf.SetLength(1024*10);// set big size of buffer

	int r_b;// receaved bytes

	// read daat from broker
	if((r_b = s.read(buf.c_str(), buf.GetLength() )) < 0)
	{
		printf("Can't write to: %s (port: %d)\n", host, port);
		printf("Error string: %s\n", s.error_str.c_str());
		return;
	}
	printf("Receaved all bytes: %d\n", r_b);

	buf.SetLength(r_b);// free unused memory

//	int answer_length = atoi((int)*(buf.c_str());
//	int answer_length = (int)*(buf.c_str());
//	int error_code = (int)*(buf.c_str() + sizeof(int));

//	printf("Answer length: %d\n", answer_length);
//	printf("Error code: %d\n", error_code);
	printf("Text:\n");
	printf("%s\n", buf.c_str());

	s.shutdown();

	WSACleanup();
}
