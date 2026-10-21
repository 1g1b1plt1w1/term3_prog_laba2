#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "linked_list.h"
#include "one_linked_list.h"
#include "array.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"
#include "Set.h"
#include "tasks.h"

using namespace std;

enum class Command {
    PRINT,

    MCREATE,
    MPUSH,
    MPUSHIDX,
    MGET,
    MDELIDX,
    MSETIDX,
    MLENGTH,
    MREAD,

    FPUSH,
    FPUSHHEAD,
    FPUSHBEFORE,
    FPUSHAFTER,
    FPOP,
    FPOPHEAD,
    FPOPBEFORE,
    FPOPAFTER,
    FDELVAL,
    FFINDVAL,
    FREADHT,
    FREADTH,

    LPUSHHEAD,
    LPUSH,
    LPUSHBEFORE,
    LPUSHAFTER,
    LPOPHEAD,
    LPOP,
    LPOPBEFORE,
    LPOPAFTER,
    LDELVAL,
    LFINDVAL,
    LREADHT,
    LREADTH,

    SPUSH,
    SPOP,
    SREAD,

    QPUSH,
    QPOP,
    QREAD,

    TINSERT,
    ISMEMBER,
    TDELETE,
    TREAD,

    SETADD,
    SETDEL,
    SET_AT
};

map<string, Command> command_map = {
    {"PRINT", Command::PRINT},

    {"MCREATE", Command::MCREATE},
    {"MPUSH", Command::MPUSH},
    {"MPUSHIDX", Command::MPUSHIDX},
    {"MGET", Command::MGET},
    {"MDELIDX", Command::MDELIDX},
    {"MSETIDX", Command::MSETIDX},
    {"MLENGTH", Command::MLENGTH},
    {"MREAD", Command::MREAD},

    {"FPUSH", Command::FPUSH},
    {"FPUSHHEAD", Command::FPUSHHEAD},
    {"FPUSHBEFORE", Command::FPUSHBEFORE},
    {"FPUSHAFTER", Command::FPUSHAFTER},
    {"FPOP", Command::FPOP},
    {"FPOPHEAD", Command::FPOPHEAD},
    {"FPOPBEFORE", Command::FPOPBEFORE},
    {"FPOPAFTER", Command::FPOPAFTER},
    {"FDELVAL", Command::FDELVAL},
    {"FFINDVAL", Command::FFINDVAL},
    {"FREADHT", Command::FREADHT},
    {"FREADTH", Command::FREADTH},

    {"LPUSHHEAD", Command::LPUSHHEAD},
    {"LPUSH", Command::LPUSH},
    {"LPUSHBEFORE", Command::LPUSHBEFORE},
    {"LPUSHAFTER", Command::LPUSHAFTER},
    {"LPOPHEAD", Command::LPOPHEAD},
    {"LPOP", Command::LPOP},
    {"LPOPBEFORE", Command::LPOPBEFORE},
    {"LPOPAFTER", Command::LPOPAFTER},
    {"LDELVAL", Command::LDELVAL},
    {"LFINDVAL", Command::LFINDVAL},
    {"LREADHT", Command::LREADHT},
    {"LREADTH", Command::LREADTH},

    {"SPUSH", Command::SPUSH},
    {"SPOP", Command::SPOP},
    {"SREAD", Command::SREAD},

    {"QPUSH", Command::QPUSH},
    {"QPOP", Command::QPOP},
    {"QREAD", Command::QREAD},

    {"TINSERT", Command::TINSERT},
    {"ISMEMBER", Command::ISMEMBER},
    {"TDELETE", Command::TDELETE},
    {"TREAD", Command::TREAD},

    {"SETADD", Command::SETADD},
    {"SETDEL", Command::SETDEL},
    {"SET_AT", Command::SET_AT}
};

map<string, LinkedList> llists;
map<string, OneLinkedList> onellists;
map<string, Array> arrays;
map<string, Queue> queues;
map<string, Stack> stacks;
map<string, Tree> trees;
map<string, Set> sets;

