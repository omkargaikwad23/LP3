#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;
using namespace std::chrono;

struct item
{
    int id;         
    int profit;     
    int weight;     
    int bound;      
    int level;      
    std::vector<int> itemList;
};
int time_out = 10;

struct knapsack_problem
{
    std::vector<item> items;    
    int capacity;               
    int time_limit = 10;        
};
int last_sol_time = 0;

knapsack_problem read_data(std::string& fn) {
    std::ifstream fin(fn);
    if (!fin.good()) {
        std::cerr << "Error opening file " << fn << std::endl;
        system("pause");
        exit(-1);
    }

    knapsack_problem ks;

    int items_number;

    fin >> items_number;
    for (int i = 0; i < items_number; i++)

    {
        item an_item;
        fin >> an_item.id;
        fin >> an_item.profit;
        fin >> an_item.weight;
        ks.items.push_back(an_item);
    }
    fin >> ks.capacity;
    return ks;
}

bool cmp(struct item a, struct item b)
{
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

/*1 Greedy Approach*/
std::vector <item> greedy_approach_solver(knapsack_problem& ks)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::cout << "Greedy Approach Solver\n";
    std::vector<item> itemsHolder(ks.items);    // δημιουργούμε ένα αντιγραφο του πίνακα των αντικειμένων ώστε να γίνει ταξινόμιση μόνο στο αντιγραφο και να μην αλλαξει η σειρά στον αρχικό πίνακα
    sort(itemsHolder.begin(), itemsHolder.end(), cmp);
    int current_weight = 0;
    double finalprofit = 0.0;
    std::vector<item> sol_list;

    for (int i = 0; i < itemsHolder.size(); i++) {
        item tempItem = itemsHolder.at(i);

        if (current_weight + tempItem.weight <= ks.capacity)
        {
            sol_list.push_back(tempItem);
            current_weight += tempItem.weight;
            finalprofit += tempItem.profit;
        }

        else
        {
            break;
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - begin);
        last_sol_time = duration.count() / 1000.0;
        if (last_sol_time > ks.time_limit) {
            std::cout << "out of time: time>" << ks.time_limit << "\n";
            return sol_list;
        }
    }
    std::cout << "max_weight=" << current_weight << "\n";
    std::cout << "max_profit=" << finalprofit << "\n";
    std::cout << "time=" << last_sol_time << "\n";
    return sol_list;
}

/*3 Branch and Bound Solver*/
int bound(item u, int n, int W, item arr[]) {
    if (u.weight >= W) return 0;
    int profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;
    while ((j < n) && (totweight + arr[j].weight <= W)) {
        totweight += arr[j].weight;
        profit_bound += arr[j].profit;
        j++;
    }
    if (j < n) profit_bound += (W - totweight) * arr[j].profit / arr[j].weight;
    return profit_bound;
}

std::vector <int>  branch_and_bound(int W, item arr[], int n) {
    std::sort(arr, arr + n, cmp);
    std::queue <item> Q;
    item u, v;
    auto begin = std::chrono::high_resolution_clock::now();
    u.level = -1;
    u.profit = u.weight = 0;
    Q.push(u);
    int max_profit = 0;
    int max_weight = 0;
    std::vector<int> selectedItems;

    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        if (u.level == -1) v.level = 0;
        if (u.level == n - 1) continue;
        v.level = u.level + 1;
        v.weight = u.weight + arr[v.level].weight;
        v.profit = u.profit + arr[v.level].profit;
        v.id = arr[v.level].id;
        v.itemList.clear();
        v.itemList = u.itemList;
        v.itemList.push_back(v.id);
        if (v.weight <= W && v.profit > max_profit) {
            max_profit = v.profit;
            max_weight = v.weight;
            selectedItems = v.itemList;
        }
        v.bound = bound(v, n, W, arr);
        if (v.bound > max_profit) {
            Q.push(v);
        }
        v.weight = u.weight;
        v.profit = u.profit;
        v.id = u.id;
        v.itemList = u.itemList;
        v.bound = bound(v, n, W, arr);
        if (v.bound > max_profit) Q.push(v);
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - begin);
        last_sol_time = duration.count() / 1000.0;
        if (last_sol_time > time_out) {
            std::cout << "out of time: time>" << time_out << "\n";

            return selectedItems;
        }

    }
    std::cout << "max_weight=" << max_weight << "\n";
    std::cout << "max_profit=" << max_profit << "\n";
    std::cout << "time=" << last_sol_time << "\n";
    return selectedItems;
}

