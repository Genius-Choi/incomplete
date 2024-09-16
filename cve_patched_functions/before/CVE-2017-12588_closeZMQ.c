static void closeZMQ(instanceData* pData) {
    errmsg.LogError(0, NO_ERRCODE, "closeZMQ called");
    if(s_context && pData->socket) {
        if(pData->socket != NULL) {
            zsocket_destroy(s_context, pData->socket);
        }
    }
}
