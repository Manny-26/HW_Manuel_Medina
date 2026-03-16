#include <iostream>
#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <string>

class MotorStatus {
private:
    uint8_t motorState; // Each bit represents the status of a motor (on/off)
    uint8_t overheatingMotors = 0; // Motors that are overheating
    int turnCount;
    // Function to randomly initialize motors (on/off) and overheat one motor
    void initialize() {
        std::srand(time(0));

        do {
            motorState = static_cast<uint8_t>(std::rand() % 256);
        }
        while (motorState == 0); // Ensure at least one motor is ON

        turnCount = 0;
        updateOverheating();
        displayStatus();
    }
    // Incrementally overheat motors with each turn, ensuring the motor is ON and not already overheating
    void updateOverheating() {
        if ( (motorState & static_cast<uint8_t>(~overheatingMotors)) == 0 ) {
            // All ON motors are already overheating (or no motors ON).
            // No change to overheatingMotors.
            turnCount++; // Still counts as a "turn event"
            return;
        }
        else{
            int newMotor = 0;
            do {
                newMotor = std::rand() % 8; //Pick a random number 1-8
            } while ( ((static_cast<uint8_t>(1u << newMotor) & motorState) == 0) ||   // Check if on
                    ((static_cast<uint8_t>(1u << newMotor) & overheatingMotors) != 0) ); // Check if not already overheating

            overheatingMotors |= static_cast<uint8_t>(1u << newMotor);
            turnCount++;
        }
    }


    void displayStatus() {
        std::cout << "Motor State (ON/OFF): " << std::bitset<8>(motorState) <<std::endl;
        std::cout << "Overheating Motors: " << std::bitset<8>(overheatingMotors)<< std::endl;
        std::cout << "Turn Count: " << turnCount << std::endl;
    }

    public:
        MotorStatus() {
            initialize();
        }


    // =====================================
    // =====YOU MAY EDIT THIS FUNCTION======
    // =====================================
    bool turnOff(uint8_t guess) {
        // 1) Turn OFF only motors that are BOTH overheating AND guessed.
        // 2) If guess tries to turn off a motor that is NOT overheating leave state unchanged.
        // 3) Correct guess means guess matches overheatingMotors EXACTLY (same 1-bits).
        // 4) If incorrect guess: call updateOverheating() to add one more overheating motor.
        // 5) Return true ONLY if correct guess.
        if ((overheatingMotors & guess) == 0) {
            updateOverheating();
            displayStatus();
            return false;
        }
        motorState ^= (overheatingMotors & guess);
        displayStatus();
        return overheatingMotors == guess;
    }
};


int  checkInput(const std::string& s) {
    int value = 0;
    bool ok = true;
    // Parse binary
    if (s.size() == 8 && s.find_first_not_of("01") == std::string::npos) {
            for (char c : s) {
                value = (value << 1) | (c - '0');
            }
            return value;
        }
        // Parse hex (0x..)
        else if (s.size() >= 3 && (s.rfind("0x", 0) == 0 || s.rfind("0X", 0) == 0)) {
            try {
                value = std::stoul(s, nullptr, 16);
                if (value > 255) {
                    ok = false;
                }
            } catch (...) {
                ok = false;
            }
            if (ok) {
                return value;
            }
        }

        std::cout << "Invalid input. Use 8-bit binary (0b00101000) or hex (0x28).\n\n";
        return -1;
}


int main() {
    MotorStatus motorStatus;
    uint8_t guess = 0;
    std::cout << "Motor Meltdown\n";
    std::cout << "Enter your guess as:\n";
    std::cout << "  - 8-bit binary (e.g., 00101000)\n";
    std::cout << "  - hex (e.g., 0x28)\n";
    std::cout << "Type 'q' to quit.\n\n";
    std::cout << "Your guess: ";
    std::string s;
    std::cin >> s;

    if (!std::cin) return 0;
    if (s == "q" || s == "Q") return 0;

    while(checkInput(s)!=-1) {return 0;}


        
}