void write(const string& filename) {
    ofstream fout(filename);

    if (!fout.is_open()) {
        throw runtime_error("Не удалось открыть файл при записи");
    }

    for (const auto& [name, obj] : arrays) {
        fout << "Array ";
        fout << name << Array_read(obj) << endl;
    }
    for (const auto& [name, obj] : onellists) {
        fout << "OneLinkedList ";
        fout << name << OneLinked_read(obj) << endl;
    }
    for (const auto& [name, obj] : llists) {
        fout << "LinkedList ";
        fout << name << Linked_read(obj) << endl;
    }
    for (const auto& [name, obj] : queues) {
        fout << "Queue ";
        fout << name << Queue_read(obj) << endl;
    }
    for (const auto& [name, obj] : stacks) {
        fout << "Stack ";
        fout << name << Stack_read(obj) << endl;
    }
    for (const auto& [name, obj] : trees) {
        fout << "Tree ";
        fout << name << Tree_read(obj) << endl;
    }
    for (const auto& [name, obj] : sets) {
        fout << "Set ";
        fout << name << " ";
        for (size_t i = 0; i < obj.map.cap; i++) {
            if (obj.map.node[i].status == NodeStatus::USED) {
                fout << obj.map.node[i].val << " ";
            }
        }
        fout << endl;
    }

    fout.close();
}

void read(const string& filename) {
    ifstream fin(filename);

    if (!fin.is_open()) {
        return;
    }

    string datatype;
    while (fin >> datatype) {
        string name;
        fin >> name;
        string line;
        getline(fin, line);
        stringstream ss(line);
        if (datatype == "Array") {
            Array arr = Array_create(10);
            string value;
            while (ss >> value) {
                Array_push_back(arr, value);
            }
            arrays[name] = arr;
        }
        if (datatype == "OneLinkedList") {
            OneLinkedList onell = OneLinked_create();
            string value;
            while (ss >> value) {
                OneLinked_push_back(onell, value);
            }
            onellists[name] = onell;
        }
        if (datatype == "LinkedList") {
            LinkedList ll = Linked_create();
            string value;
            while (ss >> value) {
                Linked_push_back(ll, value);
            }
            llists[name] = ll;
        }
        if (datatype == "Queue") {
            Queue q = Queue_create();
            string value;
            while (ss >> value) {
                Queue_push_back(q, value);
            }
            queues[name] = q;
        }
        if (datatype == "Stack") {
            Stack s = Stack_create();
            string value;
            while (ss >> value) {
                Stack_push_back(s, value);
            }
            stacks[name] = s;
        }
        if (datatype == "Tree") {
            Tree t = Tree_create();
            string value;
            while (ss >> value) {
                t.root = Tree_insert(t.root, stoi(value));
            }
            trees[name] = t;
        }
        if (datatype == "Set") {
            Set s = Set_create();
            string value;
            while (ss >> value) {
                Set_add(s, value);
            }
            sets[name] = s;
        }
    }
    fin.close();
}

