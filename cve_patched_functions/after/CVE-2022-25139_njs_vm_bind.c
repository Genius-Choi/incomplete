njs_vm_bind(njs_vm_t *vm, const njs_str_t *var_name, const njs_value_t *value,
    njs_bool_t shared)
{
    njs_int_t           ret;
    njs_object_t        *global;
    njs_lvlhsh_t        *hash;
    njs_object_prop_t   *prop;
    njs_lvlhsh_query_t  lhq;

    prop = njs_object_prop_alloc(vm, &njs_value_undefined, value, 1);
    if (njs_slow_path(prop == NULL)) {
        return NJS_ERROR;
    }

    ret = njs_string_new(vm, &prop->name, var_name->start, var_name->length, 0);
    if (njs_slow_path(ret != NJS_OK)) {
        return NJS_ERROR;
    }

    lhq.value = prop;
    lhq.key = *var_name;
    lhq.key_hash = njs_djb_hash(lhq.key.start, lhq.key.length);
    lhq.replace = 1;
    lhq.pool = vm->mem_pool;
    lhq.proto = &njs_object_hash_proto;

    global = &vm->global_object;
    hash = shared ? &global->shared_hash : &global->hash;

    ret = njs_lvlhsh_insert(hash, &lhq);
    if (njs_slow_path(ret != NJS_OK)) {
        njs_internal_error(vm, "lvlhsh insert failed");
        return ret;
    }

    return NJS_OK;
}
