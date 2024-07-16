#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>



using namespace std;
using namespace filesystem;

class FileManager {
public:
	void showDirectoryContents() {

		for (const auto& entry : directory_iterator(".")) {
			cout << entry.path().filename() << endl;
		}
		cout << "Disc contents is shown successfully.\n" << endl;

	}

	// Перегруженная функция для показа содержимого папки
	void showDirectoryContents(const string& directoryPath) {
		for (const auto& entry : directory_iterator(directoryPath)) {
			if (!is_directory(entry.status())) {
				cout << entry.path().filename() << endl;
			}
		}
		cout << "Directory " << "\"" << directoryPath << "\"" << " contents\n"
			<< "are shown successfully.\n" << endl;

	}
	void createFile(const string& fileName) {

		ofstream file(fileName);
		if (exists(fileName)) {
			cout << "File " << fileName << " created successfully." << endl;
		}
		else {
			cout << "File " << fileName << " creation failed." << endl;
		}
		if (file.is_open()) {
			file << "Text for example/Текст для примера\n";
			file.close();
			cout << "File content written successfully." << endl;
		}
		else {
			cout << "Unable to open file." << endl;
		}

	}

	void createFolder(const string& folderName) {
		create_directory(folderName);

	}

	void deleteItem(const string& folderName) {
		remove_all(folderName);

	}

	void renameItem(const string& oldName, const string& newName) {
		rename(oldName, newName);

	}

	void copyItem(const string& source, const string& destination) {
		copy_file(source, destination, copy_options::update_existing);

	}

	size_t calculateFileSize(const string& fileName) {
		return file_size(fileName);

	}

	void searchByMask(const string& rootPath, const string& mask) {
		vector<string> foundFiles;

		for (const auto& entry : recursive_directory_iterator(rootPath)) {
			if (entry.is_regular_file() && entry.path().filename().string().find(mask) != string::npos) {
				foundFiles.push_back(entry.path().string());
			}
		}

		cout << "Found files matching the mask '" << mask << "':" << endl;
		for (const auto& file : foundFiles) {
			cout << file << endl;
		}

	}
};

int main() {

	SetConsoleOutputCP(1251);

	FileManager fileManager;

	try {
		//Показ содержимого папки (включая скрытые папки и файлы)
		fileManager.showDirectoryContents();

		//Создание папки и файла
		fileManager.createFolder("OldFolder");
		fileManager.createFolder("CopyFaileExample");//Папка для последующего копирования файла
		fileManager.createFile("source.txt");
		fileManager.createFile("source2.txt");
		fileManager.showDirectoryContents();

		//Переименование папки
		fileManager.renameItem("OldFolder", "NewFolder");
		fileManager.renameItem("source2.txt", "source3.txt");
		fileManager.showDirectoryContents();

		//Удаление папки и файла
		fileManager.deleteItem("NewFolder");
		fileManager.deleteItem("source3.txt");
		fileManager.showDirectoryContents();

		//Копирование содержимиого одного файла в другой в пределах одной папки
		fileManager.copyItem("source.txt", "destination.txt");

		//Копирование файла в пределах корневой папки и из одной папки в другую
		fileManager.copyItem("source.txt", "CopyFaileExample\\source.txt");
		fileManager.copyItem("source.txt", "CopyFaileExample\\destination.txt");
		fileManager.showDirectoryContents("CopyFaileExample");

		//Удаление файла
		fileManager.deleteItem("CopyFaileExample\\destination.txt");
		fileManager.showDirectoryContents("CopyFaileExample");

		//Размер файла
		cout << "Size of file: " << fileManager.calculateFileSize("source.txt") << " bytes" << endl;

		//Поиск по маске
		fileManager.searchByMask(".", ".txt");

	}
	catch (const filesystem_error& ex) {
		cerr << "Filesystem error: " << ex.what();
	}
	catch (const exception& ex) {
		cerr << "Standard exception: " << ex.what() << endl;
	}
	catch (...) {
		cerr << "Unknown exception occurred" << endl;
	}

}