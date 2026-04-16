#include <iostream>
#include <string>

using namespace std;

// =====================================================
// Task 1.7
// Liquid -> AlcoholDrink
// =====================================================

class Liquid {
protected:
    string name;
    double density;

public:
    Liquid() : name("Unknown"), density(0.0) {
        cout << "[Liquid] Default constructor" << endl;
    }

    Liquid(const string& n, double d) : name(n), density(d >= 0 ? d : 0.0) {
        cout << "[Liquid] Constructor with parameters" << endl;
    }

    virtual ~Liquid() {
        cout << "[Liquid] Destructor" << endl;
    }

    void setDensity(double d) {
        if (d >= 0)
            density = d;
    }

    virtual void input() {
        cout << "Enter liquid name: ";
        getline(cin >> ws, name);

        cout << "Enter density: ";
        cin >> density;

        while (density < 0) {
            cout << "Density must be >= 0. Enter again: ";
            cin >> density;
        }
    }

    virtual void print() const {
        cout << "Name: " << name << endl;
        cout << "Density: " << density << endl;
    }
};

class AlcoholDrink : public Liquid {
private:
    double strength;

public:
    AlcoholDrink() : Liquid(), strength(0.0) {
        cout << "[AlcoholDrink] Default constructor" << endl;
    }

    AlcoholDrink(const string& n, double d, double s)
        : Liquid(n, d), strength((s >= 0 && s <= 100) ? s : 0.0) {
        cout << "[AlcoholDrink] Constructor with parameters" << endl;
    }

    ~AlcoholDrink() override {
        cout << "[AlcoholDrink] Destructor" << endl;
    }

    void setStrength(double s) {
        if (s >= 0 && s <= 100)
            strength = s;
    }

    void input() override {
        Liquid::input();

        cout << "Enter strength (%): ";
        cin >> strength;

        while (strength < 0 || strength > 100) {
            cout << "Strength must be in range 0..100. Enter again: ";
            cin >> strength;
        }
    }

    void print() const override {
        cout << "--- Alcohol Drink ---" << endl;
        Liquid::print();
        cout << "Strength: " << strength << "%" << endl;
    }
};

void runTask1() {
    cout << "\n===== Task 1.7 =====" << endl;

    AlcoholDrink a1("Vodka", 0.95, 40.0);
    a1.print();

    cout << endl;
    a1.setDensity(0.97);
    a1.setStrength(42.0);

    cout << "After changing density and strength:" << endl;
    a1.print();

    cout << endl;
    AlcoholDrink a2;
    a2.input();
    cout << "Entered object:" << endl;
    a2.print();
}

// =====================================================
// Task 2.7
// Wheel, Bicycle, Car
// Composition + hierarchy
// =====================================================

class Wheel {
private:
    double radius;

public:
    Wheel() : radius(0.0) {}

    Wheel(double r) : radius(r >= 0 ? r : 0.0) {}

    void setRadius(double r) {
        if (r >= 0)
            radius = r;
    }

    double getRadius() const {
        return radius;
    }

    void print() const {
        cout << "Wheel radius: " << radius << endl;
    }
};

class Transport {
protected:
    string brand;
    int wheelCount;
    Wheel wheel;

public:
    Transport() : brand("Unknown"), wheelCount(0), wheel() {}

    Transport(const string& b, int wc, double r)
        : brand(b), wheelCount(wc), wheel(r) {
    }

    virtual ~Transport() {}

    virtual void print() const {
        cout << "Brand: " << brand << endl;
        cout << "Wheel count: " << wheelCount << endl;
        wheel.print();
    }
};

class Bicycle : public Transport {
private:
    int gears;

public:
    Bicycle() : Transport("Unknown bicycle", 2, 0.3), gears(1) {}

    Bicycle(const string& b, double r, int g)
        : Transport(b, 2, r), gears(g) {
    }

    void print() const override {
        cout << "--- Bicycle ---" << endl;
        Transport::print();
        cout << "Gears: " << gears << endl;
    }
};

