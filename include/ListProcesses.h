/*
 * ListProccesses.h
 *
 *  Created on: Mar 6, 2020
 *      Author: user
 */

#ifndef LISTPROCESSES_H_
#define LISTPROCESSES_H_

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <vector>

using namespace std ;

typedef struct strProcess{
    
    string id ;
    string exe ;
    string cmd ;

} tstrProcess ;

class ListProccesses {

public:
    static vector<string> GetProcessNameList() ;
    static vector<string> GetProcessPathList() ;
    static vector<string> GetProcessCmdList()  ;
    static vector<string> GetProcessExecList() ;
    static vector<tstrProcess> GetDataStructure();
    
protected:

private:


};

#endif /* LISTPROCESSES_H_ */
