#include <bits/stdc++.h>

using namespace std;

int unesiBroj(int min, int max) {
    int broj;
    cin >> broj;
    if (broj < min || broj > max) {
        throw invalid_argument("Neispravan unos.");
    }
    return broj;
}

void unesiBrojeve(int &trazeniBroj, vector<int> &brojevi) {
    cout << "Unesite traženi broj (1-999):" << endl;
    trazeniBroj = unesiBroj(1, 999);

    cout << "Unesite 4 broja između 1 i 9:" << endl;
    for (int i = 0; i < 4; i++) {
        brojevi.push_back(unesiBroj(1, 9));
    }

    cout << "Unesite jedan broj (10, 15 ili 20):" << endl;
    int broj5 = unesiBroj(10, 20);
    if (broj5 != 10 && broj5 != 15 && broj5 != 20) {
        throw invalid_argument("Broj mora biti 10, 15 ili 20.");
    }
    brojevi.push_back(broj5);

    cout << "Unesite jedan broj (25, 50 ili 75):" << endl;
    int broj6 = unesiBroj(25, 75);
    if (broj6 != 25 && broj6 != 50 && broj6 != 75) {
        throw invalid_argument("Broj mora biti 25, 50 ili 75.");
    }
    brojevi.push_back(broj6);
}

bool jeOperator(const string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int evaluirajPostfix(const vector<string> &postfix) {
    stack<int> stek;

    for (const auto &token : postfix) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            stek.push(atoi(token.c_str())); // Konvertuj string u int
        } else if (jeOperator(token)) {
            if (stek.size() < 2) return INT_MAX; // Nije validan izraz
            int b = stek.top(); stek.pop();
            int a = stek.top(); stek.pop();
            if (token == "+") stek.push(a + b);
            else if (token == "-") stek.push(a - b);
            else if (token == "*") stek.push(a * b);
            else if (token == "/") {
                if (b == 0) return INT_MAX; // Podela sa nulom
                stek.push(a / b);
            }
        }
    }
    return stek.empty() ? INT_MAX : stek.top();
}

string postfixUInfix(const vector<string> &postfix) {
    stack<string> stek;

    for (const auto &token : postfix) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            stek.push(token);
        } else if (jeOperator(token)) {
            if (stek.size() < 2) return ""; // Nije validan izraz
            string b = stek.top(); stek.pop();
            string a = stek.top(); stek.pop();
            string izraz = "(" + a + " " + token + " " + b + ")";
            stek.push(izraz);
        }
    }
    return stek.empty() ? "" : stek.top();
}

void generisiSvePostfixKombinacije(const vector<int> &brojevi, vector<string> &operators, vector<vector<string>> &rezultati, vector<string> trenutnaKombinacija, int brojeviIndex, int operIndex) {
    if (brojeviIndex == brojevi.size() && operIndex == brojevi.size() - 1) {
        rezultati.push_back(trenutnaKombinacija);
        return;
    }

    if (brojeviIndex < brojevi.size()) {
        trenutnaKombinacija.push_back(to_string(brojevi[brojeviIndex]));
        generisiSvePostfixKombinacije(brojevi, operators, rezultati, trenutnaKombinacija, brojeviIndex + 1, operIndex);
        trenutnaKombinacija.pop_back();
    }

    if (operIndex < brojeviIndex - 1) {
        for (const auto &op : operators) {
            trenutnaKombinacija.push_back(op);
            generisiSvePostfixKombinacije(brojevi, operators, rezultati, trenutnaKombinacija, brojeviIndex, operIndex + 1);
            trenutnaKombinacija.pop_back();
        }
    }
}

int main() {
    try {
        int trazeniBroj;
        vector<int> brojevi;
        unesiBrojeve(trazeniBroj, brojevi);
        
        vector<string> operators = {"+", "-", "*", "/"};
        vector<vector<string>> postfixIzrazi;
        vector<string> trenutnaKombinacija;

        generisiSvePostfixKombinacije(brojevi, operators, postfixIzrazi, trenutnaKombinacija, 0, 0);
        
        int najboljiRezultat = INT_MAX;
        vector<string> najboljiPostfix;

        for (const auto &postfix : postfixIzrazi) {
            int rezultat = evaluirajPostfix(postfix);
            if (abs(rezultat - trazeniBroj) < abs(najboljiRezultat - trazeniBroj)) {
                najboljiRezultat = rezultat;
                najboljiPostfix = postfix;
            }
        }

        cout << "Najbolji rezultat: " << najboljiRezultat << endl;
        cout << "Najbolji izraz u postfix notaciji: ";
        for (const auto &token : najboljiPostfix) {
            cout << token << " ";
        }
        cout << endl;
        cout << "Najbolji izraz u infix notaciji: " << postfixUInfix(najboljiPostfix) << endl;
    } catch (const invalid_argument &e) {
        cout << e.what() << endl;
    }

    return 0;
}
