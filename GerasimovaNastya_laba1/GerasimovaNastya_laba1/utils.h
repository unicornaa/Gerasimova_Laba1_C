#pragma once
#include <iostream>
#include <string>

#define Save(in, str) getline(in>>std::ws, str); cerr << str << endl;
#define Load(in, str) getline(in>>std::ws, str);

using namespace std;

class redirect_output_wrapper
{
	ostream& stream;
	streambuf* const old_buf;
public:
	redirect_output_wrapper(ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(ostream& dest) {
		stream.rdbuf(dest.rdbuf());
	}
};

template <typename T>
T CorrectInput(T min, T max) {
	T x;
	while ((std::cin >> x).fail() || x < min || x > max)
	{
		std::cin.clear();//сбрасываем биты ошибок и буфер
		std::cin.ignore(100000, '\n');//сбрасываем до какого-то символа
		std::cout << "Type again (" << min << "-" << max << "):";
	}
	cerr << x << endl;
	return x;
}
template <typename T>
T Correct(T max, T min = 1)
{
	T x;
	while ((std::cin >> x).fail() || x < min || x > max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Please, try again: ";
	}
	std::cerr << x << std::endl;
	return x;
}



template <typename T>

T inputT(T value) {

	T state;
	while (1) {
		if (!(cin >> state)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Try again: ";
		}
		else if (state >= 0) {
			cerr << state << endl;
			return state;
		}
		else cout << "enter value more than 0: ";
	}
	cerr << state << endl;
	return state;
}
