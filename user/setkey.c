#include "user.h"
#include "kernel/fcntl.h"

#define MAX_KEY_LEN 32  // Maksimalna dužina ključa (dovoljno za 64-bitni int)

void print_help() {
    printf("Usage: setkey [OPTIONS]... [KEY]\n");
    printf("Options:\n");
    printf("        -h, --help: Show help prompt.\n");
    printf("        -s, --secret: Enter the key via STDIN. Hide key when entering it.\n");
    exit();
}


int main(int argc, char *argv[]) {
    int key = atoi(argv[1]);
    setkey(key);
    exit();
/*
    char key_str[MAX_KEY_LEN];
    int use_secret = 0;
    int key = -1;

    // Parsiranje argumenata
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_help();
        } else if (strcmp(argv[i], "--secret") == 0 || strcmp(argv[i], "-s") == 0) {
            use_secret = 1;
        } else {
            // Provera da li je argument validan broj
            if (atoi(argv[i]) <= 0) {
                printf("Error: Invalid key '%s'\n", argv[i]);
                exit();
            }
            key = atoi(argv[i]);
            setkey(key);
        }
    }

    if (use_secret) {
        printf("Enter key: ");
        setecho(0);  // Isključi echo
        memset(key_str, 0, MAX_KEY_LEN);
        char c;
        int idx = 0;
        while (read(0, &c, 1) > 0 && c != '\n' && idx < MAX_KEY_LEN - 1) {
            if (c == '\b') {  // Obradi backspace
                if (idx > 0) {
                    idx--;
                    printf("\b \b");
                }
            }else if (c == '\n'){
                printf("\n");
                break;
            } else {
                key_str[idx++] = c;
            }
        }
        setecho(1);  // Vrati echo
        key_str[idx] = '\0';
        key = atoi(key_str);
        setkey(key);
        exit();
    } else if(argc == 1){
        print_help();
    }
    exit();
    */
}
