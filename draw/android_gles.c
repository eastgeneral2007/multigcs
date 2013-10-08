/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* Ported from original test\common.c file. */

#include "SDL_config.h"
#include "SDL_test.h"

#include <stdio.h>

#define VIDEO_USAGE \
"[--video driver] [--renderer driver] [--gldebug] [--info all|video|modes|render|event] [--log all|error|system|audio|video|render|input] [--display N] [--fullscreen | --fullscreen-desktop | --windows N] [--title title] [--icon icon.bmp] [--center | --position X,Y] [--geometry WxH] [--min-geometry WxH] [--max-geometry WxH] [--logical WxH] [--scale N] [--depth N] [--refresh R] [--vsync] [--noframe] [--resize] [--minimize] [--maximize] [--grab]"

#define AUDIO_USAGE \
"[--rate N] [--format U8|S8|U16|U16LE|U16BE|S16|S16LE|S16BE] [--channels N] [--samples N]"

SDLTest_CommonState *
SDLTest_CommonCreateState(char **argv, Uint32 flags)
{
    SDLTest_CommonState *state = (SDLTest_CommonState *)SDL_calloc(1, sizeof(*state));
    if (!state) {
        SDL_OutOfMemory();
        return NULL;
    }

    /* Initialize some defaults */
    state->flags = flags;
    state->window_title = "TEST";
    state->window_flags = 0;
    state->window_x = SDL_WINDOWPOS_UNDEFINED;
    state->window_y = SDL_WINDOWPOS_UNDEFINED;
    state->window_w = DEFAULT_WINDOW_WIDTH;
    state->window_h = DEFAULT_WINDOW_HEIGHT;
    state->num_windows = 1;
    state->audiospec.freq = 22050;
    state->audiospec.format = AUDIO_S16;
    state->audiospec.channels = 2;
    state->audiospec.samples = 2048;

    /* Set some very sane GL defaults */
    state->gl_red_size = 3;
    state->gl_green_size = 3;
    state->gl_blue_size = 2;
    state->gl_alpha_size = 0;
    state->gl_buffer_size = 0;
    state->gl_depth_size = 16;
    state->gl_stencil_size = 0;
    state->gl_double_buffer = 1;
    state->gl_accum_red_size = 0;
    state->gl_accum_green_size = 0;
    state->gl_accum_blue_size = 0;
    state->gl_accum_alpha_size = 0;
    state->gl_stereo = 0;
    state->gl_multisamplebuffers = 0;
    state->gl_multisamplesamples = 0;
    state->gl_retained_backing = 1;
    state->gl_accelerated = -1;
    state->gl_debug = 0;

    return state;
}

