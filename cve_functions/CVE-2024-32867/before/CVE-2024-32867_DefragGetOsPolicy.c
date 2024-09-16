DefragGetOsPolicy(Packet *p)
{
    int policy = -1;

    if (PKT_IS_IPV4(p)) {
        policy = SCHInfoGetIPv4HostOSFlavour((uint8_t *)GET_IPV4_DST_ADDR_PTR(p));
    }
    else if (PKT_IS_IPV6(p)) {
        policy = SCHInfoGetIPv6HostOSFlavour((uint8_t *)GET_IPV6_DST_ADDR(p));
    }

    if (policy == -1) {
        return default_policy;
    }

    /* Map the OS policies returned from the configured host info to
     * defrag specific policies. */
    switch (policy) {
        /* BSD. */
    case OS_POLICY_BSD:
    case OS_POLICY_HPUX10:
    case OS_POLICY_IRIX:
        return DEFRAG_POLICY_BSD;

        /* BSD-Right. */
    case OS_POLICY_BSD_RIGHT:
        return DEFRAG_POLICY_BSD_RIGHT;

        /* Linux. */
    case OS_POLICY_OLD_LINUX:
    case OS_POLICY_LINUX:
        return DEFRAG_POLICY_LINUX;

        /* First. */
    case OS_POLICY_OLD_SOLARIS:
    case OS_POLICY_HPUX11:
    case OS_POLICY_MACOS:
    case OS_POLICY_FIRST:
        return DEFRAG_POLICY_FIRST;

        /* Solaris. */
    case OS_POLICY_SOLARIS:
        return DEFRAG_POLICY_SOLARIS;

        /* Windows. */
    case OS_POLICY_WINDOWS:
    case OS_POLICY_VISTA:
    case OS_POLICY_WINDOWS2K3:
        return DEFRAG_POLICY_WINDOWS;

        /* Last. */
    case OS_POLICY_LAST:
        return DEFRAG_POLICY_LAST;

    default:
        return default_policy;
    }
}
