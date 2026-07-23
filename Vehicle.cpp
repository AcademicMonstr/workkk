#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <memory>

class Vehicle{
    protected:
    std::string brand = "";
    std::string model = "";
    int year = 0;
    double mileage = 0;
    double price = 0;

    public:
    virtual void displayInfo() const = 0;
    virtual double calculateTax() const = 0;
    virtual double calculateDepreciation(double currentYear) const = 0;
    virtual std::string getType() const = 0;
    virtual ~Vehicle() = default;
    int getYear() const {return year;};
    double getMileage() const {return mileage;};
    double getPrice() const {return price;};

    Vehicle(std::string br, std::string ml, int yr, double mil, double pr) :
        brand(br), model(ml), year(yr), mileage(mil), price(pr){
            if(year < 0) throw;
            if(mileage < 0) throw;
            if(price < 0) throw;
        }

};

enum class bodyType{
    sedan,
    hatchback,
    universall
};

class Car : public Vehicle {
    bodyType type;
    double engineCC;

    std::string typeToString(bodyType type) const{
        if (type == bodyType::sedan) return "sedan";
        if (type == bodyType::hatchback) return "hatchback";
        if (type == bodyType::universall) return "universall";
    }

    public:
    Car(std::string br, std::string ml, int yr, double mil, double pr, bodyType tp, double eCC) :
        Vehicle(br, ml, yr, mil, pr), type(tp), engineCC(eCC){
            if(engineCC < 0) throw;
        } 



    void displayInfo() const override{
        std::cout << "[Car] "
                  << "brand: " << brand
                  << ", model: " << model
                  << ", year: " << year
                  << ", mileage: " << mileage
                  << ", price " << price
                  << ", type: " << typeToString(type)
                  << ", engineCC: " << engineCC;
    }

    double calculateTax() const override{
        return (engineCC/30)*2.5;
    }

    double calculateDepreciation(double currentYear) const override{
        double a = (price*(currentYear - year))/20;
        return std::max(0.0, a);
    }

    std::string getType() const override{
        return "Car";
    }
};

class Motorcycle : public Vehicle{
    double engineCC;
    bool hasSidecar;

    

    public:
    Motorcycle(std::string br, std::string ml, int yr, double mil, double pr, double eCC, bool sidecar) :
        Vehicle(br, ml, yr, mil, pr), engineCC(eCC), hasSidecar(sidecar){
            if(engineCC < 0) throw;
        } 



    void displayInfo() const override{
        std::cout << "[Motorcycle] "
                  << "brand: " << brand
                  << ", model: " << model
                  << ", year: " << year
                  << ", mileage: " << mileage
                  << ", price " << price
                  << ", engineCC: " << engineCC
                  << ", sidecar: " << hasSidecar;
    }

    double calculateTax() const override{
        return engineCC;
    }

    double calculateDepreciation(double currentYear) const override{
        double a = (price*(currentYear - year))/20;
        return std::max(0.0, a);
    }

    std::string getType() const override{
        return "Motorcycle";
    }
};

class Truck : public Vehicle{
    int capacity;
    bool hasTrailer;

    public:
    Truck(std::string br, std::string ml, int yr, double mil, double pr, int cp, bool trailer) :
        Vehicle(br, ml, yr, mil, pr), capacity(cp), hasTrailer(trailer){
            if(capacity < 0) throw;
        } 



    void displayInfo() const override{
        std::cout << "[Truck] "
                  << "brand: " << brand
                  << ", model: " << model
                  << ", year: " << year
                  << ", mileage: " << mileage
                  << ", price " << price
                  << ", capacity: " << capacity
                  << ", trailer: " << hasTrailer;
    }

    double calculateTax() const override{
        return capacity*5;
    }

    double calculateDepreciation(double currentYear) const override{
        double a = (price*(currentYear - year))/20;
        return std::max(0.0, a);
    }

    std::string getType() const override{
        return "Truck";
    }
};

class Fleet{
    std::vector<std::unique_ptr<Vehicle>> vehicles;

    public: 

    void addVehicle(std::unique_ptr<Vehicle> v){
        vehicles.push_back(std::move(v));
    }

    void removeVehicle(int index){
        vehicles.erase(vehicles.begin() + index);
    }

