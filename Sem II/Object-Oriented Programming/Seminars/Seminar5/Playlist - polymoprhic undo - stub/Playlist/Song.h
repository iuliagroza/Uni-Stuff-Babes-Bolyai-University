#pragma once
#include <iostream>

class Duration
{
private:
	double minutes;
	double seconds;
public:
	Duration() : minutes(0), seconds(0) {}
	Duration(double min, double sec) : minutes(min), seconds(sec) {}

	double getMinutes() const { return minutes; }
	double getSeconds() const { return seconds; }
	void setMinutes(double min) { minutes = min; }
	void getSeconds(double sec) { seconds = sec; }
};

class Song
{
private:
	std::string title;
	std::string artist;
	Duration duration;
	std::string source;		// youtube Link

public:
	// default constructor for a song
	Song();

	// constructor with parameters
	Song(const std::string& artist, const std::string& title, const Duration& duration, const std::string& source);
	
	std::string getTitle() const { return title; }
	std::string getArtist() const { return artist; }
	Duration getDuration() const { return duration; }
	std::string getSource() const { return source; }

	bool operator==(const Song& s);

	// Plays the current song: the page corresponding to the source link is opened in a browser.
	void play();

	friend std::istream& operator>>(std::istream& is, Song& s);
	friend std::ostream& operator<<(std::ostream& os, const Song& s);
};

