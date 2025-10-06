#include <iostream>
#include <windows.h> //pour les detections dans le cmd
#include <stdio.h>   //pour utiliser les printf
#include <vector>
#include <queue>
#include <string>
#include <cctype> //pour isdigit 
#include <cstdlib>  // pour std::stoi ca converti les chaines de caracters en numbers

using namespace std;


void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// On récupère un handle (identifiant) vers la console de sortie standard (celle qu'on voit à l'écran).
    CONSOLE_SCREEN_BUFFER_INFO csbi; //Variable qui va contenir les infos sur la taille et l’état actuel du buffer console.
    DWORD written; //savoir combien de caractères on a effacés/écrits,
    DWORD cells; //nombre total de caractères à effacer (largeur × hauteur).

    GetConsoleScreenBufferInfo(hConsole, &csbi); // Remplit csbi avec des infos sur la taille de la console, la position du curseur, etc.
    cells = csbi.dwSize.X * csbi.dwSize.Y; //Calcule le nombre total de "cellules" (caractères affichables) dans la console.

    FillConsoleOutputCharacter(hConsole, ' ', cells, {0, 0}, &written); //Remplit toute la console avec des espaces (' ') à partir du coin haut gauche (0, 0).
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, {0, 0}, &written); //Remet les couleurs d'origine dans toute la console.
    SetConsoleCursorPosition(hConsole, {0, 0}); // Replace le curseur en haut à gauche après avoir effacé.
}


long long evaluateExpression(vector<char>& vect) 
{

    string concat="";
    long long result=0;
    queue<long long>que;

    for(char tmp:vect)
    {
        if(isdigit(tmp))
        {
            concat += string(1,tmp);
        }
        else
        {
            try 
            {
                que.push(stoll(concat));
                concat="";
            }  catch (const std::invalid_argument& e) {
                std::cout << "Pas un nombre valide.\n";
            } catch (const std::out_of_range& e) {
                std::cout << "Nombre trop grand ou trop petit.\n";

            }
            
           //que.push(stoi(concat));
        }
    }
    result=que.front();
    que.pop();
    for (char tmp : vect) 
    { 
        if (!std::isdigit(tmp)) // Si un caractère n'est pas un chiffre
        {
            if (tmp == '+') 
            {
                result += que.front();
            } else if (tmp == '-') 
            {
                result -= que.front();
            } else if (tmp == '*') 
            {
                result *= que.front();
            }
            else if (tmp == '=') 
            {
                vect.clear();
                return result;
            }
            que.pop();
        }
    } 
    return 0;
}  





void presentation(vector<char>& vect)
{
    std::string expression{"   ##"};
    expression+=std::string(30,' ');
    std::string result_chaine{"   ##"};
    result_chaine+=std::string(30,' ');
    long long result{0};
    int a{0};

    if(!vect.empty())
    { 
        for(char tmp:vect)
        {
            a++;
            if(tmp!='=')
                expression+=string(1, tmp);
        }
        result=evaluateExpression(vect);
        result_chaine+=std::to_string(result); //convertir result en chaine de caractere 
    }
    while(expression.length()<66)
    {
        expression+=string(1,' ');
    }

    while(result_chaine.length()<66)
    {
        result_chaine+=string(1,' ');
    }
    expression+=string(2,' '); //reproduire 2 fois le caractere #
    expression+=string(2,'#');

    result_chaine+=string(2,' '); //reproduire 2 fois le caractere #
    result_chaine+=string(2,'#');
    clearConsole(); //efface l'ecran

    printf(" \n\n\n\n\n");

    printf
    (
       "   ###################################################################\n"
       "%s\n"
       "   ##                                                               ##\n"
       "   ##                                                               ##\n"
       "%s\n"
       "   ###################################################################\n",expression.c_str(),result_chaine.c_str() //s_str passe un pointeur car printf est une fonction du c et n'attend pas de classe 
    );

    printf(" \n\n\n");

    printf
    (
     "             ##########   ##########  ##########  ##########  \n"
     "             #   1    #   #    2   #  #   3    #  #    4   #  \n"
     "             #        #   #        #  #        #  #        #  \n"
     "             ##########   ##########  ##########  ##########  \n"
    );    
    
    printf(" \n    \n\n");
        
    printf    
    (    
     "             ##########   ##########  ##########  ##########  \n"
     "             #   5    #   #   6    #  #  7     #  #   8    #  \n"
     "             #        #   #        #  #        #  #        #  \n"
     "             ##########   ##########  ##########  ##########  \n"
    );    
    
    
    printf(" \n\n\n");

    printf
    (
     "              ##########   ##########  ##########  ##########  \n"
     "              #   9    #   #    +   #  #   -    #  #   =    #  \n"
     "              #        #   #        #  #        #  #        #  \n"
     "              ##########   ##########  ##########  ##########  \n"
    );
}


