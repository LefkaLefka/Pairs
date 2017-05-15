#include <string>
#include <list>
#include <iostream>
#include <stdlib.h>
#include "GameData.h"

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
	// Control array	
	//int controlArray[4][3];
	int** controlArray;
	bool staredtGame = false;
	bool checkWin() 
	{
		if (this->countOfGuessed == this->COUNT_OF_GAME_IMAGES)
		{
			return true;
		}
		return false;
	}
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
			// index -> [i][j]
			int buff = Math::Floor(i / 3.0);
			this->controlArray[buff][i - 3 * buff] = temp[i];
		}
		this->countOfGuessed = 0;
	}
	int** getControlArray()
	{
		return this->controlArray;
	}
	std::string* getPathImagesInGames()
	{
		return this->pathImagesInGame;
	}
	struct _resultClick click(String^ objectNumber)
	{		
		// IF STARTED GAME
		if (this->staredtGame)
		{
			// IF FIRST CLICK ON IMAGE
			if (this->openedImage == -1)
			{
				this->openedImage = Convert::ToInt16(objectNumber);
				int ic = Math::Floor(this->openedImage / 3.0);
				int jc = this->openedImage - 3 * ic;
				// If we click on empty image
				if (this->controlArray[ic][jc] == -1) 
				{
					// Nothing to show
					resultClick = { -1, -1, false, false, 0 };
					this->openedImage = -1;
					return resultClick;
				}
				// Show only first image
				resultClick = { this->openedImage, -1, true, false, 0 };
				return resultClick;
			}
			// IF SECOND CLICK
			else
			{
				int index = Convert::ToInt16(objectNumber);
				// If not one and the same pictures
				if (index != this->openedImage)
				{
					// INDEX -> [I][J]
					// Previus image indexes
					int ip = Math::Floor(this->openedImage / 3.0);
					int jp = this->openedImage - 3 * ip;
					// Current image indexes
					int ic = Math::Floor(index / 3.0);
					int	jc = index - 3 * ic;
					// Check if previous image = current image
					if (this->controlArray[ip][jp] == this->controlArray[ic][jc])
					{
						// Show first and second image

						// Delete images
						//this->controlArray[ip][jp] = -1;
						//this->controlArray[ic][jc] = -1;

						resultClick = { this->openedImage, index, true, true, 0 };
						this->openedImage = -1;
						this->countOfGuessed++;
						return resultClick;
					}
					// Check if previous image != current image
					else
					{						
						// Show first and second image to 5 second
						resultClick = { this->openedImage, index, true, true, 5 };
						this->openedImage = -1;
						return resultClick;
					}
				}
			}
		}
		else
		{
			// Nothing to show
			resultClick = { -1, -1, false, false, 0 };
			return resultClick;
		}
	}
private:
	// All images in directory
	std::string* pathImagesArray;
	// Path to image in current game
	std::string* pathImagesInGame;
	// Count of images for width
	const int WIDTH_CONTROL_ARRAY = 3;
	// Count of images for height
	const int HEIGHT_CONTROL_ARRAY = 4;
	// Count of image in game
	const int COUNT_OF_GAME_IMAGES = 6;
	int COUNT_OF_ALL_IMAGES;
	int openedImage = -1;
	// Result for showing in UI
	_resultClick resultClick;
	// Count of guessed image. When game start we don't guessed any image -> 0
	int countOfGuessed = 0;
	// Convert String^ -> std::string
	void MarshalString(String^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
	// Condition for delete non-unique value
	static bool condition(int a, int b)
	{
		return (a == b);
	}
};