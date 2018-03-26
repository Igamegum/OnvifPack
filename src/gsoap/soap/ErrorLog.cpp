#include <ErrorLog.h>
#include <wsseapi.h>
#include <wsaapi.h>
#include <string>


void processEventLog(char *fileName, uint lineNo, FILE *fp, const char *argList, ...) {


	char sLogParamString[MAX_MSG_LEN]; 
	memset(sLogParamString,0x00,MAX_MSG_LEN);
	char sLogBuffer[MAX_MSG_LEN];
	memset(sLogBuffer,0x00,MAX_MSG_LEN);
	va_list vErrorList;
	uint iStrLen;

	time_t lTime;
	struct tm tm; 
	time(&lTime);
	localtime_r(&lTime, &tm);

	tm.tm_mon += 1;
	tm.tm_year += 1900;


	strcpy(sLogParamString,"[%4d-%02d-%02d %02d:%02d:%02d] [%s] [%d] {");
	iStrLen = sprintf(sLogBuffer,
		sLogParamString,
		tm.tm_year,
		tm.tm_mon,
		tm.tm_mday,
		tm.tm_hour,
		tm.tm_min,
		tm.tm_sec,
		fileName,
		lineNo
	);

	va_start(vErrorList, argList);
	iStrLen += vsprintf((sLogBuffer+iStrLen),argList,vErrorList);
	va_end(vErrorList);
	iStrLen += sprintf(sLogBuffer+iStrLen,"}");
	sLogBuffer[iStrLen] = '\n';
	sLogBuffer[iStrLen + 1] = '\0';
	
	fprintf(fp, "%s",sLogBuffer);
	fflush(fp);
}


void PrintErr(struct soap* _psoap) {

	fflush(stdout);
	const std::string filename = __FILE__;
	processEventLog(const_cast<char *>(filename.c_str()), __LINE__, stdout, "error:%d faultstring:%s faultcode:%s faultsubcode:%s faultdetail:%s", _psoap->error, 
	*soap_faultstring(_psoap), *soap_faultcode(_psoap),*soap_faultsubcode(_psoap), *soap_faultdetail(_psoap));
}
