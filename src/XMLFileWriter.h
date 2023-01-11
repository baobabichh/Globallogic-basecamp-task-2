#pragma once

#include "XMLFileStructure.h"
#include "FileInfo.h"
#include <QtXml/qdom.h>


// Class that opens XML file, and write fileinfo to this file like in "XMLFileStructure.h".
class XMLFileWriter 
{
public:

	XMLFileWriter();

	// Opens file by filepath. When open file all inside gets removed.
	// Creates root element.
	XMLFileWriter(const QString& filepath);

	virtual ~XMLFileWriter() = default;

	// Opens file by filepath. When open file all inside gets removed.
	// Creates root element.
	void open(const QString& path);

	// Add fileinfo to XML file.
	void add(const FileInfo& file);

	// Saevs all changes to file on hard drive.
	void save();

	// Closes XML file.
	void close();

	// Clears buffer that was made while constructiong document.
	void clear();

private:

	// XMl file.
	QFile m_file;

	// Stram connected to m_file. Used to write to file.
	QTextStream m_stream;

	// Constructor of XML tree.
	QDomDocument m_document;

	// Root element of XML tree.
	QDomElement m_rootElement;
};
