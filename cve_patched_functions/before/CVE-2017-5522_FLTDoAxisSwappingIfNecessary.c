void FLTDoAxisSwappingIfNecessary(FilterEncodingNode *psFilterNode,
                                  int bDefaultSRSNeedsAxisSwapping)
{
    if( psFilterNode == NULL )
        return;

    if( psFilterNode->eType == FILTER_NODE_TYPE_SPATIAL &&
        psFilterNode->psRightNode->eType == FILTER_NODE_TYPE_BBOX )
    {
        rectObj* rect = (rectObj *)psFilterNode->psRightNode->pOther;
        const char* pszSRS = psFilterNode->pszSRS;
        if( (pszSRS != NULL && FLTNeedSRSSwapping(pszSRS)) ||
            (pszSRS == NULL && bDefaultSRSNeedsAxisSwapping) )
        {
            double tmp;

            tmp = rect->minx;
            rect->minx = rect->miny;
            rect->miny = tmp;

            tmp = rect->maxx;
            rect->maxx = rect->maxy;
            rect->maxy = tmp;
        }
    }
    else if( psFilterNode->eType == FILTER_NODE_TYPE_SPATIAL &&
             FLTIsGeometryFilterNodeType(psFilterNode->psRightNode->eType) )
    {
        shapeObj* shape = (shapeObj *)(psFilterNode->psRightNode->pOther);
        const char* pszSRS = psFilterNode->pszSRS;
        if( (pszSRS != NULL && FLTNeedSRSSwapping(pszSRS)) ||
            (pszSRS == NULL && bDefaultSRSNeedsAxisSwapping) )
        {
            msAxisSwapShape(shape);
        }
    }
    else
    {
        FLTDoAxisSwappingIfNecessary(psFilterNode->psLeftNode, bDefaultSRSNeedsAxisSwapping);
        FLTDoAxisSwappingIfNecessary(psFilterNode->psRightNode, bDefaultSRSNeedsAxisSwapping);
    }
}
