#include "Repository.h"
#include <string>
#include <fstream>
#include "Utils.h"
#include "RepositoryExceptions.h"

using namespace std;

Repository::Repository(const std::string& filename)
{
	this->filename = filename;
	this->readFromFile();
}

void Repository::addSong(const Song& s)
{
	Song s1{};
	try
	{
		s1 = this->findByArtistAndTitle(s.getArtist(), s.getTitle());
		throw DuplicateSongException();
	}
	catch (InexistenSongException&) {}
	this->songs.push_back(s);
	this->writeToFile();
}

void Repository::removeSong(const Song& s)
{
	auto it = find(this->songs.begin(), this->songs.end(), s);
	if (it == this->songs.end())
		throw InexistenSongException{};
	this->songs.erase(it);
	this->writeToFile();
}

Song Repository::findByArtistAndTitle(const std::string& artist, const std::string& title) const
{
	for (auto s: this->songs)
	{
		if (s.getArtist() == artist && s.getTitle() == title)
			return s;
	}

	throw InexistenSongException{};
}

void Repository::readFromFile()
{
	ifstream file(this->filename);

	if (!file.is_open())
		throw FileException("The file could not be opened!");

	Song s;
	while (file >> s)
		this->songs.push_back(s);
	
	file.close();
}

void Repository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto s : this->songs)
	{
		file << s;
	}
	
	file.close();
}