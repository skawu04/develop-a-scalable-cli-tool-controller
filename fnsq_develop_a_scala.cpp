#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Define a command structure
struct Command {
    std::string name;
    std::string description;
    std::vector<std::string> args;
    std::function<void(const std::vector<std::string>&)> handler;
};

// Define a controller class
class CliController {
private:
    std::map<std::string, Command> commands;

public:
    void addCommand(const Command& command) {
        commands[command.name] = command;
    }

    void run(const std::string& commandName, const std::vector<std::string>& args) {
        if (commands.find(commandName) != commands.end()) {
            commands[commandName].handler(args);
        } else {
            std::cerr << "Unknown command: " << commandName << std::endl;
        }
    }

    void listCommands() {
        std::cout << "Available commands:" << std::endl;
        for (const auto& command : commands) {
            std::cout << "  " << command.first << " - " << command.second.description << std::endl;
        }
    }
};

int main() {
    CliController controller;

    // Define some sample commands
    Command helpCommand = {"help", "Show available commands", {}, [](const std::vector<std::string>&) {
        controller.listCommands();
    }};
    Command greetCommand = {"greet", "Greet a person", {"name"}, [](const std::vector<std::string>& args) {
        std::cout << "Hello, " << args[0] << "!" << std::endl;
    }};

    // Add commands to the controller
    controller.addCommand(helpCommand);
    controller.addCommand(greetCommand);

    // Run some sample commands
    controller.run("help", {});
    controller.run("greet", {"John"});

    return 0;
}