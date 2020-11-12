#include "logger.h"
#include "json.h"

int main()
{
	AcCoRD::Logger::Initialise("logs/debug.txt");

	LOG_INFO("AcCoRD Binary To Json Conversion Tool");
}