#include <Windows.h> 
#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string fio;
    string gruppa;
    vector<int> ocenki;
};

struct Group {
    string nazvanie;
};

vector<Student> students;
vector<Group> gruppy;

void dobavit() {
    Student s;

    cin.ignore();
    cout << "ФИО: ";
    getline(cin, s.fio);

    cout << "Группа: ";
    getline(cin, s.gruppa);

    students.push_back(s);
}

void pokazat() {
    for (int i = 0; i < students.size(); i++) {
        cout << i + 1 << ". " << students[i].fio
            << " | " << students[i].gruppa << endl;
    }
}

void izmenit() {
    pokazat();

    int n;
    cout << "Номер студента: ";
    cin >> n;

    if (n >= 1 && n <= students.size()) {
        Student& s = students[n - 1];

        cin.ignore();
        cout << "Новое ФИО: ";
        getline(cin, s.fio);

        cout << "Новая группа: ";
        getline(cin, s.gruppa);
    }
}

void udalit() {
    pokazat();

    int n;
    cout << "Номер студента: ";
    cin >> n;

    if (n >= 1 && n <= students.size()) {
        students.erase(students.begin() + n - 1);
    }
}

void dobavitOcenku() {
    pokazat();

    int n, ocenka;
    cout << "Номер студента: ";
    cin >> n;

    if (n >= 1 && n <= students.size()) {
        cout << "Оценка от 2 до 5: ";
        cin >> ocenka;

        if (ocenka >= 2 && ocenka <= 5) {
            Student* s = &students[n - 1];
            s->ocenki.push_back(ocenka);
        }
    }
}

void sredniyBall() {
    pokazat();

    int n, summa = 0;
    cout << "Номер студента: ";
    cin >> n;

    if (n >= 1 && n <= students.size()) {
        Student& s = students[n - 1];

        for (int ocenka : s.ocenki) {
            summa += ocenka;
        }

        if (!s.ocenki.empty()) {
            cout << "Средний балл: "
                << (double)summa / s.ocenki.size() << endl;
        }
        else {
            cout << "Оценок нет.\n";
        }
    }
}

void dobavitGruppu() {
    Group g;

    cin.ignore();
    cout << "Название группы: ";
    getline(cin, g.nazvanie);

    gruppy.push_back(g);
}

void pokazatGruppy() {
    for (int i = 0; i < gruppy.size(); i++) {
        cout << i + 1 << ". " << gruppy[i].nazvanie << endl;
    }
}

void izmenitGruppu() {
    pokazatGruppy();

    int n;
    cout << "Номер группы: ";
    cin >> n;

    if (n >= 1 && n <= gruppy.size()) {
        string staraya = gruppy[n - 1].nazvanie;

        cin.ignore();
        cout << "Новое название: ";
        getline(cin, gruppy[n - 1].nazvanie);

        for (Student& s : students) {
            if (s.gruppa == staraya) {
                s.gruppa = gruppy[n - 1].nazvanie;
            }
        }
    }
}

void udalitGruppu() {
    pokazatGruppy();

    int n;
    cout << "Номер группы: ";
    cin >> n;

    if (n >= 1 && n <= gruppy.size()) {
        string nazvanie = gruppy[n - 1].nazvanie;
        bool est = false;

        for (Student& s : students) {
            if (s.gruppa == nazvanie) {
                est = true;
            }
        }

        if (est) {
            cout << "В группе есть студенты. Удаление невозможно.\n";
        }
        else {
            gruppy.erase(gruppy.begin() + n - 1);
            cout << "Группа удалена.\n";
        }
    }
}

void statistika() {
    pokazatGruppy();

    int n;
    cout << "Номер группы: ";
    cin >> n;

    if (n >= 1 && n <= gruppy.size()) {
        int otlichniki = 0, horoshisty = 0;

        for (Student& s : students) {
            if (s.gruppa == gruppy[n - 1].nazvanie &&
                !s.ocenki.empty()) {

                int summa = 0;

                for (int ocenka : s.ocenki) {
                    summa += ocenka;
                }

                double ball = (double)summa / s.ocenki.size();

                if (ball >= 4.5) otlichniki++;
                else if (ball >= 3.5) horoshisty++;
            }
        }

        cout << "Отличников: " << otlichniki << endl;
        cout << "Хорошистов: " << horoshisty << endl;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    gruppy.push_back({ "БД-1-25" });
    gruppy.push_back({ "БД-2-25" });

    students.push_back({ "Комлев Кирилл", "БД-1-25", {2, 2, 3} });
    students.push_back({ "Вепрева Мила", "БД-1-25", {5, 5, 4} });
    students.push_back({ "Соседова Варвара", "БД-2-25", {5, 5, 4} });

    int v;

    do {
        cout << "\n=== УЧЕБНАЯ ГРУППА ===\n 1. Добавить студента\n 2. Показать студентов\n 3. Изменить студента\n 4. Удалить студента\n 5. Добавить оценку\n 6. Средний балл студента\n 7. Добавить группу\n 8. Показать группы\n 9. Изменить группу\n 10. Удалить группу\n 11. Статистика группы\n 0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> v;

        if (v == 1) dobavit();
        if (v == 2) pokazat();
        if (v == 3) izmenit();
        if (v == 4) udalit();
        if (v == 5) dobavitOcenku();
        if (v == 6) sredniyBall();
        if (v == 7) dobavitGruppu();
        if (v == 8) pokazatGruppy();
        if (v == 9) izmenitGruppu();
        if (v == 10) udalitGruppu();
        if (v == 11) statistika();

    } while (v != 0);

    return 0;
}
