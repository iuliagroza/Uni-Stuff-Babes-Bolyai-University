#include "SaveFileStrategy.h"
#include <fstream>
#include <exception>
#include <sstream>

void SaveFileAsCSVStrategy::saveFile() const
{
	std::ofstream f{ this->filename };
	if (!f.is_open())
		throw std::runtime_error{ "Could not save file!" };

	for (auto& c : this->castles)
		f << c.getDescription() << "," << c.getLocation() << "," << c.getPrice() << "\n";
	f.close();
}

void SaveFileAsHTMLStrategy::saveFile() const
{
	std::string s = this->composeHeader() + this->composeBody() + this->composeFooter();
	std::ofstream f{ this->filename };
	if (!f.is_open())
		throw std::runtime_error{ "Could not save file!" };

	f << s;
	f.close();
}

std::string SaveFileAsHTMLStrategy::composeHeader() const
{
	std::stringstream s;
	s << "<!DOCTYPE html>\n";
	s << "<html>\n";
	s << "<head>\n";
	s << "<title>Castles</title>\n";
	s << "</head>\n";
	return s.str();
}

std::string SaveFileAsHTMLStrategy::composeBody() const
{
	std::stringstream s;
	s << "<body>\n";
	s << "<table border = \"1\">\n";
	for (auto& c : this->castles)
	{
		s << "<tr>\n";
		s << "<td>" << c.getDescription() << "</td>\n";
		s << "<td>" << c.getLocation() << "</td>\n";
		s << "<td>" << c.getPrice() << "</td>\n";
		s << "</tr>\n";
	}
	s << "</table>\n";
	s << "</body>\n";

	return s.str();

}

std::string SaveFileAsHTMLStrategy::composeFooter() const
{
	std::stringstream s;
	s << "<html>\n";

	return s.str();
}


std::unique_ptr<SaveFileStrategy> CreateStrategy::create(FileType fileType, const std::string& filename, const std::vector<Castle>& castles)
{
	switch (fileType)
	{
	case CSV:
		return std::make_unique<SaveFileAsCSVStrategy>(filename, castles);
	case HTML:
		return std::make_unique<SaveFileAsHTMLStrategy>(filename, castles);
	case XML:
		return std::make_unique<SaveFileAsHTMLStrategy>(filename, castles);
	default:
		return nullptr;
	}
}
