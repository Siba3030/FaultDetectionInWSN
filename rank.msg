cplusplus {{
#include "ApplicationPacket_m.h"
}}

class ApplicationPacket;

struct srank{
    int rank=1;
}

packet Rank extends ApplicationPacket {
    srank myrank;
    }
