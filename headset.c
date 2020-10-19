#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

// Program Name
#define name "headset"

// The device IP of your bluetooth headset
// You can find this after connecting to your bluetooth headset
// by going to Bluetooth>Your Device
char *devIP = NULL;

// Global Method Declarations
void setup();
void cleanup(int);
// End of Method Declarations

// Setup for running the program
void setup() {
    // Load ip config from ip.conf
    FILE *fptr;
    fptr = fopen("/bin/ip.conf", "rb");
    if(fptr == NULL) {
        fprintf(stderr, "%s : %s\n", name, strerror(errno));
        // Exit with return status 1
        cleanup(1);
    }

    devIP = (char *) malloc(100);
    if(fscanf(fptr, "%s", devIP) == EOF) {
        fprintf(stderr, "%s : %s\n", name, "No IP config!");
        fclose(fptr);
        cleanup(0);
    }

    fclose(fptr);
}

// Cleanup and exit the program
void cleanup(int returnValue) {
    if(devIP != NULL)
        free(devIP);
    
    exit(returnValue);
}

// Set ip in configuration file
void setip(char *address) {
    FILE *fptr;
    fptr = fopen("/bin/ip.conf", "w");

    if(fptr == NULL) {
        fprintf(stderr, "%s: Error while opening file: %s\n", name, strerror(errno));
        cleanup(1);
    }

    fprintf(fptr, "%s\n", address);
    fclose(fptr);
}

// Switch to handsfree profile
void handsfree() {
    system("/bin/handsfree.sh");
}

// Switch to A2DP
void a2dp() {
    system("/bin/a2dp.sh");
}

// Connect to saved device
void connect() {
    char command[100] = "/bin/connect.sh ";
    strcat(command, devIP);
    system(command);
}

// Help with the program
void help() {
    char *helpMessage = "Usage: headset [OPTION ...]\n\n"
        "Main modes of operation: \n"
        "  -s, --set-ip             Expects a space separated paramter, IP address of your headset.\n"
        "  -c, --connect            Connect to your saved headphone\n"
        "  -h, --handsfree          Switches to HSP/HFP profile\n"
        "  -a, --a2dp               Switches to A2DP profile\n\n"
        "  --help                   Prints program manual\n"
        "\n"
        "Report bugs to harsh19043@iiitd.ac.in, or create an issue at https://github.com/hadron43/Linux-Headset-Tool \n";
    printf("%s", helpMessage);
}

int main(int argc, char *argv[]) {
    // If command is not setip, we load config file
    if(argc <=1 || (strcmp(argv[1], "-s") && strcmp(argv[1], "--set-ip")))
        setup();

    if(argc <= 1 || !strcmp(argv[1], "--help")) {
        help();
    }
    else if(!strcmp(argv[1], "-c") || !strcmp(argv[1], "--connect")) {        
        connect();
    }
    else if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--handsfree")) {
        handsfree();
    }
    else if(!strcmp(argv[1], "-a") || !strcmp(argv[1], "--a2dp")) {
        a2dp();
    }
    else if(!strcmp(argv[1], "-s") || !strcmp(argv[1], "--set-ip")) {
        if(argv[2] == NULL) {
            fprintf(stderr, "%s: missing ip operand after '%s'\n", name, argv[1]);
            cleanup(2);
        }
        setip(argv[2]);
    }
    else {
        fprintf(stderr, "%s: unrecognized option '%s'\n", name, argv[1]);
        cleanup(2);
    }

    // Cleanup and exit with status 0
    cleanup(0);
}