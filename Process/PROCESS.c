#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>


#define FileProc "cpu_201314733"
/*Link de Información 
    http://www.makelinux.net/books/lkd2/ch03lev1sec1
    Descripción del proceso en la parte de The prcess Family Tree
*/
void readTreeProcess(struct seq_file *m, struct task_struct *s);

char get_State(struct task_struct *s)
{
    if(s->state == TASK_RUNNING){
        return 'R';    
    }else if(s->state == TASK_STOPPED){
        return 'T';
    }else if(s->state == TASK_INTERRUPTIBLE){
        return 'S';
    }else if(s->state == TASK_UNINTERRUPTIBLE){
        return 'D';
    }else if(s->state == EXIT_ZOMBIE){
        return 'Z';
    }else{
        return 'X';
    }    
}


static int pstree(struct seq_file *m, void *v)
{
    struct task_struct *root = current; 
    while (root->pid != 1)
        root = root->parent; 
    
    seq_printf(m, "<ul>\n");
    readTreeProcess(m, root);
    seq_printf(m, "</ul>\n");
    return 0;
}



void readTreeProcess(struct seq_file *m, struct task_struct *s)
{
    struct list_head *list;
    struct task_struct *task;
 
    //seq_printf(m, "<li>");
    seq_printf(m,"PID: %d -- Nombre: %s -- Estado:  %c \n", s->pid, s->comm, get_State(s));
    
    list_for_each(list, &s->children) {
        //seq_printf(m, "<ul> \n");
        task = list_entry(list, struct task_struct, sibling);
        readTreeProcess(m, task);
        //seq_printf(m, "</ul>\n");
    }

    //seq_printf(m,"  </li>\n");
}



static int processinfo_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, pstree, NULL);
}

static const struct file_operations procsinfo_proc_fops = {
    .open       = processinfo_proc_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int __init start_function(void)
{
    printk(KERN_INFO "Carnet:    201314733 .\n");
    printk(KERN_INFO "Nombre:    Alan Giovanni Guzman Toledo .\n");
    printk(KERN_INFO "Sistema Operativo:    Debian 9 - Kernel 5.0.7 .\n");
    proc_create(FileProc, 0, NULL, &procsinfo_proc_fops); // CREAR EL ARCHIVO DEL PROC
    printk(KERN_INFO "Archivo Creado: /proc/%s.\n", FileProc);
    return 0;
}

 
static void __exit clean_function(void)
{
    remove_proc_entry(FileProc, NULL); 
    printk(KERN_INFO "Modulo Eliminado.\n");
}
 
module_init(start_function);
module_exit(clean_function);
 
MODULE_AUTHOR("Alan Giovanni Guzman Toledo");
MODULE_DESCRIPTION("Modulo de kernel en la cual se despliga la familia de procesos en forma de arbol");
MODULE_LICENSE("GPL");
