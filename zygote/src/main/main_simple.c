#include <unistd.h>

__attribute__((visibility("default")))
void hello() {
    write(STDOUT_FILENO, "Hello World!\n", sizeof("Hello World!\n"));
}

__attribute__((visibility("default")))
int main() {
    hello();
    return 0;
}
