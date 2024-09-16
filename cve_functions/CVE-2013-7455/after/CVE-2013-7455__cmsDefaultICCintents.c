cmsPipeline*  CMSEXPORT _cmsDefaultICCintents(cmsContext     ContextID,
                                              cmsUInt32Number nProfiles,
                                              cmsUInt32Number TheIntents[],
                                              cmsHPROFILE     hProfiles[],
                                              cmsBool         BPC[],
                                              cmsFloat64Number AdaptationStates[],
                                              cmsUInt32Number dwFlags)
{
    return DefaultICCintents(ContextID, nProfiles, TheIntents, hProfiles, BPC, AdaptationStates, dwFlags);
}
