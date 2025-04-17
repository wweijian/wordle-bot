/* We need input to be in non-canonical mode: 							*/
/* Input is sent character by character, without waiting for Enter.  	*/
/* This is how real-time typing works (e.g., passwords, key listeners). */

#include <string>
#include <iostream>
#include <termios.h> // only works in unix/linux

using namespace std;

string inputAnswer(size_t maxLength)
{
	termios oldt, newt; // decarling two terminal config structs
	string answer;		// copy old settings to new so we can modify
	char c;

	cout << "Enter a 5-Letter word as the answer [hidden]" << endl;
	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &newt);
	while (true)
	{
        c = getchar();
		if (c == '\n' || c == '\r')
		{
            cout << endl;
            break;
        }
		if (c == 127 || c == '\b') // Handle backspace (127 on Unix) and delete
		{
			answer.pop_back();
			cout <<"\b \b";
		}
		else if (answer.length() < maxLength && isprint(c))
		{
			answer += c;
			cout << '*'; // show masked character 
		}
	}

	tcsetattr(0, TCSANOW, &oldt);

	return answer;
}