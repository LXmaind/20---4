#include <iostream>
#include <fstream>
#include <ctime>

int main()
{
    std::srand(std::time(nullptr));
    int money[1000] = { 0 };
    int banknotes[] = { 100, 200, 500, 1000, 2000, 5000 };
    char simb;
    int deductibleAmount;
    std::ifstream bankR("bank.bin", std::ios::binary);

    if (bankR.is_open()) {
        int i = 0;
        while (bankR >> money[i]) {
            i++;
        }
        bankR.close();
    }

    do {

        int numBanknotes[6] = { 0 };
        int numberBills = 0;
        int sum = 0;
        int banknotesWithdrawal[6] = { 0 };

        std::ofstream bankW("bank.bin", std::ios::binary | std::ios::trunc);

        for (int i = 0; i < 1000; i++) {

            for (int k = 0; k < 6; k++) {

                if (banknotes[k] == money[i]) {

                    bankW << money[i] << std::endl;
                    numBanknotes[k]++;
                    numberBills++;

                }

            }

        }

        bankW.close();

        for (int i = 0; i < 6; i++) {

            std::cout << "There are " << numBanknotes[i] << " banknotes in denominations of " << banknotes[i] << std::endl;

            sum += numBanknotes[i] * banknotes[i];

        }

        std::cout << "All money: " << sum << std::endl;

        std::cout << "To withdraw the amount of money, enter  - \nTo replenish the ATM with banknotes, enter  + \nTo stop working, enter any other symbol" << std::endl;
        std::cin >> simb;

        if (simb == '+') {

            for (int i = 0; i < 1000; i++) {

                if (money[i] == 0) {

                    money[i] = banknotes[(rand() % 6)];

                }

            }

        }
        else if (simb == '-') {

            std::cout << "Pls enter deductible amount: ";
            std::cin >> deductibleAmount;

            if (deductibleAmount % 100 != 0) {

                std::cout << "Pls enter CORRECT deductible amount: ";
                std::cin >> deductibleAmount;

            }

            for (int i = 5; i >= 0; i--) {

                banknotesWithdrawal[i] = deductibleAmount / banknotes[i];

                if (banknotesWithdrawal[i] > numBanknotes[i]) {

                    banknotesWithdrawal[i] = numBanknotes[i];

                }

                deductibleAmount -= banknotesWithdrawal[i] * banknotes[i];

            }

            if (deductibleAmount == 0) {

                for (int i = 0; i < 6; i++) {

                    for (int k = 0; k < 1000; k++) {

                        if (banknotesWithdrawal[i] == 0) {

                            break;

                        }

                        if (money[k] == banknotes[i] && banknotesWithdrawal[i] > 0) {

                            money[k] = 0;
                            banknotesWithdrawal[i]--;

                        }

                    }

                }

                std::cout << "The money has been given out!" << std::endl;

            }
            else {

                std::cout << "The money cannot be given out!" << std::endl;

            }

        }

    } while (simb == '+' || simb == '-');

}

