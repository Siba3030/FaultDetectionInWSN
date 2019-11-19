#ifndef _MYPROJECT_H_
#define _MYPROJECT_H_

#include "VirtualApplication.h"
#include "MyPacket_m.h"
//#include "rank_m.h"
#include "stdio.h"
using namespace std;

struct neighborRecord {
    int pid;
    int id;
    int timesRx;
   // double receivedPackets;
};

struct sensedData {
    int sid;
    float sensedvalue;
};

enum MyProjectTimers {
	REQUEST_SAMPLE = 1,
	COMPUTE_DATA = 2,
};

class MyProject: public VirtualApplication {
 private:
	int totalPackets;
	double currMaxReceivedValue;
	double currMaxSensedValue;

    //double maxSampleInterval;
    //double minSampleInterval;
	//double randomBackoffIntervalFraction;
	double sensor;
	int n=15;
	int no=15;
	double mag;
	double sum=0;
	//double sr=0.0;
	double sensorsrc[];
	double sensrc;
	int psrc;
	int sentOnce;
	int nodeNo;
	double theValue;
	double nei[15];
	double corr[15];
	double pro[15];
	double rank[15];
	double val[15];
	double corre[15];
	double proe[15];
	double ranke[15];
	double tempThreshold;
	vector<double> sensedValues;
	vector <neighborRecord> neighborTable;
	//struct neighborRecord neighborTable[10];
	vector<sensedData> Data;

 protected:
	void startup();
	void requestReading();
	void finishSpecific();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	//void handleSensorReading(SensorReadingMessage *);
	void timerFiredCallback(int);
	//void updateNeighborTable(int, int, double);
	void updateNeighborTable(int, int);
	void updateDataTable(int , float);
	void fault_detect();
	void corr_network();
	void trans_prob(double);
	void sensor_rank();
	void final_sr();
	void updatecorrTable(int , int , float);
	void fault_detection(double);
};

#endif				// _MYPROJECT_APPLICATIONMODULE_H_
