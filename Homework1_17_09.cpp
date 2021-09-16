#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <math.h>

// Electromagnetic interaction
// You have to create world and be able to add and delete particles from it
// When you add or delete particle you must recalculate all interactions

// Требуется описать мир с некоторыми частицами
// Координата/скорость задается через структуру vector3

struct vector3 {
    double x;
    double y;
    double z;
    bool comp(const vector3& p) {
        bool s = false;
        if ((x==p.x)&&(y==p.y)&&(z==p.z)) s = true;
        return s;
    }
};

// Для описания событий происходящих в мире напишите свой небольшой логгер, который умеет
// Запоминать создание, изменение и уничтожение частиц

int sign(double& a) {
    int s = 0;
    if (a > 0) s = 1;
    if (a < 0) s = -1;
    return s;
};

class Logger {
public:
    Logger() = default;
    void log(const std::string& s) {
        l.push_back(s);
        lsize++;
    };
    int GetSize() {return lsize;};
    std::string GetStr(int i) {return l[i];};
private:
    std::vector<std::string> l;
    int lsize = 0;
};

// Существует базовый класс частиц, который внутри себя хранит информацию о частице
// Допишите этот родительский класс так, чтобы он мог считать количество объектов, созданных от него

class Particle {
protected:
    // Поля, описывающие частицу
    // Можно дописать свои
    static int counter;
    double mass = 0;
    double charge = 0;
    vector3 coordinate = {0, 0, 0};
    vector3 velocity = {0, 0,0};
    vector3 force = {0, 0, 0};
    std::string name = "Default particle";
    // Логгер для записи событий
    static Logger logger;

public:
    Particle() {
        counter++;
    };

    Particle(double mass, double charge, vector3 coordinate, vector3 velocity, vector3 force, std::string name): mass(mass), charge(charge), coordinate(coordinate), velocity(velocity), force(force),  name(name) {
        counter++;
        logger.log("Creation of " + name + "\n");
    };

    Particle(const Particle& p) {
        this->mass = p.mass;
        this->charge = p.charge;
        this->coordinate = p.coordinate;
        this->velocity = p.velocity;
        this->force = p.force;
        this->name = p.name;
    }

    explicit Particle(double energy);
    // метод, который вам необходимо переопределить в дочерних классах
    // см. или вспомнить лекцию
    // внутри него напишите логику взаимодействия двух частиц (например, кулоновское)

    virtual void interaction(Particle& p) {
        vector3 rr = {(-coordinate.x + p.coordinate.x), (-coordinate.y + p.coordinate.y), (-coordinate.z + p.coordinate.z)};
        double r = sqrt((coordinate.x - p.coordinate.x)*(coordinate.x - p.coordinate.x) + (coordinate.y - p.coordinate.y)*(coordinate.y - p.coordinate.y) + (coordinate.z - p.coordinate.z)*(coordinate.z - p.coordinate.z));
        double mod_force = charge * p.charge/(r*r*r);
        force.x += sign(charge) * rr.x * mod_force;
        force.y += sign(charge) * rr.x * mod_force;
        force.z += sign(charge) * rr.x * mod_force;
        force.x -= sign(charge) * rr.x * mod_force;
        force.y -= sign(charge) * rr.x * mod_force;
        force.z -= sign(charge) * rr.x * mod_force;
    };

    std::string getName() const {return name;};
    int getCharge() const {return charge;};
    int getMass() const {return mass;};
    vector3 getCoord() const {return coordinate;};
    vector3 getVelo() const {return velocity;};
    vector3 getForce() const {return force;};

    int getEnergy() const {return mass*(velocity.x*velocity.x + velocity.y*velocity.y + velocity.z*velocity.z)/2;};

    void Setcharge() {
        charge*= (-1);
    };

    bool comp (Particle& p) {
        bool s = false;
        if ((mass == p.mass)&&(charge == p.charge)&&(velocity.comp(p.velocity))&&(coordinate.comp(p.coordinate))&&(force.comp(p.force))&&(name==p.name)) s = true;
        return s;
    }

    int GetCounter() {return counter;}
    Logger GetLogger() {return logger;}

};

int Particle :: counter = 0;
Logger Particle :: logger;

// описать несколько классов разных частиц
// например такой
class Electron : public Particle {
public:
    // в этом конструкторе предлагается задавать координаты и через энергию остальные параметры частицы
    Electron(){
    name = "Electron";
    mass = 9,1 * pow (10, -31);
    charge = -1,6 * pow(10, -19);
    logger.log("Creation of " + name + "\n");
    };

