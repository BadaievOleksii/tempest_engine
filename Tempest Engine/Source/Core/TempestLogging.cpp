#include "TempestLogging.h"


namespace Tempest {
	//namespace Core {
		Logger* Logger::mLogger = new Logger();
		stringstream* Logger::mInfo = new stringstream();
		//==============================================================================================
		Logger::Logger(){
			char execPath[MAX_PATH];
			GetModuleFileName(NULL, execPath, MAX_PATH);
			string exec(execPath);
			string::size_type pos = exec.find_last_of("\\/");
			exec = exec.substr(0, pos);
			exec.append("\\TempestEngineLog.txt");
			mFileName = exec;

			mLogFile.open(mFileName);
			mLogFile.close();
		}
		//==============================================================================================
		Logger::Logger(const Logger&){

		}
		//==============================================================================================
		Logger::~Logger(){

		}
		//==============================================================================================
		Logger* Logger::get(){
			return mLogger;
		}
		//==============================================================================================
		//==============================================================================================
		//==============================================================================================
		string TraceLogger::mIndent;
		//==============================================================================================
		TraceLogger::TraceLogger(const char* funcName) {
			mFuncName = funcName;
			LOG(mIndent << "ENTERING " << mFuncName << std::endl)

			mIndent.append("  ");
		}
		//==============================================================================================
		TraceLogger::~TraceLogger() {
			mIndent.resize(mIndent.length() - 2);
			LOG(mIndent << "LEAVING  " << mFuncName << std::endl)
		}
		//==============================================================================================
	//}
}
