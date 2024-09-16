pango_glyph_string_free (PangoGlyphString *string)
{
  if (string == NULL)
    return;

  g_free (string->glyphs);
  g_free (string->log_clusters);
  g_slice_free (PangoGlyphString, string);
}
