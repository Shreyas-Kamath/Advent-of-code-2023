#include <string>
#include <fstream>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;

    std::string line; std::ifstream in("data.txt");

    const char* format = "%3s = (%3s, %3s)";

    while (std::getline(in, line))
    {
        char src[4], dest1[4], dest2[4];

        if (sscanf(line.c_str(), format, &src, &dest1, &dest2) == 3) {
            std::string s = src;
            std::string d1 = dest1;
            std::string d2 = dest2;

            map[s] = { d1, d2 };
        }
    }
    in.close();

    std::ifstream in2("steps.txt"); std::getline(in2, line);
    in2.close();

    std::string_view result = "AAA"; int steps{};

    while (result != "ZZZ")
    {
        char next = line[steps % line.length()];

        const auto& [left, right] = map[std::string(result)];
        result = (next == 'R') ? right : left;

        ++steps;
    }

    printf("%d", steps);
}