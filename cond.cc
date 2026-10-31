#include <cstdio>
#include <initializer_list>

int main() {
    for (int x : {-1, 0, 1}) {
        if (x > 0)
            printf("positive...\n");
        else if (x < 0)
            printf("negative...\n");
        else
            printf("zero...\n");
    }
    return 0;
}
