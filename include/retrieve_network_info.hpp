#ifndef RETRIEVENETWORKINFO_H
#define RETRIEVENETWORKINFO_H

#include <string>
using namespace std;

class RetrieveNetworkInfo {
public:
  // holds JSON data
  string networkInfo;
  // Set the JSON data
  void setNetworkInfo(string file_name);

  /**
  * Creates data out of data obtained from network. 
  */
  int createNetwork();



};
#endif //RETRIEVENETWORKINFO_H
