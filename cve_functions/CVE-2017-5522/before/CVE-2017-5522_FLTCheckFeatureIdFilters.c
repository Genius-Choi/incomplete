int FLTCheckFeatureIdFilters(FilterEncodingNode *psFilterNode,
                             mapObj *map, int i)
{
    int status = MS_SUCCESS;
    
    if (psFilterNode->eType ==  FILTER_NODE_TYPE_FEATUREID)
    {
        char** tokens;
        int nTokens = 0;
        layerObj* lp;
        int j;

        lp = GET_LAYER(map, i);
        tokens = msStringSplit(psFilterNode->pszValue,',', &nTokens);
        for (j=0; j<nTokens; j++) {
            const char* pszId = tokens[j];
            const char* pszDot = strchr(pszId, '.');
            if( pszDot )
            {
                if( pszDot - pszId != strlen(lp->name) ||
                    strncasecmp(pszId, lp->name, strlen(lp->name)) != 0 )
                {
                    msSetError(MS_MISCERR, "Feature id %s not consistent with feature type name %s.",
                               "FLTPreParseFilterForAlias()", pszId, lp->name);
                    status = MS_FAILURE;
                    break;
                }
            }
        }
        msFreeCharArray(tokens, nTokens);
    }

    if (psFilterNode->psLeftNode)
    {
      status = FLTCheckFeatureIdFilters(psFilterNode->psLeftNode, map, i);
      if( status == MS_SUCCESS )
      {
        if (psFilterNode->psRightNode)
            status = FLTCheckFeatureIdFilters(psFilterNode->psRightNode, map, i);
      }
    }
    return status;
}
