#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;
using namespace std;

int main() {
  
  string inputText;

  getline(cin, inputText);

  string foundFilePath;
  string compileCommand;

  fs::path currentDir = fs::current_path();

  while(true) {

  for(const auto& entry : fs::directory_iterator(currentDir)) {
    fs::path entryName = fs::path(entry).filename();

    if (fs::is_regular_file(entry)) {
      if (entryName == inputText) {
        int initialFileSize = fs::file_size(entryName);

        foundFilePath = currentDir / inputText;
        compileCommand = "g++ -g " + foundFilePath + " -o executable";

        cout << "File found: true" << endl;

        system(compileCommand.c_str());
        system("./executable");

        cout << "File executed successfully" << endl;
        
        while(true) {
  
        int currentFileSize = fs::file_size(entryName);

          if (initialFileSize != currentFileSize) {
          cout << "File changed, recompiling and executing..." << endl;

          system(compileCommand.c_str());
          system("./executable");

          initialFileSize = currentFileSize;
          };

          this_thread::sleep_for(chrono::milliseconds(500));
        }

        return 0;
      }
    }

    if (fs::is_directory(entry)) {

      currentDir = entry;
      
      continue;
      };
    };
  }
}
;
