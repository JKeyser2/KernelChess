#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEVICE_FILE "/dev/chess_device"

int main() {
    int file_desc;
    int bytes_written;
    
    // Open the device file
    file_desc = open(DEVICE_FILE, O_WRONLY);
    if (file_desc < 0) {
        perror("Failed to open the device file");
        printf("Error code: %d\n", errno);  // Print error code
        return -1;
    }
    

    bytes_written = write(file_desc, "Data from user space", 20);
    if (bytes_written < 0) {
        printf("Error writing to device\n");
        close(file_desc);
        return -1;
    }

    close(file_desc);
    return 0;
}
