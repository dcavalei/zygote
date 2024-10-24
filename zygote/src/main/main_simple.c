#include <unistd.h>

void hello() {
    write(STDOUT_FILENO, "Hello World!\n", sizeof("Hello World!\n"));
}

int main() {
    hello();
    return 0;
}