    Electron(vector3 coordinate, vector3 velocity, vector3 force){
    Electron();
    this->coordinate = coordinate;
    this->velocity = velocity;
    this->force = force;
    };

    explicit Electron(double energy, vector3 coords) {
    Electron();
    coordinate.x = coords.x;
    coordinate.y = coords.y;
    coordinate.z = coords.z;
    velocity.x = velocity.y = velocity.z = sqrt(energy * 2 / mass);
    };
};

class Proton : public Particle {
public:
    // в этом конструкторе предлагается задавать координаты и через энергию остальные параметры частицы
    Proton() {
    name = "Proton";
    mass = 1,3 * pow (10, -27);
    charge = 1,6 * pow(10, -19);
    };

    Proton(vector3 coordinate, vector3 velocity, vector3 force){
    Proton();
    this->coordinate = coordinate;
    this->velocity = velocity;
    this->force = force;
    };

    explicit Proton(double energy, vector3 coords) {
    Proton();
    coordinate.x = coords.x;
    coordinate.y = coords.y;
    coordinate.z = coords.z;
    velocity.x = velocity.y = velocity.z = sqrt(energy * 2 / mass);
    };
};

class Neutron : public Particle {
public:
    // в этом конструкторе предлагается задавать координаты и через энергию остальные параметры частицы
    Neutron() {
    name = "Neutron";
    mass = 1,7 * pow (10, -27);
    charge = 0;
    logger.log("Creation of " + name + "\n");
    counter++;};

    explicit Neutron(double energy, vector3 coords) {
    Neutron();
    coordinate.x = coords.x;
    coordinate.y = coords.y;
    coordinate.z = coords.z;
    velocity.x = velocity.y = velocity.z = sqrt(energy * 2 / mass);
    };
};

// в этом классе опишите мир, состоящий из некоторого числа частиц
class World {
    int vsize = 0;
    std::vector<Particle> v;
    static Logger logger;
public:
    Particle& getv(int i) {return v[i];};
    // добавить частицу в мир (она должна провзаимодействовать со всеми остальными)
    void addParticle(Particle& p) {
        for (int i = 0; i < v.size(); i++)
            p.interaction(v[i]);
        v.push_back(p);
        vsize++;}

    void printw() {
        for (int i = 0; i < v.size(); i++)
            std::cout << v[i].getName() << " ";
    };
    // удалить частицу из мира
    void deleteParticle(const Particle& p) {
        Particle q = p;
        Particle j;
        q.Setcharge();
        bool b = true;
        std::vector<Particle> :: iterator it = v.begin();
        while (b) {
            if (((*it).getMass() == p.getMass())&&((*it).getCharge() == p.getCharge())&&((*it).getCoord().comp(p.getCoord()))&&((*it).getVelo().comp(p.getVelo()))&&((*it).getForce().comp(p.getForce()))&&((*it).getName() == p.getName())) b = false;
            else it++;
        }
        (*it).GetLogger().log("Deleting of " + (*it).getName());
        v.erase(it);
        for (int i = 0; i < v.size(); i++)
            q.interaction(v[i]);
        vsize--;
    };

    int getSize() {return vsize;};
};

// перегрузите оператор вывода, чтобы можно было вывести состав мира
// (может потребоваться перегрузка оператора вывода для частиц)
std::ostream& operator<<(std::ostream& os, vector3 p) {
        os << "{" << p.x << "," << p.y << "," << p.z <<"}";
        return os;
};

std::ostream& operator<<(std::ostream& os, Particle& p) {
        os << p.getName() << " " << p.getCharge() << " " << p.getMass() << " " << p.getCoord() << " " << p.getVelo() << " " << p.getForce() << "\n";
        return os;
};

std::ostream& operator<<(std::ostream& os, World& w) {
        for (int i = 0; i < w.getSize(); i++) {
            os << w.getv(i); }
        if (w.getSize() == 0) os << "World is empty!";
        return os;
};

// здесь создайте мир/миры, куда добавьте некоторое число частиц, взаимодействующих друг с другом
int main() {
    World first;
    Particle Heh(2 * pow (10, -27), 0, {1,0,1}, {0, 1, 1}, {0, 4, 5}, {"Heh"});
    Electron e, b;
    first.addParticle(e);
    first.addParticle(Heh);
    std::cout << first.getSize() << "\n";
    std::cout << first;
    std::cout << e.GetCounter();
    for (int i = 0; i < e.GetLogger().GetSize(); i++) std::cout << e.GetLogger().GetStr(i);
    first.deleteParticle(e);
    std::cout << first;
    first.deleteParticle(Heh);
    std::cout << first;
    return 0;}
