#include <string>
#include <list>
#include <iostream>
#include <stdlib.h>

using namespace System;

using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class Game {
public:
	Game()
	{
		this->setImagesPath();
	}
	~Game() { }
	void setImagesPath()
	{
		array<String^>^ files = System::IO::Directory::GetFiles(System::Environment::CurrentDirectory + "\\img\\content\\", "*.jpg");
		
		this->COUNT_OF_ALL_IMAGES = files->Length;
		this->pathImagesArray = new std::string[this->COUNT_OF_ALL_IMAGES];
		
		this->controlArray = new int*[this->HEIGHT_CONTROL_ARRAY];
		for (int i = 0; i < this->HEIGHT_CONTROL_ARRAY; ++i)
			this->controlArray[i] = new int[this->WIDTH_CONTROL_ARRAY];

		for (int i = 0; i < this->COUNT_OF_ALL_IMAGES; ++i)
		{
			std::string buff("x", files[i]->Length);
			this->MarshalString(files[i], buff);
			this->pathImagesArray[i] = buff;
			//String^ systemstring = gcnew String(this->fileImageList[i].c_str());
			//MessageBox::Show(systemstring);
		}
	}
	void startGame()
	{
		// SELECT IMAGES FOR CURRENT GAME
		// Number of image path in array pathImagesArray
		std::list<int> indexPathImageInGame;
		while (indexPathImageInGame.size() < this->COUNT_OF_GAME_IMAGES)
		{
			// Get random value from range [0..COUNT_OF_ALL_IMAGES]
			indexPathImageInGame.push_back(rand() % this->COUNT_OF_ALL_IMAGES);
			indexPathImageInGame.sort();
			// Delete the same value
			indexPathImageInGame.unique(&Game::condition);
		}
		int index = 0;
		// Path to images for game
		this->pathImagesInGame = new std::string[this->COUNT_OF_GAME_IMAGES];
		for each (int value in indexPathImageInGame)
		{
			this->pathImagesInGame[index] = this->pathImagesArray[int(value)];
			index++;
		}
		// SET CONTROL ARRAY
		int temp[] = { 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5 };
		for (int i = 0; i < this->COUNT_OF_GAME_IMAGES * 2; ++i)
		{
			std::swap(temp[i], temp[rand() % this->COUNT_OF_GAME_IMAGES * 2]);
		}
		for (int i = 0; i < this->COUNT_OF_GAME_IMAGES * 2; ++i)
		{
			int buff = Math::Floor(i / 3.0);
			this->controlArray[buff][i - 3 * buff] = temp[i];
		}
	}
	int** getControlArray()
	{
		return this->controlArray;
	}
	std::string* getPathImagesInGames()
	{
		return this->pathImagesInGame;
	}
private:
	// All images in directory
	std::string* pathImagesArray;
	// Path to image in current game
	std::string* pathImagesInGame;
	// Control array	
	//int controlArray[4][3];
	int** controlArray;
	// Count of images for width
	const int WIDTH_CONTROL_ARRAY = 3;
	// Count of images for height
	const int HEIGHT_CONTROL_ARRAY = 4;
	// Count of image in game
	const int COUNT_OF_GAME_IMAGES = 6;
	int COUNT_OF_ALL_IMAGES;
	void MarshalString(String^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
	static bool condition(int a, int b)
	{
		return (a == b);
	}
};