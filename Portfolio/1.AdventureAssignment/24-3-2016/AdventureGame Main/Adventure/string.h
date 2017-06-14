#ifndef _STRING_H_
#define _STRING_H_

#include "window.h"
// Full version

class String
{
public:
	String();
	String(char* a_str);
	String(String& a_other);
	~String();

	int length();													//DONE! :)		// The ability to query the string’s length, returning an integer
	char characterAt(int a_index);									//DONE! :)		// The ability to access a character at a certain index within the string class
	bool equalTo(String& a_str);									//DONE! :)		// The ability to compare if the string is the same as another string class
	void append(char* a_string);									//DONE! :)		// The ability to append one string to another
	void prepend(char* a_string);									//DONE! :)		// The ability to prepend one string to another
	const char* cStr();												//DONE! :)		// The ability to return the string as a basic constant C-style string (const char*)
	void toLower(bool a_capital = 0);								//DONE! :)		// The ability to convert the string to a duplicate containing all lowercase letters
	void toUpper();													//DONE! :)		// The ability to convert the string to a duplicate containing all uppercase letters
	int find(String a_FindString);									//DONE! :)		// The ability to find a sub-string within the string class
	int find(int a_Index, String a_FindString);						//DONE! :)		// The ability to find a sub-string within the string class, starting from a certain index within the string
	void replace(String a_FindString, char* a_ReplaceString);		//DONE! :)		// The ability to replace a sub-string found within the string with a different sub-string
	void setString(char* a_string);									//DONE! :)		// The ability to set the string to an input C-style string

	void ReadFromConsole();
	void WriteToConsole();
	void WriteTextBlock() { Window::DrawLine(35, 15, YELLOW, m_str, 60); }
private:
	char* m_str;
	int	m_capacity;
	int	m_size;
};

#endif