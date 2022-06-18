#pragma once
#include "FilePlaylist.h"
#include <string>

class CSVPlaylist: public FilePlaylist
{
public:
	/*
		Writes the playlist to file.
		Throws: FileException - if it cannot write.
	*/
	void writeToFile() override;

	/*
		Displays the playlist using Microsof Excel.
	*/
	void displayPlaylist() const override;
};

