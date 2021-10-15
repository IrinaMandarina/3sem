#include<iostream>

template <typename T>
class Grid {
private:
 T *memory;
 size_t x_size, y_size;

public:
 Grid(size_t x_size, size_t y_size): x_size(x_size), y_size(y_size) {
    memory = new T[x_size * y_size];
 };

 T operator()(size_t x_idx, size_t y_idx) const {
    return memory[x_idx * y_size + y_idx];
 };
 T& operator()(size_t x_idx, size_t y_idx) {
    return memory[x_idx * y_size + y_idx];
 };

 size_t get_xsize() const {
    return x_size;
 };
 size_t get_ysize() const {
    return y_size;
 };

Grid& operator=(T x) {
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            memory[i * y_size + j] = x;
        }
    }
    return *this;
};

template<typename P>
friend std::ostream& operator<<(std::ostream& os, Grid<P> const& g);
template<typename P>
friend std::istream& operator>>(std::istream& is, Grid<P> & g);

 ~Grid() {
    delete[] memory;
 };
};

template <typename V>
std::istream& operator>>(std::istream& is, Grid<V>& g) {
    V x;
    for (int i = 0; i < g.x_size; i++) {
            for (int j = 0; j < g.y_size; j++) {
                is >> x;
                g.memory[i * g.y_size + j] = x;
            }
        }
    return is;
 };

template <typename U>
std::ostream& operator<<(std::ostream& os, Grid<U> const& g) {
    for (int i = 0; i < g.get_xsize(); i++) {
            for (int j = 0; j < g.get_ysize(); j++) {
                os << g(i, j) << " ";
            }
            os << "\n";
        }
    if ((g.get_xsize() == 0) && (g.get_ysize() == 0)) os << "Empty";
    return os;
 };

int main() {
    Grid<int> g(5, 5);
    g = 0;
    std::cout << g;
    g(0,0) = 5;
    std::cout << g;
    std::cin >> g;
    std::cout << g;
    std::cout << g.get_xsize() << " " << g.get_ysize() << "\n";
return 0;}
