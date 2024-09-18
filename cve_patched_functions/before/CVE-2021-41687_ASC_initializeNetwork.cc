ASC_initializeNetwork(T_ASC_NetworkRole role,
                      int acceptorPort,
                      int timeout,
                      T_ASC_Network ** network,
                      unsigned long options)
{
    const char *mode;

    DUL_NETWORKKEY * netkey;

    switch (role) {
    case NET_ACCEPTOR:
        mode = DUL_AEACCEPTOR;
        break;
    case NET_REQUESTOR:
        mode = DUL_AEREQUESTOR;
        break;
    case NET_ACCEPTORREQUESTOR:
        mode = DUL_AEBOTH;
        break;
    default:
        mode = "unknown";
        break;
    }

    OFCondition cond = DUL_InitializeNetwork(mode, &acceptorPort, timeout, DUL_ORDERBIGENDIAN | options, &netkey);
    if (cond.bad()) return cond;

    *network = (T_ASC_Network *) malloc(sizeof(T_ASC_Network));
    if (*network == NULL) return EC_MemoryExhausted;
    (*network)->role = role;
    (*network)->acceptorPort = acceptorPort;
    (*network)->network = netkey;

    return EC_Normal;
}
