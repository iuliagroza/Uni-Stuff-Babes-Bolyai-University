#pragma once
#include "Song.h"
#include <vector>

class Repository
{
private:
	std::vector<Song> songs;
	std::string filename;

public:
	/*
		Constructor with parameters. 
		Initializes an object of type repository, by reading data from the given file.
		Throws: FileException - if the file cannot be opened.
	*/
	Repository(const std::string& filename);

	/*
		Adds a song to the repository.
		Input: s - Song.
		Output: the song is added to the repository.
		Throws: FileException - if the file cannot be opened.
				DuplicateSongException - if there is another song with the same artist and title.
	*/
	void addSong(const Song& s);

	/*
		Removes the song with the given artist and title.
		Throws: InexistenSongException - if there are no songs with the given artist and title.
	*/
	void removeSong(const Song& s);

	/*
		Finds a song, by artist and title.
		Input: artist, title - string
		Output: the song that was found, or an "empty" song (all fields empty and duration 0), if nothing was found.
	*/
	Song findByArtistAndTitle(const std::string& artist, const std::string& title) const;

	std::vector<Song> getSongs() const { return songs; }

private:
	void readFromFile();
	void writeToFile();
};