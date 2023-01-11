#pragma once

// File for XML file defines.

// Node name for root
#define ROOT_TAG L"root"

// Node name for each file.
#define FILE_TAG L"file"

// Node name for every filename node in file node.
#define NAME_TAG L"name"

// Node name for every path node in file node.
#define PATH_TAG L"path"

// Node name for every size node in file node.
#define SIZE_TAG L"size"

// Node name for every date node in file node.
#define DATE_TAG L"date"

// XML file structure.

/*
<root>
	<file>
		<name>file.txt</name>
		<path>folder/file.txt</path>
		<size>120</size>
		<date>20.01.2004 14:59:59</date>
	</file>
</root>

*/