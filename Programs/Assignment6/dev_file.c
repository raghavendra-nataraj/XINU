#include <linux/init.h>
#include <linux/module.h>

/* printk() */
#include <linux/kernel.h> 

/* kmalloc() */
#include <linux/slab.h>

/* file_operations struct */
#include <linux/fs.h> 

/* size_t */
#include <linux/types.h> 

/* O_ACCMODE */
#include <linux/fcntl.h>

/* copy_from/to_user */
#include <asm/uaccess.h> 

/*The functions required to make the driver are:*/
int dev_file_init(void);
void dev_file_exit(void);
int dev_file_open(struct inode *inode, struct file *filp);
int dev_file_release(struct inode *inode, struct file *filp);
ssize_t dev_file_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t dev_file_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);

/* Declaration of the init and exit functions */
module_init(dev_file_init);
module_exit(dev_file_exit);

/*Data structure for using file functions:*/
struct file_operations dev_file_fops = {
  read: dev_file_read,
  write: dev_file_write,
  open: dev_file_open,
  release: dev_file_release
}; 

/* Declare a buffer to store input characters */

char *buffer;
static int major_number = 60;
static int count = 0;
static int is_open = 0;

/*The functions below need to be completed as per the comments.*/

int dev_file_init(void) {
  int result;
  /* Registering device */
  buffer = kmalloc(128,GFP_KERNEL);
  if ( buffer == NULL ){
	printk("Failed to allocate buffer");
	return -1;
  }
  result = register_chrdev(major_number, "dev_file", &dev_file_fops);
  if (result < 0){
	printk ("Character device register failed");
	return -1;
  }
  printk ("\n\nCharacter device registered successfully\n");
  return 0;
}

void dev_file_exit(void) {
  /* Unregistering device */
  unregister_chrdev(major_number, "dev_file");
  
  if (buffer != NULL){
  	kfree((void*)buffer);
  }
}

/* To handle open and release, maintain a count variable to check how many times the file
    has been opened. Increment for every open and decrement for every release */

/* This is called when any process tries to open the device file such as cat /dev/dev_file*/
int dev_file_open(struct inode *inode, struct file *filp) {
  if (is_open){
	return -1;
  }
  printk("Opened\n");
  is_open = 1;
  count++;
  return 0;
  /* Check if device is already open, if so return error*/

}

/* This is called when any process closes the device file */
int dev_file_release(struct inode *inode, struct file *filp) {

 /* Close device */
  if (!is_open){
	return -1;
  }
  is_open = 0;
  count--;
  return 0;

}

ssize_t dev_file_read(struct file *filp, char *buf,size_t count, loff_t *f_pos) {

	int bytes_read = strlen(buffer);
	printk("read start");
  /* Use copy_to_user() to transfer data to user space */

  /* Return number of bytes read */

	copy_to_user(buf,buffer,bytes_read);
	if(*f_pos==0){
		*f_pos = *f_pos + strlen(buffer);
	}else{
		return 0;
	}
	printk("read end");
 
	return bytes_read;
}

ssize_t dev_file_write( struct file *filp, char *buf,size_t count, loff_t *f_pos) {

  /* Use copy_from_user() to transfer data from user space */
  /* Return number of bytes written */
	printk("\n\nExecuting1\n\n");
	copy_from_user(buffer,buf,count);
	buffer[count]='\0'; // Not sure if we are suuposed to do this..For safety..
	printk("\n\nExecuting2\n\n");
	return strlen(buffer);	

}
