#include <iostream> //Permite la entrada y salida de datos en consola
#include <string> //Permite el uso de cadenas de texto
#include <vector> //Permite el uso de vectores sin tener que implementarlos desde cero
#include <algorithm> //Permite el uso de funciones para vectores
#include <cmath> //Permite el uso de funciones paras realizar calculos

#define PASSWORD "srand"

using namespace std;

enum mainDish {pizza, pasta, lasagna};
enum drink {beer, soda, tea};
enum starter {garlicBread, pizzaRolls, cheeseSticks};

enum paymentType{cash, card};

struct address{
    string settlement, municipality, department;
    int houseNumber;
};
typedef struct address Adress;

struct mainInfo{
    string name;
    vector<mainDish> pDish;
    vector<drink> pDrink;
    vector<starter> pStarter;
    paymentType pay;
    int idOrder;
    int time;
    float total;
};
typedef struct mainInfo MainInfo;

struct delivery{
    address deliveryAddress;
    int cellphone;
    mainInfo deliveryInfo;
};
typedef struct Home;

struct houseOrder{
    int pTable;
    mainInfo houseInfo;
};
typedef struct Restaurant;

vector<Home> vDelivery, aux1;
vector<Restaurant> vRestaurant, aux2;

//Variables globales
bool isAdmin = false;
int idOrder = 1;
float count;
int aux, number;
float pPizza = 13.99, pPasta = 5.55, pLasagna = 6.25;
float pBread = 3.99, pRolls = 4.99, pSticks = 3.75;
float pBeer = 1.99, pSoda = 0.95, pTea = 1.15;

//Prototipos
bool loginUser(void);
void printMenu(void);
void restaurantOrder(void);
void homeOrder(void);
void printRestaurant(void);
void printHome(void);
void estimatedTime(vector<Home> vDelivery);
void estimatedTime(vector<Restaurant> vRestaurant);
void dispatchHome(void);
void dispatchRestaurant(void);
void cancelOrder(void);
float totalHome(int pos);
float totalRestaurant(int pos);
float totalStarter(vector<starter> pStarter);
float totalDish(vector<mainDish> pDish);
float totalDrink(vector<drink> pDrink);


int main(void){
    int option = 0;
    int option1 = 0;

    if(!loginUser())
        return 0;
        do{
            printMenu(); cin >> option;
            cin.ignore();

            switch(option){
                case 1: homeOrder(); break;
                case 2: restaurantOrder(); break;
                case 3: printHome(); break;
                case 4: printRestaurant(); break;
                case 5: dispatchHome(); break;
                case 6: dispatchRestaurant(); break;
                case 7: estimatedTime(vDelivery); break;
                case 8: estimatedTime(vRestaurant); break;
                case 9:
                    if(!isAdmin){
                        cout << "Solo los administradores pueden acceder a esta opcion\n" << endl;
                    } 
                    else{
                        cancelOrder();
                    }
                break;
                case 10:
                    cout << "Ingrese una de las siguientes opciones: " <<endl;
                    cout << "1. Ver total de ventas en domicilio" << endl;
                    cout << "2. Ver total de ventas restaurante" << endl;
                    cin >> option1; cin.ignore();
                    if (option1 == 1){
                        cout << "$" << (totalHome(0) + (totalHome(0) * 0.13));
                    }
                    else if (option == 2){
                        cout << "$" << (totalRestaurant(0) + (totalRestaurant(0) * 0.13));
                    }
                    else{
                        cout << "Opcion invalida\n" << endl;
                    }
                break;
                case 11: loginUser(); break;
                case 0: option = 0; break;
                default: cout << "La opcion ingresada no es valida!\n" << endl; break;
            }

        }while(option != 0);
    

    return 0;
}

bool loginUser(void){
    string enterPass = "";
    char option;
    cout << "\n***** SISTEMA DE INICIO DE SESION *****" <<endl;
    cout << "Ingrese una de las siguientes opciones de usuario para ingresar al sistema: " << endl;
    cout << "A - ADMINISTRADOR" << endl;
    cout << "E - EMPLEADO" << endl;
    cout << "Su opcion: "; cin >> option;

    switch(option){
    case 'a':
    case 'A':
        cout << "Digite contraseña: "; cin >> enterPass;
            if(enterPass.compare(PASSWORD) == 0){
                isAdmin = true;
                return true;
            }
            else{
                cout << "Contraseña incorrecta" << endl;
            }
    break;
    case 'e':
    case 'E':
        isAdmin = false;
        return true;
    break;
    default: cout << "La opcion ingresada no es valida!\n" << endl;
    break;
    }
     return false;
}

void printMenu(void){
    cout << "\n***** SISTEMA DE DESPACHO PIZZERIA PIZZA-MEZA *****" << endl;
    cout << "0.Salir \t\t\t\t 6.Despachar ordenes en restaurante" << endl;
    cout << "1.Agregar orden a domicilio \t\t 7.Ver tiempo promedio de espera a domicilio" << endl;
    cout << "2.Agregar orden en restaurante \t\t 8.Ver tiempo promedio de espera en restaurante" << endl;
    cout << "3.Ver ordenes a domicilio \t\t 9.Cancelar orden" << endl;
    cout << "4.Ver ordenes en restaurante \t\t 10.Calcular total de ventas" << endl;
    cout << "5.Despachar ordenes a domicilio \t 11.Cambiar de usuario" << endl;
    cout << "Su opcion: ";
}

