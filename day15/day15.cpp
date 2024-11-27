#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <climits>

void generate_combination(int size, int sum, std::vector<int> combination, std::vector<std::vector<int> >& allcombs) {
    if (size-combination.size()==0) {
        allcombs.push_back(combination);
        return;
    }
    for (int s=sum; s>=0; --s) {
        std::vector<int> newcomb = combination;
        newcomb.push_back(s);
        generate_combination(size,sum-s,newcomb,allcombs);
    }
}

class property {
public: 
    std::map<std::string,int> values;  

    int score(std::map<std::string,int> ingredients) {
        int s = 0;
        for (auto ing: ingredients)
            s += values[ing.first] * ing.second;
        if (s<0) s=0;
        return s;
    }
};

int main() {
 
    std::vector<std::vector<int> > ac;
    std::vector<int> c;
 
    std::map<std::string, property*> properties;
    std::map<std::string, int> ingredients;

    properties["capacity"] = new property;
    properties["durability"] = new property;
    properties["flavor"] = new property;
    properties["texture"] = new property;
    properties["calories"] = new property;

    std::ifstream data ("data.txt");
    if (!data.is_open()) {
        std::cout << "Error: Could not open the input file" << std::endl;
        return 1;
    }

    std::string line;
    while (getline(data, line)) {
        std::istringstream ss(line);
        std::string name;
        std::string rest;
        std::string tmp;
        std::string propname;
        int propval;
        getline(ss, name, ':');
        ingredients[name] = 0;
        getline(ss, rest, ':');
        std::istringstream sin(rest);
        while (getline(sin, tmp, ',')) {
            while (tmp[0]==' ') tmp.erase(tmp.begin());

            int space = tmp.find(" ");
            propname = tmp.substr(0,space);
            propval  = std::stoi(tmp.substr(space+1));
            properties[propname]->values[name] = propval;
        }
    }

    ingredients.begin()->second = 100;

    int maxscore = INT_MIN;
    generate_combination(ingredients.size(), 100, c, ac);

    int num_combinations = 1;

    for (auto comb: ac) {

        if (++num_combinations % 100000 == 0) { // modulo with 10,000
            std::cout << "Combination Number: " << num_combinations << std::endl;
        }

        auto ig = ingredients.begin();
        for (auto cv = comb.begin() ; cv != comb.end(); ++cv, ++ig) {
            ig->second= *cv;
        }

        // // Part 1
        // int score = 1;
        // for (auto p: properties) {
        //     // std::cout << "Considering property: " << p.first << std::endl;
        //     if (p.first.compare("calories")!=0) {
        //         int is = p.second->score(ingredients);
        //         score *= is;
        //     }
        // }
        // if (score > maxscore) maxscore = score;

        // Part 2
        if (properties["calories"]->score(ingredients) == 500) {
            int score = 1;
            for (auto p: properties) {
                if (p.first.compare("calories")!=0) {
                    int is = p.second->score(ingredients);
                    score *= is;
                }
            }
            if (score > maxscore) maxscore = score;
        }
    }

    std::cout << maxscore << std::endl;

}