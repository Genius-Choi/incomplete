static void WM_InitPatches(void) {
    int i;
    for (i = 0; i < 128; i++) {
        _WM_patch[i] = NULL;
    }
}
