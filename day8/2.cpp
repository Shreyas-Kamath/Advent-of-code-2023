#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

int main() {
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;

    std::vector<std::string> starting_points;

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

            if (s.ends_with('A')) starting_points.push_back(s);
        }
        
    }
    in.close();

    std::ifstream in2("steps.txt"); std::getline(in2, line);
    in2.close();
    std::unordered_map<std::string, long long> steps_needed;

    for (const auto& start: starting_points) {
        std::string_view result = start;
        long long steps{};

        while (!result.ends_with('Z'))
        {
            char next = line[steps % line.length()];

            const auto& [left, right] = map[std::string(result)];
            result = (next == 'R') ? right : left;

            ++steps;
        }
        steps_needed[start] = steps;
    }
    
    long long ans = std::ranges::fold_left(steps_needed | std::views::values, 1LL, std::lcm<long long, long long>);

    printf("%lld", ans);
}