#include "Song.h"
#include <Windows.h>
#include <shellapi.h>
#include "Utils.h"
#include <iostream>
#include <vector>

using namespace std;

Song::Song(): title(""), artist(""), duration(Duration()), source("") {}

Song::Song(const std::string& artist, const std::string& title, const Duration& duration, const std::string& source)
{
	this->artist = artist;
	this->title = title;
	this->duration = duration;
	this->source = source;
}

bool Song::operator==(const Song & s)
{
	return (this->artist == s.artist && this->title == s.title);
}

void Song::play()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getSource().c_str(), NULL, SW_SHOWMAXIMIZED);
}

istream & operator>>(istream & is, Song & s)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 4) // make sure all the starship data was valid
		return is;

	s.artist = tokens[0];
	s.title = tokens[1];

	// get duration
	vector<string> durationTokens = tokenize(tokens[2], ':');
	if (durationTokens.size() != 2)
		return is;
	s.duration = Duration{ stod(durationTokens[0]), stod(durationTokens[1]) };

	s.source = tokens[3];

	return is;

}

ostream & operator<<(ostream & os, const Song & s)
{
	os << s.artist << "," << s.title << "," << s.duration.getMinutes() << ":" << s.duration.getSeconds() << "," << s.source << "\n";
	return os;
}
