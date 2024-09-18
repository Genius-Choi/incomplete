*mk_vhost_fdt_chain_lookup(unsigned int hash, struct vhost_fdt_hash_table *ht)
{
    int i;
    struct vhost_fdt_hash_chain *hc = NULL;

    for (i = 0; i < VHOST_FDT_HASHTABLE_CHAINS; i++) {
        hc = &ht->chain[i];
        if (hc->hash == hash) {
            return hc;
        }
    }

    return NULL;
}
