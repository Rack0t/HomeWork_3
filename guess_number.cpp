#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <map>

void write_scores(const std::string &user_name, const int &attempts_count){
    const std::string high_scores_filename = "high_scores.txt";

    {
        std::ofstream out_file{high_scores_filename, std::ios_base::app};
        if (!out_file.is_open()){
            std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
            return;
        }

        // Append new results to the table:
        out_file << user_name << ' ';
        out_file << attempts_count;
        out_file << std::endl;
    }
}

/*
void high_scores(){
    const std::string high_scores_filename = "high_scores.txt";

    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        return;
    }

    std::cout << "High scores table:" << std::endl;

    std::string username;
    int high_score = 0;
    while (true) {
        // Read the username first
        in_file >> username;
        // Read the high score next
        in_file >> high_score;
        // Ignore the end of line symbol
        in_file.ignore();

        if (in_file.fail()) {
            break;
        }

        // Print the information to the screen
        std::cout << username << '\t' << high_score << std::endl;
    }
}
*/

void high_score_table(){
    std::ifstream in_file("high_scores.txt"); // Имя вашего текстового файла
    if (!in_file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::map<std::string, int> nameScores;
    std::string line;

    std::string username;
    int high_score = 0;
    while (true) {
        // Read the username first
        in_file >> username;
        // Read the high score next
        in_file >> high_score;
        // Ignore the end of line symbol
        in_file.ignore();
        if (nameScores.find(username) == nameScores.end() || high_score < nameScores[username]) {
            nameScores[username] = high_score;
        }
        if (in_file.fail()) {
            break;
        }
    }
    std::cout << "High scores table:" << std::endl;
    for (const auto& pair : nameScores) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {

    int max_value = 0;
    if ( argc >= 2){
        std::string arg1_value{argv[1]};

        if (arg1_value == "-max"){
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
                return -1;
            }
            max_value = std::stoi(argv[2]);
        }
        else if (arg1_value == "-level"){
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-level' requires some value!" << std::endl;
                return -1;
            }
            int case_value = std::stoi(argv[2]);
            switch (case_value)
            {
                case 1:
                    max_value = 10;
                    break;
                case 2:
                    max_value = 50;
                    break;
                default:
                    max_value = 100;
                    break;
            }
        }
        else if (arg1_value == "-table") {
//            high_scores();
            high_score_table();
            return 0;
        }
    }

    // Ask about name
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::string user_name;
    std::cin >> user_name;

    int attempts_count = 0;

    //const int max_value = 100;
    std::srand(std::time(nullptr));
    const int random_value = std::rand() % max_value;
    int current_value = 0;
    //bool not_win = true;

    std::cout << "Enter your guess:" << std::endl;

    do {
        std::cin >> current_value;

        attempts_count++;

        if (current_value < random_value) {
            std::cout << "less than " << current_value << std::endl;
        }
        else if (current_value > random_value) {
            std::cout << "greater than " << current_value << std::endl;
        }
        else {
            std::cout << "you win! attempts = " << attempts_count << std::endl;
            break;
        }
    } while(true);

    write_scores(user_name, attempts_count);
//    high_scores();
    high_score_table();

    return 0;
}