int _wstati64(const wchar_t *path, cs_stat_t *st) {
  DWORD fa = GetFileAttributesW(path);
  if (fa == INVALID_FILE_ATTRIBUTES) {
    return -1;
  }
  memset(st, 0, sizeof(*st));
  if ((fa & FILE_ATTRIBUTE_DIRECTORY) == 0) {
    HANDLE h;
    FILETIME ftime;
    st->st_mode |= _S_IFREG;
    h = CreateFileW(path, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) {
      return -1;
    }
    st->st_size = GetFileSize(h, NULL);
    GetFileTime(h, NULL, NULL, &ftime);
    st->st_mtime = (uint32_t)((((uint64_t) ftime.dwLowDateTime +
                                ((uint64_t) ftime.dwHighDateTime << 32)) /
                               10000000.0) -
                              11644473600);
    CloseHandle(h);
  } else {
    st->st_mode |= _S_IFDIR;
  }
  return 0;
}
