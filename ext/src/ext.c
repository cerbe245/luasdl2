
#include <common/common.h>
#include <common/surface.h>

/* Invert the colors in an SDL_Surface */
static int invert_surface (lua_State *L)
{
  SDL_Surface *srf = commonGetAs(L, 1, SurfaceName, SDL_Surface *);
  int alpha = lua_gettop(L) > 1;
  SDL_PixelFormat *fmt = srf->format;
  int w = srf->w, h = srf->h;

  /* Easy out, just iterate through all colors. */
  if (fmt->BytesPerPixel == 1) {
    for (int i = 0; i < fmt->palette->ncolors; ++i) {
      SDL_Color *color = &fmt->palette->colors[i];
      color->r = 255 - color->r;
      color->g = 255 - color->g;
      color->b = 255 - color->b;
      if (alpha) color->a = 255 - color->a;
    }
    return 0;
  }

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      Uint32 pixel;
      Uint8 r,g,b,a;
      Uint8 *rawpixel = (Uint8 *)srf->pixels + y * srf->pitch + x * fmt->BytesPerPixel;
      switch(fmt->BytesPerPixel) {
        case 2:
          SDL_GetRGBA(*(Uint16 *)rawpixel, fmt, &r, &g, &b, &a);
          if (alpha) a = 255 - a;
          *(Uint16 *)rawpixel = SDL_MapRGBA(fmt, 255 - r, 255 - g, 255 - b, a);
          break;
        case 3:
          pixel = rawpixel[0];
          pixel = pixel << 8 | rawpixel[1];
          pixel = pixel << 8 | rawpixel[2];

          SDL_GetRGBA(pixel, fmt, &r, &g, &b, &a);
          if (alpha) a = 255 - a;
          pixel = SDL_MapRGBA(fmt, 255 - r, 255 - g, 255 - b, a);

          rawpixel[0] = pixel >> 16 & 0xff;
          rawpixel[1] = pixel >> 8 & 0xff;
          rawpixel[2] = pixel & 0xff;
          break;
        case 4:
          SDL_GetRGBA(*(Uint32 *)rawpixel, fmt, &r, &g, &b, &a);
          if (alpha) a = 255 - a;
          *(Uint32 *)rawpixel = SDL_MapRGBA(fmt, 255 - r, 255 - g, 255 - b, a);
          break;
      }
    }
  }

  return 0;
}

luaL_Reg funcs[] = {
  { "invertSurface", invert_surface },
  { NULL, NULL }
};

extern int luaopen_SDL_ext(lua_State *L)
{
  commonNewLibrary(L, funcs);
  return 1;
}
