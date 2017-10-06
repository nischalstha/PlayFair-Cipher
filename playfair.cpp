/**
 * A program that implements playfair cipher algorithm
 * @author by Nischal Shrestha
 * @version date 2 September, 2017
 */

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <vector>

using namespace std;
typedef unsigned int uint;

// Creates a 5x5 matrix of characters with the key for en/decryption.
vector <vector<char>> createMatrix( string key )
{
	const int LIST_SIZE = 25;
	vector<char> alphabetList;
	vector<char> resultList;

    // Creating a list of alphabets from a to z.
	for ( char alphabet = 'a'; alphabet <= 'z' ; alphabet++ )
	{
    	// Since i and j are in the same place.
		if ( alphabet != 'j' ) 
		{
			alphabetList.push_back(alphabet);
		}
	}

    // for (auto v : alphabetList)
    // 	cout << v ;
    // cout << endl;

    // If the letters in the key appers in the alphabet list,
    // push back it into result list, without duplicates.
	for ( int i = 0; i <  key.length(); i++ )
	{
		for ( int j = 0; j < LIST_SIZE; j++ )
		{
			if ( key.at(i) == alphabetList.at(j) )
			{   
				resultList.push_back( key.at(i) );
				alphabetList.at(j) = '-';
				break;
			}
		}
	}

    // for (auto v : resultList)
    // 	cout << v ;
    // cout << endl;

    // Appending rest of the letters of alphabhet list to our result list.
	for ( int i = 0 ; i < LIST_SIZE ; i++ )
	{
		if( alphabetList.at(i) != '-' ) 
		{
			resultList.push_back(alphabetList.at(i)) ;
		}
	}

    // for (auto v : resultList)
    // 	cout << v ;
    // cout << endl;

	vector <vector <char>> matrix;
	vector<char> temp_vector;

    // Creating a matrix with the alphabets from result list.
	for ( int i = 0; i < resultList.size(); i++ )
	{
		temp_vector.push_back( resultList.at(i) );
		if ( (i + 1) % 5 == 0 )
		{
			matrix.push_back(temp_vector);
			temp_vector.clear();
		}
	}

	return matrix;
}

void printMatrix( vector< vector<char> > matrix )
{
	for ( int i = 0; i < matrix.size(); i++ )
	{
		for( int j = 0; j < matrix[i].size(); j++ )
		{
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
}

string encryptDecrypt ( string input, bool mode, 
	                    vector< vector<char> > matrix )
{
	string output = "";
	string init = "";

	char first = input.at(0);
	char second = input.at(1);

	uint first_row = 0;
	uint first_col = 0;
	uint second_row = 0, 
	uint second_col = 0;

	for ( int i = 0; i < 5; i++ )
	{
		for ( int j = 0; j < 5; j++ )
		{
			if ( first == matrix[i][j] )
			{
				first_row = i;
				first_col = j;
			}
			if ( second == matrix[i][j] )
			{
				second_row = i;
				second_col = j;
			}
		}
	}
	if ( first_row == second_row )
	{
		if ( mode == true )
		{
			output = init + matrix[first_row][(first_col + 1) % 5] + 
			matrix[second_row][(second_col + 1) % 5];
		}
		else if(mode == false)
		{
			output = init + matrix[first_row][(first_col + 4) % 5] + 
			matrix[second_row][(second_col + 4) % 5];
		}

	}
	else if(first_col == second_col)
	{
		if(mode == true)
		{
			output = init + matrix[(first_row + 1) % 5][first_col] +
			matrix[(second_row + 1) % 5][second_col];
		}
		else if(mode == false)
		{
			output = init + matrix[(first_row + 4) % 5][first_col] + 
			matrix[(second_row + 4) % 5][second_col];
		}
	}
	else
	{
		output = init + matrix[first_row][second_col] + matrix[second_row][first_col];
	}

	return output;
}

string formatInputText(string input)
{
	// Taking out the white spaces of input
	string temp_string = "";
	string output = "";

	for (int i = 0; i < input.length() ; i++)
	{
		if (!(isspace(input.at(i))))
		{
			temp_string += input.at(i);
		}
	}

	input = temp_string;
    // Changing the input all to lowercase for matrix.
	transform(input.begin(), input.end(), input.begin(), ::tolower);

    // Padding a letter x at the end if the input length is odd to make it even.
	if ( (input.length() % 2) == 1)
	{
		input += "x";
	} 
	return input;
}

void cipherMain (string input, string key, bool mode)
{

	string output = "";

    // Gets the string formatted in proper format required to encrypt.
	formatInputText(input);

    // Create a 5x5 matrix with inputed key and prints it.
	vector <vector<char>> matrix = createMatrix(key);
	printMatrix(matrix);

	string stringPair = "";
	while(true)
	{
		// Padding if the length of input message is only one alphabet.
		if (input.length() == 1)
		{
			stringPair = input + "x";
		}
		else
		{
			// Making a pair of two alphabets for the input message.
			stringPair = input.substr(0,2);

            // Padding when the pair of strings are same alphabets.
			if( stringPair.at(0) == stringPair.at(1) )
			{
				input = stringPair.substr(1,1) + input;
				stringPair = stringPair.substr(0,1) + "x";
			}
		}

		stringPair = encryptDecrypt(stringPair, mode, matrix);
		output +=  stringPair;
    
		if(input.length() > 2)
		{
			input = input.substr(2);    
		}
		else break;
	}
	cout << "The encrypted/decrypted message is : " << output << endl;
}

int main()
{

	string input;

	string key;
	cout << "Welcome to Playfair Cipher" << endl;
	cout << "Enter a key word: " ;
	cin >> key;

	uint choice;
	cout << "Would you like to encrypt or decrypt a message?" << endl ;
	cout << "1 - Encrypt message" << endl;
	cout << "2 - Decrypt Message" << endl;
	cin >> choice;

	bool encode;
	if (choice == 1)
	{
		cout << "Enter the text to be encrypted: " ;
		cin.ignore();
		getline(cin, input);
		encode = true;
		cipherMain(input, key, encode);	
	}
	else if (choice == 2)
	{
		cout << "Enter the text to be decrypted: " ;
		cin.ignore();
		getline(cin, input);
		encode = false;
		cipherMain(input, key, encode);
	}
	else
	{
		cout << "Bad choice! Terminating program." << endl ;
	}
	return 0;
}