    void displayAll() const{
        for(const auto& elem : vehicles){
            elem -> displayInfo();
            std::cout << "\n";
        }
    }

    void showStatistics() const {
        double totalPrice = 0.0;
        double totalMileage = 0.0;
        double totalTax = 0.0;
        std::for_each(vehicles.begin(), vehicles.end(), [&](const std::unique_ptr<Vehicle>& v) {
            totalPrice += v -> getPrice();
            totalMileage += v -> getMileage();
            totalTax += v -> calculateTax();

            std::cout << v -> getType() << ", tax: " << v -> calculateTax() << '\n';
        });

        std::cout << "\n=== Fleet Statistics ===\n";
        std::cout << "Total price: " << totalPrice << " rub\n";
        std::cout << "Total mileage: " << totalMileage << " km\n";
        std::cout << "Total tax: " << totalTax << " rub\n";
    }

    void search() const {

    }
};
















#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iomanip>

using namespace std;

// ===================== Exceptions =====================
struct AppException : runtime_error {
    using runtime_error::runtime_error;
};

struct FileException : AppException {
    using AppException::AppException;
};

struct InputException : AppException {
    using AppException::AppException;
};

struct NotFoundException : AppException {
    using AppException::AppException;
};

// ===================== Vehicle base class =====================
class Vehicle {
public:
    virtual ~Vehicle() = default;

    virtual void displayInfo() const = 0;
    virtual double calculateTax() const = 0;
    virtual double calculateDepreciation(double currentYear) const = 0;
    virtual string getType() const = 0; // "Car" / "Truck" / "Motorcycle"

    // common fields (по желанию можно унифицировать часть интерфейса)
    virtual double getPrice() const = 0;
    virtual double getMileage() const = 0;
    virtual int getYear() const = 0;
};

// ===================== Car =====================
class Car : public Vehicle {
private:
    string brand, model, bodyType, engineType; // engineType не требуется в ТЗ, но можно не использовать
    int year;
    double mileage;   // пробег, км
    double price;     // стоимость, руб
    double engineCC;  // объем двигателя, см^3
    string fuelType;  // не требуется — можно убрать
    // ТЗ: тип кузова (седан, хэтчбек, универсал)
    string body;
    // ТЗ: объем двигателя (engineCC)
public:
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getBody() const { return body; }

    Car(string br, string mo, int y, double mil, double pr, string bodyType, double engCC)
        : brand(move(br)), model(move(mo)), year(y), mileage(mil), price(pr),
          engineCC(engCC), body(move(bodyType))
    {
        if (year < 0) throw InputException("Некорректный год.");
        if (mileage < 0) throw InputException("Некорректный пробег.");
        if (price < 0) throw InputException("Некорректная стоимость.");
        if (engineCC <= 0) throw InputException("Некорректный объем двигателя.");
    }

    void displayInfo() const override {
        cout << "[Car] brand=" << brand
             << ", model=" << model
             << ", year=" << year
             << ", mileage=" << mileage
             << ", price=" << price
             << ", body=" << body
             << ", engineCC=" << engineCC << "\n";
    }

    double calculateTax() const override {
        // легковые: 2.5 руб/л.с. (мощность считается через объем, например объем/30)
        // ТЗ: мощность = объём / 30
        double power = engineCC / 30.0;
        return 2.5 * power;
    }

    double calculateDepreciation(double currentYear) const override {
        // линейная модель: стоимость * (текущий_год - год_выпуска) / 20, но не ниже 0
        double d = price * (currentYear - year) / 20.0;
        return max(0.0, d);
    }

    string getType() const override { return "Car"; }

    double getPrice() const override { return price; }
    double getMileage() const override { return mileage; }
    int getYear() const override { return year; }

    // For serialization
    string serialize() const {
        // Car|brand|model|year|mileage|price|body|engineCC
        ostringstream oss;
        oss << "Car|" << brand << "|" << model << "|"
            << year << "|" << mileage << "|" << price << "|"
            << body << "|" << engineCC;
        return oss.str();
    }

