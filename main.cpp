#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <vector>

using namespace std;

struct Customer {
    string name;
    string item;
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
                cout << "(" << cur->data.name << " - " << cur->data.item << ") ";
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

const string BRACELET_STYLES[] = {
    "Rainbow Friendship Bracelet",
    "Beaded Name Bracelet",
    "Charm Bracelet",
    "Braided String Bracelet",
    "Glow-in-the-dark Bracelet",
    "Heart Charm Bracelet",
    "Star Bead Bracelet"
};

const int NAME_COUNT = sizeof(NAMES) / sizeof(NAMES[0]);
const int COFFEE_COUNT = sizeof(COFFEE_DRINKS) / sizeof(COFFEE_DRINKS[0]);
const int MUFFIN_COUNT = sizeof(MUFFIN_FLAVORS) / sizeof(MUFFIN_FLAVORS[0]);
const int BRACELET_COUNT    = sizeof(BRACELET_STYLES) / sizeof(BRACELET_STYLES[0]);

int randomIndex (int maxExclusive){
    return rand() % maxExclusive;
}

Customer randomCoffeeCustomer() {
    Customer c;
    c.name = NAMES[randomIndex(NAME_COUNT)];
    c.item = COFFEE_DRINKS[randomIndex(COFFEE_COUNT)];
    return c;
}

Customer randomMuffinCustomer() {
    Customer c;
    c.name = NAMES[randomIndex(NAME_COUNT)];
    c.item = MUFFIN_FLAVORS[randomIndex(MUFFIN_COUNT)];
    return c;
}

Customer randomBraceletCustomer() {
    Customer c;
    c.name = NAMES[randomIndex(NAME_COUNT)];
    c.item = BRACELET_STYLES[randomIndex(BRACELET_COUNT)];
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
        cout << "(" << c.name << " - " << c.item << ") ";
    }
}

void printVector (const vector<Customer>& v){
    if (v.empty()){
        cout << "[empty]";
        return;
    }
    for (const auto& c : v){
        cout << "(" << c.name << " - " << c.item << ") ";
    }
}

void processCoffeeRound(CoffeeQueue &queue, int roundNumber){
    cout << "===== Coffee booth (Round " << roundNumber << ") =====\n";

    bool wasEmptyAtStart = queue.isEmpty();

    if (coinFlip()) {
        Customer newcomer = randomCoffeeCustomer();
        queue.enqueue(newcomer);
        cout << " New customer joined: " << newcomer.name << " ordered " << newcomer.item << "\n";
    }
    else {
        cout << " No new customer joined this round.\n ";
    }

    if (!wasEmptyAtStart) {
        Customer served;
        bool ok = queue.dequeue(served);
        if (ok){
            cout << " Served: " << served.name << " (" << served.item << ")\n";
        }
    }
    else{
        cout << " Queue was empty at start of round, so no one was served.\n";
    }

    cout << " Coffee queue now: ";
    queue.printQueue();
    cout << "\n\n";
}

void processMuffinRound(deque<Customer> &queue, int roundNumber){
    cout << "===== Muffin booth (Round " << roundNumber << ") =====\n";

    bool wasEmptyAtStart = queue.empty();

    if (coinFlip()) {
        Customer newcomer = randomMuffinCustomer();
        queue.push_back(newcomer);
        cout << " New customer joined: " << newcomer.name << " wants " << newcomer.item << "\n";
    }
    else {
        cout << " No new customer joined this round.\n ";
    }

    if (!wasEmptyAtStart) {
        if (!queue.empty()){
            Customer served = queue.front();
            queue.pop_front();
            cout << " served: " << served.name << " (" << served.item << ")\n";
        }
    }
    else{
        cout << " Queue was empty at start of round, so no one was served.\n";
    }

    cout << " Muffin queue now: ";
    printDeque(queue);
    cout << "\n\n";
}

void processBraceletRound(vector<Customer> &queue, int roundNumber){
    cout << "===== Bracelet booth (Round " << roundNumber << ") =====\n";

    bool wasEmptyAtStart = queue.empty();

    if (coinFlip()) {
        Customer newcomer = randomBraceletCustomer();
        queue.push_back(newcomer);
        cout << " New customer joined: " << newcomer.name << " wants " << newcomer.item << "\n";
    }
    else {
        cout << " No new customer joined this round.\n ";
    }

    if (!wasEmptyAtStart) {
        if (!queue.empty()){
            Customer served = queue.front();
            queue.erase(queue.begin());
            cout << " served: " << served.name << " (" << served.item << ")\n";
        }
    }
    else{
        cout << " Queue was empty at start of round, so no one was served.\n";
    }

    cout << " Muffin queue now: ";
    printVector(queue);
    cout << "\n\n";
}


int main (){
    srand(static_cast<unsigned int>(time(nullptr)));

    CoffeeQueue coffeeQ;
    deque<Customer> muffinQ;

    const int INITIAL_CUSTOMERS = 3;
    const int ROUNDS = 10;

    cout << "=== Coffee Booth Queue Simulation (Milestone 3) ===\n\n";

    cout << "Initializing COFFEE queue with " << INITIAL_CUSTOMERS << " customers...\n";

    for (int i = 0; i < INITIAL_CUSTOMERS; i++){
        Customer c = randomCoffeeCustomer();
        coffeeQ.enqueue(c);
        cout << " Coffee: " << c.name << " ordered " << c.item << "\n";
    }

    cout << "Initializing MUFFIN queue with " << INITIAL_CUSTOMERS << " customers...\n";

    for (int i = 0; i < INITIAL_CUSTOMERS; i++){
        Customer c = randomMuffinCustomer();
        muffinQ.push_back(c);
        cout << " Muffin: " << c.name << " wants " << c.item << "\n";
    }

    cout << "\nInitial coffee queue: ";
    coffeeQ.printQueue();
    cout << "\nInitial muffin queue: ";
    printDeque(muffinQ);
    cout << "\n\n";

    for (int round = 1; round <= ROUNDS; round++){
        cout << "=============================\n";
        cout << "        ROUND " << round << "\n";
        cout << "=============================\n";

        processCoffeeRound(coffeeQ, round);
        processMuffinRound(muffinQ, round);
    }

    cout << "=== End of Milestone 3 ===\n";

    return 0;
}
