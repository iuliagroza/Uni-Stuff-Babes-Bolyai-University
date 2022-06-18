#pragma once
#include <vector>
#include "Castle.h"
#include <memory>
#include <string>

class SaveFileStrategy
{
protected:
	std::string filename;
	std::vector<Castle> castles;

public:
	SaveFileStrategy(const std::string& _filename, const std::vector<Castle>& _castles) : filename{ _filename }, castles { _castles } {}
	std::string getFilename() { return this->filename; }
	virtual void saveFile() const = 0;
	virtual ~SaveFileStrategy() {}
};

class SaveFileAsCSVStrategy : public SaveFileStrategy
{
public:
	SaveFileAsCSVStrategy(const std::string& filename, const std::vector<Castle>& castles) : SaveFileStrategy{ filename, castles } {}
	void saveFile() const override;
};

class SaveFileAsHTMLStrategy : public SaveFileStrategy
{
public:
	SaveFileAsHTMLStrategy(const std::string& filename, const std::vector<Castle>& castles) : SaveFileStrategy{ filename, castles } {}
	void saveFile() const override;

private:
	std::string composeHeader() const;
	std::string composeBody() const;
	std::string composeFooter() const;
};

class SaveFileAsXMLStrategy : public SaveFileStrategy
{
public:
	SaveFileAsXMLStrategy(const std::string& filename, const std::vector<Castle>& castles) : SaveFileStrategy{ filename,castles } {}
	void saveFile() const override;	// TO DO
};

// Factory Method
enum FileType
{
	CSV,
	HTML,
	XML
};

class CreateStrategy
{
public:
	virtual std::unique_ptr<SaveFileStrategy> create(FileType fileType, const std::string& filename, const std::vector<Castle>& castles);
};