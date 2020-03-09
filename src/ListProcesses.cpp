/*
 * ListProccesses.cpp
 *
 *  Created on: Mar 6, 2020
 *      Author: Yahya Ahmed
 */


#include "ListProcesses.h"

#include <dirent.h>
#include <fnmatch.h>
#include <fstream>

#include <limits.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

//Vector of string for list of available processes
vector<string> vectProcessNameList,vectProcessPathList,
               vectProcessCmdList,vectProcessExecList ;

vector<tstrProcess> vectProcessList ;

vector<string> ListProccesses::GetProcessNameList(){

    DIR *dp;
    struct dirent *ep;


    dp = opendir ("/proc/");

    if (dp != NULL)
    {
        while (ep = readdir (dp))
        {
            if(!fnmatch("[0-9]*",ep->d_name,0)) // Returns zero on true 
                vectProcessNameList.push_back(string(ep->d_name)) ;
        }

        closedir (dp);
    }

    return vectProcessNameList ;
}


vector<string> ListProccesses::GetProcessPathList(){

    vector<string>::iterator it ;

    GetProcessNameList() ;

    for(it=vectProcessNameList.begin(); it!=vectProcessNameList.end() ; it++)
    {
        vectProcessPathList.push_back("/proc/" + *it) ;
    }

    return vectProcessPathList ;
}


vector<string> ListProccesses::GetProcessCmdList(){

    vector<string>::iterator it ;
    fstream cmdFile ;
    string cmd ;

    for(it=vectProcessPathList.begin(); it!=vectProcessPathList.end() ; it++)
    {
        cmdFile.open(*it + "/cmdline") ;
        assert(cmdFile.is_open()) ;
        cmdFile >> cmd ;
        cmdFile.close() ;
        cout << cmd <<endl ;
        vectProcessCmdList.push_back(cmd) ;
    }

    return vectProcessCmdList ;
}

vector<string> ListProccesses::GetProcessExecList(){

    vector<string>::iterator it ;
    fstream cmdFile ;
    string LinkPath ;
    char* FullPath ;
   

    FullPath = (char*) malloc(PATH_MAX) ;

    for(it=vectProcessPathList.begin(); it!=vectProcessPathList.end() ; it++)
    {
        LinkPath = *it + "/exe" ;
        realpath(LinkPath.c_str(),FullPath) ;
        vectProcessExecList.push_back(string(FullPath)) ;
    }

    free(FullPath) ;

    return vectProcessExecList ;
}

vector<tstrProcess> ListProccesses::GetDataStructure(){
    tstrProcess proc ;   
    
    /* Start Filling the Process List*/
    GetProcessPathList() ;
    GetProcessCmdList()  ;
    GetProcessExecList() ;



    for(int i=0 ; i < vectProcessNameList.size() ; i++){
        proc.id  = vectProcessNameList.at(i) ;
        proc.cmd = vectProcessCmdList.at(i) ;
        proc.exe = vectProcessExecList.at(i) ;
        vectProcessList.push_back(proc) ; 
    }

    return vectProcessList ;
}




