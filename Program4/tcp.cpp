
#include "mynew.h"
#include "tcp.h"
#include "string.h
#include <cstring>

TCP::TCP(int numPort)
{
 table = new HashTable(numPort*2);
  
}  // TCP()

TCP::~TCP() {
}

void TCP::receive(int portNum, int packetNum, char packet[257])
{
	table->insert(portNum, packetNum, packet);
} // receive()

int TCP::getStream(int portNum, char stream[100000])
{
  // getStream() should fill the stream with current packets that have
  // packet numbers greater than the last packet past in the last 
  // stream for this port.  The packets must be ascending order, though
  // not necessarily consecutive.  Return the size of the stream in bytes.
  stream = const_cast<char*>(table->getPort(portNum).c_str());
   
   
   return 0;
}