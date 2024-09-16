static void FLTRemoveGroupName(FilterEncodingNode *psFilterNode,
                               gmlGroupListObj* groupList)
{
  int i;

  if (psFilterNode) {

    if (psFilterNode->eType == FILTER_NODE_TYPE_PROPERTYNAME) {
      if( psFilterNode->pszValue != NULL )
      {
        const char* pszPropertyName = psFilterNode->pszValue;
        const char* pszSlash = strchr(pszPropertyName, '/');
        if( pszSlash != NULL ) {
          const char* pszColon = strchr(pszPropertyName, ':');
          if( pszColon != NULL && pszColon < pszSlash )
              pszPropertyName = pszColon + 1;
          for(i=0;i<groupList->numgroups;i++) {
            const char* pszGroupName = groupList->groups[i].name;
            size_t nGroupNameLen = strlen(pszGroupName);
            if(strncasecmp(pszPropertyName, pszGroupName, nGroupNameLen) == 0 &&
                            pszPropertyName[nGroupNameLen] == '/') {
              char* pszTmp;
              pszPropertyName = pszPropertyName + nGroupNameLen + 1;
              pszColon = strchr(pszPropertyName, ':');
              if( pszColon != NULL )
                pszPropertyName = pszColon + 1;
              pszTmp = msStrdup(pszPropertyName);
              msFree(psFilterNode->pszValue);
              psFilterNode->pszValue = pszTmp;
              break;
            }
          }
        }
      }
    }

    if (psFilterNode->psLeftNode)
      FLTRemoveGroupName(psFilterNode->psLeftNode, groupList);
    if (psFilterNode->psRightNode)
      FLTRemoveGroupName(psFilterNode->psRightNode, groupList);
  }

}
