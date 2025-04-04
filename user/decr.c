#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

void print_help(void) {
    printf("Usage: decr [OPTION]... [FILE]...\n");
    printf("Decrypt files encrypted using the Caesar cipher.\n");
    printf("Options:\n");
    printf("        -h, --help         Display this help message\n");
    printf("        -a, --decrypt-all  Decrypt all encrypted files in the current directory\n");
}

void decrypt_file(char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        printf("decr: cannot open %s\n", filename);
        return;
    }
    int result = decr(fd);  // sistemski poziv koji koristi global_key iz kernela
    switch (result) {
        case -1:
            printf("Error: Key not set for %s\n", filename);
            break;
        case -2:
            printf("Error: %s is a device file\n", filename);
            break;
        case -3:
            printf("Error: %s is not encrypted\n", filename);
            break;
        case 0:
            printf("Decrypted %s successfully\n", filename);
            break;
        default:
            printf("Unknown error with %s\n", filename);
    }
    close(fd);
}

void decrypt_all(void) {
    int dir_fd = open(".", O_RDONLY);
    if (dir_fd < 0) {
        printf("decr: cannot open current directory\n");
        return;
    }
    struct dirent de;
    while (read(dir_fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            continue;
        decrypt_file(de.name);
    }
    close(dir_fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        exit();
    }
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_help();
        exit();
    }
    if (strcmp(argv[1], "--decrypt-all") == 0 || strcmp(argv[1], "-a") == 0) {
        decrypt_all();
        exit();
    }
    for (int i = 1; i < argc; i++) {
        decrypt_file(argv[i]);
    }
    exit();
}
