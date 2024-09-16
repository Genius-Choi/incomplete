static apr_status_t shm_cleanup_wrapper(void *unused) {
    if (lua_ivm_shm) {
        return apr_shm_destroy(lua_ivm_shm);
    }
    return OK;
}
