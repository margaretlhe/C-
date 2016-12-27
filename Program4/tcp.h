// Authors: Matthew Gold and Margaret He
 
#ifndef TCP_H
#define	TCP_H

#include "mynew.h"
#include "HashTable.h" 
#define PACKET_SIZE 256


class TCP 
{
 
public:
  TCP(int numPorts);
  HashTable *table;
  virtual ~TCP();
  void receive(int portNum, int packetNum, char packet[257]);
  int getStream(int portNum, char stream[100000]);
};

#endif	/* TCP_H */

