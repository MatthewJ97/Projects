//--------------------------------------------------------------------------------//
//																				  //
//																				  //
// this is where to put your string class										  //
//																				  //
//																				  //
//--------------------------------------------------------------------------------//

#include "string.h"
#include "window.h"
#include <iostream>
#include <cctype>

extern const Rect pInputLine;
extern const Rect pPHOutputLine;
extern const Rect pPCOutputLine;
extern const Rect pEHOutputLine;
extern const Rect pECOutputLine;
extern const int inputLocationX;
extern const int inputLocationY;
extern const int outputLocationX;
extern const int outputLocationY;
extern const Rect pInputZone;
extern const Rect pOutputzone;
extern const Rect pMapZone;

// read a line from the console, ending with ENTER
void String::ReadFromConsole()
{
	Window::SetTextColor(YELLOW);
	Window::SetXY(pInputLine.x, pInputLine.y);
	char a_str[250];

	std::cin.getline(a_str, 30);

	//Delete m_string if it has been previously allocated
	if (m_str != nullptr) {
		delete[] m_str;
		m_str = nullptr;
	}

	m_capacity = 0;
	m_size = 0;

	//Count the new string and resize capacity for it
	for (int i = 0; a_str[i] != '\0'; i++) {
		m_size++;
	}
	if (!m_size) return;

	m_capacity = m_size + 10;
	//Allocate new memory for string
	m_str = new char[m_capacity];

	//Copy the new string into char array
	for (int i = 0; a_str[i] != '\0'; i++) {
		m_str[i] = a_str[i];
	}

	//Set the null terminator
	m_str[m_size] = '\0';
}
// write to the console
void String::WriteToConsole()
{
	std::cout << m_str << std::endl;
}

String::String()
{
	m_str = nullptr;
	m_capacity = 0;
	m_size = 0;
}

String::String(char* a_str)
{
	m_size = 0;
	for (int i = 0; a_str[i] != '\0'; i++) {
		m_size++;
	}
	m_capacity = m_size + 10;
	m_str = new char[m_capacity];

	for (int i = 0; i < m_size; i++) {
		m_str[i] = a_str[i];
	}
	m_str[m_size] = '\0';
}

String::String(String & a_other)
{
	m_size = a_other.m_size;
	m_capacity = a_other.m_capacity;
	m_str = new char[m_capacity];

	for (int i = 0; i < m_size; i++) {
		m_str[i] = a_other.m_str[i];
	}
	m_str[m_size] = '\0';
}


//FUNCTIONS
int String::length()
{
	//SAFETY CHECK
	if (m_str == nullptr) return 0;
	int m_length = 0;
	//LOOPS THRIOUGH TILL THE NULL TERMINATOR
	for (int i = 0; m_str[i] != '\0'; i++) {
		m_length++;
	}
	return m_length;
}

char String::characterAt(int a_index)
{
	//SAFETY CHECK
	if (m_size <= a_index) return '\0';
	//RETURNS CHARACTER AT INDEX 
	return m_str[a_index];
}

bool String::equalTo(String& a_str)
{
	//SAFETY CHECKS
	if (m_str == nullptr && a_str.m_str == nullptr)
		return true;
	if (m_str == nullptr || a_str.m_str == nullptr)
		return false;
	if (m_size != a_str.m_size)
		return false;

	// COMPARES THE TWO STRINGS
	for (int i = 0; a_str.m_str[i] != '\0'; i++) {
		//RETURNS FALSE IF ANY INDEXES ARE NOT EQUAL
		if (m_str[i] != a_str.m_str[i]) {
			return false;
		}
		//LOOPS THROUGH
		else {
			continue;

		}
	}
	//RETURNS TRUE IF IT REACHES THE END OF BOTH STRINGS
	return true;
}

