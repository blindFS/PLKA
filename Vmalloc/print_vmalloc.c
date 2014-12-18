#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/vmalloc.h>

#define VM_LAZY_FREE        0x01
#define VM_LAZY_FREEING     0x02
#define VMAP_AREA_LIST_ADDR     0xc1942be8

static struct list_head *vmap_area_list_p = (struct list_head *)VMAP_AREA_LIST_ADDR;

static int __init my_init(void)
{
    struct vmap_area *pos;
    list_for_each_entry(pos, vmap_area_list_p, list) {
        if (pos->flags & (VM_LAZY_FREE | VM_LAZY_FREEING))
            continue;
        printk("Vmalloc between: [0x%p - 0x%p]\tSize: %ld\n", (void *)pos->va_start, (void *)pos->va_end, pos->va_end - pos->va_start);
    }
    printk("==>>>My_Init Success<<<===\n");
    return 0;
}

static void __exit my_exit(void)
{
    printk("===>>>My_Exit<<<===\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hzc");
MODULE_DESCRIPTION("print_vmalloc");
