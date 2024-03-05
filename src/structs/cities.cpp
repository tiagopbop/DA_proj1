//
// Created by loading on 05-03-2024.
//

void HashCities::readLines() {
    string input = "../src/structs/dataset/airlines.csv";
    ifstream MyReadFile(input);

    string line;
    Airlines airlines;

    getline(MyReadFile, line);

    while (std::getline(MyReadFile, line)) {
        vector<std::string> values;
        stringstream ss(line);

        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            values.push_back(subtr);
        }

        airlines = Airlines(values[0], values[1], values[2], values[3]);
        this->airlinesTable.insert(airlines);
    }
}