void String::append(char * a_string)
{
	if (a_string == nullptr) return;
	if (m_str == nullptr) {
		setString(a_string);
		return;
	}
	//FIND THE SIZE OF THE ARGUMENT STRING
	int size = 0;
	while (a_string[size] != '\0') {
		size++;
	}

	//CHECK REMAINING SIZE
	if (m_size + size >= m_capacity) {

		//CREATE NEW CHAR BUFFER
		char* stringBuffer = new char[m_capacity + 1];

		//CHECK MEMORY IS VALID
		if (m_str != nullptr) {

			//FILL BUFFER WITH STRING 1
			for (int i = 0; i < m_size; i++) {
				stringBuffer[i] = m_str[i];
			}

			//DELETE M_STR TO BE RECREATED
			delete m_str;
		}
		//NULL TERMINATOR
		stringBuffer[m_size] = '\0';

		//SET NEW CAPACITY
		m_capacity = m_size + size + 10;

		//ALLOCATE NEW MEMORY
		m_str = new char[m_capacity];

		//COPY BUFFER OVER
		for (int i = 0; i < m_size; i++) {
			m_str[i] = stringBuffer[i];
		}

		//NULL TERMINATOR
		m_str[m_size] = '\0';

		//DELETE THE BUFFER
		delete stringBuffer;
	}

	//APPEND NEW STRING
	for (int i = 0; i < size; i++, m_size++) {
		m_str[m_size] = a_string[i];
	}

	//NULL TERMINATOR
	m_str[m_size] = '\0';
}

void String::prepend(char * a_string)
{
	if (a_string == nullptr) return;
	if (m_str == nullptr) {
		setString(a_string);
		return;
	}
	//FIND THE SIZE OF THE ARGUMENT STRING
	int size = 0;
	while (a_string[size] != '\0') {
		size++;
	}
	//SET THE CAPACITY
	m_capacity = size + m_size + 10;
	//SET NEW STRING BUFFER
	char* stringBuffer = new char[m_capacity + 1];
	// COPY A_STRING TO STRING BUFFER 
	for (int i = 0; i < size; i++) {
		stringBuffer[i] = a_string[i];
	}
	//COPY M_STR TO END OF A_STRING IN STRING BUFFER
	for (int i = 0; i < m_size; i++) {
		stringBuffer[size + i] = m_str[i];
	}
	//MAKE M_SIZE LARGE ENOUGH FOR BOTH
	m_size = size + m_size;
	//NULL TERMINATOR
	stringBuffer[m_size] = '\0';
	//SAFETY CHECK
	if (m_str != nullptr) {
		delete[] m_str;
	}
	//SETS M_STR TO POINT TO STRINGBUFFER
	m_str = stringBuffer;

}

const char * String::cStr()
{
	//SAFETY CHECK
	if (m_str == nullptr) return '\0';
	//RETURNS CONST CHAR
	return m_str;
}

void String::toLower(bool a_capital)
{
	//SAFETY CHECK
	if (m_str == nullptr) return;
	//GOES THROUGH EACH CHARACTER
	for (int i = 0; m_str[i] != '\0'; i++) {
		//CHECKS IF CHARACTER IS A CAPITAL IF SO ADD 32 TO MAKE IT A LOWER CASE
		if ((int)m_str[i] >= 65 && (int)m_str[i] <= 90) {
			m_str[i] += 32;
		}
	}
	//
	if (a_capital) {
		m_str[0] = toupper(m_str[0]);
	}
}

void String::toUpper()
{
	if (m_str == nullptr) return;
	for (int i = 0; m_str[i] != '\0'; i++) {
		if ((int)m_str[i] >= 97 && (int)m_str[i] <= 122) {
			m_str[i] -= 32;
		}
	}
}

int String::find(String a_FindString)
{

	if (m_str == nullptr || a_FindString.m_str == nullptr) return -1;

	//GOES THROUGH STRING 1
	for (int i = 0; m_str[i] != '\0'; i++) {
		int j = 0;
		bool foundEqualsTrue = true;
		for (j; j < a_FindString.m_size; j++) {
			if (i + j > m_size) return -1;
			if (m_str[i + j] != a_FindString.m_str[j]) {
				foundEqualsTrue = false;
			}
		}
		if (foundEqualsTrue) {
			return i;
		}
	}
	return -1;
}

