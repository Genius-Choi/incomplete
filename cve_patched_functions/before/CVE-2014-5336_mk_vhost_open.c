int mk_vhost_open(struct session_request *sr)
{
    int id;
    int off;
    unsigned int hash;

    off = sr->host_conf->documentroot.len;
    hash = mk_utils_gen_hash(sr->real_path.data + off,
                             sr->real_path.len - off);
    id   = (hash % VHOST_FDT_HASHTABLE_SIZE);

    return mk_vhost_fdt_open(id, hash, sr);
}
