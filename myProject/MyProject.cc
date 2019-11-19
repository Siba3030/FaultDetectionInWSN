#include "MyProject.h"

Define_Module(MyProject);

void MyProject::startup()
{

    sensor=0.0;
    tempThreshold = par("tempThreshold");
	totalPackets = 0;
	currMaxReceivedValue = -1.0;
	currMaxSensedValue = -1.0;
	sentOnce = 0;
	theValue = 0;
    neighborTable.clear();
	setTimer(REQUEST_SAMPLE, 0);
}

void MyProject::timerFiredCallback(int index)
{
	switch (index) {
		case REQUEST_SAMPLE:{
			requestReading();
			setTimer(REQUEST_SAMPLE, 10);
			break;
		}
	//	case COMPUTE_DATA:{
	//	    corr_network();
		//    break;
		//}
	}
}

void MyProject::requestReading()
{
    int i;
    sensor = (rand()%10) + 30;
    trace() << "Sensed Values : " << sensor;
    MyPacket *pkt= new MyPacket ("SensorPacket", APPLICATION_PACKET);
    data d;
    d.src = (unsigned short)self;
    for(i=0;i<n;i++){
        if(i==(d.src))
        sensorsrc[i]= sensor;
    }
    sensrc = d.src;
    if(sensrc==0 ||sensrc==3||sensrc==9||sensrc==10||sensrc==12||sensrc==13)
    {
        sensor = (rand()%10) + 100;
        //sensor=sensor+70;
        updateDataTable(sensrc, sensor);
        pkt->setMydata(d);
        pkt->setData(sensor);

    }
    else
    {
        sensor = (rand()%10) + 30;
        //sensor=sensor+70;
        updateDataTable(sensrc, sensor);
        pkt->setMydata(d);
        pkt->setData(sensor);

    }
    //updateDataTable(sensrc, sensor);
    //MyPacket *pkt= new MyPacket ("SensorPacket", APPLICATION_PACKET);
    //pkt->setMydata(d);
    //pkt->setData(sensor);
    toNetworkLayer(pkt,BROADCAST_NETWORK_ADDRESS);
}

void MyProject::fromNetworkLayer(ApplicationPacket * rcvPacket, const char *source, double rssi, double lqi)
{
    MyPacket *rvc =check_and_cast<MyPacket*>(rcvPacket);
	data d= rvc->getMydata();
    double receivedData = rcvPacket->getData();
	totalPackets++;
	theValue = receivedData;

		trace() << "Sensed Values: " << sensor;
		trace() << "Sensed Values of neigbor: " << theValue;
		trace() << "From neighbor : " << source;
		nodeNo =atoi(source);
		d.src = (unsigned short)self;

		//data d;
		    psrc=d.src;
		    trace()<<"Sensed Node id:"<<psrc;

		//updateNeighborTable(psrc ,nodeNo,theValue);
		    nei[nodeNo]=theValue;
        updateNeighborTable(psrc ,nodeNo);
		//trace() << "current simulation time"<< simTime();
        //int tblSize = (int)neighborTable.size();
        //for(int i=0;i<tblSize;i++){
            //if(i==nodeNo)
                //nei[nodeNo]=theValue;
            //else
              //  continue;
            //}
        if (simTime()==40.0)
		{
		    cancelTimer(REQUEST_SAMPLE);
		    //setTimer(COMPUTE_DATA,79.0);
		}
     //   corr_network();
}

void MyProject::finishSpecific()
{

    //int tblSize = (int)neighborTable.size();
    declareOutput("got value");
    for (int i = 0; i < (int)Data.size(); i++)
    {
        trace() << " ID: " << Data[i].sid;
        trace() << "Value of node: " << Data[i].sensedvalue;
        collectOutput("ID",  Data[i].sid);
        collectOutput("Value of node", Data[i].sensedvalue);
    }

    for (int i = 0; i < (int)neighborTable.size(); i++)
            {
             trace() << "Parent node ID: " << neighborTable[i].pid;
             trace() << "neighbor node ID: " << neighborTable[i].id;

             collectOutput("Parent node ID: " ,neighborTable[i].pid);
             collectOutput("neighbor node ID: ", neighborTable[i].id);
             //trace() << "value received from neighbor node: " << neighborTable[i].receivedPackets;
            }

	for(int i=0;i<no;i++)
	    trace()<<"neighbor Reading"<<nei[i];

	corr_network();
	//fault_detect();
}

//void MyProject::updateNeighborTable(int src,int nodeID, double value)

void MyProject::updateNeighborTable(int src,int nodeID)
{
        int i = 0, pos = -1;
        //FILE *fp = fopen("neighborTable.txt", "a+");
          //int nid;
        //nid= (int)src;
        int tblSize = (int)neighborTable.size();

        for (i = 0; i < tblSize; i++)
        {
            if (neighborTable[i].id == nodeID)
            {
                pos = i;
                break;
            }
        }
        if (pos == -1)
        {
            neighborRecord newRec;
            newRec.pid= src;
            newRec.id = nodeID;
            newRec.timesRx = 1;
            //newRec.receivedPackets = value;
            neighborTable.push_back(newRec);
           // fprintf(fp, "%d %d\n",src,nodeID);
            //fclose(fp);
        }
        else
        {
            //neighborTable[pos].pid=src;
            //neighborTable[pos].id=nodeID;
            neighborTable[pos].timesRx++;
            //neighborTable[pos].receivedPackets = value;
        }

}

