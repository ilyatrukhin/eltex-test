#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>

#define DRIVER_AUTHOR "Your Name <yourname@isp.com>"
#define DRIVER_DESC   "A Hello World kernel module."

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);            /* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC);         /* What does this module do */


static int __init hello_world( void )
{
  printk("hello world\n");
  return 0;
}

static void __exit goodbye_world( void )
{
  printk("goodbye world\n");
}

module_init( hello_world );
module_exit( goodbye_world );