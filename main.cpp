#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <deque>

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

const string COFFEE_DRINKS[] = {
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

const string MUFFIN_FLAVORS[] = {
    "Blueberry Muffin",
    "Chocolate Chip Muffin",
    "Banana Nut Muffin",
    "Bran Muffin",
    "Lemon Poppyseed Muffin",
    "Cinnamon Streusel Muffin",
    "Pumpkin Spice Muffin"
};

const int NAME_COUNT = sizeof(NAMES) / sizeof(NAMES[0]);
const int COFFEE_COUNT = sizeof(COFFEE_DRINKS) / sizeof(COFFEE_DRINKS[0]);
const int MUFFIN_COUNT = sizeof(MUFFIN_FLAVORS) / sizeof(MUFFIN_FLAVORS[0]);

int randomIndex (int maxExclusive){
    return rand() % maxExclusive;
}

Customer randomCoffeeCustomer() {
    Customer c;
    c.name = NAMES[randomIndex(NAME_COUNT)];
    c.drink = COFFEE_DRINKS[randomIndex(COFFEE_COUNT)];
    return c;
}

Customer randomMuffinCustomer() {
    Customer c;
    c.name = NAMES[randomIndex(NAME_COUNT)];
    c.drink = MUFFIN_FLAVORS[randomIndex(MUFFIN_COUNT)];
    return c;
}


bool coinFlip() {
    return rand() % 2 == 0;
}

void printDeque(const deque<Customer>& dq){
    if (dq.empty()){
        cout << "[empty]";
        return;
    }
    for (const auto& c : dq){
        cout << "(" << c.name << " - " << c.drink << ") ";
    }
}

void processCoffeeRound(CoffeeQueue &queue, int roundNumber){
    cout << "===== Coffee booth (Round " << roundNumber << ") =====\n";

    bool wasEmptyAtStart = queue.isEmpty();

    if (coinFlip()) {
        Customer newcomer = randomCoffeeCustomer();
        queue.enqueue(newcomer);
        cout << " New customer joined: " << newcomer.name << " ordered " << newcomer.drink << "\n";
    }
    else {
        cout << " No new customer joined this round.\n ";
    }

    if (!wasEmptyAtStart) {
        Customer served;
        bool ok = queue.dequeue(served);
        if (ok){
            cout << " Served: " << served.name << " (" << served.drink << ")\n";
        }
    }
    else{
        cout << " Queue was empty at start of round, so no one was served.\n";
    }

    cout << " Queue now: ";
    queue.printQueue();
    cout << "\n\n";
}

int main (){
    srand(static_cast<unsigned int>(time(nullptr)));

    CoffeeQueue coffeeQ;

    const int INITIAL_CUSTOMERS = 3;
    const int ROUNDS = 10;

    cout << "=== Coffee Booth Queue Simulation (Milestone 2) ===\n\n";

    cout << "Initializing queue with " << INITIAL_CUSTOMERS << " customers...\n";

    for (int i = 0; i < INITIAL_CUSTOMERS; i++){
        Customer c = randomCustomer();
        coffeeQ.enqueue(c);
        cout << " Joined queue: " << c.name << " ordered " << c.drink << "\n";
    }

    cout << "\nInitial queue: ";
    coffeeQ.printQueue();
    cout << "\n\n";

    for (int round = 1; round <= ROUNDS; round++){
        processRound(coffeeQ, round);
    }

    cout << "=== End of Milestone 2 ===\n";

    return 0;
}
