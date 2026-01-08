#include <string>

class Encryptor
{
public:
    bool processFile(const std::string &inputFilePath,
                     const std::string &outputFilePath,
                     const std::string &key);
};
