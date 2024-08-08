#pragma once
#include<iostream>
#include <fstream>
#include<string>

namespace FileIO
{

	std::ofstream create_file(std::string FileName, std::string FileExtention) {
		std::string fullFileName;

		if (FileExtention[0] != '.') {
			fullFileName += FileName + '.' + FileExtention;
		}
		else {
			fullFileName += FileName + FileExtention;
		}

		std::ofstream outFile(fullFileName);
		if (!outFile) {
			std::cerr << "Error creating file: " << fullFileName << std::endl;
		}
		return outFile;
	}

	void create_file(const std::string FileName, const std::string FileExtension, short NumberOfFiles) {
		for (short i = 1; i <= NumberOfFiles; ++i) {
			std::string fullFileName;

			if (FileExtension[0] != '.') {
				fullFileName = FileName + '_' + std::to_string(i) + '.' + FileExtension;
			}
			else {
				fullFileName = FileName + '_' + std::to_string(i) + FileExtension;
			}

			std::ofstream outFile(fullFileName);
			if (!outFile) {
				std::cerr << "Error creating file: " << fullFileName << std::endl;
			}
		}
	}


	//void create_file(std::string FileName, std::string FileExtention) {
	//	if (FileExtention[0] != '.')
	//		std::ofstream outFile(FileName + '.' + FileExtention);
	//	else 
	//		std::ofstream outFile(FileName + FileExtention);
	//}

	//void create_multiple_files(std::string FileName, std::string FileExtention, short NumberOfFiles) {
	//	if (FileExtention[0] != '.') {
	//		for (int i = 1; i <= NumberOfFiles; i++)
	//		{
	//			std::ofstream outFile(FileName + '_' + std::to_string(i) + '.' + FileExtention);
	//		}
	//	}
	//	else {
	//		for (int i = 1; i <= NumberOfFiles; i++)
	//		{
	//			std::ofstream outFile(FileName + '_' + std::to_string(i) + FileExtention);
	//		}
	//	}
	//}

	bool fileExists(const std::string& filename) {	//	Check if File Exists
		std::ifstream file(filename);
		return file.good();
	}

}
