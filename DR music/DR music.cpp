#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
using namespace std;

int main() {
	//Set random seed to the system time
	srand(time(0));
	bool mainLoop = true;
	string input;
	string deltarune_path;
	vector<string> oggs;
	int randomOgg = 0;
	string dummyString;
	string path;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	bool isValid = true;


	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!filesystem::exists("C:/SteamLibrary/steamapps/common/DELTARUNE/DELTARUNE.exe"))
	{
		if (!filesystem::exists("D:/SteamLibrary/steamapps/common/DELTARUNE/DELTARUNE.exe"))
		{
			if (!filesystem::exists("config.txt")) {
				ofstream file("config.txt");
				cout << "Enter the path to your DELTARUNE installation: ";
				cin >> deltarune_path;
				deltarune_path = deltarune_path + "/mus";
				file << deltarune_path;
				file.close();
			}
			else {
				cout << "DELTARUNE path detected!" << endl << endl;
				deltarune_path = ".";
			}
		} else {
			cout << "DELTARUNE path detected!" << endl << endl;
			deltarune_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/DELTARUNE.exe";
		}
	} else {
		cout << "DELTARUNE path detected!" << endl << endl;
		deltarune_path = "C:/SteamLibrary/steamapps/common/DELTARUNE/DELTARUNE.exe";
	}


	while (mainLoop == true)
	{
		cout << "Enter the numebr of the song(s) you want to randomise. Type exit to proceed." << endl
			<< "1. Black Knife" << endl
			<< "2. Its TV Time!" << endl
			<< "3. Burning Eyes" << endl
			<< "4. Template" << endl
			<< "5. A DARK ZONE" << endl
			<< "6. From Now On (Battle 2)" << endl
			<< "7. The Second Sanctuary" << endl
			<< "8. The Third Sanctuary" << endl
			<< "9. Dark Sanctuary" << endl
			<< "10. GUARDIAN" << endl;
		//< "4. Template" << endl;
		cin >> input;
		if (input == "1")
		{
			path = "./Black Knife";
		} 
		else if (input == "2") {
			path = "./TV Time";
		}
		else if (input == "3") {
			path = "./Hammer Of Justice";
		}
		else if (input == "4") {
			path = "./Burning Eyes";
		}
		else if (input == "5") {
			path = "./A DARK ZONE";
		}
		else if (input == "6") {
			path = "./From Now On";
		}
		else if (input == "7") {
			path = "./The Second Sanctuary";
		}
		else if (input == "8") {
			path = "./The Third Sanctuary";
		}
		else if (input == "9") {
			path = "./Dark Sanctuary";
		}
		else if (input == "10") {
			path = "./GUARDIAN";
		}
		else if (input == "exit") {
			mainLoop = false;
			path = ".";
		}
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout << "Error: Invalid Input" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			isValid = false;
		}
		//Getting the ogg files and adding them to a array
		if (path != "." && filesystem::exists(path))
		{
			for (auto const& it : std::filesystem::directory_iterator{ path }) {
				if (it.path().extension().string() != ".ogg") continue;
				oggs.push_back(it.path().string());
			}
			if (oggs.size() != 0)
			{
				randomOgg = rand() % (oggs.size());
				ifstream f1(oggs[randomOgg], ios::binary);
				ofstream f2("D:/SteamLibrary/steamapps/common/DELTARUNE/mus/knight.ogg", ios::binary);

				if (!f1.is_open()) {
					std::cerr << "Error: Could not open file to copy" << std::endl;
					f1.close();
					return 0;
				}

				if (!f2.is_open()) {
					std::cerr << "Error: Could not open destination file" << std::endl;
					f1.close();
					return 0;
				}
				f2 << f1.rdbuf();
				cout << "Wrote song: " << oggs[randomOgg] << " to Black Knife" << endl << endl;
			}
			else {
				cout << "No .ogg files detected for inputed song" << endl << endl;
			}

			
		}
		else if (isValid == true) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout << "Error: No folder detected for selected song" << endl;
			//This is to make it white for some fucking reason
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else if (isValid == false) {
			isValid = true;
		}
	}
	
	
	
	TCHAR cmdLine[] = _T("D:\\SteamLibrary\\steamapps\\common\\DELTARUNE\\DELTARUNE.exe");

	if (!CreateProcess(
		NULL,
		cmdLine,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		_T("D:\\SteamLibrary\\steamapps\\common\\DELTARUNE"),
		&si,
		&pi
	)) {
		_tprintf(_T("CreateProcess failed (%d).\n"), GetLastError());
		return 1;
	}

	cout << "Running DELTARUNE: " << endl;
	this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}
