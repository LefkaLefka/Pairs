#pragma once
#include "Game.h";
#include <string>

namespace Pairs {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  startToolStripMenuItem;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	// Count of images for width
	private: int WIDTH_AMOUNT_OF_IMAGES = 3;
	// Count of images for height
	private: int HEIGHT_AMOUNT_OF_IMAGES = 4;
	// Margin between images
	private: int INDENTATION_BETWEEN_IMAGES = 6;
	// Count of images in window
	private: int AMOUNT_OF_IMAGES = 12;
	// Images array
	private: array <PictureBox^, 1>^ images = gcnew array <PictureBox^, 1>(AMOUNT_OF_IMAGES);
	// Start of image position
	private: int START_X = 12;
	private: int START_Y = 28;
	// Size of image
	private: int WIDTH_OF_IMAGE = 100;
	private: int HEIGHT_OF_IMAGE = 100;
	// 
	private: Game* game = new Game();



	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->startToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->startToolStripMenuItem,
					this->exitToolStripMenuItem, this->aboutToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(336, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// startToolStripMenuItem
			// 
			this->startToolStripMenuItem->Name = L"startToolStripMenuItem";
			this->startToolStripMenuItem->Size = System::Drawing::Size(76, 20);
			this->startToolStripMenuItem->Text = L"Start game";
			this->startToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::startToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 449);
			this->progressBar1->Margin = System::Windows::Forms::Padding(0);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(312, 23);
			this->progressBar1->TabIndex = 2;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ClientSize = System::Drawing::Size(336, 481);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pairs";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		Image^ bg = Image::FromFile(Environment::CurrentDirectory + "\\img\\system\\bg.png");
		for (int i = 0; i < HEIGHT_AMOUNT_OF_IMAGES; ++i)
		{
			for (int j = 0; j < WIDTH_AMOUNT_OF_IMAGES; ++j)
			{
				// Transform: (i, j)->index
				int index = i * WIDTH_AMOUNT_OF_IMAGES + j;
				// Create each image
				images[index] = gcnew PictureBox();
				// Set propetrties:
				images[index]->Location = Point(START_X + j * (WIDTH_OF_IMAGE + INDENTATION_BETWEEN_IMAGES),
												START_Y + i * (HEIGHT_OF_IMAGE + INDENTATION_BETWEEN_IMAGES));
				images[index]->Height = HEIGHT_OF_IMAGE;
				images[index]->Width = WIDTH_OF_IMAGE;
				images[index]->Image = bg;
				images[index]->Tag = index;
				images[index]->Click += gcnew System::EventHandler(&MyForm::image_Click);
				this->Controls->Add(images[index]);
			}
		}
	}
	static System::Void image_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		PictureBox^ image = (PictureBox^)sender;
		MessageBox::Show(Convert::ToString(image->Tag));
		/////////////////////////////////////////////////
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		Application::Exit();
	}
	private: System::Void startToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		game->startGame();
		int** controlArray = game->getControlArray();
		std::string* pathImagesInGame = game->getPathImagesInGames();

		for (int i = 0; i < HEIGHT_AMOUNT_OF_IMAGES; ++i)
		{
			for (int j = 0; j < WIDTH_AMOUNT_OF_IMAGES; ++j)
			{
				// Transform: (i, j)->index
				int index = i * WIDTH_AMOUNT_OF_IMAGES + j;
				String^ path = gcnew String(pathImagesInGame[controlArray[i][j]].c_str());
				Image^ img = Image::FromFile(path);
				images[index]->Image = img;
			}
		}
	}
};
}
