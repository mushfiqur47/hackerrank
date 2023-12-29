#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

bool checkEnd(string name, string end) {
    name = "</" + name + ">";
    if (name == end) return true;
    return false;
}

string nameTag(string demo) {
    int from = demo.find_first_of('<');
    int off = fmin(demo.find_first_of(' '), demo.find_first_of('>')) - 1;
    return demo.substr(from + 1, off);
}

struct range {
    int from;
    int to;
};

range rangeOfTag(string tags, string nameTag, int index = 0) {
    range result;
    result.from = 0;
    result.to = 0;
    string endTag = "</" + nameTag + ">";
    nameTag = "<" + nameTag;
    unsigned long int j = 0, k = 0;
    for (unsigned long int i = index; i < tags.length(); i++) {
        if (tags[i] == nameTag[j]) {
            ++j;
            if (j == nameTag.length()) {
                result.from = i - j + 1;
            }
        }
        else
            j = 0;
        if (tags[i] == endTag[k]) {
            ++k;
            if (k == endTag.length()) {
                result.to = i - k + 1;
            }
        }
        else
            k = 0;
    }
    return result;
}

int indexEnd(string tags, string name) {
    int j = 0;
    for (int i = 0; i < tags.length(); i++) {
        if (tags.at(i) == name.at(j)) {
            ++j;
            if (j == name.length()) {
                return i - j;
            }
        }
    }
    return 0;
}

string solve(string tags, string querie, int index) {
    if (index < 0) return "Not Found!";
    string temp = "";
    string att;
    range correct;
    correct.from = index;
    correct.to = index;
    while (tags[correct.from] != ' ') --correct.from;
    while (tags[correct.to] != ' ') ++correct.to;
    vector<string> split;
    string name = tags.substr(correct.from + 1, correct.to - correct.from - 1);
    string templateS = "";
    for (int i = 0; i < tags.length(); i++) {
        if (tags.at(i) == '<') {
            string temp = tags.substr(i + 1, fmin(tags.find('>', i + 1), tags.find(' ', i + 1)) - i - 1);
            range ran = rangeOfTag(tags, temp);
            if (ran.from < index && ran.to > index) {
                templateS = templateS + temp + '.';
            }
        }
    }
    templateS[templateS.length() - 1] = '~';
    templateS = templateS + name;
    string result = tags.substr(tags.find('"', index) + 1, tags.find('"', tags.find('"', index) + 1) - tags.find('"', index) - 1);
    if (querie == templateS) return result;
    return "Not Found!";
}

int main() {
    int n, q;
    cin >> n >> q;
    cin.ignore(1, '\n');
    map<string, string> tags;
    string title, temp = "";
    bool check = true;
    for (int i = 0; i < n; i++) {
        string temp1;
        getline(cin, temp1);
        if (check) {
            title = nameTag(temp1);
            check = false;            
        }
        temp = temp + temp1;
        if (checkEnd(title, temp1)) {
            tags[title] = temp;
            temp = "";
            check = true;
        }
    }
    for (int i = 0; i < q; i++) {
        string querie;
        cin >> querie;
        int j = 0;
        string title = "";
        while (!ispunct(querie.at(j)) && j < querie.length()) {
            title = title + querie.at(j);
            j++;
        }
        if (tags.find(title) != tags.end()) {
            int check = querie.find('~');
            if (check) {
                string nameAttri = querie.substr(querie.find('~') + 1, querie.length() - querie.find('~'));
                int index = tags[title].find(nameAttri);
                string demo = solve(tags[title], querie, index);
                while (index >= 0) {
                    if (demo != "Not Found!") break;
                    index = tags[title].find(nameAttri, index + nameAttri.length() + 1);
                    demo = solve(tags[title], querie, index);
                }
                cout << demo << endl;
            }
            else cout << "Not Found!";
        }
        else
        {
            cout << "Not Found!" << endl;
        }
    }
    return 0;
}