insert_prefix(int options, char **buffer, int *offset, int *max, int depth)
{
    if (options & xml_log_option_formatted) {
        size_t spaces = 2 * depth;

        if ((*buffer) == NULL || spaces >= ((*max) - (*offset))) {
            (*max) = QB_MAX(CHUNK_SIZE, (*max) * 2);
            (*buffer) = realloc_safe((*buffer), (*max) + 1);
        }
        memset((*buffer) + (*offset), ' ', spaces);
        (*offset) += spaces;
    }
}