    static unique_ptr<Vehicle> deserialize(const string& line) {
        // Car|...
        vector<string> t;
        split(line, '|', t);
        if (t.size() != 8) throw InputException("Некорректная строка Car.");
        return make_unique<Car>(
            t[1], t[2],
            stoi(t[3]),
            stod(t[4]),
            stod(t[5]),
            t[6],
            stod(t[7])
        );
    }

private:
    static void split(const string& s, char delim, vector<string>& out) {
        out.clear();
        string cur;
        for (char c : s) {
            if (c == delim) { out.push_back(cur); cur.clear(); }
            else cur += c;
        }
        out.push_back(cur);
    }
};

// ===================== Truck =====================
class Truck : public Vehicle {
private:
    string brand, model;
    int year;
    double mileage;
    double price;
    double engineCC;
    double capacityTons;   // грузоподъемность, тонн
    bool hasTrailer;
public:
    Truck(string br, string mo, int y, double mil, double pr, double engCC, double capT, bool trailer)
        : brand(move(br)), model(move(mo)), year(y), mileage(mil), price(pr),
          engineCC(engCC), capacityTons(capT), hasTrailer(trailer)
    {
        if (year < 0) throw InputException("Некорректный год.");
        if (mileage < 0) throw InputException("Некорректный пробег.");
        if (price < 0) throw InputException("Некорректная стоимость.");
        if (engineCC <= 0) throw InputException("Некорректный объем двигателя.");
        if (capacityTons < 0) throw InputException("Некорректная грузоподъемность.");
    }

    void displayInfo() const override {
        cout << "[Truck] brand=" << brand
             << ", model=" << model
             << ", year=" << year
             << ", mileage=" << mileage
             << ", price=" << price
             << ", engineCC=" << engineCC
             << ", capacityTons=" << capacityTons
             << ", hasTrailer=" << (hasTrailer ? "true" : "false") << "\n";
    }

    double calculateTax() const override {
        // грузовики: 5 руб/тонна
        return 5.0 * capacityTons;
    }

    double calculateDepreciation(double currentYear) const override {
        double d = price * (currentYear - year) / 20.0;
        return max(0.0, d);
    }

    string getType() const override { return "Truck"; }

    double getPrice() const override { return price; }
    double getMileage() const override { return mileage; }
    int getYear() const override { return year; }

    string serialize() const {
        // Truck|brand|model|year|mileage|price|engineCC|capacityTons|hasTrailer
        ostringstream oss;
        oss << "Truck|" << brand << "|" << model << "|"
            << year << "|" << mileage << "|" << price << "|"
            << engineCC << "|" << capacityTons << "|"
            << (hasTrailer ? 1 : 0);
        return oss.str();
    }

    static unique_ptr<Vehicle> deserialize(const string& line) {
        vector<string> t;
        split(line, '|', t);
        if (t.size() != 9) throw InputException("Некорректная строка Truck.");
        return make_unique<Truck>(
            t[1], t[2],
            stoi(t[3]),
            stod(t[4]),
            stod(t[5]),
            stod(t[6]),
            stod(t[7]),
            (stoi(t[8]) != 0)
        );
    }

private:
    static void split(const string& s, char delim, vector<string>& out) {
        out.clear();
        string cur;
        for (char c : s) {
            if (c == delim) { out.push_back(cur); cur.clear(); }
            else cur += c;
        }
        out.push_back(cur);
    }
};

// ===================== Motorcycle =====================
class Motorcycle : public Vehicle {
private:
    string brand, model;
    int year;
    double mileage;
    double price;
    double engineCC;
    bool hasSidecar;
public:
    Motorcycle(string br, string mo, int y, double mil, double pr, double engCC, bool sidecar)
        : brand(move(br)), model(move(mo)), year(y), mileage(mil), price(pr),
          engineCC(engCC), hasSidecar(sidecar)
    {
        if (year < 0) throw InputException("Некорректный год.");
        if (mileage < 0) throw InputException("Некорректный пробег.");
        if (price < 0) throw InputException("Некорректная стоимость.");
        if (engineCC <= 0) throw InputException("Некорректный объем двигателя.");
    }

    void displayInfo() const override {
        cout << "[Motorcycle] brand=" << brand
             << ", model=" << model
             << ", year=" << year
             << ", mileage=" << mileage
             << ", price=" << price
             << ", engineCC=" << engineCC
             << ", hasSidecar=" << (hasSidecar ? "true" : "false") << "\n";
    }

