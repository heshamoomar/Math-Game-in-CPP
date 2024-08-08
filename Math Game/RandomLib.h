#pragma once
#include<iostream>

namespace rnd
{
	int RandomNumber(int min, int max) {
		return min + rand() % (max - min + 1);
	}

	float add_tax_on_bill(float bill, float tax) {
		if (bill < 0 || tax < 0) {
			throw std::invalid_argument("Bill and tax rate must be non-negative");
		}
		return bill * (1 + tax / 100);
	}

	float time_in_seconds(float days, float hours, float minutes, float seconds) {
		if (days < 0 || hours < 0 || minutes < 0 || seconds < 0) {
			throw std::invalid_argument("time must be non-negative");
		}
		float sum = 0;
		sum += days * 60 * 60 * 24;
		sum += hours * 60 * 60;
		sum += minutes * 60;
		sum += seconds;
		return sum;
	}

	void time(int seconds) {
		int secondsPerDay = 24 * 60 * 60;
		int secondsPerHour = 60 * 60;
		int secondsPerMinute = 60;

		int days = (int)floor(seconds / secondsPerDay);
		seconds %= secondsPerDay;

		int hours = (int)floor(seconds / secondsPerHour);
		seconds %= secondsPerHour;

		int minutes = (int)floor(seconds / secondsPerMinute);
		seconds %= secondsPerMinute;

		std::cout << days << ":" << hours << ":" << minutes << ":" << seconds << std::endl;
	}

	std::string Password_Generator(int length) {
		std::string Password = "";
		int x;
		for (int i = 0; i < length; i++)
		{
			x = RandomNumber(0, 3);
			switch (x)
			{
			case 0:
				Password += char(RandomNumber(97, 122)); // lowercase letters
				break;
			case 1:
				Password += char(RandomNumber(65, 90)); // uppercase letters
				break;
			case 2:
				Password += char(RandomNumber(33, 47)); // special characters
				break;
			case 3:
				Password += char(RandomNumber(48, 57)); // digits
				break;
			default:
				break;
			}
		}
		return Password;
	}


	std::string encrypt_string(std::string s1, short offset) {
		std::string s2 = "";
		for (int i = 0; i < s1.length(); i++)
		{
			s2 += char(s1[i] + offset);
		}

		std::cout << "Original: " << s1 << std::endl;
		std::cout << "Encrypted: " << s2 << std::endl;
		std::cout << "Decrypted: " << s1 << std::endl;
		return s2;
	}

	const int ASCII_A = 65;
	const int ASCII_Z = 90;
	const int KEY_LENGTH = 16;

	std::string GenerateKey() {
		std::string Key;
		for (int i = 1; i <= KEY_LENGTH; i++)
		{
			Key += char(RandomNumber(ASCII_A, ASCII_Z)); // Generate uppercase letters
			if (i % 4 == 0 && i != KEY_LENGTH)
				Key += '-'; // Insert hyphens after every 4 characters, except at the end
		}
		return Key;
	}

	void Key_Generator(int numOfKeys) {
		std::string Key;
		for (int i = 0; i < numOfKeys; i++)
		{
			Key = GenerateKey();
			std::cout << "Key [" << i << "]: " << Key << std::endl;
		}
	}


}

