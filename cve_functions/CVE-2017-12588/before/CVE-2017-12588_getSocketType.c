static int getSocketType(char* name) {
    int type = -1;
    uint i;
    
    /* match name with known socket type */
    for(i=0; i<sizeof(socketTypes)/sizeof(socket_type); ++i) {
        if( !strcmp(socketTypes[i].name, name) ) {
            type = socketTypes[i].type;
            break;
        }
    }
    
    /* whine if no match was found. */
    if (type == -1) 
        errmsg.LogError(0, NO_ERRCODE, "unknown type %s",name);
    
    return type;
}
