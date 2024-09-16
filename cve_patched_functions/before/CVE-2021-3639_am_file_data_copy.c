am_file_data_t *am_file_data_copy(apr_pool_t *pool,
                                  am_file_data_t *src_file_data)
{
    am_file_data_t *dst_file_data = NULL;

    if ((dst_file_data = am_file_data_new(pool, src_file_data->path)) == NULL) {
        return NULL;
    }

    dst_file_data->path = apr_pstrdup(pool, src_file_data->path);
    dst_file_data->stat_time = src_file_data->stat_time;
    dst_file_data->finfo = src_file_data->finfo;
    dst_file_data->contents = apr_pstrdup(pool, src_file_data->contents);
    dst_file_data->read_time = src_file_data->read_time;
    dst_file_data->rv = src_file_data->rv;
    dst_file_data->strerror = apr_pstrdup(pool, src_file_data->strerror);
    dst_file_data->generated = src_file_data->generated;

    return dst_file_data;
}
