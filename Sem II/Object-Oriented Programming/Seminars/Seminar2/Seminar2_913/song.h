#pragma once

#include <string>

class song
{
private:
	std::string artist;
	std::string title;
	double duration;
	std::string link;

public:
	song() :artist{ "" }, title{ "" }, duration{ 0.0 }, link{ "" }{}
	song(const std::string& artist, const std::string& title, const double duration, const std::string& link);
	std::string getArtist() const { return this->artist; }
	std::string getTitle() const { return this->title; }
	double getDuration() const { return this->duration; }
	std::string getLink() const { return this->link; }
	void setArtist(const std::string& artist) { this->artist = artist; }
};

