static mk_ptr_t *mk_request_set_default_page(char *title, mk_ptr_t message,
                                        char *signature)
{
    char *temp;
    mk_ptr_t *p;

    p = mk_mem_malloc(sizeof(mk_ptr_t));
    p->data = NULL;

    temp = mk_ptr_to_buf(message);
    mk_string_build(&p->data, &p->len,
                    MK_REQUEST_DEFAULT_PAGE, title, temp, signature);

    mk_mem_free(temp);

    return p;
}
