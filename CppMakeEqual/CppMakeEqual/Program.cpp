// Program.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma warning(disable: 6386)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Source.h"

using namespace std;

void tokenize(string const&, vector<string>&);

int main()
{
    ifstream inputFile;
    inputFile.open("..\\inputs.txt", ios::in);

    if (inputFile.is_open() == true)
    {
        unsigned char iterations = 1;
        unsigned char stage = 0;
        int* arr1 = NULL;
        int arr1_size = 0;
        int* arr2 = NULL;
        int arr2_size = 0;
        int studentResult = 0;

        unsigned char questionsCorrect = 0;

        string line;
        while (getline(inputFile, line))
        {
            if (line == "")
            {
                continue;
            }

            vector<string> out;
            tokenize(line, out);

            if (stage == 0)//Input lengths
            {
                arr1_size = stoi(out[0]);
                arr2_size = stoi(out[1]);
                stage = 1;
            }
            else if (stage == 1)//Input for array 1
            {
                arr1 = new int[arr1_size];

                for (int i = 0; i < out.size(); i++)
                {
                    arr1[i] = stoi(out[i]);
                }

                stage = 2;
            }
            else if (stage == 2)//Input for array 2 & execution of student code
            {
                arr2 = new int[arr2_size];

                for (int i = 0; i < out.size(); i++)
                {
                    arr2[i] = stoi(out[i]);
                }

                //Execute the student's code
                try
                {
                    studentResult = makeEqual(arr1, arr1_size, arr2, arr2_size);
                }
                catch (const exception& e)
                {
                    std::cerr << e.what();
                    studentResult = -2;
                }

                stage = 3;
            }
            else if (stage == 3) //Check answer
            {
                int answer = stoi(line);

                if (answer == studentResult)
                {
                    questionsCorrect++;
                    cout << "Input #" << to_string(iterations) << " is correct." << endl;
                }
                else
                {
                    cout << "Input #" << to_string(iterations) << " is incorrect." << endl;
                }

                iterations++;
                stage = 0;
            }
        }

        inputFile.close();

        cout << endl << to_string(questionsCorrect) << "/" << to_string(iterations - 1) << " correct." << endl;
        cout << to_string(questionsCorrect * 2) << "/" << to_string((iterations - 1) * 2) << " points scored." << endl;
    }
    else
    {
        cerr << "Unable to open the input file!" << endl;
    } 
}

void tokenize(string const& str, vector<string>& out)
{
    const char delim = ' ';

    // construct a stream from the string
    stringstream ss(str);

    string s;
    while (getline(ss, s, delim))
    {
        out.push_back(s);
    }
}