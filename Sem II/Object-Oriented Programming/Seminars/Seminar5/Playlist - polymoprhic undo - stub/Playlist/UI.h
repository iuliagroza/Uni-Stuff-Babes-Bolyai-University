#pragma once
#include "Service.h"

class UI
{
private:
	Service& serv;	// reference to the Service (Service cannot be copied!)

public:
	UI(Service& s) : serv(s) {}

	void run();

private:
	static void printMenu();
	static void printRepositoryMenu();
	static void printPlayListMenu();

	void addSongToRepo();
	void removeSongFromRepo();
	void displayAllSongsRepo();
	void addSongToPlaylist();
	void addAllSongsByArtistToPlaylist();
	void savePlaylistToFile();
};

