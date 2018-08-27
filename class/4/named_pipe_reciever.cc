#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

const char* FIFO_FILE = "MYFIFO";

int
main(int argc, char* argv[])
{
  umask(0);

  dev_t dev = 0; /*This is required, and only portage usage of this...*/
  mknod(FIFO_FILE, S_IFIFO | S_IWUSR | S_IRUSR, dev);

  while (true) {
    std::ifstream fifo(FIFO_FILE);
    if (fifo) {
      std::string buffer;
      getline(fifo, buffer);
      std::cout << "got: " << buffer << std::endl;
    } else {
      std::cerr << "error" << std::endl;
    }
  }

  return 0;
}
