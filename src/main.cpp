#include <iostream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <fnmatch.h>
#include <unistd.h>
#include <sys/types.h>
#include "ListProcesses.h"





using namespace std;

int main (void)
{
  if(geteuid() != 0)
  {
    // Tell user to run app as root, then exit.
    cout << "This program must be run as root!" << endl;
    exit(-1) ;
  }

  vector<tstrProcess> v ;
  v = ListProccesses::GetDataStructure() ;

  for(vector<tstrProcess>::iterator it=v.begin() ; it<v.end() ; it++){
    cout << (*it).id << "\t\t" << std::setw(100) << (*it).exe << "\t\t" << (*it).cmd << endl ;
  }


  return 0;
}
