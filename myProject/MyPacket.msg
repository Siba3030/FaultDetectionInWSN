cplusplus {{
#include "ApplicationPacket_m.h"
}}

class ApplicationPacket;

struct data{
    int src;
}

packet MyPacket extends ApplicationPacket {
    data mydata;
    
    }
