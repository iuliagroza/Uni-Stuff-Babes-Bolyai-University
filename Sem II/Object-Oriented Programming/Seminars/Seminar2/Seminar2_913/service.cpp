#include "service.h"


service::service(repo& rep): r{rep}
{
}

void service::add(std::string name, std::string artist, double duration, std::string link)
{
	song s{ name, artist, duration, link };
	r.add(s);
}
