uripClose(void * context) {
    if (context == NULL) return(-1);
    urip_cur = NULL;
    urip_rlen = 0;
    return(0);
}
