njs_vm_create(njs_vm_opt_t *options)
{
    njs_mp_t      *mp;
    njs_vm_t      *vm;
    njs_int_t     ret;
    njs_uint_t    i;
    njs_module_t  **addons;

    mp = njs_mp_fast_create(2 * njs_pagesize(), 128, 512, 16);
    if (njs_slow_path(mp == NULL)) {
        return NULL;
    }

    vm = njs_mp_zalign(mp, sizeof(njs_value_t), sizeof(njs_vm_t));
    if (njs_slow_path(vm == NULL)) {
        return NULL;
    }

    vm->mem_pool = mp;

    ret = njs_regexp_init(vm);
    if (njs_slow_path(ret != NJS_OK)) {
        return NULL;
    }

    njs_lvlhsh_init(&vm->values_hash);

    vm->options = *options;

    if (options->shared != NULL) {
        vm->shared = options->shared;

    } else {
        ret = njs_builtin_objects_create(vm);
        if (njs_slow_path(ret != NJS_OK)) {
            return NULL;
        }
    }

    vm->external = options->external;

    vm->trace.level = NJS_LEVEL_TRACE;
    vm->trace.size = 2048;
    vm->trace.data = vm;

    njs_set_undefined(&vm->retval);

    if (options->init) {
        ret = njs_vm_init(vm);
        if (njs_slow_path(ret != NJS_OK)) {
            return NULL;
        }
    }

    for (i = 0; njs_modules[i] != NULL; i++) {
        ret = njs_modules[i]->init(vm);
        if (njs_slow_path(ret != NJS_OK)) {
            return NULL;
        }
    }

    if (options->addons != NULL) {
        addons = options->addons;
        for (i = 0; addons[i] != NULL; i++) {
            ret = addons[i]->init(vm);
            if (njs_slow_path(ret != NJS_OK)) {
                return NULL;
            }
        }
    }

    vm->symbol_generator = NJS_SYMBOL_KNOWN_MAX;

    if (njs_scope_undefined_index(vm, 0) == NJS_INDEX_ERROR) {
        return NULL;
    }

    return vm;
}
