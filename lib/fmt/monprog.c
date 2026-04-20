#include <gc.h>

int main() {
    GC_INIT();
    int *p = GC_MALLOC(sizeof(int));
    *p = 42;
    // Pas de free() nécessaire
    return 0;
}
