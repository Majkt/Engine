#ifndef MAJKT_MMGDEBUG_H_
#define MAJKT_MMGDEBUG_H_
#include <string>

namespace majkt {

class Debug{

public:
 
const bool DEBUGGING_ON = true;
const std::string appName ="MMgApi.MmgDebug";
//
static void wr(std::string s); // REGUALER WORD

 static void wr(std::string key, std::string s);//
 static void wrTs(std::string s); // creates time statments  of which logs occcur 


//void wrErr(); 
//ujhk,mbngyhjvnmgjnvb mstatic void wrErr(std::string s);  //  This is used to long error files with in the engine 





};




}

#endif; // MAJKT_MMGDEBUG_H_