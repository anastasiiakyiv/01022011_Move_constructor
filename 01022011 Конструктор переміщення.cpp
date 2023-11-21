#include <iostream>
#include <vector>
#include <utility>

class Ion {
private:
    char charge;
    int valence;

public:
    Ion(char charge, int valence) : charge(charge), valence(valence) {}

    ~Ion() {}

    Ion(Ion&& other) noexcept : charge(std::move(other.charge)), valence(std::move(other.valence)) {}

    Ion& operator=(Ion&& other) noexcept {
        if (this != &other) {
            charge = std::move(other.charge);
            valence = std::move(other.valence);
        }
        return *this;
    }

    void print() const {
        std::cout << "Ion: charge " << charge << ", valence " << valence << std::endl;
    }

    bool reaction(const Ion& other) const {
        return (charge != other.charge) && (valence == other.valence);
    }
};

int main() {
    std::vector<Ion> ions;
    ions.emplace_back('+', 1);
    ions.emplace_back('-', 1);
    ions.emplace_back('+', 2);
    ions.emplace_back('-', 2);
    ions.emplace_back('-', 3);
    ions.emplace_back('+', 4);
    ions.emplace_back('+', 4);

    std::vector<Ion> reactingIons;
    std::vector<Ion> nonReactingIons;

    for (size_t i = 0; i < ions.size(); ++i) {
        bool reacts = false;
        for (size_t j = i + 1; j < ions.size(); ++j) {
            if (ions[i].reaction(ions[j])) {
                reactingIons.push_back(std::move(ions[i]));
                reactingIons.push_back(std::move(ions[j]));
                reacts = true;
                ions.erase(ions.begin() + j);
                break;
            }
        }
        if (!reacts) {
            nonReactingIons.push_back(std::move(ions[i]));
        }
    }

    std::cout << "Ions that have reacted: " << std::endl;
    for (const auto& ion : reactingIons) {
        ion.print();
    }

    std::cout << std::endl;
    std::cout << "Ions that haven't reacted: " << std::endl;
    for (const auto& ion : nonReactingIons) {
        ion.print();
    }

    return 0;
}