static int handlePoll(zloop_t __attribute__((unused)) * loop, zmq_pollitem_t *poller, void* pd) {
    smsg_t* pMsg;
    poller_data* pollerData = (poller_data*)pd;

    char* buf = zstr_recv(poller->socket);
    if (msgConstruct(&pMsg) == RS_RET_OK) {
        MsgSetRawMsg(pMsg, buf, strlen(buf));
        MsgSetInputName(pMsg, s_namep);
        MsgSetHOSTNAME(pMsg, glbl.GetLocalHostName(), ustrlen(glbl.GetLocalHostName()));
        MsgSetRcvFrom(pMsg, glbl.GetLocalHostNameProp());
        MsgSetRcvFromIP(pMsg, glbl.GetLocalHostIP());
        MsgSetMSGoffs(pMsg, 0);
        MsgSetFlowControlType(pMsg, eFLOWCTL_NO_DELAY);
        MsgSetRuleset(pMsg, pollerData->ruleset);
        pMsg->msgFlags = NEEDS_PARSING | PARSE_HOSTNAME;
        submitMsg2(pMsg);
    }
    
    /* gotta free the string returned from zstr_recv() */
    free(buf);
    
    if( pollerData->thread->bShallStop == TRUE) {
        /* a handler that returns -1 will terminate the 
           czmq reactor loop
        */
        return -1; 
    }
    
    return 0;
}
