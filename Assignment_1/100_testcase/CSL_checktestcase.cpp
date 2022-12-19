/*#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

/*#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG*/

using namespace std;

const string dir = "_\\input\\";
const string dir2 = "_\\result\\";

// Replace '_' with your ConcatStringList_testcases's directory

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes

public:
    ConcatStringList(const char*);
    int length() const;
    int get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList& otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

public:
    class ReferencesList {
        // TODO: may provide some attributes

    public:
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes

    public:
        int size() const;
        std::string totalRefCountsString() const;
    };
};

void myAssert(bool val, string msg)
{
    if (val == false)
    {
        cout << msg;
        abort();
    }
}

int main()
{
    /*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);*/
    //_CrtMemState s1, s2, s3;
    vector<ConcatStringList*> CSLVector(100, nullptr);
    //_CrtMemCheckpoint(&s1);
    for (int i = 1; i <= 100; i++)
    {
        cout << "Testcase #" << i << ": ";
        fstream inp(dir + "test" + to_string(i) + ".txt", ios::in);
        fstream out(dir2 + "test" + to_string(i) + ".txt", ios::in);
        string line;
        while (getline(inp, line))
        {
            string res_line = "";
            string s = "";
            if (line == "refCountsString")
            {
                getline(out, res_line);
                s = ConcatStringList::refList.refCountsString();
            }
            else if (line == "totalRefCountsString")
            {
                getline(out, res_line);
                s = ConcatStringList::delStrList.totalRefCountsString();
            }
            else if (line == "CheckMemoryLeaks")
            {
                break;
            }
            else
            {
                string key, variable, instruction;
                int space_index = line.find(' ');
                key = line.substr(0, space_index);
                if (key == "toString")
                {
                    getline(out, res_line);
                    variable = line.substr(space_index + 1);
                    int index = stoi(variable);
                    myAssert((index >= 0 && index < 100), "Index is out of bound!");
                    if (CSLVector[index] != nullptr)
                    {
                        s = CSLVector[index]->toString();
                    }
                }
                else if (key == "length")
                {
                    getline(out, res_line);
                    variable = line.substr(space_index + 1);
                    if (variable == "refList")
                    {
                        s = to_string(ConcatStringList::refList.size());
                    }
                    else if (variable == "delStrList")
                    {
                        s = to_string(ConcatStringList::delStrList.size());
                    }
                    else
                    {
                        int index = stoi(variable);
                        myAssert((index >= 0 && index < 100), "Index is out of bound!");
                        if (CSLVector[index] != nullptr)
                        {
                            s = to_string(CSLVector[index]->length());
                        }
                    }
                }
                else if (key == "refCountAt")
                {
                    getline(out, res_line);
                    variable = line.substr(space_index + 1);
                    int idx = stoi(variable);
                    try
                    {
                        s = to_string(ConcatStringList::refList.refCountAt(idx));
                    }
                    catch (exception& e)
                    {
                        s = string(e.what());
                    }
                }
                else if (key == "get")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index = stoi(variable);
                    int idx = stoi(instruction);
                    myAssert((index >= 0 && index < 100), "Index is out of bound!");
                    if (CSLVector[index] != nullptr)
                    {
                        try
                        {
                            s += CSLVector[index]->get(idx);
                        }
                        catch (exception& e)
                        {
                            s = string(e.what());
                        }
                    }
                }
                else if (key == "indexOf")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index = stoi(variable);
                    myAssert((index >= 0 && index < 100), "Index is out of bound!");
                    if (CSLVector[index] != nullptr)
                    {
                        s = to_string(CSLVector[index]->indexOf(instruction[0]));
                    }
                }
                else if (key == "subString")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    int space_index3 = line.find(' ', space_index2 + 1);
                    int space_index4 = line.find(' ', space_index3 + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1, space_index3 - space_index2 - 1);
                    string from = line.substr(space_index3 + 1, space_index4 - space_index3 - 1);
                    string to = line.substr(space_index4 + 1);
                    int index1 = stoi(variable);
                    int index2 = stoi(instruction);
                    myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
                    myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
                    myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    if (CSLVector[index2] != nullptr)
                    {
                        try
                        {
                            CSLVector[index1] = new ConcatStringList(CSLVector[index2]->subString(stoi(from), stoi(to)));
                            s = (CSLVector[index1] == nullptr ? "Failed to allocate memory" : "Success");
                        }
                        catch (exception& e)
                        {
                            s = string(e.what());
                        }
                    }
                }
                else if (key == "reverse")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index1 = stoi(variable);
                    int index2 = stoi(instruction);
                    myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
                    myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
                    myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    if (CSLVector[index2] != nullptr)
                    {
                        CSLVector[index1] = new ConcatStringList(CSLVector[index2]->reverse());
                        s = (CSLVector[index1] == nullptr ? "Failed to allocate memory" : "Success");
                    }
                }
                else if (key == "single_concat")
                {
                    getline(out, res_line);
                    string safe_object;
                    int space_index2 = line.find(' ', space_index + 1);
                    int space_index3 = line.find(' ', space_index2 + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1, space_index3 - space_index2 - 1);
                    safe_object = line.substr(space_index3 + 1);
                    myAssert(instruction != safe_object, "An object cannot appear twice in function concat() !");
                    int index1 = stoi(variable);
                    int index2 = stoi(instruction);
                    int index3 = stoi(safe_object);
                    myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
                    myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
                    myAssert((index3 >= 0 && index3 < 100), "Index is out of bound!");
                    myAssert((CSLVector[index2] != nullptr) || (CSLVector[index3] != nullptr), "Object is not initialize!");
                    myAssert((variable != safe_object) || (variable != instruction), "Memory will be leaked!");
                    myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    CSLVector[index1] = new ConcatStringList(CSLVector[index2]->concat(*CSLVector[index3]));
                    s = (CSLVector[index1] == nullptr ? "Failed to allocate memory" : "Success");
                }
                else if (key == "init")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index1 = stoi(variable);
                    myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
                    myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    if (instruction == "\"empty_string\"")
                    {
                        CSLVector[index1] = new ConcatStringList("");
                    }
                    else
                    {
                        CSLVector[index1] = new ConcatStringList(instruction.c_str());
                    }
                    s = (CSLVector[index1] == nullptr ? "Failed to allocate memory!" : "Success");
                }
                else if (key == "delete")
                {
                    variable = line.substr(space_index + 1);
                    int index1 = stoi(variable);
                    delete CSLVector[index1];
                    CSLVector[index1] = nullptr;
                }
                else
                {
                    cout << "Invalid instruction: " + line;
                    break;
                }
            }
            myAssert(s == res_line, "Wrong answer! Expected " + res_line + ", got " + s);
        }
        cout << "Correct!\n";
    }
    /*_CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s1, &s2))
    {
        _CrtMemDumpStatistics(&s3);
    }*/
}
