#pragma once
#include <cmath>
#include<numbers>
#include<string>
#include<iostream>

namespace Geometry
{
	float area_of_triangle(float side1, float side2) {	//	by 2 sides
		return side1 * side2;
	}

	float area_of_triangle_by_diagonal(float side, float diagonal) {	//	by side and diagonal 
		return (float)(side * sqrt(pow(diagonal, 2) - pow(side, 2)));
	}

	float area_of_triangle_by_base_height(float base, float height) {	//	by side and diagonal 
		return base / 2 * height;
	}

	float area_of_circle(float radius) {
		return (float)ceil(std::numbers::pi * pow(radius, 2));
	}

	float area_of_circle_by_diameter(float diameter) {
		return (float)(std::numbers::pi * pow(diameter, 2) / 4);
	}

	float area_of_circle_inscribed_in_square(float area_of_square) {
		return (float)(std::numbers::pi * pow(area_of_square, 2) / 4);
	}

	float area_of_circle_isosceles_triangle(float a, float b) {
		return (float)(std::numbers::pi * pow(b, 2) / 4 * ((2 * a - b) / (2 * a + b)));
	}

}

namespace NumOps
{
	int readNumber(std::string message) {
		int num;
		std::cout << message;
		std::cin >> num;
		while (std::cin.fail())
		{
			//	user didn't input a number
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Please enter a number: ";
			std::cin >> num;
		}
		return num;
	}

	int readPositiveNumber(std::string Message) {
		int num;
		do
		{
			std::cout << Message;
			std::cin >> num;

		} while (num <= 0);
		return num;
	}


	long long fact(int number) {
		if (number < 0) {
			throw std::invalid_argument("Factorial is not defined for negative numbers");
		}

		long long fact = 1;
		for (int i = 1; i <= number; i++)
		{
			fact *= i;
		}
		return fact;
	}

	float MySqrt(float Number) {
		return (float)pow(Number, 0.5);
	}

	float getFractionPart(float n) {
		return n - int(n);
	}

	int myCeil(float Number) {
		if (Number >= 0 && getFractionPart(Number) > 0) {
			return int(Number) + 1;
		}
		else if (Number < 0 && getFractionPart(Number) != 0) {
			return int(Number);
		}
		return int(Number);
	}

	bool isPrime(int n) {
		for (int i = 2; i <= sqrt(n); i++)
		{
			if (n % i == 0)
				return false;
		}
		return true;
	}

	void print_primes_till_N() {
		std::cout << "Enter N: ";
		int n; std::cin >> n;
		std::cout << "Primes from 1 till " << n << ": ";
		for (int i = 2; i <= n; i++)
		{
			if (isPrime(i))
				std::cout << i << ' ';
		}std::cout << std::endl;
	}

}

