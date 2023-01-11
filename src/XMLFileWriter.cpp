#include "XMLFileWriter.h"

XMLFileWriter::XMLFileWriter()
	: m_stream(&m_file)
{
}

XMLFileWriter::XMLFileWriter(const QString& filepath)
	: m_file(filepath), m_stream(&m_file)
{
	m_file.open(QFile::WriteOnly | QFile::Truncate);

	m_rootElement = m_document.createElement(QString::fromStdWString(ROOT_TAG));
	m_document.appendChild(m_rootElement);
}

void XMLFileWriter::open(const QString& path)
{
	m_file.setFileName(path);
	m_file.open(QFile::WriteOnly | QFile::Truncate);

	m_rootElement = m_document.createElement(QString::fromStdWString(ROOT_TAG));
	m_document.appendChild(m_rootElement);
}


void XMLFileWriter::add(const FileInfo& file)
{
    QDomElement fileElement = m_document.createElement("file");
    m_rootElement.appendChild(fileElement);

	// Name.
    QDomElement nameElement = m_document.createElement("name");
	fileElement.appendChild(nameElement);
    QDomText pathName = m_document.createTextNode(file.name);
    nameElement.appendChild(pathName);

	// Path.
    QDomElement pathElement = m_document.createElement("path");
	fileElement.appendChild(pathElement);
    QDomText pathText = m_document.createTextNode(file.path);
    pathElement.appendChild(pathText);

	// Size.
    QDomElement sizeElement = m_document.createElement("size");
	fileElement.appendChild(sizeElement);
    QDomText sizeText = m_document.createTextNode(QString::number(file.size));
    sizeElement.appendChild(sizeText);

	// Date.
    QDomElement dateElement = m_document.createElement("date");
	fileElement.appendChild(dateElement);
    QDomText dateText = m_document.createTextNode(file.date.toQString());
    dateElement.appendChild(dateText);

}

void XMLFileWriter::save()
{
	m_stream << m_document.toString();
    m_stream.flush();
}

void XMLFileWriter::close()
{
	m_file.close();
}

void XMLFileWriter::clear()
{
	m_document.clear();
	m_rootElement.clear();
}