void addOrder(delivery* array){
    int size = 0;
    cout << "Cantidad de pedidos a ingresar: "; cin >> size;
    cin.ignore();

    array = new delivery[size];

    for (int i = 0; i < size; i++){
        int aux = 0;
        cout << "\nDatos del cliente, pedido a domicilio" << endl;
        cout << "Nombre: "; getline(cin, array[i].deliveryInfo.name);
        cout << "\nDireccion del cliente, pedido a domicilio" << endl;
        cout << "Colonia: "; getline(cin, array[i].deliveryAddress.settlement);
        cout << "Municipio: "; getline(cin, array[i].deliveryAddress.municipality);
        cout << "Departamento: "; getline(cin, array[i].deliveryAddress.department);
        cout << "No Casa: "; cin >> array[i].deliveryAddress.houseNumber;
        cin.ignore();
        
        cout << "Entrada:" << endl;
        cout << "1. Pan con ajo" << endl;
        cout << "2. Pizza Rolls" << endl;
        cout << "3. Palitos de queso" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].deliveryInfo.pStarter = garlicBread;
        }
        else if(aux == 2){
            array[i].deliveryInfo.pStarter = pizzaRolls;
        }
        else if(aux == 3){
            array[i].deliveryInfo.pStarter = cheeseSticks;
        }
        else{
            cout << "Opcion no valida\n" << endl;
            return;
        }

        cout << "Plato principal:" << endl;
        cout << "1. Pizza" << endl;
        cout << "2. Pasta" << endl;
        cout << "3. Lasagna" << endl; 
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].deliveryInfo.pDish = pizza;
        }
        else if(aux == 2){
            array[i].deliveryInfo.pDish = pasta;
        }
        else if(aux == 3){
            array[i].deliveryInfo.pDish = lasagna;
        }
        else{
            cout << "Opcion no valida\n" << endl;
            return;
        }

        cout << "Bebida" << endl;
        cout << "1. Cerveza " << endl;
        cout << "2. Soda" << endl;
        cout << "3. Te Helado" << endl; 
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].deliveryInfo.pDrink= beer;
        }
        else if(aux == 2){
            array[i].deliveryInfo.pDrink = soda;
        }
        else if(aux == 3){
            array[i].deliveryInfo.pDrink = tea;
        }
        else{
            cout << "Opcion no valida\n" << endl;
            return;
        }

        array[i].deliveryInfo.idOrder = idOrder++;

        cout << "Tipo de pago" << endl;
        cout << "1. Tarjeta" << endl;
        cout << "2. Efectivo" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].deliveryInfo.pay = card;
        }
        else if(aux == 2){
            array[i].deliveryInfo.pay = cash;
        }
        else{
            cout << "Opcion no valida\n" << endl;
        }

        cout << "Monto: "; cin >> array[i].deliveryInfo.total;
        cin.ignore();
        cout << "Telefono: "; cin >> array[i].cellphone;
        cin.ignore();
    }
}

void addOrder(houseOrder* array){
    int size = 0;
    cout << "Cantidad de pedidos a ingresar: "; cin >> size;
    cin.ignore();

    array = new houseOrder[size];

    for(int i = 0; i < size; i++){
        int aux = 0;
        cout << "Nombre: "; getline(cin, array[i].houseInfo.name);
        
        cout << "Entrada" << endl;
        cout << "1. Pan con ajo" << endl;
        cout << "2. Pizza rolls" << endl;
        cout << "3. Palitos de queso" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].houseInfo.pStarter = garlicBread;
        }
        else if(aux == 2){
            array[i].houseInfo.pStarter = pizzaRolls;
        }
            
        else if(aux == 3){
            array[i].houseInfo.pStarter = cheeseSticks;
        }
        else{
            cout << "Opcion no valida\n" << endl;
            return;
        }
            

        cout << "Plato principal" << endl;
        cout << "1. Pizza" << endl;
        cout << "2. Pasta" << endl;
        cout << "3. Lasagna" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].houseInfo.pDish = pizza;
        }
            
        else if(aux == 2){
             array[i].houseInfo.pDish = pasta;
        }
           
        else if (aux == 3){
            array[i].houseInfo.pDish = lasagna;
        }
        else{
            cout << "Opcion no valida\n" << endl;
            return;
        }
            

        cout << "Bebida" << endl;
        cout << "1. Cerveza" << endl;
        cout << "2. Soda" << endl;
        cout << "3. Te helado" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].houseInfo.pDrink = beer;
        }
            
        else if(aux == 2){
            array[i].houseInfo.pDrink = soda;
        }
            
        else if (aux == 3){
            array[i].houseInfo.pDrink = tea;
        }
        else{
            cout << "Opcion no valida\n" << endl;
            return;
        }
            

        array[i].houseInfo.idOrder = idOrder++;
        
        cout << "Tipo de pago" << endl;
        cout << "1. Tarjeta" << endl;
        cout << "2. Efectivo" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].houseInfo.pay = card;
        }
            
        else if(aux == 2){
            array[i].houseInfo.pay = cash;
        }
        else{
            cout << "Opcion no valida\n" << endl;
            return;
        }
            

        cout << "Monto: "; cin >> array[i].houseInfo.total;
        cin.ignore();
    }
}