void make_change(const string& name, const vector<string>& data, Command command) {
    switch (command) {
        case Command::MCREATE: {
            Array arr = Array_create(10);
            arrays[name] = arr;
            break;
        }
        case Command::MPUSH: {
            for (auto& v : data)
                Array_push_back(arrays[name], v);
            break;
        }
        case Command::MPUSHIDX: {
            if (data.size() >= 2)
                Array_insert(arrays[name], stoi(data[0]), data[1]);
            break;
        }
        case Command::MGET: {
            if (!data.empty())
                cout << Array_get(arrays[name], stoi(data[0])) << endl;
            break;
        }
        case Command::MDELIDX: {
            if (!data.empty())
                Array_erase(arrays[name], stoi(data[0]));
            break;
        }
        case Command::MSETIDX: {
            if (data.size() >= 2)
                Array_set(arrays[name], stoi(data[0]), data[1]);
            break;
        }
        case Command::MLENGTH: {
            cout << "Length: " << Array_length(arrays[name]) << endl;
            break;
        }
        case Command::MREAD: {
            cout << Array_read(arrays[name]) << endl;
            break;
        }

        case Command::FPUSH: {
            for (auto& v : data)
                OneLinked_push_back(onellists[name], v);
            break;
        }
        case Command::FPUSHHEAD: {
            for (auto& v : data)
                OneLinked_push_front(onellists[name], v);
            break;
        }
        case Command::FPUSHBEFORE: {
            if (data.size() >= 2)
                OneLinked_push_before(onellists[name], data[0], data[1]);
            break;
        }
        case Command::FPUSHAFTER: {
            if (data.size() >= 2)
                OneLinked_push_after(onellists[name], data[0], data[1]);
            break;
        }
        case Command::FPOP: {
            string val = OneLinked_pop_back(onellists[name]);
            if (!val.empty()) cout << val << endl;
            break;
        }
        case Command::FPOPHEAD: {
            string val = OneLinked_pop_front(onellists[name]);
            if (!val.empty()) cout << val << endl;
            break;
        }
        case Command::FPOPAFTER: {
            if (!data.empty()) {
                string val = OneLinked_pop_after(onellists[name], data[0]);
                if (!val.empty()) cout << val << endl;
            }
            break;
        }
        case Command::FPOPBEFORE: {
            if (!data.empty()) {
                string val = OneLinked_pop_before(onellists[name], data[0]);
                if (!val.empty()) cout << val << endl;
            }
            break;
        }
        case Command::FDELVAL: {
            if (!data.empty())
                OneLinked_del_by_value(onellists[name], data[0]);
            break;
        }
        case Command::FFINDVAL: {
            if (!data.empty())
                cout << OneLinked_find_by_value(onellists[name], data[0]) << endl;
            break;
        }
        case Command::FREADHT: {
            cout << OneLinked_read(onellists[name]) << endl;
            break;
        }
        case Command::FREADTH: {
            cout << OneLinked_read_reverse(onellists[name]) << endl;
            break;
        }

        case Command::LPUSHHEAD: {
            for (auto& v : data)
                Linked_push_front(llists[name], v);
            break;
        }
        case Command::LPUSH: {
            for (auto& v : data)
                Linked_push_back(llists[name], v);
            break;
        }
        case Command::LPOPHEAD: {
            string val = Linked_pop_front(llists[name]);
            if (!val.empty()) cout << val << endl;
            break;
        }
        case Command::LPOP: {
            string val = Linked_pop_back(llists[name]);
            if (!val.empty()) cout << val << endl;
            break;
        }
        case Command::LPOPBEFORE: {
            if (!data.empty()) {
                string val = Linked_pop_before(llists[name], data[0]);
                if (!val.empty()) cout << val << endl;
            }
            break;
        }
        case Command::LPOPAFTER: {
            if (!data.empty()) {
                string val = Linked_pop_after(llists[name], data[0]);
                if (!val.empty()) cout << val << endl;
            }
            break;
        }
        case Command::LPUSHBEFORE: {
            if (data.size() >= 2)
                Linked_push_before(llists[name], data[0], data[1]);
            break;
        }
        case Command::LPUSHAFTER: {
            if (data.size() >= 2)
                Linked_push_after(llists[name], data[0], data[1]);
            break;
        }
        case Command::LDELVAL: {
            if (!data.empty())
                Linked_del_by_value(llists[name], data[0]);
            break;
        }
        case Command::LFINDVAL: {
            if (!data.empty())
                cout << Linked_find(llists[name], data[0]) << endl;
            break;
        }
        case Command::LREADHT: {
            cout << Linked_read(llists[name]) << endl;
            break;
        }
        case Command::LREADTH: {
            cout << Linked_read_reverse(llists[name]) << endl;
            break;
        }

        case Command::SPUSH: {
            for (auto& v : data)
                Stack_push_back(stacks[name], v);
            break;
        }
        case Command::SPOP: {
            string val = Stack_pop(stacks[name]);
            if (!val.empty()) cout << val << endl;
            break;
        }
        case Command::SREAD: {
            cout << Stack_read(stacks[name]) << endl;
            break;
        }

        case Command::QPUSH: {
            for (const auto& v : data)
                Queue_push_back(queues[name], v);
            break;
        }
        case Command::QPOP: {
            string val = Queue_pop(queues[name]);
            if (!val.empty()) cout << val << endl;
            break;
        }
        case Command::QREAD: {
            cout << Queue_read(queues[name]) << endl;
            break;
        }

        case Command::TINSERT: {
            for (auto& v : data)
                trees[name].root = Tree_insert(trees[name].root, stoi(v));
            break;
        }
        case Command::TDELETE: {
            if (!data.empty())
                trees[name].root = Tree_delete(trees[name].root, stoi(data[0]));
            break;
        }
        case Command::TREAD: {
            cout << Tree_read(trees[name]) << endl;
            break;
        }
        case Command::ISMEMBER: {
            if (!data.empty()) {
                if (is_member(trees[name], stoi(data[0]))) {
                    cout << "TRUE" << endl;
                } else {
                    cout << "FALSE" << endl;
                }
            }
            break;
        }

        case Command::SETADD: {
            if (!sets.count(name)) {
                sets[name] = Set_create();
            }
            for (const auto& v : data) {
                Set_add(sets[name], v);
            }
            break;
        }
        case Command::SETDEL: {
            if (sets.count(name)) {
                for (const auto& v : data) {
                    Set_del(sets[name], v);
                }
            }
            break;
        }
        case Command::SET_AT: {
            if (!data.empty()) {
                if (sets.count(name) && Set_has(sets[name], data[0])) {
                    cout << "true" << endl;
                } else {
                    cout << "false" << endl;
                }
            }
            break;
        }

        case Command::PRINT: {
            cout << "=== PRINT ===" << endl;

            if (arrays.count(name)) {
                cout << "Array " << name << ":" << Array_read(arrays[name]) << endl;
                break;
            }
            if (onellists.count(name)) {
                cout << "OneLinkedList " << name << " (Head→Tail):" 
                     << OneLinked_read(onellists[name]) << endl;
                cout << "OneLinkedList " << name << " (Tail→Head):" 
                     << OneLinked_read_reverse(onellists[name]) << endl;
                break;
            }
            if (llists.count(name)) {
                cout << "LinkedList " << name << " (Head→Tail):" 
                     << Linked_read(llists[name]) << endl;
                cout << "LinkedList " << name << " (Tail→Head):" 
                     << Linked_read_reverse(llists[name]) << endl;
                break;
            }
            if (queues.count(name)) {
                cout << "Queue " << name << ":" << Queue_read(queues[name]) << endl;
                break;
            }
            if (stacks.count(name)) {
                cout << "Stack " << name << ":" << Stack_read(stacks[name]) << endl;
                break;
            }
            if (trees.count(name)) {
                Tree_print(trees[name]);
                break;
            }
            if (sets.count(name)) {
                cout << "Set " << name << ": {";
                bool first = true;
                for (size_t i = 0; i < sets[name].map.cap; i++) {
                    if (sets[name].map.node[i].status == NodeStatus::USED) {
                        if (!first) cout << ", ";
                        cout << sets[name].map.node[i].val;
                        first = false;
                    }
                }
                cout << "}" << endl;
                break;
            }

            cout << "Объект \"" << name << "\" не найден." << endl;
            break;
        }

        default:
            cout << "Неизвестная команда." << endl;
    }
}

