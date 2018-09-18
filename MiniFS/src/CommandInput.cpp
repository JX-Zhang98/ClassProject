#include "CommandInput.h"

CommandInput::CommandInput()
{

}
string CommandInput::UserInput()
{
	string input = "";
	char i = 'a';
	while (i != '\n') {
		i = getchar();
		if (i != '\n')
			input += i;
		//cout << i;
	}
	return input;
}