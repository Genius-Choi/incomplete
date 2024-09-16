void *mp_realloc(lua_State *L, void *target, size_t osize,size_t nsize) {
    void *(*local_realloc) (void *, void *, size_t osize, size_t nsize) = NULL;
    void *ud;

    local_realloc = lua_getallocf(L, &ud);

    return local_realloc(ud, target, osize, nsize);
}
