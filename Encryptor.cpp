#include "Encryptor.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool Encryptor::processFile(const string &inputFilePath, const string &outputFilePath, const string &key)
{
    ifstream inputFile(inputFilePath, ios::binary);
    ofstream outputFile(outputFilePath, ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Error opening files." << endl;
        return false;
    }

    int keyIndex = 0;
    int keyLength = key.length();

    if (keyLength == 0)
    {
        cerr << "Key cannot be empty." << endl;
        return false;
    }

    char buffer;
    while (inputFile.get(buffer))
    {
        char encryptedChar = buffer ^ key[keyIndex];
        outputFile.put(encryptedChar);
        keyIndex = (keyIndex + 1) % keyLength;
    }
    inputFile.close();
    outputFile.close();
    return true;
}