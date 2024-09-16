static int gdRotatedImageSize(gdImagePtr src, const float angle, gdRectPtr bbox)
{
    gdRect src_area;
    double m[6];

    gdAffineRotate(m, angle);
    src_area.x = 0;
    src_area.y = 0;
    src_area.width = gdImageSX(src);
    src_area.height = gdImageSY(src);
    if (gdTransformAffineBoundingBox(&src_area, m, bbox) != GD_TRUE) {
        return GD_FALSE;
    }

    return GD_TRUE;
}
