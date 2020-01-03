#include "../include/Interface.hpp"

Interface::Interface(SDL_Window* window, SDL_GLContext* glContext) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, &glContext);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

Interface::~Interface() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
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

void Interface::drawInterface(Scene &scene, const Cursor &cursor, const Texture &texture, Lights &lights) {
    
    ImGuiIO &i_io = ImGui::GetIO();
    ImGuiStyle &i_style = ImGui::GetStyle();
    i_style.WindowRounding = 0.2f;

    const float distance = 5.0f;
    static uint radioSelect = 0;

    std::string menu_action = "";

    // Menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) {
                menu_action = "open";
                // std::string test;
                // std::cout << "enter file name : ";
                // std::cin >> test;
                // scene.loadScene(test);
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                menu_action = "save";
                // std::string test;
                // std::cout << "enter file name : ";
                // std::cin >> test;
                // scene.saveScene(test);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if(menu_action == "open") { ImGui::OpenPopup("Open"); }
    if(menu_action == "save") { ImGui::OpenPopup("Save"); }

    if(ImGui::BeginPopup("Open")) {
        ImVec2 sizeButtons = ImVec2(ImGui::GetWindowSize().x-16.0f, 0.0f);
        if (ImGui::Button("Open scene", sizeButtons)) {
            std::string test;
            std::cout << "enter file name : ";
            std::cin >> test;
            scene.loadScene(test);
        }
        ImGui::EndPopup();
    }

    if(ImGui::BeginPopup("Save")) {
        ImVec2 sizeButtons = ImVec2(ImGui::GetWindowSize().x-16.0f, 0.0f);
        char fileName[128] = "";
        if (ImGui::InputTextWithHint("", "enter file name", fileName, sizeof(fileName))) {
        // input doesn't work, have to name the file in the terminal
            std::cout << "test : " << i_io.KeyMap[ImGuiKey_Backspace] << std::endl;
        }
        if (ImGui::Button("Save scene", sizeButtons)) {
            // std::string test;
            // std::cout << "enter file name : ";
            // std::cin >> test;
            std::string fileNameStg(fileName);
            scene.saveScene(fileNameStg);
        }
        ImGui::EndPopup();
    }


    // Toolbox
    int corner = 3;
    ImVec2 window_pos = ImVec2((corner & 1) ? i_io.DisplaySize.x - distance : distance, (corner & 2) ? i_io.DisplaySize.y - distance : distance);
    ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    if (ImGui::Begin("Toolbox", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::SetWindowSize(ImVec2(185, 315));
        ImVec2 sizeButtons = ImVec2(ImGui::GetWindowSize().x-16.0f, 0.0f);

        if (ImGui::Button("Create cube", sizeButtons)) {
            scene.addCube(cursor.getPosition(), glm::vec3(i_color.x, i_color.y, i_color.z), radioSelect);
        }
        if (ImGui::Button("Delete cube", sizeButtons)) {
            scene.deleteCube(cursor.getPosition());
        }
        if (ImGui::Button("Extrude cube", sizeButtons)) {
            scene.extrudeCube(cursor.getPosition());
        }
        if (ImGui::Button("Dig cube", sizeButtons)) {
            scene.digCube(cursor.getPosition());
        }

        // Color
        ImGui::NewLine();
        ImGui::TextWrapped("Color:");
        ImGui::ColorEdit3("", (float*)&i_color);
        if (ImGui::Button("Add color", sizeButtons)) {
            scene.changeColorCube(cursor.getPosition(), glm::vec3(i_color.x, i_color.y, i_color.z));
        }
        if (ImGui::Button("Delete color", sizeButtons)) {
            scene.changeColorCube(cursor.getPosition());
        }

        // Texture
        ImGui::NewLine();
        ImGui::TextWrapped("Texture:");
        if (ImGui::Button("Add texture", sizeButtons)) {
            scene.changeTextureCube(cursor.getPosition(), radioSelect);
        }
        if (ImGui::Button("Delete texture", sizeButtons)) {
            scene.changeTextureCube(cursor.getPosition(), 0);
        }

        ImGui::End();
    }

    // Texturebox
    corner = 2;
    window_pos = ImVec2((corner & 1) ? i_io.DisplaySize.x - distance : distance, (corner & 2) ? i_io.DisplaySize.y - distance : distance);
    window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    if (ImGui::Begin("Texturebox", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::SetWindowSize(ImVec2(230, 175));
        
        for (uint i = 0; i < texture.getCubeReferences().size(); i++) {
            bool popColor = false;
            ImGui::PushID(i);
            if(radioSelect == i){
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); 
                popColor = true;
            }
            ImTextureID textureRadio = (void*)(intptr_t)(texture.getCubeReferences()[i].t_cubeRadio);
            if (ImGui::ImageButton(textureRadio, ImVec2(32,32), ImVec2(0,0), ImVec2(1,1), 2)){
                radioSelect = i;
            }
            if(popColor){
                ImGui::PopStyleColor();
            }
            ImGui::PopID();
            if((i+1)%5 != 0){
                ImGui::SameLine();
            }
        }

        ImGui::End();
    }

    // Lightbox
    corner = 1;
    window_pos = ImVec2((corner & 1) ? i_io.DisplaySize.x - distance : distance, (corner & 2) ? i_io.DisplaySize.y - distance : distance);
    window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    if (ImGui::Begin("Lightbox", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::SetWindowSize(ImVec2(185, 145));
        ImVec2 sizeButtons = ImVec2(ImGui::GetWindowSize().x-16.0f, 0.0f);

        // Lights
        ImGui::TextWrapped("Light:");
        if (ImGui::Button("Switch day/night", sizeButtons)) {
            lights.switchDayNight();
        }
        if (ImGui::Button("Add ponctual light", sizeButtons)) {
            lights.addPonctualLight(cursor.getPosition());
        }
        if (ImGui::Button("Remove ponctual light", sizeButtons)) {
            lights.removePonctualLight(cursor.getPosition());
        }
        if (ImGui::Button("Reset lights", sizeButtons)) {
            lights.removeAllPonctualLight();
        }


        ImGui::End();
    }


    //ImGui::ShowDemoWindow();
}

bool Interface::isMouseOnInterface() const {
    ImGuiIO &i_io = ImGui::GetIO();
    return i_io.WantCaptureMouse;
}

