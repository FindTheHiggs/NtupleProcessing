#include "CNtupAnaSkeleton.h"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void print_help(){
  cout << __FILE__ << " "<<endl;
  cout << __FILE__ << " Please provide : "<<endl;
  cout << __FILE__ << " -i : name of input file to analyse "<< endl;
  cout << __FILE__ << " -o : name of file in which output histos should go "<< endl;
  cout << __FILE__ << " -t : name of tree to analyse ; "<< endl;
}

int main(int _argc, char **_argv) {

  string tInFileName="";
  string tTreeName=""; 
  string tOutFileName="";

  int optind(1);
  while ((optind < _argc)) {
    if(_argv[optind][0]!='-'){++optind; continue;}
    std::string sw = _argv[optind];
    if (sw == "-i") { ++optind; tInFileName=_argv[optind];}
    else if (sw == "-t") { ++optind; tTreeName=_argv[optind];}    
    else if (sw == "-o") { ++optind; tOutFileName=_argv[optind];}
    else if (sw == "-h") { ++optind; print_help(); return 0;}   
    else { 
      cout << __FILE__ << " arg not known : "<< _argv[optind] << endl;
      print_help();
      return 1;
    }
    ++optind;
  }

  if ( "" == tInFileName || "" == tTreeName || "" == tOutFileName ) {
    cout << "missing arg" << endl;
    print_help();    
  }
    
  CNtupAnaSkeleton tNtupAnaSkeleton(tInFileName,tTreeName,tOutFileName);
  tNtupAnaSkeleton.fAnalyse();

  return 0;

}
