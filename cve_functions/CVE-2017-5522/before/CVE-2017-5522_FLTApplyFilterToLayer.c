int FLTApplyFilterToLayer(FilterEncodingNode *psNode, mapObj *map, int iLayerIndex)
{
  layerObj *layer = GET_LAYER(map, iLayerIndex);

  if ( ! layer->vtable) {
    int rv =  msInitializeVirtualTable(layer);
    if (rv != MS_SUCCESS)
      return rv;
  }
  return layer->vtable->LayerApplyFilterToLayer(psNode, map,  iLayerIndex);
}
