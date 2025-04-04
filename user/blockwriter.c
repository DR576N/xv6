// user/blockwriter.c
#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

#define DEFAULT_BLOCKS 150
#define DEFAULT_FILENAME "long.txt"

int
main(int argc, char *argv[])
{
    int blocks = DEFAULT_BLOCKS;
    char *filename = DEFAULT_FILENAME;
    int i;
    char buf[BSIZE];

    // Parsiranje argumenata
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
            printf("Use this program to create a big file filled with a-z characters.\n");
            printf("Default filename: %s\n", DEFAULT_FILENAME);
            printf("Default blocks: %d\n", DEFAULT_BLOCKS);
            printf("Usage: blockwriter [OPTION]...\n\n");
            printf("Command line options:\n");
            printf("        -h, --help: Show help prompt.\n");
            printf("        -b, --blocks: Number of blocks to write.\n");
            printf("        -o, --output-file: Set output filename.\n");
            exit();
        }
        else if(strcmp(argv[i], "--output-file") == 0 || strcmp(argv[i], "-o") == 0){
            if(i+1 < argc) {
                filename = argv[++i];
            } else {
                printf("Error: Missing filename argument\n");
                exit();
            }
        }
        else if(strcmp(argv[i], "--blocks") == 0 || strcmp(argv[i], "-b") == 0){
            if(i+1 < argc) {
                blocks = atoi(argv[++i]);
            } else {
                printf("Error: Missing blocks argument\n");
                exit();
            }
        }
    }

    // Kreiranje fajla (O_CREATE | O_WRONLY je validno)
    int fd = open(filename, O_CREATE | O_WRONLY);
    if(fd < 0){
        printf("Error: Cannot create file %s\n", filename);
        exit();
    }

    // Popunjavanje bafera sa predvidljivim sadržajem (a-z)
    for(i = 0; i < BSIZE; i++)
        buf[i] = 'a' + (i % 26);

    // Pisanje blokova sa ispisom
    for(i = 0; i < blocks; i++){
        if(write(fd, buf, BSIZE) != BSIZE){
            printf("Error: Writing block %d failed\n", i);
            close(fd);
            exit();
        }
        printf("Writing block %d\n", i); // Dodat ispis
    }

    close(fd);
    printf("File %s created with %d blocks\n", filename, blocks);
    exit();
}
