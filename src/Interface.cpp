#include "../include/Interface.hpp"

    Interface::Interface() {
    }

    Interface::~Interface() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Interface::initImgui(SDL_Window* window, SDL_GLContext* glContext) const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window, &glContext);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void Interface::beginFrame(SDL_Window* window) const {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }

    void Interface::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Interface::drawInterface(Scene &scene) {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGuiIO& io = ImGui::GetIO();
        const float DISTANCE = 5.0f;
        static int corner = 3;
        ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
        ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        if (ImGui::Begin("ImacraftSB tools", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 0.0f;
            ImGui::SetWindowSize(ImVec2(200, 300));

            ImVec2 sizeButtons = ImVec2(ImGui::GetWindowSize().x*0.75f, 0.0f);
            if (ImGui::Button("Create cube", sizeButtons)) {
                scene.addCube(glm::vec3(1, 0, 1));
            }

            if (ImGui::Button("Delete cube", sizeButtons)) {
                scene.deleteCube(glm::vec3(1, 0, 1));
            }

            if (ImGui::Button("Extrude cube", sizeButtons)) {
                scene.extrudeCube(glm::vec3(1, 0, 1));
            }

            if (ImGui::Button("Dig cube", sizeButtons)) {
                scene.digCube(glm::vec3(1, 0, 1));
            }
            ImGui::End();

        }

        //ImGui::ShowDemoWindow();
    }