std::vector <item>  branch_and_bound_solver(knapsack_problem& ks) {

    int n = ks.items.size();
    item* arr = new item[n];
    for (int i = 0; i < n; i++) arr[i] = ks.items.at(i);
    std::cout << "Branch and Bound Solver\n";
    std::vector <int> solutionIDs = branch_and_bound(ks.capacity, arr, n);
    std::vector <item> solution;
    for (int i = 0; i < solutionIDs.size(); i++) {
        int itemIndex = solutionIDs[i] - 1;
        solution.push_back(ks.items[itemIndex]);
    }
    delete[] arr;
    return solution;
}

void print_solution(std::vector<item> sol) {

    int total_weight = 0;
    int total_profit = 0;

    for (int i = 0; i < sol.size(); i++) {
        std::cout << sol[i].id << " " << sol[i].profit << " " << sol[i].weight << "\n";
        total_weight += sol[i].weight;
        total_profit += sol[i].profit;
    }
    std::cout << "Total weight:" << total_weight << "\n";
    std::cout << "Total profit:" << total_profit << "\n";


}

void calc_p_w(std::vector<item>& solution, std::fstream& fout) {
    int w = 0;
    int v = 0;
    for (int i = 0; i < solution.size(); i++) {
        item tmpItem = solution.at(i);
        w += tmpItem.weight;
        v += tmpItem.profit;
    }
    std::string s = ";" + std::to_string(w) + ";" + std::to_string(v);
    fout << s;
}

int main() {
    int choice = -1;
    do {
        system("CLS");
        std::cout << "|====================================================================|\n";
        std::cout << "|========================0-1 Knapsack Problem========================|\n";
        std::cout << "|====================================================================|\n";
        std::cout << "Please choice the algorithm to solve 0-1 Knapsack Problem: \n" << std::endl;
        std::cout << "1. Greedy approach solver" << std::endl;
        std::cout << "2. Branch and bound solver " << std::endl;
        std::cout << "0. Exit\n" << std::endl;
        std::cout << "Please enter your choice" << std::endl;
        std::cin >> choice;
        if ((choice < 0) || (choice > 7)) {
            std::cout << "Wrong choice!\n";
            system("pause");
            exit(0);
        }
        if (choice == 0) {
            exit(0);
            system("pause");
        }
        if (choice == 7) {
            system("pause");
        }

        else {
            int n;
            int r;
            int type;
            int i;
            int s;
            std::cout << "Enter the 5 parameters for 0-1 knapsack problem to print and export the solution: \n";
            std::cout << "Enter the parameter n (10,50,100,500) n: ";
            std::cin >> n;
            std::cout << "Enter the parameter r (50,100,500,1000) r: ";
            std::cin >> r;
            std::cout << "Enter the parameter type(1,2,3,4) type: ";
            std::cin >> type;
            std::cout << "Enter the parameter i (1,2,3,4,5) i: ";
            std::cin >> i;
            std::cout << "Enter the number 5 in the parameter s: ";
            std::cin >> s;
            std::string  fn = "problem_" + std::to_string(n) + "_" + std::to_string(r) + "_" + std::to_string(type) + "_" + std::to_string(i) + "_" + std::to_string(s) + ".txt";
            std::string solution_fn = "solution_" + std::to_string(n) + "_" + std::to_string(r) + "_" + std::to_string(type) + "_" + std::to_string(i) + "_" + std::to_string(s) + ".txt";
            std::cout << "Filename=" << fn << "\n";
            knapsack_problem ks = read_data(fn);
            std::cout << "total capacity=" << ks.capacity << "\n";
            std::string fname;

            std::vector<item> result;
            switch (choice) {
            case 1: 
                result = greedy_approach_solver(ks);
                print_solution(result);
                break;
            case 2: 
                result = branch_and_bound_solver(ks);
                print_solution(result);
                break;
            default: break;
            }
            system("pause");
        }
    } while (choice != 0);
    exit(0);
}
