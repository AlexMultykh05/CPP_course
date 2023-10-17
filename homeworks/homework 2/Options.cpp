#include "Options.h"
#include <iostream>

using namespace std;

bool processFlagOptions(const string &name) {
    cout << "Flag option <" << name << "> detected" << endl;

    return true;
}

bool processValueOptions(const string &name, const string &value) {
    if (value.empty()) {
        cout << "Value option <" << name << "> detected but its value is missing!" << endl;
        return false;
    }
    cout << "Value option <" << name << "> detected with value <" << value << '>' << endl;

    return true;
}

bool processUnknownOptions(const string &name) {
    cout << "Unknown option <" << name << "> found!" << endl;

    return false;
}

bool processStandaloneValues(const string &value) {
    cout << "Standalone value detected <" << value << '>' << endl;

    return true;
}

void
processConcatenatedOptions(const string &options, vector<string>::const_iterator &it, const vector<string> &arguments) {
    for (size_t i = 0; i < options.length(); ++i) {
        string name = string(1, options[i]);

        if (name == FLAG_X || name == FLAG_Y || name == FLAG_T)
            processFlagOptions(name);

        else if (name == VALUE_R || name == VALUE_G || name == VALUE_B || name == VALUE_A) {
            string value;
            if (i + 1 != options.length())
                value = options.substr(i + 1, options.length() - i);
            else {
                if (it + 1 != arguments.end()) {
                    ++it;
                    value = *it;

                } else {
                    value = "";
                }
            }
            processValueOptions(name, value);
            break;

        } else {
            processUnknownOptions(name);
        }
    }
}

bool processOption(const string &name, vector<string>::const_iterator &it, const vector<string> &arguments) {
    if (name == FLAG_GRAYSCALE || name == FLAG_TRANSPARENT) {
        processFlagOptions(name);

    } else if (name == VALUE_RED ||
               name == VALUE_GREEN ||
               name == VALUE_BLUE || name == VALUE_ALPHA) {

        if (it + 1 != arguments.end()) {
            ++it;
            processValueOptions(name, *it);

        } else {
            processValueOptions(name, "");
        }
    } else {
        processUnknownOptions(name);
        return false;
    }

    return true;
}

bool processOptions(const vector<string> &arguments) {
    for (auto it = arguments.begin(); it != arguments.end(); ++it) {
        const string arg = *it;

        if (arg.length() >= 2 && arg[0] == '-' && arg[1] != '-') {
            processConcatenatedOptions(arg.substr(1), it, arguments);

        } else if (arg.length() > 2 && arg.substr(0, 2) == "--") {
            processOption(arg.substr(2), it, arguments);

        } else {
            processStandaloneValues(arg);
        }
    }
    return true;
}