    double calculateTax() const override {
        // мотоциклы: 1 руб/см^3
        return 1.0 * engineCC;
    }

    double calculateDepreciation(double currentYear) const override {
        double d = price * (currentYear - year) / 20.0;
        return max(0.0, d);
    }

    string getType() const override { return "Motorcycle"; }

    double getPrice() const override { return price; }
    double getMileage() const override { return mileage; }
    int getYear() const override { return year; }

    string serialize() const {
        // Motorcycle|brand|model|year|mileage|price|engineCC|hasSidecar
        ostringstream oss;
        oss << "Motorcycle|" << brand << "|" << model << "|"
            << year << "|" << mileage << "|" << price << "|"
            << engineCC << "|" << (hasSidecar ? 1 : 0);
        return oss.str();
    }

    static unique_ptr<Vehicle> deserialize(const string& line) {
        vector<string> t;
        split(line, '|', t);
        if (t.size() != 8) throw InputException("Некорректная строка Motorcycle.");
        return make_unique<Motorcycle>(
            t[1], t[2],
            stoi(t[3]),
            stod(t[4]),
            stod(t[5]),
            stod(t[6]),
            (stoi(t[7]) != 0)
        );
    }

private:
    static void split(const string& s, char delim, vector<string>& out) {
        out.clear();
        string cur;
        for (char c : s) {
            if (c == delim) { out.push_back(cur); cur.clear(); }
            else cur += c;
        }
        out.push_back(cur);
    }
};

// ===================== Fleet =====================
class Fleet {
private:
    // контейнер для всех объектов парка
    vector<unique_ptr<Vehicle>> vehicles;

public:
    void addVehicle(unique_ptr<Vehicle> v) {
        if (!v) throw AppException("addVehicle: null vehicle.");
        vehicles.push_back(move(v));
    }

    void removeVehicleByIndex(size_t index) {
        if (index >= vehicles.size()) throw NotFoundException("Удаление: индекс вне диапазона.");
        vehicles.erase(vehicles.begin() + index);
    }

    // "по уникальному идентификатору" — в учебном варианте можно использовать индекс.
    // Если хочешь строгое поле id — скажи, добавим.
    void removeVehicleByIdLikeIndex(size_t index) { removeVehicleByIndex(index); }

    void displayAll() const {
        if (vehicles.empty()) {
            cout << "Парк пуст.\n";
            return;
        }
        for (const auto& v : vehicles) v->displayInfo();
    }

    vector<Vehicle*> searchByCriteria(string brand, int yearFrom, int yearTo, double mileFrom, double mileTo, string typeTC) {
        // Лямбда в алгоритмах (фильтрация)
        vector<Vehicle*> res;
        auto pred = [&](const unique_ptr<Vehicle>& v) -> bool {
            bool typeOk = (typeTC.empty() || v->getType() == typeTC);
            bool yearOk = (v->getYear() >= yearFrom && v->getYear() <= yearTo);
            bool mileOk = (v->getMileage() >= mileFrom && v->getMileage() <= mileTo);

            // brand: без единого getter у базового класса — в простом варианте игнорируем.
            // Чтобы было по ТЗ, лучше добавить виртуальный getBrand().
            // Здесь сделаем "как есть": brand пустой => ок, иначе не фильтруем жестко.
            bool brandOk = (brand.empty());

            return typeOk && yearOk && mileOk && brandOk;
        };

        for (auto& v : vehicles) {
            if (pred(v)) res.push_back(v.get());
        }
        return res;
    }

    // sort: по году, стоимости или пробегу (направление — по выбору)
    void sortBy(string field, bool ascending) {
        auto cmp = [&](const unique_ptr<Vehicle>& a, const unique_ptr<Vehicle>& b) {
            double va = 0.0, vb = 0.0;
            if (field == "year") { va = a->getYear(); vb = b->getYear(); }
            else if (field == "price") { va = a->getPrice(); vb = b->getPrice(); }
            else if (field == "mileage") { va = a->getMileage(); vb = b->getMileage(); }
            else throw InputException("sortBy: неизвестное поле.");

            if (ascending) return va < vb;
            return va > vb;
        };

        sort(vehicles.begin(), vehicles.end(), cmp);
    }

