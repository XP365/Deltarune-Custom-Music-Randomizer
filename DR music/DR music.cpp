#undef UNICODE
#undef _UNICODE

#include <fstream>
#include <iostream>
#include <filesystem>
#include <random>
#include <chrono>
#include <thread>
#include <windows.h>
#include <string>
#include <sstream>
#include <shobjidl.h> 
using namespace std;

struct presetData
{
	string songName;
	string oggName;
};
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool isValid = true;
string input;
vector<string> oggs;
string songName;
vector<presetData> loadedEntries;
random_device rd;
mt19937 rng(rd());
bool mainLoop = true;
string deltarune_path;
string deltarune_root_path;
string output_path;
string path;


const vector<string> songNames = {
"Black Knife", "Its TV Time", "Hammer Of Justice", "Burning Eyes", "A DARK ZONE",
"From Now On", "The Seccond Sanctuary", "The Third Sanctuary", "Dark Sanctuary", "The World Revolving", "BIG SHOT"
, "GUARDIAN", "ANOTHER HIM", "Beginning", "School", "Susie", "The Door", "Cliffs",
"The Chase", "The Legend", "Lancer", "Rude Buster", "Empty Town", "Weird Birds", "Field of Hopes and Dreams"
, "Fanfare", "Lantern", "I'm Very Bad", "Checker Dance", "Quiet Autumn", "Scarlet Forest",
	"Thrash Machine","Vs Lancer","Basement","Imminent Death","Vs Susie","Card Castle","Rouxls Kaard","April 2012"
	, "Hip Shop", "Gallery", "Chaos King", "Darkness Falls", "The Circus", "Friendship", "THE HOLY", "Your Power",
	"A Town Called Hometown", "You Can Always Come Home", "Don't Forget", "Before The Story"
};
const vector<string> paths = {
	"./Black Knife", "./Its TV Time", "./Hammer Of Justice", "./Burning Eyes", "./A DARK ZONE",
	"./From Now On", "./The Second Sanctuary", "./The Third Sanctuary", "./Dark Sanctuary",
	"./GUARDIAN", "./The World Revolving", "./BIG SHOT", "./ANOTHER HIM", "./Beginning", "./School", "./Susie",
	"./The Door", "./Cliffs", "./The Chase", "./The Legend", "./Lancer", "./Rude Buster"
	, "./Empty Town", "./Weird Birds", "./Field of Hopes and Dreams",
	"./Fanfare", "./Lantern", "./I'm Very Bad", "./Checker Dance", "./Quiet Autumn", "./Scarlet Forest", "./Thrash Machine"
	, "./Vs Lancer", "./Basement", "./Imminent Death", "./Vs Susie", "./Card Castle", "./Rouxls Kaard", "./April 2012", "./Hip Shop"
	, "./Gallery", "./Chaos King", "./Darkness Falls", "./The Circus", "./Friendship", "./THE HOLY", "./Your Power", "./A Town Called Hometown"
	, "./You Can Always Come Home", "./Don't Forget", "./Before The Story"
};
vector<string> output_paths = {
	"/mus/knight.ogg",
	"/mus/tenna_battle.ogg",
	"/mus/ch4_extra_boss.ogg",
	"/mus/nightmare_boss_heavy.ogg",
	"/mus/pumpkin_boss.ogg",
	"/mus/ch4_battle",
	"/mus/church_zone2_alt_longer_test.ogg",
	"/mus/church_zone3.ogg",
	"/mus/church_wip.ogg",
	"/mus/titan_battle.ogg",
	"/mus/joker.ogg",
	"/mus/spamton_neo_mix_ex_wip.ogg",
	"/mus/AUDIO_ANOTHERHIM.ogg",
	"/mus/mus_introcar.ogg",
	"/mus/mus_school.ogg",
	"/mus/s_neo.ogg",
	"/mus/creepydoor.ogg",
	"/mus/creepylandscape.ogg",
	"/mus/creepychase.ogg",
	"/mus/legend.ogg",
	"/mus/lancer.ogg",
	"/mus/battle.ogg",
	"/mus/castletown_empty.ogg",
	"/mus/bird.ogg",
	"/mus/field_of_hopes.ogg",
	"/mus/fanfare.ogg",
	"/mus/shop1.ogg",
	"/mus/lancer_susie.ogg",
	"/mus/checkers.ogg",
	"/mus/quiet_autumn.ogg",
	"/mus/forest.ogg",
	"/mus/thrashmachine.ogg",
	"/mus/lancerfight.ogg",
	"/mus/basement.ogg",
	"/mus/tense.ogg",
	"/mus/vs_susie.ogg",
	"/mus/card_castle.ogg",
	"/mus/ruruskaado.ogg",
	"/mus/april_2012.ogg",
	"/mus/hip_shop.ogg",
	"/mus/GALLERY.ogg",
	"/mus/kingboss.ogg",
	"/mus/AUDIO_DARKNESS.ogg",
	"/mus/prejoker.ogg",
	"/mus/friendship.ogg",
	"/mus/THE_HOLY.ogg",
	"/mus/snd_usefountain.ogg",
	"/mus/town.ogg",
	"/mus/home.ogg",
	"/mus/dontforget.ogg",
	"/mus/AUDIO_STORY.ogg"
};

