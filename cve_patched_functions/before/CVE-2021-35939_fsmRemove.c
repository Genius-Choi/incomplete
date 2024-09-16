static int fsmRemove(const char *path, mode_t mode)
{
    return S_ISDIR(mode) ? fsmRmdir(path) : fsmUnlink(path);
}
