#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> validate(string userInput);
string getFileName();
string getInput(int argc, char *argv[]);

int main(int argc, char *argv[]) {

    string userInput = getInput(argc, argv);
    vector<int> validated = validate(userInput);

    int n = validated[0];
    vector<int> packets(n);
    for (int i = 1; i <= n; i++)
        packets[i - 1] = validated[i];

    // Create the file we'll write to
    ofstream csv_file(getFileName());
    csv_file << "PacketID,MoudleNumber,ValidModule\n";

    // Sort so that next_permutation() works properly
    sort(packets.begin(), packets.end());
    int counter = 1;
    do {
        counter = 1;
        int previous_packet = packets[0];

        for (int& current_packet : packets){
            csv_file << counter++ << "," << current_packet << ",";
            if ((current_packet != previous_packet) &&
                (current_packet != previous_packet % n + 1))
                csv_file << "No\n";
            else
                csv_file << "Yes\n";
            previous_packet = current_packet;
        }
    } while (next_permutation(packets.begin(), packets.end()));

    csv_file.close();

    return 0;
}


vector<int> validate(string userInput){
    string token = "";
    vector<int> validated;

    // To make it easier to parse the final token
    userInput += ' ';

    for (char c : userInput){
        if (c == ' '){
            // If a token was all zeros, it's ignored.
            if (token.empty())
                continue;

            // If a token has more than 5 digits, it's deemed too large.
            if (token.size() > 5) {
                throw runtime_error("The number " + token + " is too large.");
                return {};
            }

            // Otherwise, it's a valid number.
            validated.push_back(stoi(token));
            token = "";

        } else {
            if (!isdigit(c)) {
                throw runtime_error("The character '" + string(1, c) + "' was found in the input.");
                return {};
            }

            // Leading zeros in numbers are ignored.
            if (token.empty() && c == '0') continue;
            token += c;
        }
    }

    // The first token represents the number of packets,
    // so if the number doesn't match, that's an error.
    if ((!validated.empty() && validated.size() == validated[0] + 1) && (validated[0] != 0))
        return validated;
    else {
        throw runtime_error("The number of packet module numbers does not match"
                            " the number of packets (first number in the input),"
                            " or the input is empty.");
        return {};
    }
}

string getFileName(){
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    ostringstream oss;
    oss << "generated_tests_";

    oss << (localTime->tm_year - 100)
        << setfill('0') << setw(2) << (localTime->tm_mon + 1)
        << setfill('0') << setw(2) << localTime->tm_mday << '_'
        << setfill('0') << setw(2) << localTime->tm_hour
        << setfill('0') << setw(2) << localTime->tm_min
        << setfill('0') << setw(2) << localTime->tm_sec;

    oss << ".csv";

    string file_name = oss.str();
    return file_name;
}

string getInput(int argc, char *argv[]){
    string userInput = "";

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        exit(1);
    }

    ifstream inputFile(argv[1]);
    if (inputFile.is_open()) {
        getline(inputFile, userInput);
        inputFile.close();
    } else {
        throw runtime_error("Unable to open file: " + string(argv[1]));
    }

    return userInput;
}
