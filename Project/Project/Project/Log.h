#pragma once

#include <string>
#include <fstream>

class Log {
public:
	Log(const std::string &filename);
	~Log();

	void Write(const std::string &output);

private:
	std::ofstream m_stream;
};
