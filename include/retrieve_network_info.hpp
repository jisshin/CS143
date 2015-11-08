#ifndef RETRIEVENETWORKINFO_H
#define RETRIEVENETWORKINFO_H

#include <string>
using namespace std;

class RetrieveNetworkInfo {
public:
  // holds JSON data
  string networkInfo;
  // Set the JSON data
  void setNetworkInfo();

  /** extracts flow info from JSON then registers into networkmanager
  * using registerFlow
  */
  int createFlow();
  /** extracts link info from JSON then registers into networkmanager
  * using registerLink
  */
  int createLink();

};
#endif //RETRIEVENETWORKINFO_H
