#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct FileStats {
    int lines = 0;
    int words = 0;
    int bytes = 0;
    int chars = 0;
};

FileStats analyzeFile(const string& filename) {
    FileStats stats;

    ifstream byteFile(filename, ios::binary);
    if (!byteFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        return stats;
    }
    byteFile.seekg(0, ios::end);
    stats.bytes = byteFile.tellg();
    byteFile.close();

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        return stats;
    }

    string line;
    while (getline(file, line)) {
        stats.lines++;
        stats.chars += line.length();

        istringstream iss(line);
        string word;
        while (iss >> word) {
            stats.words++;
        }
    }

    file.close();
    return stats;
}

void parseOptions(const vector<string>& args,
    set<string>& options,
    vector<string>& filenames) {

    for (const string& arg : args) {
        if (!arg.empty() && arg[0] == '-') {
            // Это опция
            if (arg.substr(0, 2) == "--") {
                options.insert(arg.substr(2));
            } else {
                for (size_t i = 1; i < arg.size(); ++i) {
                    switch (arg[i]) {
                        case 'l': options.insert("lines"); break;
                        case 'w': options.insert("words"); break;
                        case 'c': options.insert("bytes"); break;
                        case 'm': options.insert("chars"); break;
                        default:
                            cerr << "Неизвестная опция: -" << arg[i] << '\n';
                    }
                }
            }
        } else {
            filenames.push_back(arg);
        }
    }
}

void printStats(const FileStats& stats, const set<string>& options, const string& filename, bool showFilename = true) {
    if (options.empty() || options.count("lines"))
        cout << "Lines: " << stats.lines << " -- ";
    if (options.empty() || options.count("words"))
        cout << "Words: " << stats.words << " -- ";
    if (options.empty() || options.count("bytes"))
        cout << "Bytes: " << stats.bytes << " -- ";
    if (options.empty() || options.count("chars"))
        cout << "Chars: " << stats.chars << " -- ";
    if (showFilename)
        cout << filename;
    cout << '\n';
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Использование: WordCount [опции] файл1 [файл2 ...]\n";
        return 1;
    }

    vector<string> args(argv + 1, argv + argc);

    set<string> options;
    vector<string> filenames;

    parseOptions(args, options, filenames);

    if (filenames.empty()) {
        cerr << "Ошибка: не указаны файлы для обработки.\n";
        return 1;
    }

    for (const string& filename : filenames) {
        FileStats stats = analyzeFile(filename);
        printStats(stats, options, filename, filenames.size() > 1);
    }

    return 0;
}
