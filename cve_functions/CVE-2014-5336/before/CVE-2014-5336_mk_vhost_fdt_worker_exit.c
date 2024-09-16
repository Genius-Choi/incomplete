int mk_vhost_fdt_worker_exit()
{
    struct mk_list *head;
    struct mk_list *tmp;
    struct vhost_fdt_host *fdt;

    if (config->fdt == MK_FALSE) {
        return -1;
    }

    mk_list_foreach_safe(head, tmp, mk_vhost_fdt_key) {
        fdt = mk_list_entry(head, struct vhost_fdt_host, _head);
        mk_list_del(&fdt->_head);
        mk_mem_free(fdt);
    }

    mk_mem_free(mk_vhost_fdt_key);
    return 0;
}
