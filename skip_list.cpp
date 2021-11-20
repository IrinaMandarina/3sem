#include <iostream>
#include <random>
#include <iomanip>
#include <vector>

template <typename T>
class SkipNode{
private:
    T value;
    int key;
    std::vector<SkipNode<T>*> forwardNodes;
public:

    SkipNode() {};

    SkipNode(SkipNode<T>& p) {
        value = p.value;
        key = p.key;
        for (auto k: p.forwardNodes) {
            forwardNodes.push_back(k);
        }
    };

    SkipNode(int key, T value, size_t maxLevel): key(key), value(value) {
        forwardNodes.reserve(maxLevel);
        forwardNodes.clear();
    };

    template <typename SkipNode>
    friend class SkipList;
};

template <typename T>
class SkipList{
private:
    SkipNode<T>* head;
    SkipNode<T>* NIL = nullptr;
    double p = 0.5;
    size_t _size = 0;
    size_t maxLevel;
    size_t Level = 0;
public:
    SkipList(size_t _maxLevel): maxLevel(_maxLevel){
        head = new SkipNode<T>;
        head->forwardNodes.push_back(NIL);
    }

    int randomLevel(){
    int lvl = 1;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0, 1);
    while ((distr(eng) < p) && (lvl < maxLevel)) {
    std::uniform_real_distribution<float> distr(0, 1);
        lvl++;
    }
    return lvl;
    };

    T search(int search_key) {
        SkipNode<T>* t = head;
        for (int i = Level; i > 0; --i) {
            while (t->forwardNodes[i] < search_key) {
                t = t->forwardNodes[i];
            }
        }
        t = t->forwardNodes[0];
        if (t->key == search_key) return t->value;
        else return false;
    };

    void insert(int search_key, T new_value) {
        std::vector<SkipNode<T>*> update;
        SkipNode<T>* t = head;
        for (int i = Level; i > 0; i--) {
            while (t->forwardNodes[i] < search_key) {
                t = t->forwardNodes[i];
            }
            update.push_back(t);
        }
        t = t->forwardNodes[0];
        if (t->key == search_key) t->value = new_value;
        else {
            _size++;
            int lvl = randomLevel();
            if (lvl > Level) {
                for (int i = Level + 1; i < lvl; i++) {
                    update[i] = head;
                }
            Level = lvl;
            }
            SkipNode<T> t(search_key, new_value, lvl);
            for (int i = 0; i < Level; i++) {
                t->forwardNodes[i] = update[i]->forwardNodes[i];
                update[i]->forwardNodes[i] = t;
            }
        }
    };

    void _erase(int search_key) {
        std::vector<SkipNode<T>*> update;
        SkipNode<T>* t = head;
        for (int i = Level; i > 0; i--) {
            while (t->forwardNodes[i] < search_key) {
                t = t->forwardNodes[i];
            }
            update[i] = t;
        }
        t = t->forwardNodes[0];
        if (t->key == search_key) {
            for (int i = 0; i < Level; i++) {
                if (update[i]->forwardNodes[i] != t)
                    break;
                update[i]->forwardNodes[i] = t->forwardNodes[i];
            }
            delete t;
            _size--;
        }
        while ((Level > 1) && (head->forwardNodes[Level - 1] == nullptr))
            Level--;
    };

    bool _empty() {
        return (_size == 0);
    };

    size_t get_size() {
        return _size;
    };

    void _clear() {
        SkipNode<T>* t;
        SkipNode<T>* n = head;
        while (n->forwardNodes[0] != nullptr) {
            t = n;
            n = n->forwardNodes[0];
            delete t;
        }
        head->forwardNodes.clear();
        head->forwardNodes.push_back(NIL);
    };

    ~SkipList(){
        _clear();
        delete head;
        delete NIL;
    };
};

int main() {
    SkipList<int> a(5);
return 0;}
