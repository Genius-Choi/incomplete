njs_vm_value_error_set(njs_vm_t *vm, njs_value_t *value, const char *fmt, ...)
{
    va_list  args;
    u_char   buf[NJS_MAX_ERROR_STR], *p;

    p = buf;

    if (fmt != NULL) {
        va_start(args, fmt);
        p = njs_vsprintf(buf, buf + sizeof(buf), fmt, args);
        va_end(args);
    }

    njs_error_new(vm, value, NJS_OBJ_TYPE_ERROR, buf, p - buf);
}
