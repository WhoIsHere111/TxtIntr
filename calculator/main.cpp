#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

const double PI = 3.14159265358979323846;

// ---------- Справка ----------
void printHelp() {
    cout << "Использование:\n";
    cout << "  calculator -o <операция> [-u <единицы>] <угол>\n\n";
    cout << "Операции:\n";
    cout << "  tan   — тангенс угла\n";
    cout << "  cot   — котангенс угла\n\n";
    cout << "Единицы измерения (-u, --units):\n";
    cout << "  deg   — градусы (по умолчанию)\n";
    cout << "  rad   — радианы\n\n";
    cout << "Примеры:\n";
    cout << "  calculator -o tan 45                # tan(45°) = 1\n";
    cout << "  calculator -o tan -u rad 0.785398   # tan(π/4) ≈ 1\n";
    cout << "  calculator -o cot 45                # cot(45°) = 1\n";
    cout << "  calculator --operation tan --units rad 1.5708  # tan(π/2) → ∞\n";
    cout << "  calculator                          # эта справка\n";
}

// ---------- Перевод в радианы ----------
double toRadians(double angle, const string& units) {
    if (units == "rad") return angle;
    // по умолчанию — градусы
    return angle * PI / 180.0;
}

// ---------- Тангенс ----------
double opTan(double angle, const string& units) {
    double x = toRadians(angle, units);
    return tan(x);
}

// ---------- Котангенс ----------
double opCot(double angle, const string& units) {
    double x = toRadians(angle, units);
    double s = sin(x);
    if (fabs(s) < 1e-12) {
        // котангенс не определён
        return NAN;
    }
    return cos(x) / s;
}

// ---------- main ----------
int main(int argc, char* argv[]) {
    if (argc == 1) {
        printHelp();
        return 0;
    }

    string operation;
    string units = "deg";   // по умолчанию градусы
    vector<double> operands;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-o" || arg == "--operation") {
            if (i + 1 >= argc) {
                cerr << "Ошибка: не указано имя операции после " << arg << "\n";
                return 1;
            }
            operation = argv[++i];
        } else if (arg == "-u" || arg == "--units") {
            if (i + 1 >= argc) {
                cerr << "Ошибка: не указаны единицы измерения после " << arg << "\n";
                return 1;
            }
            units = argv[++i];
            if (units != "deg" && units != "rad") {
                cerr << "Ошибка: единицы должны быть deg или rad (получено '"
                     << units << "')\n";
                return 1;
            }
        } else {
            try {
                operands.push_back(stod(arg));
            } catch (...) {
                cerr << "Ошибка: неизвестный аргумент '" << arg << "'\n";
                return 1;
            }
        }
    }

    if (operation.empty()) {
        cerr << "Ошибка: не задана операция (-o <tan|cot>)\n";
        printHelp();
        return 1;
    }

    if (operands.size() != 1) {
        cerr << "Ошибка: нужен ровно один операнд (угол). Получено "
             << operands.size() << "\n";
        return 1;
    }

    double angle = operands[0];
    double result = 0.0;

    if (operation == "tan") {
        result = opTan(angle, units);
    } else if (operation == "cot") {
        result = opCot(angle, units);
    } else {
        cerr << "Ошибка: неизвестная операция '" << operation
             << "'. Доступны: tan, cot\n";
        return 1;
    }

    if (isnan(result)) {
        cerr << "Ошибка: результат не определён (деление на ноль)\n";
        return 2;
    }

    cout << result << endl;
    return 0;
}
