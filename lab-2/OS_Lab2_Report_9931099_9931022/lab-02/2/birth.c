#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
struct birthday{
    int day;
    int month;
    int year;
    struct list_head list;
};

//Create a list of birthday struct
static LIST_HEAD(birthday_list);

int simple_init(void){
    int i;
    struct birthday *ptr;
    struct birthday *person;
    
    //Create a new object of birthday
    person = kmalloc(sizeof(person),GFP_KERNEL);
    person->day = 27;
    person->month = 4;
    person->year= 2001;

    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list , &birthday_list);
    
    for(i=0;i < 4;i++){
        struct birthday * newPerson;
        newPerson=kmalloc(sizeof(newPerson),GFP_KERNEL);
        newPerson->day = i;
        newPerson->month =i + 1;
        newPerson->year = 2000 + i;
        list_add_tail(&newPerson->list, &birthday_list);
    }
    
    list_for_each_entry(ptr , &birthday_list, list){
        printk(KERN_INFO "BirthDate: %d/%d/%d\n", ptr->day , ptr->month , ptr->year);
    }
    printk(KERN_INFO "Module Loaded\n");
    return 0;   
}

void exit_birth(void){
    printk(KERN_INFO "Removing Module From Kernel\n");
    struct birthday *ptr , *tmp;
    list_for_each_entry_safe(ptr, tmp , &birthday_list , list){
        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(exit_birth);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("birth module");
MODULE_AUTHOR("SGG");