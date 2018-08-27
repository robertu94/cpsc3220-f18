#include <unistd.h>
int main()
{
	return write(0, "hello world!\n", 14);
}
