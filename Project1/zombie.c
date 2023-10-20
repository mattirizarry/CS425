#include <stdio.h>
#include <unistd.h>

void sleep_for_seconds(int seconds) {
    sleep(seconds);
}

int main() {
    printf("Sleeping for 5 seconds...\n");
    sleep_for_seconds(5);
    printf("Done sleeping.\n");

    return 0;
}
