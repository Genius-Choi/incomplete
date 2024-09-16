mk_ptr_t mk_request_index(char *pathfile, char *file_aux, const unsigned int flen)
{
    unsigned long len;
    mk_ptr_t f;
    struct mk_string_line *entry;
    struct mk_list *head;

    mk_ptr_reset(&f);
    if (!config->index_files) return f;

    mk_list_foreach(head, config->index_files) {
        entry = mk_list_entry(head, struct mk_string_line, _head);
        len = snprintf(file_aux, flen, "%s%s", pathfile, entry->val);
        if (mk_unlikely(len > flen)) {
            len = flen - 1;
            mk_warn("Path too long, truncated! '%s'", file_aux);
        }

        if (access(file_aux, F_OK) == 0) {
            f.data = file_aux;
            f.len = len;
            return f;
        }
    }

    return f;
}
