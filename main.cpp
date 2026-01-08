#include <iostream>
#include "Encryptor.h"
#include <string>
#include <cstdio>

using namespace std;

void printHelp()
{
    cout << "\n";
    cout << "==========================================================\n";
    cout << "                  SAFEBOX FILE ENCRYPTOR          \n";
    cout << "==========================================================\n\n";
    cout << "Usage: \\.safebox <mode> <filename> <key> [options]\n";
    cout << "Modes: \n";
    cout << "  -e : Encrypt the file\n";
    cout << "  -d : Decrypt the file\n";
    cout << "Options: \n";
    cout << "  --shred : Delete the original file after encryption\n";
    cout << "Example: \n";
    cout << "  .\\safebox -e myfile.txt K\n";
    cout << "Remember your key! Without it, decryption is not possible.\n\n";
}

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        printHelp();
        return 1;
    }
    if (argc < 4 || argc > 5)
    {
        cerr << "Invalid number of arguments.\n";
        printHelp();
        return 1;
    }

    string mode = argv[1];
    string filename = argv[2];
    string key = argv[3];

    bool shred = false;
    if (argc == 5)
    {
        string extraArg = argv[4];
        if (extraArg == "--shred")
            shred = true;
        else
        {
            cerr << "Invalid input of option.\n";
            printHelp();
            return 1;
        }
    }

    Encryptor encryptor;
    string outputFilename;
    bool taskdone = false;

    if (mode == "-e")
    {
        outputFilename = filename + ".enc";
        if (encryptor.processFile(filename, outputFilename, key))
        {
            cout << "File encrypted successfully: " << outputFilename << endl;
            taskdone = true;
        }
        else
        {
            cerr << "Encryption failed." << endl;
            return 1;
        }
    }
    else if (mode == "-d")
    {
        if (filename.find(".enc") != std::string::npos)
        {
            outputFilename = filename.substr(0, filename.find(".enc"));
        }
        else
        {
            outputFilename = filename + ".dec";
        }

        if (encryptor.processFile(filename, outputFilename, key))
        {
            cout << "File decrypted successfully: " << outputFilename << endl;
            taskdone = true;
        }
        else
        {
            cerr << "Decryption failed." << endl;
            return 1;
        }
    }
    else
    {
        cerr << "Invalid mode specified.\n";
        printHelp();
        return 1;
    }

    if (shred && taskdone)
    {
        cout << "Are you sure you want to delete the original file '" << filename << "'? (y/n): ";
        char response;
        cin >> response;
        if (response == 'y' || response == 'Y')
        {
            if (remove(filename.c_str()) == 0)
            {
                cout << "Original file securely deleted.\n";
            }
            else
            {
                cerr << "Error deleting the original file.\n";
            }
        }
        else
        {
            cout << "Shred cancelled. Original file preserved.\n";
        }
    }

    return 0;
}