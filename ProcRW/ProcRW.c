#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#define MAX 20

unsigned long len, temp;
char *msg;
static struct proc_dir_entry *proc_parent;

ssize_t proc_rw_read(struct file *filp, char *buf, size_t count, loff_t *offp)
{
    if (count > temp)
    {
        count = temp;
    }
    temp = temp - count;
    copy_to_user(buf, msg, count);
    if (count == 0)
        temp = len;
    return count;
}

ssize_t proc_rw_write(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
    if (count > MAX)
    {
        /* count = MAX; */
        return -ENOMEM;
    }
    copy_from_user(msg, buf, count);
    len = count;
    temp = len;
    return count;
}

static const struct file_operations rw_proc_fops =
{
    .read = proc_rw_read,
    .write = proc_rw_write
};

static int __init proc_rw_init(void)
{
    proc_parent = proc_mkdir_mode("proctest", 0777, NULL);
    if (!proc_parent)
        return -ENOMEM;
    proc_create("rw", 0666, proc_parent, &rw_proc_fops);
    msg = kmalloc(MAX * sizeof(char), GFP_KERNEL);
    return 0;
}

static void __exit proc_rw_exit(void)
{
    remove_proc_entry("rw", proc_parent);
    remove_proc_entry("proctest", NULL);
    kfree(msg);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hzc");

module_init(proc_rw_init);
module_exit(proc_rw_exit);

// vim:ts=4:sw=4:tw=0:ft=c:fdm=marker:fdl=10

