#include <stdio.h>

/* Declare a buffer for user input of size 2048 */
static char buffer[2048];
int main(int argc, char** argv) {
/* Print Version and Exit Information */
puts("Lispy Version 0.0.0.0.1");
puts("Stage: Parrot");
puts("Press Ctrl+c to Exit\n");
/* In a never ending loop */
while (1) {
/* Output our prompt */
fputs("lispy> ", stdout);
/* Read a line of user input of maximum size 2048 */
fgets(buffer, 2048, stdin);
/* Echo input back to user */
printf("No you're the %s", buffer);
}
return 0;
}
