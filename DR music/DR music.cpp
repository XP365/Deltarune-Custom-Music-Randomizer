#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
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

	if (!filesystem::exists("config.txt")) {
		ofstream file("config.txt");
		cout << "Enter the path to your DELTARUNE installation: ";
		cin >> deltarune_path;
		deltarune_path = deltarune_path  + "/mus";
		file << deltarune_path;
		file.close();
	}
	else {
		cout << "DELTARUNE path detected!" << endl;
		deltarune_path = ".";
	}


	while (mainLoop == true)
	{
		cout << "Enter the numebr of the song(s) you want to randomise. Type exit to proceed." << endl
			<< "1. Black Knife" << endl
			<< "2. Its TV Time!" << endl
			<< "3. Hammer Of Justice" << endl;
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
		else if (input == "exit") {
			mainLoop = false;
			path = ".";
		}
		else {
			cout << "Error: Invalid Input";
		}
		//Getting the ogg files and adding them to a array
		if (path != ".")
		{
			for (auto const& it : std::filesystem::directory_iterator{ path }) {
				if (it.path().extension().string() != ".ogg") continue;
				oggs.push_back(it.path().string());
			}
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
	}
	
	
	
	ShellExecute(NULL, L"open", L"D:\\SteamLibrary\\steamapps\\common\\DELTARUNE\\DELTARUNE.exe", NULL, NULL, SW_SHOWDEFAULT);
	cout << "Running DELTARUNE: ";
	this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}
