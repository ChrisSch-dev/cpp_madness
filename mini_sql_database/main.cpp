#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

struct Row { int id; std::string name; };
std::vector<Row> table;

void save() {
    std::ofstream out("db.txt");
    for (auto& r : table) out << r.id << " " << r.name << "\n";
}
void load() {
    std::ifstream in("db.txt");
    int id; std::string name;
    while (in >> id >> name) table.push_back({id, name});
}
void insert(const std::string& name) {
    int id = table.empty() ? 1 : table.back().id + 1;
    table.push_back({id, name});
    save();
    std::cout << "Inserted: " << id << ", " << name << std::endl;
}
void select(const std::string& cond = "") {
    std::cout << "ID\tName\n";
    for (auto& r : table)
        if (cond.empty() || r.name == cond)
            std::cout << r.id << "\t" << r.name << "\n";
}
void update(int id, const std::string& newname) {
    for (auto& r : table) if (r.id == id) r.name = newname;
    save();
}
void remove(int id) {
    table.erase(std::remove_if(table.begin(), table.end(),
        [&](Row& r){ return r.id == id; }), table.end());
    save();
}
int main() {
    load();
    std::string cmd;
    std::cout << "Mini SQL. Commands: insert <name>, select, update <id> <name>, delete <id>, exit\n";
    while (true) {
        std::cout << "sql> ";
        std::getline(std::cin, cmd);
        std::istringstream iss(cmd);
        std::string w; iss >> w;
        if (w == "insert") { std::string name; iss >> name; insert(name); }
        else if (w == "select") { std::string n; iss >> n; select(n); }
        else if (w == "update") { int id; std::string name; iss >> id >> name; update(id,name);}
        else if (w == "delete") { int id; iss >> id; remove(id);}
        else if (w == "exit") break;
        else std::cout << "Unknown command.\n";
    }
}