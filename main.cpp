#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Customer {
    string name;
    string drink;
};

class CoffeeQueue{
    private:
        struct Node{
            Customer data;
            Node* next;
            Node(const Customer& c) : data(c), next(nullptr){}
        };

        Node* head;
        Node* tail;

    public:
        CoffeeQueue() : head(nullptr), tail(nullptr) {}

        ~CoffeeQueue() {
            while (head != nullptr){
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
        }

        bool isEmpty() const{
            return head == nullptr;
        }

        void enqueue(const Customer& c) {
            Node* n = new Node(c);
            if (tail == nullptr){
                head = tail = n;
            } 
            else{
                tail->next = n;
                tail = n;
            }
        }

        bool dequeue(Customer& out){
            if (isEmpty()) return false;

            Node* n = head;
            out = n->data;

            head = head->next;
            if(head == nullptr){
                tail = nullptr;
            }

            delete n;
            return true;
        }

        void printQueue() const{
            if (isEmpty()){
                cout << "[empty]";
                return;
            }

            Node* cur = head;
            while (cur != nullptr){
                cout << "(" << cur->data.name << " - " << cur->data.drink << ") ";
                cur = cur->next;
            }
        }
};

const string NAMES[] = {
    "Alex", "Jordan", "Taylor", "Riley", "Sam",
    "Casey", "Morgan", "Jamie", "Drew", "Quinn"
};

const string DRINKS[] = {
    "Latte",
    "Cappuccino",
    "Espresso",
    "Americano",
    "Mocha",
    "Caramel Macchiato",
    "Vanilla Cold Brew",
    "Iced Mocha",
    "Chai Latte",
    "Matcha Latte"
};

const int NAME_COUNT = sizeof(NAMES) / sizeof(NAMES[0]);
const int DRINK_COUNT = sizeof(DRINKS) / sizeof(DRINKS[0]);

int randomIndex (int maxExclusive){
    return rand() % maxExclusive;
}

Customer randomCustomer() {
    Customer c;
    c.name = NAMES[randomIndex(NAME_COUNT)];
    c.drink = DRINKS[randomIndex(DRINK_COUNT)];
    return c;
}


int main (){


    return 0;
}
