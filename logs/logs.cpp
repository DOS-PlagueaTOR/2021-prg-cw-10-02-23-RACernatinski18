#include <iostream>
#include <string>
#include <fstream>

using namespace std;

fstream logFile;

enum SEVERITY
{
	CRITICAL = 0,
	ERROR = 1,
	WARNING = 2,
	INFO = 3,
	DEBUG = 4
};

struct LOG
{
	string Date;
	string Time;
	SEVERITY severity;
	string message;

	string toString();
};

string severityToString(SEVERITY severity) 
{
	switch (severity)
	{
	case CRITICAL:
		return "CRITICAL";
	case ERROR:
		return "ERROR";
	case WARNING:
		return "WARNING";
	case INFO:
		return "INFO";
	default:
		return "UNKNOWN";
	}
}
string LOG::toString()
{
	return Date + " " + Time + " " + severityToString(severity) + " " + message;
}

void log(SEVERITY severity, string message)
{
	LOG logEntry
	{
		"2021-02-23",
		"08:40:00",
		severity,
		message
	};

	logFile << logEntry.toString() << endl;
}


bool openLogFile(string filename)
{
	logFile.open(filename, ios::out | ios::app);
	return logFile.is_open();

}

void closeLogFile()
{
	logFile.close();
}


int main() 
{
	if (openLogFile("mylog.txt"))
	{
		log(SEVERITY::INFO, "Program startup complete");

		int a;
		string choice;
		cin >> choice;
		
		try
		{
			a = stoi(choice);
		}
		catch (const std::exception& ex)
		{
			log(SEVERITY::CRITICAL, ex.what());
		}

		

		log(SEVERITY::INFO, "Program finish");
		closeLogFile();
	}
}