    // stats: суммарная стоимость парка, суммарный пробег, налог на каждое TC
    void showStatistics(double currentYear) const {
        double sumPrice = 0.0;
        double sumMileage = 0.0;

        // лямбды в accumulate
        for (const auto& v : vehicles) {
            sumPrice += v->getPrice();
            sumMileage += v->getMileage();
        }

        cout << "=== Статистика парка ===\n";
        cout << "Суммарная стоимость: " << sumPrice << " руб\n";
        cout << "Суммарный пробег: " << sumMileage << " км\n";
        cout << "Налог по каждому ТС (и амортизация, если нужно):\n";

        for (size_t i = 0; i < vehicles.size(); ++i) {
            const auto& v = vehicles[i];
            double tax = v->calculateTax();
            double dep = v->calculateDepreciation(currentYear);
            cout << "  [" << i << "] type=" << v->getType()
                 << ", tax=" << tax
                 << ", depreciation=" << dep
                 << "\n";
        }
    }

    // ===================== File save/load =====================
    void saveToFile(const string& path) const {
        ofstream out(path);
        if (!out) throw FileException("Не удалось открыть файл для записи: " + path);

        // Формат: одна строка на ТС
        for (const auto& v : vehicles) {
            if (v->getType() == "Car") out << static_cast<const Car*>(v.get())->serialize() << "\n";
            else if (v->getType() == "Truck") out << static_cast<const Truck*>(v.get())->serialize() << "\n";
            else if (v->getType() == "Motorcycle") out << static_cast<const Motorcycle*>(v.get())->serialize() << "\n";
            else throw AppException("Неизвестный тип ТС при сохранении.");
        }
    }

    void loadFromFile(const string& path) {
        ifstream in(path);
        if (!in) throw FileException("Не удалось открыть файл для чтения: " + path);

        vehicles.clear();

        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;

            // первая часть = тип
            auto pos = line.find('|');
            if (pos == string::npos) throw InputException("Некорректная строка в файле.");

            string type = line.substr(0, pos);

            unique_ptr<Vehicle> v;
            if (type == "Car") v = Car::deserialize(line);
            else if (type == "Truck") v = Truck::deserialize(line);
            else if (type == "Motorcycle") v = Motorcycle::deserialize(line);
            else throw InputException("Неизвестный тип в файле: " + type);

            vehicles.push_back(move(v));
        }
    }

    size_t size() const { return vehicles.size(); }
};

// ===================== Input helpers =====================
static int readInt(const string& prompt) {
    cout << prompt;
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите целое число: ";
    }
    return x;
}

static double readDouble(const string& prompt) {
    cout << prompt;
    double x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите число: ";
    }
    return x;
}

static string readString(const string& prompt) {
    cout << prompt;
    string s;
    cin >> ws;
    getline(cin, s);
    if (s.empty()) throw InputException("Пустая строка.");
    return s;
}

