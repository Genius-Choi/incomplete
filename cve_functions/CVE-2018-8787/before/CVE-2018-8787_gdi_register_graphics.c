BOOL gdi_register_graphics(rdpGraphics* graphics)
{
	rdpBitmap bitmap;
	rdpGlyph glyph;
	bitmap.size = sizeof(gdiBitmap);
	bitmap.New = gdi_Bitmap_New;
	bitmap.Free = gdi_Bitmap_Free;
	bitmap.Paint = gdi_Bitmap_Paint;
	bitmap.Decompress = gdi_Bitmap_Decompress;
	bitmap.SetSurface = gdi_Bitmap_SetSurface;
	graphics_register_bitmap(graphics, &bitmap);
	glyph.size = sizeof(gdiGlyph);
	glyph.New = gdi_Glyph_New;
	glyph.Free = gdi_Glyph_Free;
	glyph.Draw = gdi_Glyph_Draw;
	glyph.BeginDraw = gdi_Glyph_BeginDraw;
	glyph.EndDraw = gdi_Glyph_EndDraw;
	glyph.SetBounds = gdi_Glyph_SetBounds;
	graphics_register_glyph(graphics, &glyph);
	return TRUE;
}
