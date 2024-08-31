#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jackson Keyser");
MODULE_DESCRIPTION("Chess is cool");

#define DEVICE_NAME "chess_device"


static void CreateBoard(char theBoardArray[8][8][4]);
static void PrintBoard(char theBoardArray[8][8][4]);


static int major_number;
static char message[256] = {};
static short size_of_message;


static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .release = device_release
};

static int __init hello_init(void){
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if(major_number < 0){
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }
    
    
    printk(KERN_INFO "Chess device is registered with major number %d\n", major_number);
    
    printk(KERN_INFO "init\n");


    //char theBoardArray[8][8][4];
    
    
    
    //CreateBoard(theBoardArray);
    //PrintBoard(theBoardArray);
    
    return 0;
}


static void __exit hello_cleanup(void){ 
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Chess device unregistered\n");
}


static int device_open(struct inode *inode, struct file *file){
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file){
    printk(KERN_INFO "Device closed\n");
    return 0;
}


static ssize_t device_read(struct file *file, char *buffer, size_t length, loff_t *offset){
    printk(KERN_INFO "Reading from device\n");
    return 0;
} 


static ssize_t device_write(struct file *file, const char *buffer, size_t length, loff_t *offset){
    printk(KERN_INFO "Writing to device\n");
    return length;
}


static void CreateBoard(char theBoardArray[8][8][4]) {
    // Initialize the board with piece positions
    char initialBoard[8][8][4] = {
        {"**", "**", "WK", "WR", "**", "**", "WN", "WR"},
        {"WP", "**", "**", "WN", "**", "WP", "WP", "WP"},
        {"BB", "**", "WP", "**", "WP", "**", "**", "**"},
        {"**", "**", "**", "**", "**", "**", "**", "**"},
        {"**", "BP", "**", "BP", "**", "BB", "**", "**"},
        {"**", "**", "BN", "**", "**", "**", "**", "BP"},
        {"**", "BP", "BP", "BK", "**", "BP", "BP", "**"},
        {"**", "**", "**", "**", "**", "**", "**", "WQ"}
    };
    
    int i;
    int j;

    // Copy the initial board to the actual board
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            strcpy(theBoardArray[i][j], initialBoard[i][j]);
        }
    }
}




static void PrintBoard(char theBoardArray[8][8][4]){
    int i;
    int j;
    
    printk(KERN_INFO "\n");
    for(i = 0; i < 8; i++){
        printk(KERN_INFO "\n");
        for(j = 0; j < 8; j++){
            printk(KERN_INFO "%s ", theBoardArray[i][j]);
        }
    }
    printk(KERN_INFO "\n");

}




module_init(hello_init);
module_exit(hello_cleanup);
