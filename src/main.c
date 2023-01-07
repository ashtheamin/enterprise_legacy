// Enterprise by Ash Amin. (Copyright 2023)

// Third Party Disclosure: This program code is based on the code here: 
// https://github.com/Immediate-Mode-UI/Nuklear/blob/master/demo/sdl_opengl2/main.c
// It is licensed under the MIT.
// Big thank you to the Nuklear team for providing the GUI API.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GLES2_IMPLEMENTATION

// Import libraries
#include "constants.c"
#include "../third_party/Nuklear/nuklear.h"
#include "../third_party/Nuklear/demo/sdl_opengles2/nuklear_sdl_gles2.h"
#include "../third_party/Nuklear/demo/common/style.c"

// Define the program state structure used to hold everything.
enum program_status {program_status_quit, program_status_running,
};
struct program {
    SDL_Window* window;
    struct nk_context *nk_context;
    SDL_GLContext glctx;
    enum program_status status;
};

// Initialise a new program state and initialise associated libraries.
// Returns program state pointer on success, or NULL on failure.
struct program* program_init() {
    // Allocate program state memory and return pointer to it.
    struct program* program = malloc(sizeof(struct program));
    if (program == NULL) return NULL;

    // Initialise SDL.
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, 
    SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, 
    SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Initialise SDL Window
    program->window = SDL_CreateWindow("Enterprise",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL|
    SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);

    // Return NULL and free resources on failure
    if (program->window == NULL) 
    printf("SDL_GetError(): %s", SDL_GetError());SDL_Quit();
    free(program);return NULL;

    // Initialise OpenGL
    program->glctx = SDL_GL_CreateContext(program->window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Initialise Nuklear library context. 
    // Return NULL and free resources on failure.
    program->nk_context = nk_sdl_init(program->window);
    if (program->nk_context == NULL) 
    SDL_GL_DeleteContext(program->glctx);SDL_DestroyWindow(program->window);
    SDL_Quit();free(program);return NULL;

    // Initialise font
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(atlas, 
    "../third_party/Nuklear/extra_font/ProggyClean.ttf",
    ENTERPRISE_FONT_SIZE, 0);
    nk_sdl_font_stash_end();

    // Return NULL if font failed to load.
    if (font == NULL) nk_sdl_shutdown();SDL_GL_DeleteContext(program->glctx);
    SDL_DestroyWindow(program->window);SDL_Quit();free(program);return NULL;
    nk_style_set_font(program->nk_context, &font->handle);

    // Return program pointer.
    return program;
}

// Runs the main loop of the program
void program_loop(void* loop_argument) {
    // Load in the program state.
    struct program* program = (struct program*)loop_argument;

    // Handle SDL Input
    SDL_Event evt;
    nk_input_begin(program->nk_context);
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) program->status = program_status_quit;
        nk_sdl_handle_event(&evt);
    }
    nk_input_end(program->nk_context);


    // Initialise and draw Nuklear GUI widgets + elements.
    if (nk_begin(program->nk_context, "Enterprise", 
    nk_rect(50, 50, WINDOW_WIDTH, WINDOW_HEIGHT),NK_WINDOW_BORDER)) {
        nk_layout_row_dynamic(program->nk_context, 40, 1);
        nk_label(program->nk_context, "Enterprise", NK_TEXT_CENTERED);
    }
    nk_end(program->nk_context);

    // Render the GUI.
    float bg[4];
    int win_width, win_height;
    nk_color_fv(bg, nk_rgb(28,48,62));
    SDL_GetWindowSize(program->window, &win_width, &win_height);
    glViewport(0, 0, win_width, win_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg[0], bg[1], bg[2], bg[3]);
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    SDL_GL_SwapWindow(program->window);
}

// Free all resources and exit.
void program_quit(struct program* program) {
    if (program == NULL) return;
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(program->glctx);
    SDL_DestroyWindow(program->window);
    SDL_Quit();
    free(program);
}

int main() {
    // Initailise the program state and everything required.
    // Return to OS on failure to initialise.
    struct program* program = program_init();
    if (program == NULL) return -1;

    // Run the main program loop, 
    // differently based on whether program is native or on web.
    #if defined(__EMSCRIPTEN__)
        #include <emscripten.h>
        emscripten_set_main_loop_arg(program_loop, (void*)program, 0, 1);
    #else
        while (program->status ) program_loop((void*)program);
    #endif

    // Free all resources associated with program and exit.
    void program_quit(struct program* program);
    return 0;
}
