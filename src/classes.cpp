#include "main.h"
#include "classes.hpp"

void loadConfiguration(const char* configFilePath) {
  try {
    printf("Loading Config\n");
    std::ifstream fileStream;
    fileStream.open(configFilePath);
    if (fileStream.fail()) {
      printf("filestream loading failed\n");
    }
    char* fileContentsCSTR;
    std::stringstream formatter;


    fileStream.getline(fileContentsCSTR, 1024);
    std::string fileContents(fileContentsCSTR);
    printf("file contents:\n%s\n", fileContentsCSTR);
    formatter << fileContentsCSTR;
    bool park;
    formatter >> park;
    autonConfig.park = park;


    //use formatter.flush(); to empty stream

    fileStream.close();
    printf("Loaded Config\n");
  } catch (std::exception& e) {
    printf(e.what());
  }
}

void writeConfiguration(const char* configFilePath) {
  printf("Doing write");
  try {
    FILE* usd_file_write = fopen("/usd/example.txt", "w+");
    fwrite(&autonConfig, sizeof(sdl::AutonConfig), 1, usd_file_write);
    fclose(usd_file_write);

    /*
    FILE* usd_file_read = fopen("/example.txt", "r");
    char buf[50]; // This just needs to be larger than the contents of the file
    fread(buf, 1, 50, usd_file_read); // passing 1 because a `char` is 1 byte, and 50 b/c it's the length of buf
    printf("%s\n", buf); // print the string read from the file
    // Should print "Example text" to the terminal
    fclose(usd_file_read); // always close files when you're done with them
    */
  } catch (std::exception& e) {
    printf("%s\n",e.what());
  }
  printf("Fin\n");
  /*
  printf("Writing Config\n");
  FILE* configFile = fopen(configFilePath, "w");
  std::stringstream formatter;

  formatter << autonConfig.park;

  char* fileContents;
  formatter >> fileContents;
  printf("file contents:\n%s\n\n", fileContents);
  fputs(fileContents, configFile);
  fclose(configFile);
  printf("Wrote Config\n");
  */
}
