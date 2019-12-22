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
        ImGui::Begin("ImacraftSB tools",&p_open,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar  |ImGuiWindowFlags_NoCollapse);
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                    if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
                    ImGui::EndMenu();
                }
            ImGui::EndMenuBar();
            }

            ImGui::ColorEdit4("Color", getColor());

            if (ImGui::Button("Create cube")) {
                scene.addCube(glm::vec3(1, 0, 1));
            }

            if (ImGui::Button("Delete cube")) {
                scene.deleteCube(glm::vec3(1, 0, 1));
            }

            if (ImGui::Button("Extrude cube")) {
                scene.extrudeCube(glm::vec3(1, 0, 1));
            }

            if (ImGui::Button("Dig cube")) {
                scene.digCube(glm::vec3(1, 0, 1));
            }

        ImGui::End();
    }
