#include <iostream>
#include <bitset>
#include <cctype>
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
            return false;
        }
        motorState ^= (overheatingMotors & guess);
        displayStatus();
        return overheatingMotors == guess;
    }

    bool win(uint8_t guess)
        {
            if (guess == overheatingMotors)
                return true;
            return false;
        }

    friend std::ostream& operator<<(std::ostream& lhs, MotorStatus rhs) {
        return lhs << "Motor State (ON/OFF): " << std::bitset<8>(rhs.motorState) << '\n'
            << "Overheating Motors: " << std::bitset<8>(rhs.overheatingMotors)<< '\n'
            << "Turn Count: " << rhs.turnCount;
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

std::string& cmdLower(std::string& cmd) {
    for (char &c : cmd) {
       c = static_cast<char>(std::tolower(c));
    }
    return cmd;
}

int main() {
    MotorStatus motorStatus;
    uint8_t guess = 0;

    std::cout << "\n========================================\n";
    std::cout << "          MOTOR MELTDOWN\n";
    std::cout << "========================================\n";
    std::cout << "Goal: identify EVERY overheating motor.\n";
    std::cout << "      Wrong or incomplete guesses add more overheating motors!\n\n";
    std::cout << "Commands:\n";
    std::cout << "  Submit <bits/hex>  -- submit your final guess (e.g. submit 00100100)\n";
    std::cout << "  or <bits/hex>      -- OR  your guess with a motor bit\n";
    std::cout << "  and <bits/hex>     -- AND your guess with a mask\n";
    std::cout << "  XOR <bits/hex>     -- XOR your guess with a bit\n";
    std::cout << "  Clear              -- reset your guess to 00000000\n";
    std::cout << "  Status             -- show motor ON/OFF state and turn count\n";
    std::cout << "  Guess              -- show your current guess\n";
    std::cout << "  Help               -- show this command list\n";
    std::cout << "  q                  -- quit\n";
    std::cout << "========================================\n\n";
    std::cout << "Enter Command: ";

    while (motorStatus.win(guess) == false) {
        std::string cmd;
        std::cin >> cmd;
        cmdLower(cmd);

        if (cmd == "q" || cmd == "Q")
            return 0;
        if (cmd == "help") {
            std::cout << "\n========================================\n";
            std::cout << "          MOTOR MELTDOWN\n";
            std::cout << "========================================\n";
            std::cout << "Goal: identify EVERY overheating motor.\n";
            std::cout << "      Wrong or incomplete guesses add more overheating motors!\n\n";
            std::cout << "Commands:\n";
            std::cout << "  Submit <bits/hex>  -- submit your final guess (e.g. submit 00100100)\n";
            std::cout << "  or <bits/hex>      -- OR  your guess with input\n";
            std::cout << "  and <bits/hex>     -- AND your guess with input\n";
            std::cout << "  XOR <bits/hex>     -- XOR your guess with input\n";
            std::cout << "  Clear              -- reset your guess to 00000000\n";
            std::cout << "  Status             -- show motor ON/OFF state and turn count\n";
            std::cout << "  Guess              -- show your current guess\n";
            std::cout << "  Help               -- show this command list\n";
            std::cout << "  q                  -- quit\n";
            std::cout << "========================================\n\n";
            std::cout << "Enter Command: ";
        }
        if (cmd == "guess")
            std::cout << std::bitset<8>(guess) << '\n';

        if (cmd == "status")
            std::cout << motorStatus << '\n';

        if (cmd == "clear")
            guess = 0;

        if (cmd == "or") {
            std::string sMutator;
            std::cout << "Input: ";
            std::cin >> sMutator;
            int mutator = checkInput(sMutator);

            guess |= mutator;
        }
        if (cmd == "and") {
            std::string sMutator;
            std::cout << "Input: ";
            std::cin >> sMutator;
            int mutator = checkInput(sMutator);

            guess &= mutator;
        }
        if (cmd == "xor") {
            std::string sMutator;
            std::cout << "Input: ";
            std::cin >> sMutator;
            int mutator = checkInput(sMutator);

            guess ^= mutator;
        }
        if (cmd == "submit") {
            motorStatus.turnOff(guess);
        }
        std::cout << "Enter command: ";
    }

}