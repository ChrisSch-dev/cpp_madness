#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "../src/chat_client.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Chat Client (ImGui)");
    ImGui::SFML::Init(window);

    ChatClient client;
    std::string host = "127.0.0.1";
    unsigned short port = 12345;
    char input[256] = "";
    std::vector<std::string> messages;
    bool connected = false;
    std::string status = "Disconnected";

    client.set_on_message([&](const std::string& msg) {
        messages.push_back(msg);
    });

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Chat");
        if (!connected) {
            ImGui::InputText("Host", &host[0], host.size() + 1);
            ImGui::InputScalar("Port", ImGuiDataType_U16, &port);
            if (ImGui::Button("Connect")) {
                connected = client.connect(host, port);
                status = connected ? "Connected" : "Failed to connect";
            }
            ImGui::Text("%s", status.c_str());
        } else {
            if (ImGui::Button("Disconnect")) {
                client.close(); connected = false; status = "Disconnected";
            }
            ImGui::Text("Messages:");
            ImGui::BeginChild("msglist", ImVec2(0, 200), true);
            for (const auto& m : messages)
                ImGui::Text("%s", m.c_str());
            ImGui::EndChild();
            ImGui::InputText("Message", input, sizeof(input));
            ImGui::SameLine();
            if (ImGui::Button("Send")) {
                client.send(input); strcpy(input, "");
            }
        }
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    client.close();
    return 0;
}