const char *
SDLTest_CommonUsage(SDLTest_CommonState * state)
{
    switch (state->flags & (SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    case SDL_INIT_VIDEO:
        return VIDEO_USAGE;
    case SDL_INIT_AUDIO:
        return AUDIO_USAGE;
    case (SDL_INIT_VIDEO | SDL_INIT_AUDIO):
        return VIDEO_USAGE " " AUDIO_USAGE;
    default:
        return "";
    }
}

static void
SDLTest_PrintRendererFlag(Uint32 flag)
{
    switch (flag) {
    case SDL_RENDERER_PRESENTVSYNC:
        fprintf(stderr, "PresentVSync");
        break;
    case SDL_RENDERER_ACCELERATED:
        fprintf(stderr, "Accelerated");
        break;
    default:
        fprintf(stderr, "0x%8.8x", flag);
        break;
    }
}

static void
SDLTest_PrintPixelFormat(Uint32 format)
{
    switch (format) {
    case SDL_PIXELFORMAT_UNKNOWN:
        fprintf(stderr, "Unknwon");
        break;
    case SDL_PIXELFORMAT_INDEX1LSB:
        fprintf(stderr, "Index1LSB");
        break;
    case SDL_PIXELFORMAT_INDEX1MSB:
        fprintf(stderr, "Index1MSB");
        break;
    case SDL_PIXELFORMAT_INDEX4LSB:
        fprintf(stderr, "Index4LSB");
        break;
    case SDL_PIXELFORMAT_INDEX4MSB:
        fprintf(stderr, "Index4MSB");
        break;
    case SDL_PIXELFORMAT_INDEX8:
        fprintf(stderr, "Index8");
        break;
    case SDL_PIXELFORMAT_RGB332:
        fprintf(stderr, "RGB332");
        break;
    case SDL_PIXELFORMAT_RGB444:
        fprintf(stderr, "RGB444");
        break;
    case SDL_PIXELFORMAT_RGB555:
        fprintf(stderr, "RGB555");
        break;
    case SDL_PIXELFORMAT_BGR555:
        fprintf(stderr, "BGR555");
        break;
    case SDL_PIXELFORMAT_ARGB4444:
        fprintf(stderr, "ARGB4444");
        break;
    case SDL_PIXELFORMAT_ABGR4444:
        fprintf(stderr, "ABGR4444");
        break;
    case SDL_PIXELFORMAT_ARGB1555:
        fprintf(stderr, "ARGB1555");
        break;
    case SDL_PIXELFORMAT_ABGR1555:
        fprintf(stderr, "ABGR1555");
        break;
    case SDL_PIXELFORMAT_RGB565:
        fprintf(stderr, "RGB565");
        break;
    case SDL_PIXELFORMAT_BGR565:
        fprintf(stderr, "BGR565");
        break;
    case SDL_PIXELFORMAT_RGB24:
        fprintf(stderr, "RGB24");
        break;
    case SDL_PIXELFORMAT_BGR24:
        fprintf(stderr, "BGR24");
        break;
    case SDL_PIXELFORMAT_RGB888:
        fprintf(stderr, "RGB888");
        break;
    case SDL_PIXELFORMAT_BGR888:
        fprintf(stderr, "BGR888");
        break;
    case SDL_PIXELFORMAT_ARGB8888:
        fprintf(stderr, "ARGB8888");
        break;
    case SDL_PIXELFORMAT_RGBA8888:
        fprintf(stderr, "RGBA8888");
        break;
    case SDL_PIXELFORMAT_ABGR8888:
        fprintf(stderr, "ABGR8888");
        break;
    case SDL_PIXELFORMAT_BGRA8888:
        fprintf(stderr, "BGRA8888");
        break;
    case SDL_PIXELFORMAT_ARGB2101010:
        fprintf(stderr, "ARGB2101010");
        break;
    case SDL_PIXELFORMAT_YV12:
        fprintf(stderr, "YV12");
        break;
    case SDL_PIXELFORMAT_IYUV:
        fprintf(stderr, "IYUV");
        break;
    case SDL_PIXELFORMAT_YUY2:
        fprintf(stderr, "YUY2");
        break;
    case SDL_PIXELFORMAT_UYVY:
        fprintf(stderr, "UYVY");
        break;
    case SDL_PIXELFORMAT_YVYU:
        fprintf(stderr, "YVYU");
        break;
    default:
        fprintf(stderr, "0x%8.8x", format);
        break;
    }
}

static void
SDLTest_PrintRenderer(SDL_RendererInfo * info)
{
    int i, count;

    fprintf(stderr, "  Renderer %s:\n", info->name);

    fprintf(stderr, "    Flags: 0x%8.8X", info->flags);
    fprintf(stderr, " (");
    count = 0;
    for (i = 0; i < sizeof(info->flags) * 8; ++i) {
        Uint32 flag = (1 << i);
        if (info->flags & flag) {
            if (count > 0) {
                fprintf(stderr, " | ");
            }
            SDLTest_PrintRendererFlag(flag);
            ++count;
        }
    }
    fprintf(stderr, ")\n");

    fprintf(stderr, "    Texture formats (%d): ", info->num_texture_formats);
    for (i = 0; i < (int) info->num_texture_formats; ++i) {
        if (i > 0) {
            fprintf(stderr, ", ");
        }
        SDLTest_PrintPixelFormat(info->texture_formats[i]);
    }
    fprintf(stderr, "\n");

    if (info->max_texture_width || info->max_texture_height) {
        fprintf(stderr, "    Max Texture Size: %dx%d\n",
                info->max_texture_width, info->max_texture_height);
    }
}

static SDL_Surface *
SDLTest_LoadIcon(const char *file)
{
    SDL_Surface *icon;

    /* Load the icon surface */
    icon = SDL_LoadBMP(file);
    if (icon == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return (NULL);
    }

    if (icon->format->palette) {
        /* Set the colorkey */
        SDL_SetColorKey(icon, 1, *((Uint8 *) icon->pixels));
    }

    return (icon);
}

SDL_bool
SDLTest_CommonInit(SDLTest_CommonState * state)
{
    int i, j, m, n, w, h;
    SDL_DisplayMode fullscreen_mode;

    if (state->flags & SDL_INIT_VIDEO) {
        if (state->verbose & VERBOSE_VIDEO) {
            n = SDL_GetNumVideoDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in video drivers\n");
            } else {
                fprintf(stderr, "Built-in video drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        fprintf(stderr, ",");
                    }
                    fprintf(stderr, " %s", SDL_GetVideoDriver(i));
                }
                fprintf(stderr, "\n");
            }
        }
        if (SDL_VideoInit(state->videodriver) < 0) {
            fprintf(stderr, "Couldn't initialize video driver: %s\n",
                    SDL_GetError());
            return SDL_FALSE;
        }
        if (state->verbose & VERBOSE_VIDEO) {
            fprintf(stderr, "Video driver: %s\n",
                    SDL_GetCurrentVideoDriver());
        }

        /* Upload GL settings */
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, state->gl_red_size);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, state->gl_green_size);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, state->gl_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, state->gl_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, state->gl_double_buffer);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, state->gl_buffer_size);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, state->gl_depth_size);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, state->gl_stencil_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, state->gl_accum_red_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, state->gl_accum_green_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, state->gl_accum_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, state->gl_accum_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_STEREO, state->gl_stereo);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, state->gl_multisamplebuffers);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, state->gl_multisamplesamples);
        if (state->gl_accelerated >= 0) {
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,
                                state->gl_accelerated);
        }
        SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, state->gl_retained_backing);
        if (state->gl_major_version) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, state->gl_major_version);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, state->gl_minor_version);
        }
        if (state->gl_debug) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        }

        if (state->verbose & VERBOSE_MODES) {
            SDL_Rect bounds;
            SDL_DisplayMode mode;
            int bpp;
            Uint32 Rmask, Gmask, Bmask, Amask;

            n = SDL_GetNumVideoDisplays();
            fprintf(stderr, "Number of displays: %d\n", n);
            for (i = 0; i < n; ++i) {
                fprintf(stderr, "Display %d: %s\n", i, SDL_GetDisplayName(i));

                SDL_zero(bounds);
                SDL_GetDisplayBounds(i, &bounds);
                fprintf(stderr, "Bounds: %dx%d at %d,%d\n", bounds.w, bounds.h, bounds.x, bounds.y);

                SDL_GetDesktopDisplayMode(i, &mode);
                SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask, &Gmask,
                                           &Bmask, &Amask);
                fprintf(stderr,
                        "  Current mode: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                        mode.w, mode.h, mode.refresh_rate, bpp,
                        SDL_GetPixelFormatName(mode.format));
                if (Rmask || Gmask || Bmask) {
                    fprintf(stderr, "      Red Mask   = 0x%.8x\n", Rmask);
                    fprintf(stderr, "      Green Mask = 0x%.8x\n", Gmask);
                    fprintf(stderr, "      Blue Mask  = 0x%.8x\n", Bmask);
                    if (Amask)
                        fprintf(stderr, "      Alpha Mask = 0x%.8x\n", Amask);
                }

                /* Print available fullscreen video modes */
                m = SDL_GetNumDisplayModes(i);
                if (m == 0) {
                    fprintf(stderr, "No available fullscreen video modes\n");
                } else {
                    fprintf(stderr, "  Fullscreen video modes:\n");
                    for (j = 0; j < m; ++j) {
                        SDL_GetDisplayMode(i, j, &mode);
                        SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask,
                                                   &Gmask, &Bmask, &Amask);
                        fprintf(stderr,
                                "    Mode %d: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                                j, mode.w, mode.h, mode.refresh_rate, bpp,
                                SDL_GetPixelFormatName(mode.format));
                        if (Rmask || Gmask || Bmask) {
                            fprintf(stderr, "        Red Mask   = 0x%.8x\n",
                                    Rmask);
                            fprintf(stderr, "        Green Mask = 0x%.8x\n",
                                    Gmask);
                            fprintf(stderr, "        Blue Mask  = 0x%.8x\n",
                                    Bmask);
                            if (Amask)
                                fprintf(stderr,
                                        "        Alpha Mask = 0x%.8x\n",
                                        Amask);
                        }
                    }
                }
            }
        }

        if (state->verbose & VERBOSE_RENDER) {
            SDL_RendererInfo info;

            n = SDL_GetNumRenderDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in render drivers\n");
            } else {
                fprintf(stderr, "Built-in render drivers:\n");
                for (i = 0; i < n; ++i) {
                    SDL_GetRenderDriverInfo(i, &info);
                    SDLTest_PrintRenderer(&info);
                }
            }
        }

        SDL_zero(fullscreen_mode);
        switch (state->depth) {
        case 8:
            fullscreen_mode.format = SDL_PIXELFORMAT_INDEX8;
            break;
        case 15:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB555;
            break;
        case 16:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB565;
            break;
        case 24:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB24;
            break;
        default:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB888;
            break;
        }
        fullscreen_mode.refresh_rate = state->refresh_rate;

        state->windows =
            (SDL_Window **) SDL_malloc(state->num_windows *
                                        sizeof(*state->windows));
        state->renderers =
            (SDL_Renderer **) SDL_malloc(state->num_windows *
                                        sizeof(*state->renderers));
        if (!state->windows || !state->renderers) {
            fprintf(stderr, "Out of memory!\n");
            return SDL_FALSE;
        }
        for (i = 0; i < state->num_windows; ++i) {
            char title[1024];

            if (state->num_windows > 1) {
                SDL_snprintf(title, SDL_arraysize(title), "%s %d",
                             state->window_title, i + 1);
            } else {
                SDL_strlcpy(title, state->window_title, SDL_arraysize(title));
            }
            state->windows[i] =
                SDL_CreateWindow(title, state->window_x, state->window_y,
                                 state->window_w, state->window_h,
                                 state->window_flags);
            if (!state->windows[i]) {
                fprintf(stderr, "Couldn't create window: %s\n",
                        SDL_GetError());
                return SDL_FALSE;
            }
            if (state->window_minW || state->window_minH) {
                SDL_SetWindowMinimumSize(state->windows[i], state->window_minW, state->window_minH);
            }
            if (state->window_maxW || state->window_maxH) {
                SDL_SetWindowMaximumSize(state->windows[i], state->window_maxW, state->window_maxH);
            }
            SDL_GetWindowSize(state->windows[i], &w, &h);
            if (!(state->window_flags & SDL_WINDOW_RESIZABLE) &&
                (w != state->window_w || h != state->window_h)) {
                printf("Window requested size %dx%d, got %dx%d\n", state->window_w, state->window_h, w, h);
                state->window_w = w;
                state->window_h = h;
            }
            if (SDL_SetWindowDisplayMode(state->windows[i], &fullscreen_mode) < 0) {
                fprintf(stderr, "Can't set up fullscreen display mode: %s\n",
                        SDL_GetError());
                return SDL_FALSE;
            }

            if (state->window_icon) {
                SDL_Surface *icon = SDLTest_LoadIcon(state->window_icon);
                if (icon) {
                    SDL_SetWindowIcon(state->windows[i], icon);
                    SDL_FreeSurface(icon);
                }
            }

            SDL_ShowWindow(state->windows[i]);

            state->renderers[i] = NULL;

            if (!state->skip_renderer
                && (state->renderdriver
                    || !(state->window_flags & SDL_WINDOW_OPENGL))) {
                m = -1;
                if (state->renderdriver) {
                    SDL_RendererInfo info;
                    n = SDL_GetNumRenderDrivers();
                    for (j = 0; j < n; ++j) {
                        SDL_GetRenderDriverInfo(j, &info);
                        if (SDL_strcasecmp(info.name, state->renderdriver) ==
                            0) {
                            m = j;
                            break;
                        }
                    }
                    if (m == n) {
                        fprintf(stderr,
                                "Couldn't find render driver named %s",
                                state->renderdriver);
                        return SDL_FALSE;
                    }
                }
                state->renderers[i] = SDL_CreateRenderer(state->windows[i],
                                            m, state->render_flags);
                if (!state->renderers[i]) {
                    fprintf(stderr, "Couldn't create renderer: %s\n",
                            SDL_GetError());
                    return SDL_FALSE;
                }
                if (state->logical_w && state->logical_h) {
                    SDL_RenderSetLogicalSize(state->renderers[i], state->logical_w, state->logical_h);
                } else if (state->scale) {
                    SDL_RenderSetScale(state->renderers[i], state->scale, state->scale);
                }
                if (state->verbose & VERBOSE_RENDER) {
                    SDL_RendererInfo info;

                    fprintf(stderr, "Current renderer:\n");
                    SDL_GetRendererInfo(state->renderers[i], &info);
                    SDLTest_PrintRenderer(&info);
                }
            }
        }
    }

    if (state->flags & SDL_INIT_AUDIO) {
        if (state->verbose & VERBOSE_AUDIO) {
            n = SDL_GetNumAudioDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in audio drivers\n");
            } else {
                fprintf(stderr, "Built-in audio drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        fprintf(stderr, ",");
                    }
                    fprintf(stderr, " %s", SDL_GetAudioDriver(i));
                }
                fprintf(stderr, "\n");
            }
        }
        if (SDL_AudioInit(state->audiodriver) < 0) {
            fprintf(stderr, "Couldn't initialize audio driver: %s\n",
                    SDL_GetError());
            return SDL_FALSE;
        }
        if (state->verbose & VERBOSE_VIDEO) {
            fprintf(stderr, "Audio driver: %s\n",
                    SDL_GetCurrentAudioDriver());
        }

        if (SDL_OpenAudio(&state->audiospec, NULL) < 0) {
            fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
            return SDL_FALSE;
        }
    }

    return SDL_TRUE;
}