class Car : public Transport {
private:
    double engineVolume;

public:
    Car() : Transport("Unknown car", 4, 0.4), engineVolume(0.0) {}

    Car(const string& b, double r, double e)
        : Transport(b, 4, r), engineVolume(e) {
    }

    void print() const override {
        cout << "--- Car ---" << endl;
        Transport::print();
        cout << "Engine volume: " << engineVolume << endl;
    }
};

void runTask2() {
    cout << "\n===== Task 2.7 =====" << endl;

    Bicycle bike("Trek", 0.3, 18);
    Car car("BMW", 0.4, 2.0);

    bike.print();
    cout << endl;
    car.print();
}

// =====================================================
// Task 3.7
// Person -> Teacher
// Copy constructor and assignment via base class
// Stream-like input/output through methods
// =====================================================

class Person {
protected:
    string fullName;
    int age;

public:
    Person() : fullName("Unknown"), age(0) {}

    Person(const string& fn, int a) : fullName(fn), age(a) {}

    Person(const Person& other) : fullName(other.fullName), age(other.age) {
        cout << "[Person] Copy constructor" << endl;
    }

    Person& operator=(const Person& other) {
        if (this != &other) {
            fullName = other.fullName;
            age = other.age;
        }
        cout << "[Person] Assignment operator" << endl;
        return *this;
    }

    virtual ~Person() {}

    virtual void input() {
        cout << "Enter full name: ";
        getline(cin >> ws, fullName);

        cout << "Enter age: ";
        cin >> age;
    }

    virtual void print() const {
        cout << "Full name: " << fullName << endl;
        cout << "Age: " << age << endl;
    }
};

class Teacher : public Person {
private:
    string subject;
    int experience;

public:
    Teacher() : Person(), subject("Unknown"), experience(0) {}

    Teacher(const string& fn, int a, const string& s, int e)
        : Person(fn, a), subject(s), experience(e) {
    }

    Teacher(const Teacher& other) : Person(other) {
        subject = other.subject;
        experience = other.experience;
        cout << "[Teacher] Copy constructor" << endl;
    }

    Teacher& operator=(const Teacher& other) {
        if (this != &other) {
            Person::operator=(other);
            subject = other.subject;
            experience = other.experience;
        }
        cout << "[Teacher] Assignment operator" << endl;
        return *this;
    }

    void input() override {
        Person::input();

        cout << "Enter subject: ";
        getline(cin >> ws, subject);

        cout << "Enter experience: ";
        cin >> experience;
    }

    void print() const override {
        cout << "--- Teacher ---" << endl;
        Person::print();
        cout << "Subject: " << subject << endl;
        cout << "Experience: " << experience << endl;
    }
};

void runTask3() {
    cout << "\n===== Task 3.7 =====" << endl;

    Teacher t1;
    t1.input();

    cout << "\nEntered object:" << endl;
    t1.print();

    cout << "\nCopy constructor test:" << endl;
    Teacher t2(t1);
    t2.print();

    cout << "\nAssignment operator test:" << endl;
    Teacher t3;
    t3 = t1;
    t3.print();
}

// =====================================================
// Main menu
// =====================================================

void showMenu() {
    cout << "\n========================" << endl;
    cout << "Lab Work #5" << endl;
    cout << "1 - Task 1.7" << endl;
    cout << "2 - Task 2.7" << endl;
    cout << "3 - Task 3.7" << endl;
    cout << "4 - Run all tasks" << endl;
    cout << "q - Exit" << endl;
    cout << "Your choice: ";
}

int main() {
    char choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case '1':
            runTask1();
            break;
        case '2':
            runTask2();
            break;
        case '3':
            runTask3();
            break;
        case '4':
            runTask1();
            runTask2();
            runTask3();
            break;
        case 'q':
            cout << "Program finished." << endl;
            break;
        default:
            cout << "Wrong choice." << endl;
        }

    } while (choice != 'q');

    return 0;
}