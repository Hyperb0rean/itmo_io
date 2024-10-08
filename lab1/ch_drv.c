#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

#define BUF_SIZE 256

static dev_t first;
static struct cdev c_dev;
static struct class *cl;

char ibuf[BUF_SIZE];

char log_buf[BUF_SIZE];
int log_off = 0;

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: open()\n");
    return 0;
}

static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: close()\n");
    return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len,
                       loff_t *off)
{
    int count = strlen(log_buf);
    printk(KERN_INFO "Driver: read()\n");

    if (*off > 0 || len < count) {
        return 0;
    }

    if (copy_to_user(buf, log_buf, count) != 0) {
        return -EFAULT;
    }

    *off = count;

    return count;
}

static int count_not_alnum(int len)
{
    char sym;
    int i;
    int letters_count = 0;

    for (i = 0; i != len; ++i) {
        sym = ibuf[i];

        //https://en.cppreference.com/w/c/string/byte/isalnum

        if (isalnum(sym) == 0) {
            ++letters_count;
        }
    }

    return letters_count - 1;
}

static void log_number(int count)
{
    char int_to_str[5];
    sprintf(int_to_str, "%d ", count);
    strncat(log_buf, int_to_str, strlen(int_to_str));
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len,
                        loff_t *off)
{
    printk(KERN_INFO "Driver: write()\n");

    if (len > BUF_SIZE)
        return 0;

    if (copy_from_user(ibuf, buf, len) != 0) {
        return -EFAULT;
    }

    if (log_off >= BUF_SIZE - 4) {
        return 0;
    }

    int count = count_not_alnum(len);
    log_number(count);

    return len;
}

static struct file_operations mychdev_fops = { .owner = THIS_MODULE,
                                               .open = my_open,
                                               .release = my_close,
                                               .read = my_read,
                                               .write = my_write };

static int __init ch_drv_init(void)
{
    printk(KERN_INFO "Hello!\n");
    if (alloc_chrdev_region(&first, 0, 1, "ch_dev") < 0) {
        return -1;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    cl = class_create("chardrv");
#else
    cl = class_create(THIS_MODULE, "chardrv");
#endif

    if (cl == NULL) {
        unregister_chrdev_region(first, 1);
        return -1;
    }

    if (device_create(cl, NULL, first, NULL, "var9") == NULL) {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }

    cdev_init(&c_dev, &mychdev_fops);
    if (cdev_add(&c_dev, first, 1) == -1) {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }
    return 0;
}

static void __exit ch_drv_exit(void)
{
    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    printk(KERN_INFO "Bye!!!\n");
}

module_init(ch_drv_init);
module_exit(ch_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("greg");
MODULE_DESCRIPTION("BLOCK DRIVER");
