#pragma once
#include "LongInteger.h"
#include <msclr/marshal_cppstd.h>
#include <cstdlib>
#include <ctime>

namespace CW {

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
	private: System::Windows::Forms::Button^ btn_calculate;
	protected:

	private: System::Windows::Forms::TextBox^ txt_number1;
	private: System::Windows::Forms::TextBox^ txt_number2;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ cmb_operation;
	private: System::Windows::Forms::TextBox^ txt_result;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ btn_generate;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ txt_remainder;


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
			this->btn_calculate = (gcnew System::Windows::Forms::Button());
			this->txt_number1 = (gcnew System::Windows::Forms::TextBox());
			this->txt_number2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->cmb_operation = (gcnew System::Windows::Forms::ComboBox());
			this->txt_result = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btn_generate = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->txt_remainder = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// btn_calculate
			// 
			this->btn_calculate->Location = System::Drawing::Point(15, 137);
			this->btn_calculate->Name = L"btn_calculate";
			this->btn_calculate->Size = System::Drawing::Size(206, 34);
			this->btn_calculate->TabIndex = 0;
			this->btn_calculate->Text = L"calculate";
			this->btn_calculate->UseVisualStyleBackColor = true;
			this->btn_calculate->Click += gcnew System::EventHandler(this, &MyForm::btn_calculate_Click);
			// 
			// txt_number1
			// 
			this->txt_number1->Location = System::Drawing::Point(69, 18);
			this->txt_number1->Name = L"txt_number1";
			this->txt_number1->Size = System::Drawing::Size(152, 20);
			this->txt_number1->TabIndex = 1;
			// 
			// txt_number2
			// 
			this->txt_number2->Location = System::Drawing::Point(69, 87);
			this->txt_number2->Name = L"txt_number2";
			this->txt_number2->Size = System::Drawing::Size(152, 20);
			this->txt_number2->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"number 1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 90);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(51, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"number 2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 56);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(51, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"operation";
			// 
			// cmb_operation
			// 
			this->cmb_operation->FormattingEnabled = true;
			this->cmb_operation->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"+", L"-", L"*", L"/" });
			this->cmb_operation->Location = System::Drawing::Point(70, 53);
			this->cmb_operation->Name = L"cmb_operation";
			this->cmb_operation->Size = System::Drawing::Size(48, 21);
			this->cmb_operation->TabIndex = 6;
			this->cmb_operation->Text = L"+";
			// 
			// txt_result
			// 
			this->txt_result->Enabled = false;
			this->txt_result->Location = System::Drawing::Point(70, 190);
			this->txt_result->Name = L"txt_result";
			this->txt_result->Size = System::Drawing::Size(152, 20);
			this->txt_result->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 193);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"result";
			// 
			// btn_generate
			// 
			this->btn_generate->Location = System::Drawing::Point(264, 18);
			this->btn_generate->Name = L"btn_generate";
			this->btn_generate->Size = System::Drawing::Size(67, 73);
			this->btn_generate->TabIndex = 9;
			this->btn_generate->Text = L"generate random nums";
			this->btn_generate->UseVisualStyleBackColor = true;
			this->btn_generate->Click += gcnew System::EventHandler(this, &MyForm::btn_generate_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(12, 219);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(53, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"remainder";
			this->label5->Visible = false;
			// 
			// txt_remainder
			// 
			this->txt_remainder->Enabled = false;
			this->txt_remainder->Location = System::Drawing::Point(70, 216);
			this->txt_remainder->Name = L"txt_remainder";
			this->txt_remainder->Size = System::Drawing::Size(152, 20);
			this->txt_remainder->TabIndex = 10;
			this->txt_remainder->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(349, 280);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->txt_remainder);
			this->Controls->Add(this->btn_generate);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->txt_result);
			this->Controls->Add(this->cmb_operation);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txt_number2);
			this->Controls->Add(this->txt_number1);
			this->Controls->Add(this->btn_calculate);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void btn_calculate_Click(System::Object^ sender, System::EventArgs^ e) {
		LongInteger num1 = msclr::interop::marshal_as<std::string>(txt_number1->Text);
		LongInteger num2 = msclr::interop::marshal_as<std::string>(txt_number2->Text);

		LongInteger result;
		std::string operation = msclr::interop::marshal_as<std::string>(cmb_operation->Text);
		if (operation == "+")
		{
			result = num1 + num2;

			label5->Visible = false;
			txt_remainder->Visible = false;
		}
		else if (operation == "-")
		{
			result = num1 - num2;

			label5->Visible = false;
			txt_remainder->Visible = false;
		}
		else if (operation == "*")
		{
			result = num1 * num2;

			label5->Visible = false;
			txt_remainder->Visible = false;
		}
		else if (operation == "/")
		{
			result = num1 / num2;

			label5->Visible = true;
			txt_remainder->Visible = true;

			txt_remainder->Text = msclr::interop::marshal_as<String^>((num1 % num2).toString());
		}

		txt_result->Text = msclr::interop::marshal_as<String^>(result.toString());


	}

	std::string generateRandomNumberAsString(int minLength, int maxLength) {
		std::string result;

		int length = minLength + rand() % (maxLength - minLength + 1);
		result += '1' + rand() % 9;
		length--;

		for (int i = 0; i < length; ++i) {
			char digit = '0' + rand() % 10;
			result += digit;
		}

		return result;
	}

	private: System::Void btn_generate_Click(System::Object^ sender, System::EventArgs^ e) {
		int min_length = 10;
		int max_length = 20;

		srand(static_cast<unsigned int>(time(nullptr)));
		std::string n1 = generateRandomNumberAsString(min_length, max_length);
		std::string n2 = generateRandomNumberAsString(min_length, max_length);

		txt_number1->Text = msclr::interop::marshal_as<String^>(n1);
		txt_number2->Text = msclr::interop::marshal_as<String^>(n2);

	}
};
}