static void
SDLTest_PrintEvent(SDL_Event * event)
{
    if ((event->type == SDL_MOUSEMOTION) || (event->type == SDL_FINGERMOTION)) {
        /* Mouse and finger motion are really spammy */
        return;
    }

    fprintf(stderr, "SDL EVENT: ");
    switch (event->type) {
    case SDL_WINDOWEVENT:
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            fprintf(stderr, "Window %d shown", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            fprintf(stderr, "Window %d hidden", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            fprintf(stderr, "Window %d exposed", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            fprintf(stderr, "Window %d moved to %d,%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            fprintf(stderr, "Window %d resized to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            fprintf(stderr, "Window %d changed size to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            fprintf(stderr, "Window %d minimized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            fprintf(stderr, "Window %d maximized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            fprintf(stderr, "Window %d restored", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            fprintf(stderr, "Mouse entered window %d",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            fprintf(stderr, "Mouse left window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            fprintf(stderr, "Window %d gained keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            fprintf(stderr, "Window %d lost keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            fprintf(stderr, "Window %d closed", event->window.windowID);
            break;
        default:
            fprintf(stderr, "Window %d got unknown event %d",
                    event->window.windowID, event->window.event);
            break;
        }
        break;
    case SDL_KEYDOWN:
        fprintf(stderr,
                "Keyboard: key pressed  in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID,
                event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
    case SDL_KEYUP:
        fprintf(stderr,
                "Keyboard: key released in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID,
                event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
    case SDL_TEXTINPUT:
        fprintf(stderr, "Keyboard: text input \"%s\" in window %d",
                event->text.text, event->text.windowID);
        break;
    case SDL_MOUSEMOTION:
        fprintf(stderr, "Mouse: moved to %d,%d (%d,%d) in window %d",
                event->motion.x, event->motion.y,
                event->motion.xrel, event->motion.yrel,
                event->motion.windowID);
        break;
    case SDL_MOUSEBUTTONDOWN:
        fprintf(stderr, "Mouse: button %d pressed at %d,%d in window %d",
                event->button.button, event->button.x, event->button.y,
                event->button.windowID);
        break;
    case SDL_MOUSEBUTTONUP:
        fprintf(stderr, "Mouse: button %d released at %d,%d in window %d",
                event->button.button, event->button.x, event->button.y,
                event->button.windowID);
        break;
    case SDL_MOUSEWHEEL:
        fprintf(stderr,
                "Mouse: wheel scrolled %d in x and %d in y in window %d",
                event->wheel.x, event->wheel.y, event->wheel.windowID);
        break;
    case SDL_JOYBALLMOTION:
        fprintf(stderr, "Joystick %d: ball %d moved by %d,%d",
                event->jball.which, event->jball.ball, event->jball.xrel,
                event->jball.yrel);
        break;
    case SDL_JOYHATMOTION:
        fprintf(stderr, "Joystick %d: hat %d moved to ", event->jhat.which,
                event->jhat.hat);
        switch (event->jhat.value) {
        case SDL_HAT_CENTERED:
            fprintf(stderr, "CENTER");
            break;
        case SDL_HAT_UP:
            fprintf(stderr, "UP");
            break;
        case SDL_HAT_RIGHTUP:
            fprintf(stderr, "RIGHTUP");
            break;
        case SDL_HAT_RIGHT:
            fprintf(stderr, "RIGHT");
            break;
        case SDL_HAT_RIGHTDOWN:
            fprintf(stderr, "RIGHTDOWN");
            break;
        case SDL_HAT_DOWN:
            fprintf(stderr, "DOWN");
            break;
        case SDL_HAT_LEFTDOWN:
            fprintf(stderr, "LEFTDOWN");
            break;
        case SDL_HAT_LEFT:
            fprintf(stderr, "LEFT");
            break;
        case SDL_HAT_LEFTUP:
            fprintf(stderr, "LEFTUP");
            break;
        default:
            fprintf(stderr, "UNKNOWN");
            break;
        }
        break;
    case SDL_JOYBUTTONDOWN:
        fprintf(stderr, "Joystick %d: button %d pressed",
                event->jbutton.which, event->jbutton.button);
        break;
    case SDL_JOYBUTTONUP:
        fprintf(stderr, "Joystick %d: button %d released",
                event->jbutton.which, event->jbutton.button);
        break;
    case SDL_CLIPBOARDUPDATE:
        fprintf(stderr, "Clipboard updated");
        break;

    case SDL_FINGERDOWN:
    case SDL_FINGERUP:
        fprintf(stderr, "Finger: %s touch=%lld, finger=%lld, x=%f, y=%f, dx=%f, dy=%f, pressure=%f",
                (event->type == SDL_FINGERDOWN) ? "down" : "up",
                (long long) event->tfinger.touchId,
                (long long) event->tfinger.fingerId,
                event->tfinger.x, event->tfinger.y,
                event->tfinger.dx, event->tfinger.dy, event->tfinger.pressure);
        break;

    case SDL_QUIT:
        fprintf(stderr, "Quit requested");
        break;
    case SDL_USEREVENT:
        fprintf(stderr, "User event %d", event->user.code);
        break;
    default:
        fprintf(stderr, "Unknown event %d", event->type);
        break;
    }
    fprintf(stderr, "\n");
}

static void
SDLTest_ScreenShot(SDL_Renderer *renderer)
{
    SDL_Rect viewport;
    SDL_Surface *surface;

    if (!renderer) {
        return;
    }

    SDL_RenderGetViewport(renderer, &viewport);
    surface = SDL_CreateRGBSurface(0, viewport.w, viewport.h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
                    0x00FF0000, 0x0000FF00, 0x000000FF,
#else
                    0x000000FF, 0x0000FF00, 0x00FF0000,
#endif
                    0x00000000);
    if (!surface) {
        fprintf(stderr, "Couldn't create surface: %s\n", SDL_GetError());
        return;
    }

    if (SDL_RenderReadPixels(renderer, NULL, surface->format->format,
                             surface->pixels, surface->pitch) < 0) {
        fprintf(stderr, "Couldn't read screen: %s\n", SDL_GetError());
        return;
    }

    if (SDL_SaveBMP(surface, "screenshot.bmp") < 0) {
        fprintf(stderr, "Couldn't save screenshot.bmp: %s\n", SDL_GetError());
        return;
    }
}

static void
FullscreenTo(int index, int windowId)
{
    Uint32 flags;
    struct SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Window *window = SDL_GetWindowFromID(windowId);
    if (!window) {
        return;
    }

    SDL_GetDisplayBounds( index, &rect );

    flags = SDL_GetWindowFlags(window);
    if (flags & SDL_WINDOW_FULLSCREEN) {
        SDL_SetWindowFullscreen( window, SDL_FALSE );
        SDL_Delay( 15 );
    }

    SDL_SetWindowPosition( window, rect.x, rect.y );
    SDL_SetWindowFullscreen( window, SDL_TRUE );
}

void
SDLTest_CommonEvent(SDLTest_CommonState * state, SDL_Event * event, int *done)
{
    int i;
    static SDL_MouseMotionEvent lastEvent;

    if (state->verbose & VERBOSE_EVENT) {
        SDLTest_PrintEvent(event);
    }

    switch (event->type) {
    case SDL_WINDOWEVENT:
        switch (event->window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            {
                SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
                if (window) {
                    SDL_DestroyWindow(window);
                }
            }
            break;
        }
        break;
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {
            /* Add hotkeys here */
        case SDLK_PRINTSCREEN: {
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    for (i = 0; i < state->num_windows; ++i) {
                        if (window == state->windows[i]) {
                            SDLTest_ScreenShot(state->renderers[i]);
                        }
                    }
                }
            }
            break;
        case SDLK_EQUALS:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-+ double the size of the window */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    SDL_SetWindowSize(window, w*2, h*2);
                }
            }
            break;
        case SDLK_MINUS:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-- half the size of the window */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    SDL_SetWindowSize(window, w/2, h/2);
                }
            }
            break;
        case SDLK_c:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-C copy awesome text! */
                SDL_SetClipboardText("SDL rocks!\nYou know it!");
                printf("Copied text to clipboard\n");
            }
            if (event->key.keysym.mod & KMOD_ALT) {
                /* Alt-C toggle a render clip rectangle */
                for (i = 0; i < state->num_windows; ++i) {
                    int w, h;
                    if (state->renderers[i]) {
                        SDL_Rect clip;
                        SDL_GetWindowSize(state->windows[i], &w, &h);
                        SDL_RenderGetClipRect(state->renderers[i], &clip);
                        if (SDL_RectEmpty(&clip)) {
                            clip.x = w/4;
                            clip.y = h/4;
                            clip.w = w/2;
                            clip.h = h/2;
                            SDL_RenderSetClipRect(state->renderers[i], &clip);
                        } else {
                            SDL_RenderSetClipRect(state->renderers[i], NULL);
                        }
                    }
                }
            }
            break;
        case SDLK_v:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-V paste awesome text! */
                char *text = SDL_GetClipboardText();
                if (*text) {
                    printf("Clipboard: %s\n", text);
                } else {
                    printf("Clipboard is empty\n");
                }
                SDL_free(text);
            }
            break;
        case SDLK_g:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-G toggle grab */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    SDL_SetWindowGrab(window, !SDL_GetWindowGrab(window) ? SDL_TRUE : SDL_FALSE);
                }
            }
            break;
        case SDLK_m:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-M maximize */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_MAXIMIZED) {
                        SDL_RestoreWindow(window);
                    } else {
                        SDL_MaximizeWindow(window);
                    }
                }
            }
            break;
        case SDLK_r:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-R toggle mouse relative mode */
                SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode() ? SDL_TRUE : SDL_FALSE);
            }
            break;
        case SDLK_z:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-Z minimize */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    SDL_MinimizeWindow(window);
                }
            }
            break;
        case SDLK_RETURN:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-Enter toggle fullscreen */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_FULLSCREEN) {
                        SDL_SetWindowFullscreen(window, SDL_FALSE);
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_TRUE);
                    }
                }
            } else if (event->key.keysym.mod & KMOD_ALT) {
                /* Alt-Enter toggle fullscreen desktop */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_FULLSCREEN) {
                        SDL_SetWindowFullscreen(window, SDL_FALSE);
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                }
            }
            break;
        case SDLK_b:
            if (event->key.keysym.mod & KMOD_CTRL) {
                /* Ctrl-B toggle window border */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    const Uint32 flags = SDL_GetWindowFlags(window);
                    const SDL_bool b = ((flags & SDL_WINDOW_BORDERLESS) != 0) ? SDL_TRUE : SDL_FALSE;
                    SDL_SetWindowBordered(window, b);
                }
            }
            break;
        case SDLK_0:
            if (event->key.keysym.mod & KMOD_CTRL) {
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Test Message", "You're awesome!", window);
            }
            break;
        case SDLK_1:
            if (event->key.keysym.mod & KMOD_CTRL) {
                FullscreenTo(0, event->key.windowID);
            }
            break;
        case SDLK_2:
            if (event->key.keysym.mod & KMOD_CTRL) {
                FullscreenTo(1, event->key.windowID);
            }
            break;
        case SDLK_ESCAPE:
            *done = 1;
            break;
        case SDLK_SPACE:
        {
            char message[256];
            SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);

            SDL_snprintf(message, sizeof(message), "(%i, %i), rel (%i, %i)\n", lastEvent.x, lastEvent.y, lastEvent.xrel, lastEvent.yrel);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Last mouse position", message, window);
            break;
        }
        default:
            break;
        }
        break;
    case SDL_QUIT:
        *done = 1;
        break;
    case SDL_MOUSEMOTION:
        lastEvent = event->motion;
        break;
    }
}

void
SDLTest_CommonQuit(SDLTest_CommonState * state)
{
    int i;

    if (state->windows) {
        SDL_free(state->windows);
    }
    if (state->renderers) {
        for (i = 0; i < state->num_windows; ++i) {
            if (state->renderers[i]) {
                SDL_DestroyRenderer(state->renderers[i]);
            }
        }
        SDL_free(state->renderers);
    }
    if (state->flags & SDL_INIT_VIDEO) {
        SDL_VideoQuit();
    }
    if (state->flags & SDL_INIT_AUDIO) {
        SDL_AudioQuit();
    }
    SDL_free(state);
}

/* vi: set ts=4 sw=4 expandtab: */