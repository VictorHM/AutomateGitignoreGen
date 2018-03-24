#include "FileDealer.h"
#include <string>

/* Takes the values of each set element and saves them in the file.
	Each line of the file will contain just one element, in order to make
	the reading of the file easier in a later stage.
	
	Returns True if the writing of the file was succesful. False if
	not (does not distinguish between types of errors.*/
bool WriteSetToFile(std::string filename, std::set<std::string> extensionSet)
{
	bool isWriteOk = true;

	std::ofstream writefile;
	writefile.open(filename);
	if (writefile && writefile.is_open())
	{
		for(auto& itset : extensionSet)
		{
			if (itset != "")
			{
				writefile << itset;
				writefile << "\n";
			}
		}

		if (writefile.fail())
		{
			isWriteOk = false;
		}
		writefile.close();
	}
	return isWriteOk;
}

/* Reads the specified file in filename and saves each line of it
	into each element of the set. It returns a copy of the set.*/
std::set<std::string> ReadSetFromFile(std::string filename)
{
	std::set<std::string> extSetRead;
	std::ifstream readfile (filename);

	std::string line;

	if (readfile.is_open())
	{
		while (std::getline(readfile, line))
		{
			extSetRead.insert(line);
		}
		readfile.close();
	}
	return extSetRead;
}
