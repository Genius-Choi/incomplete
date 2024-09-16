static int FLTIsGeometryFilterNodeType(int eType)
{
    return (eType == FILTER_NODE_TYPE_GEOMETRY_POINT ||
            eType == FILTER_NODE_TYPE_GEOMETRY_LINE ||
            eType == FILTER_NODE_TYPE_GEOMETRY_POLYGON);
}
