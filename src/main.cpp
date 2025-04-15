#include <SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <imnodes.h>
#include <SDL.h>
#include <stdio.h>
#include "NodeEditor.h"
#include "ImGuiFileDialog.h"

NodeEditor nodeEditor;

int main(int, char**) {
    printf("Debug: Starting main\n");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }
    printf("Debug: SDL initialized\n");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    printf("Debug: OpenGL attributes set\n");

    SDL_Window* window = SDL_CreateWindow("Node-Based Image Processor",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    printf("Debug: Window created\n");

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_Log("Failed to create GL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    printf("Debug: GL context created\n");
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);
    printf("Debug: GL context set\n");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    printf("Debug: ImGui context created\n");
    ImNodes::CreateContext();
    printf("Debug: ImNodes context created\n");

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    printf("Debug: ImGui SDL2 backend initialized\n");
    ImGui_ImplOpenGL3_Init("#version 330");
    printf("Debug: ImGui OpenGL3 backend initialized\n");

    // // Setup ImGuiFileDialog
    // IGFD::FileDialog::Instance()->SetExtentionInfos(".png", ImVec4(0,1,0,1));
    // IGFD::FileDialog::Instance()->SetExtentionInfos(".jpg", ImVec4(1,1,0,1));

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) done = true;
            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(window)) done = true;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        printf("Debug: ImGui frame started\n");

        ImGui::Begin("Node-Based Image Processor");

        // ImNodes::BeginNodeEditor();
        nodeEditor.Render();
        // ImNodes::EndNodeEditor();

        ImGui::End();

        // File dialog global render (required)
        // IGFD::FileDialog::Instance()->Display();
        IGFD::FileDialog::Instance()->Display("ChooseFileDlgKey", ImGuiWindowFlags_NoCollapse, ImVec2(700, 400), ImVec2(0, 0));

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    printf("Debug: Starting cleanup\n");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("Debug: Cleanup completed\n");

    return 0;
}