IFileOpenDialog* pfd = NULL;
HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));


bool copyOggs(const string& path, const string& output_path, mt19937& rng, string songName, bool isImport = false)
{
	vector<string> oggsVector;

	if (path != "." && filesystem::exists(path))
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		if (isImport)
		{
			cout << "Imported Song: " << songName << endl;
		}
		else
			cout << "Successfully Randomised Song: " << songName << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return true;
	}
	else if (isValid == false) {
		isValid = true;
	}
	oggsVector.clear();
	if (filesystem::exists(path))
	{
		for (auto const& it : filesystem::directory_iterator{ path }) {
			if (it.path().extension() == ".ogg") {
				oggsVector.push_back(it.path().string());
			}
		}
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout << "Error: No folder found for the song: " << songName << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return false;
	}

	if (oggsVector.empty()) {
		cout << "No .ogg files detected for: " << songName << endl;
		return false;
	}

	uniform_int_distribution<> dist(0, oggsVector.size() - 1);
	int randomOgg = dist(rng);

	ifstream f1(oggsVector[randomOgg], ios::binary);
	ofstream f2(output_path, ios::binary);

	if (!f1.is_open()) {
		cout << "Error: Could not open file to copy: " << oggsVector[randomOgg] << endl;
	}
	if (!f2.is_open()) {
		cout << "Error: Could not open destination file: " << output_path << endl;
	}

	f2 << f1.rdbuf();

	f1.close();
	f2.close();
	oggs = oggsVector;
	return true;
}

wstring OpenFileDialog() {
	std::wstring path;

	if (SUCCEEDED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) {
		IFileDialog* pFileDialog = nullptr;
		if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pFileDialog)))) {
			if (SUCCEEDED(pFileDialog->Show(nullptr))) {
				IShellItem* pItem = nullptr;
				if (SUCCEEDED(pFileDialog->GetResult(&pItem))) {
					PWSTR pszFilePath = nullptr;
					if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath))) {
						path = pszFilePath;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileDialog->Release();
		}
		CoUninitialize();
	}

	return path; // Empty if nothing selected or failed
}


string WStringToString(const std::wstring& wstr) {
	if (wstr.empty()) return {};

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1,
		nullptr, 0, nullptr, nullptr);
	std::string result(size_needed - 1, 0); // exclude null terminator
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1,
		&result[0], size_needed, nullptr, nullptr);
	return result;
}


