#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

void print_help() {
    printf("Usage: encr [OPTION]... [FILE]...\n");
    printf("Encrypt files using the Caesar cipher.\n");
    printf("Options:\n");
    printf("        -h, --help         Display this help message\n");
    printf("        -a, --encrypt-all  Encrypt all non-encrypted files in the current directory\n");
}

void encrypt_file(char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        printf("encr: cannot open %s\n", filename);
        return;
    }

    int result = encr(fd);
    switch (result) {
        case -1:
            printf("Error: Key not set for %s\n", filename);
            break;
        case -2:
            printf("Error: %s is a device file\n", filename);
            break;
        case -3:
            printf("Error: %s is already encrypted\n", filename);
            break;
        case 0:
            printf("Encrypted %s successfully\n", filename);
            break;
        default:
            printf("Unknown error with %s\n", filename);
    }
    close(fd);
}

void encrypt_all() {
    int dir_fd = open(".", O_RDONLY);
    if (dir_fd < 0) {
        printf("encr: cannot open current directory\n");
        return;
    }

    struct dirent de;
    while (read(dir_fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            continue;
        encrypt_file(de.name);
    }

    close(dir_fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        exit();
    }

    // Handle help option
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_help();
        exit();
    }

    // Handle encrypt-all option
    if (strcmp(argv[1], "--encrypt-all") == 0 || strcmp(argv[1], "-a") == 0) {
        encrypt_all();
        exit();
    }

    // Process individual files
    for (int i = 1; i < argc; i++)
        encrypt_file(argv[i]);

    exit();
}
