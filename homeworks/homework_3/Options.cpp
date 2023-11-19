#include "Options.h"
#include <iostream>

using namespace std;

bool processFlagOptions(const string &name, bool &flag) {
    cout << "Flag option <" << name << "> detected" << endl;
    flag = true;

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

bool processStandaloneValues(const string &value, Options &options) {
    cout << "Standalone value detected <" << value << '>' << endl;
    options.standalone_values.push_back(value);

    return true;
}

bool processStringOption(const string &name, const string &value, string &convertedValue, bool &flag) {
    flag = true;
    if (!processValueOptions(name, value)) {
        flag = false;
        return false;
    }

    convertedValue = value;

    return true;
}

bool processIntOption(const string &name, const string &value, int &convertedValue, bool &flag) {
    flag = true;
    if (!processValueOptions(name, value)) {
        flag = false;
        return false;
    }

    size_t firstUnparsedPos;

    try {
        convertedValue = stoi(value, &firstUnparsedPos);
        if (firstUnparsedPos != value.size()) {
            cout << "Value <" << value << "> is not a valid integer number!" << endl;
            flag = false;
            return false;
        }
    } catch (...) {
        cout << "Value <" << value << "> is not a valid integer number!" << endl;
        flag = false;
        return false;
    }

    return true;
}

bool processFloatOption(const string &name, const string &value, float &convertedValue, bool &flag) {
    flag = true;

    if (!processValueOptions(name, value)) {
        flag = false;
        return false;
    }

    size_t firstUnparsedPos;

    try {
        convertedValue = stof(value, &firstUnparsedPos);
        if (firstUnparsedPos != value.size()) {
            cout << "Value <" << value << "> is not a valid floating point number!" << endl;
            flag = false;
            return false;
        }
    } catch (...) {
        cout << "Value <" << value << "> is not a valid floating point number!" << endl;
        flag = false;
        return false;
    }

    return true;
}

string getShortOptionValue(const string &option, size_t i, vector<string>::const_iterator &it,
                           const vector<string> &arguments) {
    string value;
    if (i + 1 != option.length())
        value = option.substr(i + 1, option.length() - i);
    else {
        if (it + 1 != arguments.end()) {
            ++it;
            value = *it;

        } else {
            value = "";
        }
    }
    return value;
}

string getLongOptionsValue(vector<string>::const_iterator &it, const vector<string> &arguments) {
    if (next(it) != arguments.end()) {
        return *(++it);

    } else {
        return "";
    }
}


bool
processConcatenatedOptions(const string &option, vector<string>::const_iterator &it, const vector<string> &arguments,
                           Options &options) {
    for (size_t i = 0; i < option.length(); ++i) {
        string name = string(1, option[i]);

        if (name == FLAG_X)
            processFlagOptions(name, options.xFlag);
        else if (name == FLAG_Y)
            processFlagOptions(name, options.yFlag);
        else if (name == FLAG_T)
            processFlagOptions(name, options.transparent);
        else if (name == FLAG_GRAYSCALE)
            processFlagOptions(name, options.grayscale);


        else if (name == VALUE_R) {
            return processIntOption(name, getShortOptionValue(option, i, it, arguments), options.r, options.redFlag);

        } else if (name == VALUE_G) {
            return processIntOption(name, getShortOptionValue(option, i, it, arguments), options.g, options.greenFlag);

        } else if (name == VALUE_B) {
            return processIntOption(name, getShortOptionValue(option, i, it, arguments), options.b, options.blueFlag);

        } else if (name == VALUE_A) {
            return processFloatOption(name, getShortOptionValue(option, i, it, arguments), options.a,
                                      options.alphaFlag);

        } else if (name == VALUE_O) {
            return processStringOption(name, getShortOptionValue(option, i, it, arguments), options.value_output,
                                       options.outputFlag);

        } else {
            processUnknownOptions(name);
        }
    }
    return true;
}

bool processOption(const string &name, vector<string>::const_iterator &it, const vector<string> &arguments,
                   Options &options) {
    if (name == FLAG_GRAYSCALE)
        processFlagOptions(name, options.grayscale);
    else if (name == FLAG_TRANSPARENT) {
        processFlagOptions(name, options.transparent);

    } else if (name == VALUE_RED) {
        return processIntOption(name, getLongOptionsValue(it, arguments), options.r, options.redFlag);

    } else if (name == VALUE_GREEN) {
        return processIntOption(name, getLongOptionsValue(it, arguments), options.g, options.greenFlag);

    } else if (name == VALUE_BLUE) {
        return processIntOption(name, getLongOptionsValue(it, arguments), options.b, options.blueFlag);

    } else if (name == VALUE_ALPHA) {
        return processFloatOption(name, getLongOptionsValue(it, arguments), options.a, options.alphaFlag);

    } else if (name == VALUE_OUTPUT) {
        return processStringOption(name, getLongOptionsValue(it, arguments), options.value_output, options.outputFlag);

    } else {
        processUnknownOptions(name);
        return false;
    }

    return true;
}

bool processOptions(const vector<string> &arguments, Options &options) {
    for (auto it = arguments.begin(); it != arguments.end(); ++it) {
        const string arg = *it;

        if (arg.length() >= 2 && arg[0] == '-' && arg[1] != '-') {
            processConcatenatedOptions(arg.substr(1), it, arguments, options);

        } else if (arg.length() > 2 && arg.substr(0, 2) == "--") {
            processOption(arg.substr(2), it, arguments, options);

        } else {
            processStandaloneValues(arg, options);
        }
    }
    return true;
}

void printStatus(Options &options) {
    cout << "Flag option <" << FLAG_X << "> is <" << (options.xFlag ? "enabled" : "disabled") << ">" << endl;

    cout << "Flag option <" << FLAG_Y << "> is <" << (options.yFlag ? "enabled" : "disabled") << ">" << endl;

    cout << "Flag option <" << FLAG_GRAYSCALE << "> is <" << (options.grayscale ? "enabled" : "disabled") << ">"
         << endl;

    cout << "Flag option <" << FLAG_T << '|' << FLAG_TRANSPARENT << "> is <"
         << (options.transparent ? "enabled" : "disabled") << ">" << endl;

    cout << "Value option <" << VALUE_R << '|' << VALUE_RED << "> is <"
         << (options.redFlag ? "enabled> and associated with value <" +
                               to_string(options.r) : "disabled") << '>' << endl;

    cout << "Value option <" << VALUE_G << '|' << VALUE_GREEN << "> is <"
         << (options.greenFlag ? "enabled> and associated with value <" +
                                 to_string(options.g) : "disabled") << '>' << endl;

    cout << "Value option <" << VALUE_B << '|' << VALUE_BLUE << "> is <"
         << (options.blueFlag ? "enabled> and associated with value <" +
                                to_string(options.b) : "disabled") << '>' << endl;

    cout << "Value option <" << VALUE_A << '|' << VALUE_ALPHA << "> is <"
         << (options.alphaFlag ? "enabled> and associated with value <" +
                                 to_string(options.a) : "disabled") << '>' << endl;

    cout << "Value option <" << VALUE_O << '|' << VALUE_OUTPUT << "> is <"
         << (options.outputFlag ? "enabled> and associated with value <" +
                                  options.value_output : "disabled") << '>' << endl;

    for (auto &&it: options.standalone_values) {
        cout << "Standalone value <" << it << '>' << endl;
    }

}