int String::find(int a_Index, String a_FindString)
{

	if (m_str == nullptr || a_FindString.m_str == nullptr) return -1;

	//GOES THROUGH STRING 1 FROM INDEX
	for (int i = a_Index; m_str[i] != '\0'; i++) {

		bool foundEqualsTrue = true;

		for (int j = 0; j < a_FindString.m_size; j++) {
			if (i + j > m_size) return -1;
			if (m_str[i + j] != a_FindString.m_str[j]) {
				foundEqualsTrue = false;
			}
		}
		if (foundEqualsTrue) {
			return i;
		}
	}
	return -1;

}

void String::replace(String a_FindString, char * a_ReplaceString)
{
	//CHECK FOR NULL VALUES
	if (m_str == nullptr || a_FindString.m_str == nullptr || a_ReplaceString == nullptr) return;

	//GET REPLACE STRING AS A STRING OBJECT
	String replaceString(a_ReplaceString);


	unsigned int replaceCount = 0;
	int findReturn = -a_FindString.m_size;
	//GET NUMBER OF REPLACEMENTS
	//FIND RETURNS -1 IF NOT FOUND
	while ((findReturn = find(findReturn + a_FindString.m_size, a_FindString)) != -1) {
		replaceCount++;
	}
	//RETURNS IF NO WORDS NEED TO BE REPLACED
	if (replaceCount == 0) return;

	//CALCULATE SIZE REQUIRED (this string size - (find string size * replacecount) + (replace string size * replace count)
	unsigned int sizeRequired = m_size - a_FindString.m_size * replaceCount + replaceString.m_size * replaceCount;

	//CHECK IF I HAVE ENOUGH SIZE
	if (sizeRequired >= (unsigned int)m_capacity) {

		//SET CAPACITY
		m_capacity = sizeRequired + 10;

		// SET BUFFER 1
		char* buffer = new char[m_capacity];

		// COPY OVER THE OLD VALUES
		for (int i = 0; i < m_size; i++)
			buffer[i] = m_str[i];

		//NULL TERMINATE
		buffer[m_size] = '\0';

		//DELETE M_STR
		delete[] m_str;

		//M_STR SET TO BUFFER ADDRESS
		m_str = buffer;
	}

	//CREATE SECOND BUFFER
	char* buffer2 = new char[m_capacity];
	unsigned int oldIndex = 0;
	unsigned int newIndex = 0;
	unsigned int findLoc;

	//LOOP THROUGH THE REPLACEMENTS
	do {

		//FIND NEXT WORD TO REPLACE 
		findLoc = find(oldIndex, a_FindString);


		//FINDS WORDS TO BE REPLACED
		if (findLoc != -1) {

			//COPY OVER THE OLD VALUES
			for (; oldIndex < findLoc; oldIndex++, newIndex++)
				buffer2[newIndex] = m_str[oldIndex];

			//COPY THE REPLACE STRING OVER THE REPLACED WORDS
			for (int i = 0; i < replaceString.m_size; i++, newIndex++)
				buffer2[newIndex] = replaceString.m_str[i];

			//ADDS REPLACED WORDS LENGTH TO OLD INDEX
			oldIndex += a_FindString.m_size;
		}
		else {

			//COPY REMAINDER OF STRING TO BUFFER IF FINISHED/NO WORDS TO REPLACE
			for (; oldIndex < (unsigned int)m_size; oldIndex++, newIndex++)
				buffer2[newIndex] = m_str[oldIndex];
		}

		//DO WHILE LOOP^^^^^
	} while (findLoc != -1);

	//DELETE OLD STRING
	delete[] m_str;

	//SETS M_SIZE TO SIZE REQUIRED
	m_size = sizeRequired;

	//NULL TERMINATE
	buffer2[m_size] = '\0';

	//M_STR SET TO BUFFER ADDRESS
	m_str = buffer2;
}

void String::setString(char * a_string)
{
	if (a_string == nullptr) return;
	if (m_str != nullptr) {
		delete[] m_str;
	}
	m_size = 0;
	for (int i = 0; a_string[i] != '\0'; i++) {
		m_size++;
	}
	m_capacity = m_size + 10;
	m_str = new char[m_capacity];

	for (int i = 0; i < m_size; i++) {
		m_str[i] = a_string[i];
	}
	m_str[m_size] = '\0';

}

// deconstructor
String::~String()
{
	if (m_str != nullptr) {
		delete[] m_str;
		m_str = nullptr;
	}
}

