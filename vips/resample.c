#include "resample.h"

int shrink_image(VipsImage *in, VipsImage **out, double xshrink,
                 double yshrink) {
  return vips_shrink(in, out, xshrink, yshrink, NULL);
}

int reduce_image(VipsImage *in, VipsImage **out, double xshrink,
                 double yshrink) {
  return vips_reduce(in, out, xshrink, yshrink, NULL);
}

int affine_image(VipsImage *in, VipsImage **out, double a, double b, double c,
                 double d, VipsInterpolate *interpolator) {
  return vips_affine(in, out, a, b, c, d, "interpolate", interpolator, NULL);
}

int resize_image(VipsImage *in, VipsImage **out, double scale, gdouble vscale,
                 int kernel) {
  if (vscale > 0) {
    return vips_resize(in, out, scale, "vscale", vscale, "kernel", kernel,
                       NULL);
  }

  return vips_resize(in, out, scale, "kernel", kernel, NULL);
}

int thumbnail(const char *filename, VipsImage **out,
                    int width, int height, int crop, int size) {
  return vips_thumbnail(filename, out, width, "height", height,
                              "crop", crop, "size", size, NULL);
}

int thumbnail_image(VipsImage *in, VipsImage **out, int width, int height,
                    int crop, int size) {
  return vips_thumbnail_image(in, out, width, "height", height, "crop", crop,
                              "size", size, NULL);
}

int thumbnail_buffer_with_option(void *buf, size_t len, VipsImage **out,
                    int width, int height, int crop, int size,
                    const char *option_string) {
  return vips_thumbnail_buffer(buf, len, out, width, "height", height,
                              "crop", crop, "size", size,
                              "option_string", option_string, NULL);
}

int thumbnail_buffer(void *buf, size_t len, VipsImage **out,
                    int width, int height, int crop, int size) {
  return vips_thumbnail_buffer(buf, len, out, width, "height", height,
                              "crop", crop, "size", size, NULL);
}

int mapim(VipsImage *in, VipsImage **out, VipsImage *index) {
  return vips_mapim(in, out, index, NULL);
}

int maplut(VipsImage *in, VipsImage **out, VipsImage *lut) {
  return vips_maplut(in, out, lut, NULL);
}

int rotate(VipsImage *in, VipsImage **out, double angle, double r, double g, double b, double a) {
  double background[3] = {r, g, b};
  double backgroundRGBA[4] = {r, g, b, a};

  VipsArrayDouble *vipsBackground;

  // Ignore the alpha channel if the image doesn't have one
  if (in->Bands <= 3) {
    vipsBackground = vips_array_double_new(background, 3);
  } else {
    vipsBackground = vips_array_double_new(backgroundRGBA, 4);
  }

  int code = vips_rotate(in, out, angle, "background", vipsBackground, NULL);
  
  vips_area_unref(VIPS_AREA(vipsBackground));
  return code;
}


