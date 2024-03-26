#include <iostream>
#include "menu.h"

using namespace std;

int Menu::Terminal() {

    cout << endl;
    cout << "\033[1;34mWelcome to the Water Supply Management Analysis Tool\033[0m" << endl;
    cout << endl;
    cout << "\033[1;34mWhat do you wish to do?\033[0m" << endl;

    cout << "\033[1;36m[ 1 ]\033[0m" << " Basic Service Metrics" << endl;
    cout << "\033[1;36m[ 2 ]\033[0m" << " Reliability and Sensitivity to Failures" << endl;
    cout << "\033[1;33m[ 9 ] Read and Parse the Input Data\033[0m" << endl;
    cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
    cout << endl;

    int decision;
    string input;

    cout << "\033[1;34mDecision: \033[0m";
    cin >> decision;
    cout << endl << endl;

    while (decision != 0) {

        switch (decision) {
            case 1:

                while (decision != 0 && decision != 9) {

                    cout << "\033[1;36m[ 1 ]\033[0m" << " Maximum amount of water that can reach each or a specific city"
                         << endl;
                    cout << "\033[1;36m[ 2 ]\033[0m"
                         << " Check the water supply given to every delivery site and list those who have a deficit"
                         << endl;
                    cout << "\033[1;36m[ 3 ]\033[0m"
                         << " Balance the load of water across the entire network (Não percebi bem esta, vejam melhor depois)"
                         << endl;
                    cout << "\033[1;33m[ 9 ] Go back\033[0m" << endl;
                    cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
                    cout << endl;

                    cout << "\033[1;34mDecision: \033[0m";
                    cin >> decision;
                    cout << endl << endl;

                    switch (decision) {
                        case 1:

                            cout << "\033[1;34mDo you want to check a specific city? \033[0m"
                                 << "\033[1;33m [ Y | N ]\033[0m" << endl;
                            cin >> input;
                            cout << endl << endl;

                            if (input == "y" || input == "Y") {

                                cout << "\033[1;34mWhich city? \033[0m";
                                cin >> input;
                                cout << endl << endl;


                                decision = 9;

                            } else if (input == "n" || input == "N") {


                                decision = 9;

                            } else {

                                cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            }

                            break;
                        case 2:


                            break;
                        case 3:


                            break;
                        case 9: case 0:

                            break;
                        default:

                            cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            break;
                    }

                }

                break;
            case 2:

                while (decision != 0 && decision != 9) {

                    cout << "\033[1;36m[ 1 ]\033[0m"
                         << " Check the delivery capacity of the network putting one water reservoir out of commission"
                         << endl;
                    cout << "\033[1;36m[ 2 ]\033[0m"
                         << " Check the effects of a temporary removal of each pumping station" << endl;
                    cout << "\033[1;36m[ 3 ]\033[0m"
                         << " Check which pipelines would make it impossible to deliver the desired amount of water, for each city"
                         << endl;
                    cout << "\033[1;33m[ 9 ] Go back\033[0m" << endl;
                    cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
                    cout << endl;

                    cout << "\033[1;34mDecision: \033[0m";
                    cin >> decision;
                    cout << endl << endl;

                    switch (decision) {
                        case 1:

                            cout << "\033[1;34mWhich water reservoir?\033[0m";
                            cin >> input;
                            cout << endl << endl;


                            break;
                        case 2:


                            break;
                        case 3:


                            break;
                        case 0: case 9:

                            break;
                        default:

                            cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            break;
                    }

                }

                break;
            case 3:



                break;
            case 0:

                break;
            default:

                cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;
                decision = 9;

                break;
        }

        if (decision != 0) {

            cout << "\033[1;34mWish to do anything else?\033[0m" << endl;

            cout << "\033[1;36m[ 1 ]\033[0m" << " Basic Service Metrics" << endl;
            cout << "\033[1;36m[ 2 ]\033[0m" << " Reliability and Sensitivity to Failures" << endl;
            cout << "\033[1;33m[ 9 ] Read and Parse the Input Data\033[0m" << endl;
            cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
            cout << endl;

            cout << "\033[1;34mDecision: \033[0m";
            cin >> decision;
            cout << endl << endl;

        }

    }

    return 0;
}