struct limit
{
    int limit_X_debut;
    int limit_X_fin;
    int limit_Y_debut;
    int limit_Y_fin;
};






int main() {
    std::vector<char> vect{}; //va contenir les options de la calco que l' user va entrer 

    limit limit1{13,22,15,18};
    limit limit2{26,35,15,18};
    limit limit3{38,47,15,18};
    limit limit4{50,59,15,18};

    limit limit5{13,22,22,25};
    limit limit6{26,35,22,25};
    limit limit7{38,47,22,25};
    limit limit8{50,59,22,25};

    limit limit9     {14,23,29,32};
    limit limit_plus {27,36,29,32};
    limit limit_moins{39,48,29,32};
    limit limit_egal {51,60,29,32};

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    INPUT_RECORD input;
    DWORD count;


    printf("Cliquez avec la souris (clic gauche pour quitter).\n");

    while (1) {
       
        ReadConsoleInput(hIn, &input, 1, &count);
        if (input.EventType == MOUSE_EVENT) 
        {
            MOUSE_EVENT_RECORD mer = input.Event.MouseEvent;

            if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) 
            {
                
                if(limit1.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit1.limit_X_fin &&
                   limit1.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit1.limit_Y_fin)
                {
                    vect.push_back('1'); 
                }

                else if(limit2.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit2.limit_X_fin && 
                        limit2.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit2.limit_Y_fin)
                {
                    vect.push_back('2');
                }

                else if(limit3.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit3.limit_X_fin && 
                        limit3.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit3.limit_Y_fin)
                {
                    vect.push_back('3'); 
                }

                else if(limit4.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit4.limit_X_fin && 
                        limit4.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit4.limit_Y_fin)
                {
                    vect.push_back('4');
                }

                else if(limit5.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit5.limit_X_fin && 
                        limit5.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit5.limit_Y_fin)
                {
                    vect.push_back('5'); 
                }

                else if(limit6.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit6.limit_X_fin && 
                        limit6.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit6.limit_Y_fin)
                {
                    vect.push_back('6');
                }
                
                else if(limit7.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit7.limit_X_fin && 
                        limit7.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit7.limit_Y_fin)
                {
                    vect.push_back('7');

                }

                else if(limit8.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit8.limit_X_fin && 
                        limit8.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit8.limit_Y_fin)
                {
                    vect.push_back('8'); 
                }
                
                else if(limit9.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit9.limit_X_fin && 
                        limit9.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit9.limit_Y_fin)
                {
                    vect.push_back('9');

                }
                
                else if(limit_plus.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit_plus.limit_X_fin && 
                        limit_plus.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit_plus.limit_Y_fin)
                {
                    vect.push_back('+'); 
                }
                
                else if(limit_moins.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit_moins.limit_X_fin && 
                        limit_moins.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit_moins.limit_Y_fin)
                {
                    vect.push_back('-'); 
                }
                
                else if(limit_egal.limit_X_debut<=mer.dwMousePosition.X && mer.dwMousePosition.X<=limit_egal.limit_X_fin && 
                        limit_egal.limit_Y_debut<=mer.dwMousePosition.Y && mer.dwMousePosition.Y<=limit_egal.limit_Y_fin)
                {
                    vect.push_back('='); 
                }
                
                else if(mer.dwMousePosition.X==0){break;}
                printf("Clic détecté en (%d, %d)\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
                presentation(vect);
                //break;
            }
        }
    }
    
    return 0;
}


/*
if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                printf("Clic détecté en (%d, %d)\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);

                if(mer.dwMousePosition.X<33 && mer.dwMousePosition.Y<41)
                
                break;
            }
*/