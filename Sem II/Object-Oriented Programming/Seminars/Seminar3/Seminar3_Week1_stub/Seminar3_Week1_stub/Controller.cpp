#include "Controller.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

void Controller::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->repo.addSong(s);
}

void Controller::addSongToPlaylist(const Song& song)
{
	// TODO
}

void Controller::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	// get all the songs from the repository
	DynamicVector<Song> songs = this->repo.getSongs();

	// use STL algorithms and lambdas
}