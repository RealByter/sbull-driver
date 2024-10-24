#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/fs.h>
#include <linux/genhd.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sbull_major = 0;
module_param(sbull_major, int, 0);
static int hardsect_size = 512;
module_param(hardsect_size, int, 0);
static int nsectors = 1024;	/* How big the drive is */
module_param(nsectors, int, 0);
static int ndevices = 4;
module_param(ndevices, int, 0);

struct sbull_dev {
    int size;
    u8 *data;
    short users;
    short media_change;
    spinlock_t lock;
    struct request_queue *queue;
    struct gendisk *gd;
    struct timer_list timer;
};

static struct sbull_dev* devices = NULL;

static void setup_device(struct sbull_dev *dev, int which)
{
    memset(dev, 0, sizeof(struct sbull_dev));
    dev->size = nsectors * hardsect_size;
    dev->data = vmalloc(dev->size);
    if(dev->data == NULL)
    {
        printk(KERN_NOTICE "vmalloc failure\n");
        return;
    }

    spin_lock_init(&dev->lock);

    dev->queue = 
}

static int __init sbull_init(void)
{
    int i;

    sbull_major = register_blkdev(sbull_major, "sbull");
    if(sbull_major <= 0) 
    {
        printk(KERN_WARNING "sbull: unable to get major number\n");
        return -EBUSY;
    }

    devices = kmalloc(ndevices * sizeof(struct sbull_dev), GFP_KERNEL);
    if(devices == NULL)
    {
        printk(KERN_NOTICE "kmalloc failure\n");
        unregister_blkdev(sbull_major, "sbull");
        return -ENOMEM;
    }

    for(i = 0; i < ndevices; i++)
    {
        setup_device(devices + i, i);
    }
}

static void sbull_exit(void)
{
    unregister_blkdev(sbull_major, "sbull");
}

module_init(sbull_init);
module_exit(sbull_exit);