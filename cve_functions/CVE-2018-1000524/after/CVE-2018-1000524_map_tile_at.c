map_tile_at(int x, int y, int layer)
{
	int layer_h;
	int layer_w;

	layer_w = s_map->layers[layer].width;
	layer_h = s_map->layers[layer].height;

	if (s_map->is_repeating || s_map->layers[layer].is_parallax) {
		x = (x % layer_w + layer_w) % layer_w;
		y = (y % layer_h + layer_h) % layer_h;
	}
	if (x < 0 || y < 0 || x >= layer_w || y >= layer_h)
		return -1;
	return layer_get_tile(layer, x, y);
}
