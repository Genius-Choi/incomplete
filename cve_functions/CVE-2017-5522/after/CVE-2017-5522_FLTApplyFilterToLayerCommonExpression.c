int FLTApplyFilterToLayerCommonExpression(mapObj *map, int iLayerIndex, const char *pszExpression)
{
  return FLTApplyFilterToLayerCommonExpressionWithRect(map, iLayerIndex, pszExpression, map->extent);
}
