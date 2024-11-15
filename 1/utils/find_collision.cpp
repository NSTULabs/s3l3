#include <iostream>
#include <string>
#include <unordered_set>
#include <random>

uint32_t hash_function(const std::string& key) {
    uint32_t hash = 5381;
    for (char c : key) {
        hash = (hash << 5) + hash + c; // hash * 33 + c
    }
    return hash;
}

std::string generate_random_string(size_t length) {
    static const char chars[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<> dist(0, sizeof(chars) - 2);

    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += chars[dist(rng)];
    }
    return result;
}

void find_collision(const std::string& target_str) {
    uint32_t target_hash = hash_function(target_str);
    std::unordered_set<uint32_t> seen_hashes = { target_hash };
    int attempts = 0;

    while (true) {
        std::string random_str = generate_random_string(5); // Можно настроить длину случайных строк
        uint32_t hash = hash_function(random_str);
        attempts++;

        if (hash % 32 == target_hash % 32 && random_str != target_str) {
            std::cout << "Коллизия найдена после " << attempts << " попыток!" << std::endl;
            std::cout << "Строка 1: " << target_str << " с хешем: " << target_hash << std::endl;
            std::cout << "Строка 2: " << random_str << " с хешем: " << hash << std::endl;
            break;
        }
    }
}

int main() {
    std::string target = "a";
    find_collision(target);
    return 0;
}
