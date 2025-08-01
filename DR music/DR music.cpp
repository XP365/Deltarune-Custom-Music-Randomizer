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
	string output_path;
	vector<string> oggs;
	int randomOgg = 0;
	string dummyString;
	string path;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	bool isValid = true;
	string songName;

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
		}
		else {
			cout << "DELTARUNE path detected!" << endl << endl;
			deltarune_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/DELTARUNE.exe";
		}
	}
	else {
		cout << "DELTARUNE path detected!" << endl << endl;
		deltarune_path = "C:/SteamLibrary/steamapps/common/DELTARUNE/DELTARUNE.exe";
	}

	while (mainLoop == true)
	{
		cout << "Enter the number of the song(s) you want to randomise. Type 'all' to do all, or 'exit' to proceed." << endl
			<< "1. Black Knife" << endl
			<< "2. Its TV Time!" << endl
			<< "3. Burning Eyes" << endl
			<< "4. Hammer Of Justice" << endl
			<< "5. A DARK ZONE" << endl
			<< "6. From Now On (Battle 2)" << endl
			<< "7. The Second Sanctuary" << endl
			<< "8. The Third Sanctuary" << endl
			<< "9. Dark Sanctuary" << endl
			<< "10. GUARDIAN" << endl;

		cin >> input;

		if (input == "1") {
			songName = "Black Knife";
			path = "./Black Knife";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/knight.ogg";
		}
		else if (input == "2") {
			songName = "Its TV Time";
			path = "./Its TV Time";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/tenna_battle.ogg";
		}
		else if (input == "3") {
			songName = "Hammer Of Justice";
			path = "./Hammer Of Justice";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/ch4_extra_boss.ogg";
		}
		else if (input == "4") {
			songName = "Burning Eyes";
			path = "./Burning Eyes";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/nightmare_boss_heavy.ogg";
		}
		else if (input == "5") {
			songName = "A DARK ZONE";
			path = "./A DARK ZONE";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/pumpkin_boss.ogg";
		}
		else if (input == "6") {
			songName = "From Now On";
			path = "./From Now On";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/ch4_battle";
		}
		else if (input == "7") {
			songName = "The Seccond Sanctuary";
			path = "./The Second Sanctuary";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/church_zone2_alt_longer_test,ogg";
		}
		else if (input == "8") {
			songName = "The Third Sanctuary";
			path = "./The Third Sanctuary";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/church_zone3.ogg";
		}
		else if (input == "9") {
			songName = "Dark Sanctuary";
			path = "./Dark Sanctuary";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/church_wip.ogg";
		}
		else if (input == "10") {
			songName = "GUARDIAN";
			path = "./GUARDIAN";
			output_path = "D:/SteamLibrary/steamapps/common/DELTARUNE/mus/titan_battle.ogg";
		}
		else if (input == "all") {
			vector<string> songNames = {
				"Black Knife", "Its TV Time", "Hammer Of Justice", "Burning Eyes", "A DARK ZONE",
				"From Now On", "The Seccond Sanctuary", "The Third Sanctuary", "Dark Sanctuary", "GUARDIAN"
			};
			vector<string> paths = {
				"./Black Knife", "./Its TV Time", "./Hammer Of Justice", "./Burning Eyes", "./A DARK ZONE",
				"./From Now On", "./The Second Sanctuary", "./The Third Sanctuary", "./Dark Sanctuary", "./GUARDIAN"
			};
			vector<string> output_paths = {
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/knight.ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/tenna_battle.ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/ch4_extra_boss.ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/nightmare_boss_heavy.ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/pumpkin_boss.ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/ch4_battle",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/church_zone2_alt_longer_test,ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/church_zone3.ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/church_wip.ogg",
				"D:/SteamLibrary/steamapps/common/DELTARUNE/mus/titan_battle.ogg"
			};

			for (int i = 0; i < songNames.size(); i++) {
				string songNameAll = songNames[i];
				string pathAll = paths[i];
				string outputPathAll = output_paths[i];
				vector<string> oggsAll;

				if (!filesystem::exists(pathAll)) {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					cout << "Error: No folder for song: " << songNameAll << endl;
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					continue;
				}

				for (auto const& it : std::filesystem::directory_iterator{ pathAll }) {
					if (it.path().extension().string() != ".ogg") continue;
					oggsAll.push_back(it.path().string());
				}

				if (!oggsAll.empty()) {
					int randomIndex = rand() % oggsAll.size();
					ifstream f1(oggsAll[randomIndex], ios::binary);
					ofstream f2(outputPathAll, ios::binary);

					if (!f1.is_open() || !f2.is_open()) {
						cerr << "Error: Cannot copy for song: " << songNameAll << endl;
						continue;
					}

					f2 << f1.rdbuf();
					f1.close();
					f2.close();

					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
					cout << "Randomized: " << songNameAll << endl;
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				else {
					cout << "No .ogg files found for: " << songNameAll << endl;
				}
			}
			continue; // skip the rest of the loop for "all"
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
			oggs.clear();
			for (auto const& it : std::filesystem::directory_iterator{ path }) {
				if (it.path().extension().string() != ".ogg") continue;
				oggs.push_back(it.path().string());
			}
			if (!oggs.empty())
			{
				randomOgg = rand() % (oggs.size());
				ifstream f1(oggs[randomOgg], ios::binary);
				ofstream f2(output_path, ios::binary);

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
			}
			else {
				cout << "No .ogg files detected for selected song" << endl << endl;
			}
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			cout << "Successfully Randomised Song: " << songName << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else if (isValid == true && input != "exit") {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout << "Error: No folder detected for selected song" << endl;
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

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "Running DELTARUNE: " << endl;
	this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}