void MyProject::updateDataTable(int nodeID, float data)
{
    int i = 0, pos = -1;
    //FILE *fp = fopen("dataTable.txt", "a+");
        int tblSize = (int)Data.size();
        for (i = 0; i < tblSize; i++)
            if (Data[i].sid == nodeID)
                pos = i;
        if (pos == -1)
        {
            sensedData newRecs;
            newRecs.sid = nodeID;
            newRecs.sensedvalue = data;
            Data.push_back(newRecs);
            //fprintf(fp, "%d %f\n",nodeID,data);
            //fclose(fp);
        }
        else
        {
            Data[pos].sensedvalue = data;
        }
}


void MyProject::corr_network()
{
    //int tblSize = (int)neighborTable.size();
    double c,d,csum=0;
    for(int i=0;i<no;i++)
    {
        //if(nei[i]==0)
        //{
         //continue;
        //}
        //else{
        //trace()<<"neighbor Reading:"<<nei[i];
            c=(sensor * nei[i]);
            d=(nei[i] * nei[i])+(sensor * sensor)-(sensor * nei[i]);
            corr[nodeNo]=c/d;
            corre[i]=corr[nodeNo];
           csum=csum+corr[nodeNo];
            // for(int i=0;i<5;i++)
                   //trace()<<"corr Reading"<<corr[i];

              //pro[nodeNo]=e/csum;
              //trace()<<"Transaction Probability:"<<pro[nodeNo];
      }
    //trace()<<"sum :"<<csum;
    for(int i=0;i<no;i++)
       {
    trace()<<"corre :"<<corre[i];
       }
    //}
trans_prob(csum);

}

void MyProject::trans_prob(double s)
{
  //int tblSize = (int)neighborTable.size();
    double c;
    /*for(int i=0;i<5;i++)
              {
                 csum=csum+nei[i];
              }
      trace()<<"csum :"<<csum;
    //*/
    for(int i=0;i<no;i++)
    {
        //if(corr[i]==0)
          //   {
            //  continue;
             //}
        //else
        //{
        //trace()<<"s :"<<s;
        c=corre[i]/s;
        //trace()<<"c :"<<corr[i];
       pro[nodeNo]=c;
       proe[i]=pro[nodeNo];
       //trace()<<"transaction probability :"<<pro[nodeNo];
        //}
    }
    for(int i=0;i<no;i++)
           {
        trace()<<"transition probability :"<<proe[i];
           }

    sensor_rank();
}

void MyProject::sensor_rank()
{
    //int r;
    //int tblSize = (int)neighborTable.size();
    for(int i=0;i<no;i++)
        {
           //rank[i]=1;
           //r=1*proe[i];
           //trace()<<"Rankr :"<<r;
           rank[nodeNo]=theValue*proe[i];
           //trace()<<"Rankr :"<<rank[nodeNo];
           ranke[i]=rank[nodeNo];
         }
    /*for(int i=0;i<no;i++)
    {
        //if(pro[i]==0)
          //  {
            //continue;
            //}
         //else
         //{
        r=rank[i]*proe[i];
        trace()<<"Rankr :"<<proe[i];
        rank[nodeNo]=r;
        ranke[i]=rank[nodeNo];
       trace()<<"Rank :"<<ranke[i];
         //}
    }*/
    for(int i=0;i<no;i++)
      {
            trace()<<"Sensor Rank :"<<ranke[i];
       }
    final_sr();
}

void MyProject::final_sr()
{
    double sr=0;
    //int tblSize = (int)neighborTable.size();
    for(int i=0;i<no;i++)
        {
           //trace()<< rank[i];
           sr=sr+ranke[i];
           //trace() << "Each sr" << sr;
        }
    //sr=sr;
    trace()<<"Final Rank :"<<sr;
    fault_detection(sr);
}

void MyProject::fault_detect()
{

    int tblSize = (int)neighborTable.size();
   // trace()<<"table :"<<tblsize;
int dec=0;
float vote,x=0,y, thre=0.5;
for(int i=0;i<tblSize;i++)
    {
    //if(pro[i]==0)
      //  {
        //continue;
        //}
   // else
     //   {
        val[i]=sensor - nei[i];
        trace()<<"value of val :"<<val[i];
       // }
    }
for(int i=0;i<tblSize;i++)
    {
    if(pro[i]==0)
        {
        continue;
        }
    else
        {
        x=x+val[i];

        }
    }
trace()<<"value of x :"<<x;
y=x/3;
if (y>=thre)
        {
        vote=x;
        }
    else
        {
        vote =-x;
        }
    dec=dec+vote;
    if(dec>0)
    {
        trace()<<"fault free";
    }
    else
    {
        trace()<<"faulty";

    }
}


void MyProject::fault_detection(double s)
{
    //int tblSize = (int)neighborTable.size();

    double dec=0,vote,thr=0.5;
    for(int i=0;i<no;i++)
        {
            //if(nei[i]==0)
            //{
             //continue;
            //}
            //else
            //{
            //trace()<<"neighbor Reading:"<<nei[i];
            //c=(sensor - nei[i]);
            //trace()<<"value of val:"<<c;
            //}
            //if( c < 0 )
              //  c= c*(-1);
            //else
              //  c =sum - sensor;
            if(corre[i]>thr)
            {
                vote=s;
                //trace() << "vote: " << vote;

            }
            else
            {
                vote=-s;
                //trace() << "vote: " << vote;

            }
            dec=dec+proe[i]*vote;
            trace() << "dec: " << dec;
        }
            if(dec>=0)
            {
                trace()<<"fault free node";
            }
            else
            {
                trace()<<"faulty node";
            }
}
