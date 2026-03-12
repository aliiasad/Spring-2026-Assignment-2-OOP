# include <iostream>
using namespace std;

char* cpy(const char*); // returns a new heap allocated string copy

class Spell {
    private:
        char* spellName;
        int power;
        int manaCost;
        int difficulty;
    public:
        Spell(); // default constructor
        Spell(char* , int, int, int); // parameterized constructor
        Spell(const Spell&);
        ~Spell(); // destructor

        // implementation
        void displaySpell();
        char* getName();
        Spell& operator=(const Spell&);
        Spell operator+(const Spell&);
        bool operator>(const Spell&);
        friend ostream& operator<<(ostream&, const Spell&);
};

Spell :: Spell()    {
    power = 0, manaCost = 0, difficulty = 0;
    spellName = cpy("Unknown");
}

Spell :: Spell(char* spell, int pow, int mana, int diff)    {
    power = pow, manaCost = mana, difficulty = diff;
    spellName = cpy(spell);
}

Spell :: Spell(const Spell& dummy)  {
    power = dummy.power;
    manaCost = dummy.manaCost;
    difficulty = dummy.difficulty;
    spellName = cpy(dummy.spellName);
}

Spell& Spell :: operator=(const Spell& other) {
    if (this == &other) return *this;
    delete[] spellName;
    spellName = cpy(other.spellName);
    power = other.power;
    manaCost = other.manaCost;
    difficulty = other.difficulty;
    return *this;
}

Spell Spell :: operator+(const Spell& dummy)    {

    Spell temp;

    // free constructor allocated memory
    delete[] temp.spellName;

    temp.spellName = cpy("FusionSpell");
    temp.power = this->power + dummy.power;
    temp.manaCost = this->manaCost +  dummy.manaCost;
    temp.difficulty = (this->difficulty + dummy.difficulty) / 2;

    if (temp.power > 100)   {
        delete[] temp.spellName;
        temp.spellName = cpy("UnstableMagic");
    }

    return temp;
}

bool Spell :: operator>(const Spell& dummy) {

    return this->power > dummy.power;
}

ostream& operator<<(ostream& cout, const Spell& dummy)    {

    cout << "Name: " << dummy.spellName << " | Power: " 
    << dummy.power << " | Mana: " << dummy.manaCost 
    << " | Difficulty: " << dummy.difficulty << endl;

    return cout;
}

void Spell::displaySpell() {
    cout << "Spell: " << spellName << endl;
    cout << "Power: " << power << endl;
    cout << "Mana Cost: " << manaCost << endl;
    cout << "Difficulty: " << difficulty << endl;
}

char* Spell::getName() {
    return spellName;
}

Spell :: ~Spell()   {
    delete[] spellName;
}

class SpellBook {
    private:
        Spell* spells;
        int capacity;
        int totalSpells;
        char* ownerName;
    public:
        SpellBook(char*, int);
        ~SpellBook();

        // implementation
        void learnSpell(Spell);
        void displaySpellBook();
};

SpellBook :: SpellBook(char* owner, int cap)    {
    ownerName = cpy(owner);
    capacity = cap;
    totalSpells = 0;
    spells = new Spell [capacity];
}

void SpellBook::learnSpell(Spell s) {
    if (totalSpells >= capacity) {
        cout << "SpellBook is full!" << endl;
    } else {
        *(spells + totalSpells) = s;
        totalSpells++; 
    }
}

void SpellBook::displaySpellBook() {
    // print owner name header
    cout << "---" << ownerName << "\'s SpellBook---" << endl;
    for (int i = 0; i < totalSpells; i++)   {
        cout << i + 1 << ". " << (*(spells + i)).getName() << endl;
    }
    // loop through spells and print number + name
}

SpellBook :: ~SpellBook()   {
    delete[] spells;
    delete[] ownerName;
}

int main()  {

    
    return 0;
}

char* cpy (const char* src)   {
    int len = 0;
    while (src[len] != '\0')  len++;
    char* dest = new char[len + 1];
    for (int i = 0; i <= len; ++i) dest[i] = src[i];
    return dest;
}