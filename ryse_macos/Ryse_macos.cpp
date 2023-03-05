/*
    Developers 
    Darryl Abueg
    Richard Host
    Sean Gonzaga
*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

std::string get_intro();
std::vector<std::string> get_dilemmas();
std::vector<std::vector<std::vector<int> > > get_consqs();
std::vector<std::string> get_endings();
void typewriter(const std::string &text);
void display_hud();
void ending_screen();
void score_screen();
bool ask_quit();
bool run_game();

int welfare, resources, military, politics, geography, days = 0;
std::string intro = get_intro();
std::vector<std::string> dilemmas = get_dilemmas();
std::vector<std::vector<std::vector<int> > > consqs = get_consqs();
std::vector<std::string> endings = get_endings();

int main()
{
    std::fstream f_title("resources/title.txt", std::ifstream::in);
    std::string title;
    char choice;
    bool quit = false;

    system("clear");
    getline(f_title, title, '=');
    std::cout << title << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << std::setw(65) << "[Enter A] Start" << std::endl;
    std::cout << '\n'
              << std::setw(53) << ">> ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    choice = toupper(choice);

    if (choice == 'A')
    {
        // Intro
        system("clear");
        typewriter(intro);
        std::cout << "\n\nEnter any key to continue...";
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (!quit)
        {
            quit = run_game();
        }
    }
    return 0;
}

std::string get_intro()
{
    std::fstream f_intro("resources/intro.txt", std::ifstream::in);
    std::string intro_text;
    getline(f_intro, intro_text, '_');
    return intro_text;
}

std::vector<std::string> get_dilemmas()
{
    std::fstream f_dilemmas("resources/dilemmas.txt", std::ifstream::in);
    std::string dilemma;
    std::vector<std::string> all_dilemmas;

    while (getline(f_dilemmas, dilemma, '_'))
    {
        all_dilemmas.push_back(dilemma);
    }
    f_dilemmas.close();

    return all_dilemmas;
}

std::vector<std::vector<std::vector<int> > > get_consqs()
{
    std::fstream f_consequences("resources/consequences.txt", std::ifstream::in);
    std::string num;
    std::vector<int> consq;
    std::vector<std::vector<int> > two_consq;
    std::vector<std::vector<std::vector<int> > > all_consqs;

    while (getline(f_consequences, num, ','))
    {
        consq.push_back(stoi(num));
        if (consq.size() == 5)
        {
            two_consq.push_back(consq);
            consq.clear();
        }

        if (two_consq.size() == 2)
        {
            all_consqs.push_back(two_consq);
            two_consq.clear();
        }
    }
    f_consequences.close();

    return all_consqs;
}

std::vector<std::string> get_endings()
{
    std::fstream f_endings("resources/endings.txt", std::ifstream::in);
    std::string line;
    std::vector<std::string> endings;

    while (getline(f_endings, line, '_'))
    {
        endings.push_back(line);
    }
    f_endings.close();

    return endings;
}

void typewriter(const std::string &text)
{
    for (const char &c : text)
    {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

void display_hud()
{
    system("clear");
    std::cout << '\n'
              << std::setfill('-') << std::setw(130) << " Day " << days << std::endl;
    std::cout << std::setfill(' ') << std::setw(20) << "Welfare: " << welfare
              << std::setw(20) << "Resources: " << resources
              << std::setw(20) << "Military: " << military
              << std::setw(20) << "Politics: " << politics
              << std::setw(20) << "Geography: " << geography << std::endl;
}

void ending_screen()
{
    system("clear");
    std::string end_type;
    if (!welfare)
    {
        end_type = endings[1];
    }
    else if (!resources)
    {
        end_type = endings[2];
    }
    else if (!military)
    {
        end_type = endings[3];
    }
    else if (!politics)
    {
        end_type = endings[4];
    }
    else if (!geography)
    {
        end_type = endings[5];
    }
    else if (days == 60)
    {
        end_type = endings[0];
    }
    typewriter(end_type);
    std::cout << "\n\nEnter any key to continue...";
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void score_screen()
{
    system("clear");
    std::cout << std::setw(53) << "GAME OVER" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << '\n'
              << std::setw(50) << "Welfare" << std::setw(5) << welfare << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::setw(50) << "Resources" << std::setw(5) << resources << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::setw(50) << "Military" << std::setw(5) << military << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::setw(50) << "Politics" << std::setw(5) << politics << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::setw(50) << "Geography" << std::setw(5) << geography << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << '\n'
              << std::setw(50) << "Days Ruled" << std::setw(5) << days << std::endl;

    std::cout << "\nEnter any key to continue...";
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool ask_quit(){
    char choice;

    system("clear");
    std::cout << std::setw(40) << "[Enter A] Retry" << std::endl;
    std::cout << std::setw(40) << "[Enter D] Quit " << std::endl;
    std::cout << '\n'
              << std::setw(28) << ">> ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    choice = toupper(choice);

    if (choice == 'A')
    {
        days = 0;
        return false;
    }
    else
    {
        return true;
    }
}

bool run_game()
{
    char choice;
    int curr_line, rand_values[5];
    bool next_day = true, game_over = false, skip_typewriter = false;
    srand(time(0));

    for (int i = 0; i < 5; i++)
    {
        rand_values[i] = (rand() % 101) + 150;
    }
    welfare = rand_values[0];
    resources = rand_values[1];
    military = rand_values[2];
    politics = rand_values[3];
    geography = rand_values[4];

    while (!game_over)
    {
        if (next_day)
        {
            curr_line = rand() % dilemmas.size();
            days++;
        }

        display_hud();

        if (!skip_typewriter)
        {
            typewriter(dilemmas[curr_line]);
        }
        else
        {
            std::cout << dilemmas[curr_line];
            skip_typewriter = false;
        }

        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "\n[Enter A] Yes" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "[Enter D] No" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\n>> ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = toupper(choice);

        switch (choice)
        {
        case 'A':
            welfare += consqs[curr_line][0][0];
            resources += consqs[curr_line][0][1];
            military += consqs[curr_line][0][2];
            politics += consqs[curr_line][0][3];
            geography += consqs[curr_line][0][4];
            next_day = true;
            break;

        case 'D':
            welfare += consqs[curr_line][1][0];
            resources += consqs[curr_line][1][1];
            military += consqs[curr_line][1][2];
            politics += consqs[curr_line][1][3];
            geography += consqs[curr_line][1][4];
            next_day = true;
            break;

        default:
            std::this_thread::sleep_for(std::chrono::seconds(1));
            typewriter("\nYou started to speak gibberish in front of everyone. Sadly, no one understood you.");
            std::cout << std::endl;
            next_day = false;
            skip_typewriter = true;
            break;
        }

        welfare = std::min(welfare, 250);
        resources = std::min(resources, 250);
        military = std::min(military, 250);
        politics = std::min(politics, 250);
        geography = std::min(geography, 250);

        welfare = std::max(welfare, 0);
        resources = std::max(resources, 0);
        military = std::max(military, 0);
        politics = std::max(politics, 0);
        geography = std::max(geography, 0);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (days == 60 || welfare == 0 || resources == 0 || military == 0 || politics == 0 || geography == 0)
        {
            game_over = true;
        }
    }

    display_hud();
    std::this_thread::sleep_for(std::chrono::seconds(3));

    ending_screen();
    score_screen();

    return ask_quit();
}