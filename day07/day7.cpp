#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Instruction {
    public:
        string operation;
        string operand1;
        string operand2;
        string output;

        Instruction() {}

        Instruction(string o1, string op, string o2, string out) : operand1(o1), operand2(o2), operation(op), output(out) {}

        void print() {
            cout << operand1 << " " << operation << " " << operand2 << " -> " << output << "\n";
        }
        void details() {
            cout << "Operand 1: " << operand1 << "\n";
            cout << "Operand 2: " << operand2 << "\n";
            cout << "Operation: " << operation << "\n";
            cout << "Output: " << output << endl;
        }
        int length() {
            return operand1.length() + operation.length() + operand2.length() + output.length();
        }
};

bool isnumber(const std::string &s) {
    if (s == "") {
        return 0;
    }
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

unsigned short regularize(string operand, map<string, unsigned short> wires) {

    unsigned short result;

    if (isnumber(operand)) {
        result = stoi(operand);
    } else {
        result = wires[operand];
    }

    return result;
}

// Function to parse the input string and extract instructions
Instruction parseInstruction(const string& input) {
    Instruction instruction;
    istringstream iss(input);
    string arrow;

    // Parse the instruction based on its format
    if (input.find("NOT") != string::npos) {
        instruction.operation = "NOT";
        iss >> instruction.operation >> instruction.operand1 >> arrow >> instruction.output;
    } else if (input.find("AND") != string::npos ||
               input.find("OR") != string::npos ||
               input.find("LSHIFT") != string::npos ||
               input.find("RSHIFT") != string::npos) {
        iss >> instruction.operand1 >> instruction.operation >> instruction.operand2 >> arrow >> instruction.output;
    } else {
        instruction.operation = "SIGNAL";
        iss >> instruction.operand1 >> arrow >> instruction.output;
    }

    return instruction;
}

pair<string, unsigned short> evaluateInstruction(Instruction instruction, map<string, unsigned short>& wires) {

    unsigned short result, value1, value2;
    value1 = regularize(instruction.operand1, wires);
    value2 = regularize(instruction.operand2, wires);

    if (instruction.operation == "SIGNAL") {
        // If the instruction is a signal, parse the operand1 as the value
        result = value1;

    } else if (instruction.operation == "NOT") {
        // If the instruction is NOT, recursively evaluate the operand1 wire and apply bitwise complement
        result = ~wires[instruction.operand1];
    } else if ( instruction.operation == "AND" || 
                instruction.operation == "OR" || 
                instruction.operation == "LSHIFT" || 
                instruction.operation == "RSHIFT" ) {
        // If the instruction is a binary operation, recursively evaluate both operand wires and apply the operation

        // cout << value1 << " " << instruction.operation << " " << value2 << "\n";

        if (instruction.operation == "AND") {
            result = value1 & value2;
        } else if (instruction.operation == "OR") {
            result = value1 | value2;
        } else if (instruction.operation == "LSHIFT") {
            result = value1 << value2;
        } else if (instruction.operation == "RSHIFT") {
            result = value1 >> value2;
        }
    }

    return make_pair(instruction.output, result);

}

unsigned short traceback(string wire, vector<Instruction> instructions, map<string, unsigned short>& wires) {

    /*
    1. find the instruction that has `wire` as the output. 
    2. figure out which wire(s) are used in that instruction
    3. find the value(s) of the wire(s) using recursive traceback calls
        a. check if the value already exists in wires
        b. If the value does not already exist, find the relevant instruction and see if the prereq values exist
        c. If the prereq values exist, do the calculation
        d. if the prereqs do not exist, do a traceback.
    4. evaluate the instruction with the saved values
    */
    // cout << "Tracing wire " << wire << " with count " << wires.count(wire) << " . . .\t";

    auto search_for_output = [wire](const Instruction instr){return instr.output == wire;};

    if (wires.count(wire) > 0) {
        return wires[wire];
    } else {
        auto it = find_if(instructions.begin(), instructions.end(), search_for_output);
        Instruction dependency = *it;

        // dependency.print();
        // cout << "Operand 1 is number: " << isnumber(dependency.operand1) << "\n";
        // cout << "Operand 2 is number: " << isnumber(dependency.operand2) << "\n";
        // cout << endl;

        // If the operand1 is not a number and it does not exist in wires, traceback operand1
        if (!isnumber(dependency.operand1) & wires.count(dependency.operand1) == 0) {
            wires[dependency.operand1] = traceback(dependency.operand1, instructions, wires);
        } else if (isnumber(dependency.operand1) & dependency.operation == "SIGNAL") {
            // If operand 1 is a number, and the operation is SIGNAL
            wires[dependency.output] = stoi(dependency.operand1);
        }

        // If the operand1 is not a number and it does not exist in wires, traceback operand1
        if (dependency.operand2.length() > 0 & !isnumber(dependency.operand2) & wires.count(dependency.operand2) == 0) {
            wires[dependency.operand2] = traceback(dependency.operand2, instructions, wires);
        } 

        auto [name, signal] = evaluateInstruction(*it, wires);
        wires[wire] = signal;
        return signal;
    }

}

int part1(ifstream& data, string wire) {

    string line;
    map<string, unsigned short> wires;
    vector<Instruction> instructions;

    while(getline(data, line)) {
        Instruction instruction = parseInstruction(line);
        instructions.push_back(instruction);
    }

    // for (Instruction instruction : instructions) {
    //     cout << instruction.operand1 << " " << instruction.operation << " " << instruction.operand2 << " -> " << instruction.output << "\n";
    // }
    // cout << endl;

    unsigned short signal = traceback(wire, instructions, wires);

    // for(map<string, unsigned short>::const_iterator it = wires.begin(); it != wires.end(); ++it) {
    //     std::cout << it->first << " " << it->second << "\n";
    // }
    cout << endl;
    return signal;

}

int part2(ifstream & data, string wire, int new_signal) {
    string line;
    map<string, unsigned short> wires;
    vector<Instruction> instructions;

    // Add the new instruction
    ostringstream new_instr_stream;
    new_instr_stream << new_signal << " -> b";
    string new_instr = new_instr_stream.str();
    Instruction instruction = parseInstruction(new_instr);
    instructions.push_back(instruction);

    while(getline(data, line)) {
        instruction = parseInstruction(line);
        instructions.push_back(instruction);
    }
    unsigned short signal = traceback(wire, instructions, wires);

    // for(map<string, unsigned short>::const_iterator it = wires.begin(); it != wires.end(); ++it) {
    //     std::cout << it->first << " " << it->second << "\n";
    // }
    // cout << endl;
    return signal;
}

int main() {
    ifstream data ("day7.txt");

    if (data.is_open()) {
        
        // Part 1
        string wire;
        cout << "Enter the name of the wire to trace: ";
        cin >> wire;

        int signal1 = part1(data, wire);
        cout << "Part 1 -> The signal on wire " << wire << " is " << signal1 << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        // Part 2
        int signal2 = part2(data, wire, signal1);
        cout << "Part 2 -> The signal on wire " << wire << " is " << signal2 << endl;

    }

    data.close();

    return 0;
}
