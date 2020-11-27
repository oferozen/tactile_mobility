#include <stdio.h>
#include <stdlib.h>
#include "containers/List.h"

int main(void) {
    list_t list = list_create();
    if (list) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
    }
	return EXIT_SUCCESS;
}
