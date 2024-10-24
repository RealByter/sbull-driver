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

static int __init sbull_init(void)
{
    sbull_major = register_blkdev(sbull_major, "sbull");
}

static void sbull_exit(void)
{
    unregister_blkdev(sbull_major, "sbull");
}

module_init(sbull_init);
module_exit(sbull_exit);