ar6000_pmkid_list_event(void *devt, u8 numPMKID, WMI_PMKID *pmkidList,
                        u8 *bssidList)
{
    u8 i, j;

    A_PRINTF("Number of Cached PMKIDs is %d\n", numPMKID);

    for (i = 0; i < numPMKID; i++) {
        A_PRINTF("\nBSSID %d ", i);
            for (j = 0; j < ATH_MAC_LEN; j++) {
                A_PRINTF("%2.2x", bssidList[j]);
            }
        bssidList += (ATH_MAC_LEN + WMI_PMKID_LEN);
        A_PRINTF("\nPMKID %d ", i);
            for (j = 0; j < WMI_PMKID_LEN; j++) {
                A_PRINTF("%2.2x", pmkidList->pmkid[j]);
            }
        pmkidList = (WMI_PMKID *)((u8 *)pmkidList + ATH_MAC_LEN +
                                  WMI_PMKID_LEN);
    }
}
