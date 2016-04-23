#pragma once 

#include "Core\TempestSharedHeader.h"


/*
Макросы для использования:
__FILE__ полное имя текущего файла кода
__func__ имя функции
__LINE__ номер строки в файле
*/


namespace Tempest {
	//namespace Core {
		class Logger{
		private:
			static Logger* mLogger;

			//Core::Chrono* mChrono;

			Logger();
			Logger(const Logger&);
			~Logger();
		public:
			ofstream mLogFile;
			string mFileName;
			static stringstream* mInfo;

			static Logger* get();
		};







		class TraceLogger {
		public:
			TraceLogger(const char* funcName);
			~TraceLogger();

		private:
			static string mIndent;
			const char* mFuncName;
		};




	//}
}


#define LOG(x) Logger::get()->mLogFile.open(Logger::get()->mFileName, ios::app); \
	Logger::get()->mLogFile << x << endl;	\
	Logger::get()->mLogFile.close();


#define LOG_TRACE TraceLogger traceLogger(__FUNCTION__);

#define INFO(x)  Logger::mInfo->str(""); Logger::mInfo->clear(); *Logger::mInfo << x; \
	MessageBox(NULL, Logger::mInfo->str().c_str(), "TEMPEST Info", MB_OK | MB_ICONEXCLAMATION);


