struct vhost_fdt_hash_table *mk_vhost_fdt_table_lookup(int id, struct host *host)
{
    struct mk_list *head;
    struct mk_list *vhost_list;
    struct vhost_fdt_host *fdt_host;
    struct vhost_fdt_hash_table *ht = NULL;

    vhost_list = mk_vhost_fdt_key;
    mk_list_foreach(head, vhost_list) {
        fdt_host = mk_list_entry(head, struct vhost_fdt_host, _head);
        if (fdt_host->host == host) {
            ht = &fdt_host->hash_table[id];
            return ht;
        }
    }

    return ht;
}