bool receiveInput()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Enter all to randomise all avalible songs and proceed to deltarune" << endl
		<< "Enter exit to close and proceed to deltarune" << endl
		<< "Enter Help for help" << endl;
	cout << endl << "> ";
	cin >> input;

	if (input == "all" || input == "All" || input == "ALL") {
		for (int i = 0; i < output_paths.size(); i++) {
			string songNameAll = songNames[i];
			string pathAll = paths[i];
			string outputPathAll = deltarune_root_path + output_paths[i]; // Make sure full path
			copyOggs(pathAll, outputPathAll, rng, songNameAll, false);
		}
		mainLoop = false;
		path = ".";
		return true; // skip the rest of the loop for "all"
	}
	else if (input == "exit" || input == "Exit" || input == "EXIT") {
		mainLoop = false;
		path = ".";
		return true;
	}
	else if (input == "help" || input == "Help" || input == "HELP")
	{
		isValid = false;
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		cout << "Welcome to the DELTARUNE music tool!" << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "To use this tool, create a folder in the app's directory folder (Where the .exe is) with the name of the song." << endl
			<< "Then place any .ogg files you want to randomise for that song in the folder (name them anything)." << endl
			<< "Typing 'Songs' will give a list of all avalible songs" << endl
			<< "You can then type the number of the song you want to randomize, if you just want to randomize a singe song" << endl
			<< "Typing 'All' will randomize all songs you have folders and files for and open Deltarune." << endl
			<< "Typing 'Exit' will open Deltarune and close the program" << endl << endl;
		return true;
	}
	else if (input == "songs" || input == "Songs" || input == "SONGS" || input == "song" || input == "Song" || input == "SONG")
	{
		for (int i = 0; i < songNames.size(); ++i) {
			cout << i + 1 << ". " << songNames[i] << endl;
		}
		isValid = false;
		return true;
	}
	else if (input == "import" || input == "Import" || input == "IMPORT" || input == "inport" || input == "Inport" || input == "INPORT")
	{
		wstring selectedPathW = OpenFileDialog();
		string importOggPath = WStringToString(selectedPathW);

		if (importOggPath.empty()) {
			cout << "Import cancelled or no file selected." << endl;
			return true;
		}

		filesystem::path sourcePath(importOggPath);
		if (sourcePath.extension() != ".ogg") {
			cout << "Error: Selected file is not an .ogg audio file." << endl;
			return false;
		}

		cout << "Enter the song number to add the .ogg to (or 999 to abort import): ";
		int songInput;
		cin >> songInput;

		if (songInput == 999) {
			cout << "Import aborted." << endl;
			return true;
		}

		if (songInput < 0 || songInput >= (int)songNames.size()) {
			cout << "Invalid song number." << endl;
			return false;
		}

		filesystem::path destFolder(paths[songInput]);
		filesystem::path destFile = destFolder / sourcePath.filename();

		try {
			filesystem::create_directories(destFolder);
			filesystem::copy_file(sourcePath, destFile, filesystem::copy_options::overwrite_existing);

			// Update global variables so later calls use this selection
			path = paths[songInput];
			songName = songNames[songInput];
			output_path = deltarune_root_path + output_paths[songInput];
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			cout << "Imported " << sourcePath.filename().string() << " to " << destFolder.string() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			return true;
		}
		catch (const filesystem::filesystem_error& e) {
			cout << "Error copying file: " << e.what() << endl;
			return false;
		}                                 
	}
	else {
		// Single selection songs
		int songIndex = -1;
		try {
			songIndex = stoi(input) - 1;
		}
		catch (const std::invalid_argument& e) {
			cout << "Please enter a number." << endl;
			return false;
		}

		if (songIndex >= 0 && songIndex < (int)songNames.size()) {
			songName = songNames[songIndex];
			path = paths[songIndex];
			output_path = deltarune_root_path + output_paths[songIndex];
			return true;
		}
		else {
			cout << "Invalid selection." << endl;
			return false;
		}
		copyOggs(path, output_path, rng, songName, false);
	}
}




int main() {


	//Test Preset Code
	/*vector<presetData> entries = {
	{"Black Knife", "Everyname.ogg"}
	};

	ofstream outFile("preset.txt");
	if (!outFile) {
		cerr << "Failed to open preset.txt for writing!" << endl;
		return 1;  // or exit(1);
	}
	for (const auto& e : entries) {
		outFile << e.songName << " " << e.oggName << endl;
	}
	outFile.close();

	//Reading test
	ifstream inFile("preset.txt");

	if (!inFile) {
		cerr << "Could not open preset.txt for reading!" << endl;
		return 1;
	}

	presetData temp;
	while (inFile >> temp.songName >> temp.oggName) {
		loadedEntries.push_back(temp);
	}
	for (const auto& entry : loadedEntries) {
		cout << "Song: " << entry.songName << ", OGG: " << entry.oggName << endl;
	}

	inFile.close();*/


	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	vector<string> drives = { "C", "D" };
	bool found = false;

	for (const string& drive : drives) {
		string exePath = drive + ":/SteamLibrary/steamapps/common/DELTARUNE/DELTARUNE.exe";
		if (filesystem::exists(exePath)) {
			cout << "DELTARUNE path detected!" << endl << endl;
			deltarune_path = exePath;
			deltarune_root_path = drive + ":/SteamLibrary/steamapps/common/DELTARUNE";
			found = true;
			break;
		}
	}

	if (!found) {
		if (!filesystem::exists("config.txt")) {
			ofstream file("config.txt");
			cout << "Enter the path to your DELTARUNE installation: ";
			cin >> deltarune_path;
			file << deltarune_path;
			file.close();
		}
		else {
			cout << "Please enter your deltarune path:" << endl << endl;
			cin >> deltarune_path;
		}
	}

	for (int i = 0; i < output_paths.size(); i++)
	{
		output_paths[i] = deltarune_root_path + output_paths[i];
	}

	while (mainLoop == true)
	{
		isValid = true;
		receiveInput();
	}


	char cmdLine[] = "D:\\SteamLibrary\\steamapps\\common\\DELTARUNE\\DELTARUNE.exe";

	CreateProcessA(NULL,cmdLine,NULL,NULL,FALSE,0,NULL,"D:\\SteamLibrary\\steamapps\\common\\DELTARUNE",&si,&pi);


	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "Running DELTARUNE: " << endl;
	this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}