void parsing(const string& filename, const string& query) {
    read(filename);

    stringstream ss(query);
    string command;
    ss >> command;

    if (!command_map.count(command)) {
        cout << "Неизвестная команда: " << command << endl;
        return;
    }

    string name;
    ss >> name;
    vector<string> data;
    string temp;
    while (ss >> temp) {
        data.push_back(temp);
    }

    make_change(name, data, command_map[command]);

    write(filename);
}

void run_task2() {
    cout << "Task 2 (Set ADT)\n";
    string filename, query;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter query (e.g. SETADD myset val1, SETDEL myset val1, SET_AT myset val1, PRINT myset):\n> ";
    cin.ignore();
    getline(cin, query);
    try {
        parsing(filename, query);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

void run_task(int choice) {
    switch (choice) {
        case 1: {
            run_task1();
            break;
        }
        case 3: {
            run_task3();
            break;
        }
        case 4: {
            run_task4();
            break;
        }
        case 5: {
            run_task5();
            break;
        }
        case 7: {
            run_task7();
            break;
        }
        default: {
            cout << "Unknown task.\n";
            break;
        }
    }
}

void run_interactive() {
    int choice;
    cout << "Enter task (1, 3, 4, 5, 7 or 0 to exit): ";
    while (cin >> choice && choice != 0) {
        run_task(choice);
        cout << "\nEnter task (1, 3, 4, 5, 7 or 0 to exit): ";
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        run_interactive();
        return 0;
    }

    string filename, query;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (string(argv[i]) == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (!filename.empty() && !query.empty()) {
        try {
            parsing(filename, query);
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}