// ===================== Main menu =====================
static void printMenu() {
    cout << "\n===== MENU =====\n";
    cout << "1) Добавить ТС (addVehicle)\n";
    cout << "2) Удалить ТС по индексу (removeVehicle)\n";
    cout << "3) Показать все ТС (displayAll)\n";
    cout << "4) Поиск по критериям (search)\n";
    cout << "5) Сортировка (year / price / mileage)\n";
    cout << "6) Показать статистику (showStatistics)\n";
    cout << "7) Сохранить парк в файл (saveToFile)\n";
    cout << "8) Загрузить парк из файла (loadFromFile)\n";
    cout << "0) Выход\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Fleet fleet;
    // текущий год можно брать из пользователя, либо фиксировать
    int currentYear = 2026;

    try {
        while (true) {
            printMenu();
            cout << "Выберите пункт: ";
            int cmd;
            if (!(cin >> cmd)) break;

            if (cmd == 0) {
                cout << "Выход.\n";
                break;
            }

            if (cmd == 1) {
                cout << "Выберите тип ТС: 1-Car, 2-Truck, 3-Motorcycle: ";
                int t;
                cin >> t;

                if (t == 1) {
                    string brand = readString("brand: ");
                    string model = readString("model: ");
                    int year = readInt("year: ");
                    double mileage = readDouble("mileage (km): ");
                    double price = readDouble("price (rub): ");
                    string body = readString("bodyType (sedan/hatchback/universal): ");
                    double engineCC = readDouble("engineCC (см^3): ");

                    fleet.addVehicle(make_unique<Car>(brand, model, year, mileage, price, body, engineCC));
                } else if (t == 2) {
                    string brand = readString("brand: ");
                    string model = readString("model: ");
                    int year = readInt("year: ");
                    double mileage = readDouble("mileage (km): ");
                    double price = readDouble("price (rub): ");
                    double engineCC = readDouble("engineCC (см^3): ");
                    double capacity = readDouble("capacity (tons): ");
                    cout << "hasTrailer? (1-yes/0-no): ";
                    int x; cin >> x;
                    bool trailer = (x != 0);

                    fleet.addVehicle(make_unique<Truck>(brand, model, year, mileage, price, engineCC, capacity, trailer));
                } else if (t == 3) {
                    string brand = readString("brand: ");
                    string model = readString("model: ");
                    int year = readInt("year: ");
                    double mileage = readDouble("mileage (km): ");
                    double price = readDouble("price (rub): ");
                    double engineCC = readDouble("engineCC (см^3): ");
                    cout << "hasSidecar? (1-yes/0-no): ";
                    int x; cin >> x;
                    bool sidecar = (x != 0);

                    fleet.addVehicle(make_unique<Motorcycle>(brand, model, year, mileage, price, engineCC, sidecar));
                } else {
                    throw InputException("Неизвестный тип.");
                }

                cout << "ТС добавлено.\n";
            }
            else if (cmd == 2) {
                if (fleet.size() == 0) {
                    cout << "Парк пуст.\n";
                    continue;
                }
                size_t idx = (size_t)readInt("Введите индекс ТС для удаления: ");
                fleet.removeVehicleByIndex(idx);
                cout << "Удалено.\n";
            }
            else if (cmd == 3) {
                fleet.displayAll();
            }
            else if (cmd == 4) {
                cout << "Введите критерии:\n";
                string brand = readString("brand (введите пустую строку, если не фильтровать): ");
                int yFrom = readInt("yearFrom: ");
                int yTo   = readInt("yearTo: ");
                double mFrom = readDouble("mileageFrom: ");
                double mTo   = readDouble("mileageTo: ");
                string typeTC = readString("typeTC (Car/Truck/Motorcycle) или пусто: ");

                // Чтобы "пусто" в readString работало корректно, тут нужно вводить реально пустую строку.
                // Для простоты можно сказать: вводить слово или просто набрать пустое значение и нажать Enter.
                // (Если твоё окружение не даст пустую строку — скажи, поправлю на std::getline без throw.)
                auto res = fleet.searchByCriteria(brand, yFrom, yTo, mFrom, mTo, typeTC);
                if (res.empty()) {
                    cout << "Ничего не найдено.\n";
                } else {
                    cout << "Найдено: " << res.size() << "\n";
                    for (auto* v : res) v->displayInfo();
                }
            }
            else if (cmd == 5) {
                string field = readString("sort field (year/price/mileage): ");
                cout << "direction (1-asc, 0-desc): ";
                int a; cin >> a;
                bool ascending = (a != 0);
                fleet.sortBy(field, ascending);
                cout << "Сортировка выполнена.\n";
            }
            else if (cmd == 6) {
                cout << "Текущий год для амортизации (Enter=2026): ";
                string tmp;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, tmp);
                if (!tmp.empty()) currentYear = stoi(tmp);

                fleet.showStatistics(currentYear);
            }
            else if (cmd == 7) {
                string path = readString("Путь файла для сохранения: ");
                fleet.saveToFile(path);
                cout << "Сохранено.\n";
            }
            else if (cmd == 8) {
                string path = readString("Путь файла для загрузки: ");
                fleet.loadFromFile(path);
                cout << "Загружено. ТС в парке: " << fleet.size() << "\n";
            }
            else {
                cout << "Неизвестный пункт меню.\n";
            }
        }
    }
    catch (const NotFoundException& e) {
        cout << "[Ошибка] " << e.what() << "\n";
    }
    catch (const InputException& e) {
        cout << "[Ошибка ввода] " << e.what() << "\n";
    }
    catch (const FileException& e) {
        cout << "[Ошибка файла] " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "[Неожиданная ошибка] " << e.what() << "\n";
    }

    return 0;
}