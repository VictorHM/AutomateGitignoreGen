/* Utility to get the extensions of the files generated
   after the compilation to add those to .gitignore file*/

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator>

#include "header\FileDealer.h"
namespace fs = std::experimental::filesystem;
using namespace std;
//TODO: GENERAL
/* Se ha de chequear si hay un archivo de extensiones ya guardado
	si existe, se lee de el y se comparan las extensiones con las
	que se descubren nuevas
	Si no existe, se crea con todas las extensiones que se necesiten.
	DONE.
	SE HACE EN BASE A LOS PARAMETROS DE ENTRADA. SI HAY DOS, ES QUE
	UNO ES EL ARCHIVO DESDE EL QUE LEER. SI SOLO UNO, ES EL PATH Y HA DE
	CREARSE EL ARCHIVO.

	DEBE: recibir un parametro minimo. Esto es el path donde ha de ir buscando las
	extensiones a valorar.*/
void CreateSetExtensions(const fs::path& pathToShow, std::set<std::string>& extensions);
std::set<std::string> DiffSetFromComparision(std::set<std::string> origSet, std::set<std::string> newSet);
bool CreateGitFileFromSet(fs::path path, std::set<std::string> finalSet);

int main(int argc, char *argv[])
{
	char intro;
	std::set<std::string> extns;
	fs::path path;
	//Show HELP to user
	if (argc == 1)
	{
		//TODO: print general usage of software
		cout << "No command line arguments. \n";
		std::cin >> intro;
	}
	//First pass. Gather the extensions and save them in a file for comparison
	else if (argc == 2)
	{
		//A path to extract extensions
		path = argv[1];

		CreateSetExtensions(path, extns);
		if (extns.empty())
		{
			cout << "Something went wrong. No extensions were detected.\n";
		}
		else
		{
			cout << "Extensions detected:\n";
			for (auto& elem : extns)
			{
				cout << "          " << elem << endl;
			}

			if (!WriteSetToFile("extensionsBefore.txt", extns))
			{
				cout << "ERROR: Something went wrong! File not written properly!!\n";
			}
			else
			{
				cout << "Extensions saved in file extensionsBefore.txt\n";
			}
		}
		std::cin >> intro;
	}

	//If there is three parameters, create new set of extensions, read and compare with the file
	//and create .gitignore file
	else if (argc == 3)
	{
		cout << "Reading extensions file and preparing to create .gitignore\n";
		path = argv[2]; //path is now in second position
		std::string filename = argv[1];

		//TODO: compare the new created set with the set recovered from the file
		std::set<std::string> newset, diffSet;
		CreateSetExtensions(path, newset);
		extns = ReadSetFromFile(filename);
		diffSet = DiffSetFromComparision(extns, newset);

		if (diffSet.empty())
		{
			cout << "No difference between the extension sets. No file will be created\n";
		}
		else
		{
			//Create the gitignore file
			CreateGitFileFromSet(path, diffSet);
		}
	}

	//Read the file with extensions and compare it with newfound extensions, if any
}

/* It takes a string reference that contains the path where it has to run, a set reference
	where the extensions will be stored and the level of deepness (this will be deprecated).
	The reason for receiving reference to the set is because the function is recursive.
	If it uses a set inside it, each time the function is called, a new set will be created 
	and destroyed, so some of the information will not be saved.*/
void CreateSetExtensions(const fs::path& pathToShow, std::set<std::string>& extensions)
{
	if (fs::exists(pathToShow))
	{
		for (const auto& entry : fs::directory_iterator(pathToShow))
		{
			//.git directory will be ignored because it is not relevant for the functionality
			if (entry.path().filename() == ".git")
				continue;
			else {

				fs::path filename = entry.path().filename();
				fs::path extn = entry.path().extension();
				if (fs::is_directory(entry.status()))
				{
					CreateSetExtensions(entry, extensions);
				}
				else if (fs::is_regular_file(entry.status()) && extensions.count(extn.string()) == 0)
				{
					//TODO: do a Try-Catch here to detect exceptions in the insertion

					extensions.insert(extn.string());
				}
			}
		}
	}
}

std::set<std::string> DiffSetFromComparision(std::set<std::string> origSet, std::set<std::string> newSet)
{
	std::set<std::string> diffSet;
	auto it = newSet.find("");
	//First element could be empty string. TODO: find the reason for this and solve it more elegantly
	if (it != newSet.end())
	{
		newSet.erase(it);
	}
	//Comparing both sets and find the differencies
	std::set_difference(origSet.begin(), origSet.end(), newSet.begin(), newSet.end(), std::inserter(diffSet, diffSet.begin()));

	return diffSet;
}

bool CreateGitFileFromSet(fs::path path, std::set<std::string> finalSet)
{
	path.append(".gitignore");
	std::string gitfile = path.string();
	if (!WriteSetToFile(gitfile, finalSet))
	{
		cout << "ERROR: Something went wrong! .gitignore file not written properly!!\n";
	}
	else
	{
		cout << ".gitignore file created properly\n";
	}
	return false;
}
