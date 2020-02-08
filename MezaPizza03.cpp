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
typedef struct address Address;

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
typedef struct delivery Home;

struct houseOrder{
    int pTable;
    mainInfo houseInfo;
};
typedef struct houseOrder Restaurant;

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
                    cout << "\nIngrese una de las siguientes opciones: " <<endl;
                    cout << "1. Ver total de ventas a domicilio" << endl;
                    cout << "2. Ver total de ventas en restaurante" << endl;
                    cout << "Su opcion: ";
                    cin >> option1; cin.ignore();
                    if (option1 == 1){
                        cout << "\n$" << (totalHome(0) + (totalHome(0) * 0.13)) << endl;
                    }
                    else if (option == 2){
                        cout << "\n$" << (totalRestaurant(0) + (totalRestaurant(0) * 0.13)) << endl;
                    }
                    else{
                        cout << "Opcion invalida\n" << endl;
                    }
                break;
                case 11: 
                    cout << "\nCambiando de usuario...\n";
                    loginUser();
                break;
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

void homeOrder(void){
    Home hOrder;
    int aux = 0;

    cout << "\nDatos del cliente, pedido a domicilio" << endl;
    cout << "Nombre: "; getline(cin, hOrder.deliveryInfo.name);
    cout << "\nDireccion del cliente, pedido a domicilio" << endl;
    cout << "Colonia: "; getline(cin, hOrder.deliveryAddress.settlement);
    cout << "Municipio: "; getline(cin, hOrder.deliveryAddress.municipality);
    cout << "Departamento: "; getline(cin, hOrder.deliveryAddress.department);
    cout << "No. Casa: "; cin >> hOrder.deliveryAddress.houseNumber; cin.ignore();
    cout << "No. Telefono: "; cin >> hOrder.cellphone; cin.ignore();

    do{
        cout << "\nEntrada:" << endl;
        cout << "1. Pan con ajo\t\t" << pBread << endl;
        cout << "2. Pizza Rolls\t\t" << pRolls << endl;
        cout << "3. Palitos de queso\t" << pSticks << endl;
        cout << "0. Cancelar" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 0)
            break;
        
        aux--;
        hOrder.deliveryInfo.pStarter.push_back(starter(aux));
        aux++;
    }while(aux != 0);

    do{
        cout << "\nPlato principal:" << endl;
        cout << "1. Pizza\t" << pPizza << endl;
        cout << "2. Pasta\t" << pPasta << endl;
        cout << "3. Lasagna\t" << pLasagna << endl; 
        cout << "0. Cancelar" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 0)
            break;
        
        aux--;
        hOrder.deliveryInfo.pDish.push_back(mainDish(aux));
        aux++;
    }while(aux != 0);

    do{
        cout << "\nBebida" << endl;
        cout << "1. Cerveza\t" << pBeer << endl;
        cout << "2. Soda\t\t" << pSoda << endl;
        cout << "3. Te Helado\t" << pTea << endl; 
        cout << "0. Cancelar" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 0)
            break;
        
        aux--;
        hOrder.deliveryInfo.pDrink.push_back(drink(aux));
        aux++;
        
    }while(aux != 0);

    hOrder.deliveryInfo.idOrder = idOrder++;

    cout << "\nTipo de pago" << endl;
    cout << "1. Tarjeta" << endl;
    cout << "2. Efectivo" << endl;
    cout << "Su opcion: "; cin >> aux;
    cin.ignore();    

    if (aux == 1){
        hOrder.deliveryInfo.pay = card;
    }

    else if (aux == 2){
        hOrder.deliveryInfo.pay = cash;
    }

    else{
        cout << "Opcion de pago no valida!" << endl;
        return;
    }
    aux--;

    cout << "Monto: "; cin >> hOrder.deliveryInfo.total;
    cin.ignore();

    hOrder.deliveryInfo.time = ((hOrder.deliveryInfo.pDish.size() * 1.5 + hOrder.deliveryInfo.pStarter.size() * 1.10 + hOrder.deliveryInfo.pDrink.size() * 1.35) + 15);
    cout << "\nTiempo estimado esta orden: " << hOrder.deliveryInfo.time << " minutos." <<endl;
    cout << "Orden a domicilio agregada exitosamente..." << endl;
    
    vDelivery.push_back(hOrder);
}

void restaurantOrder(void){
    Restaurant rOrder;
    int aux = 0;

    cout << "\nDatos del cliente, pedido en restaurante" << endl;
    cout << "Nombre: "; getline(cin, rOrder.houseInfo.name);
    cout << "Ingrese la cantidad de personas: "; cin >> rOrder.pTable; cin.ignore();

     do{
        cout << "\nEntrada:" << endl;
        cout << "1. Pan con ajo\t\t" << pBread << endl;
        cout << "2. Pizza Rolls\t\t" << pRolls << endl;
        cout << "3. Palitos de queso\t" << pSticks << endl;
        cout << "0. Cancelar" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 0)
            break;
        
        aux--;
        rOrder.houseInfo.pStarter.push_back(starter(aux));
        aux++;
    }while(aux != 0);

    do{
        cout << "\nPlato principal:" << endl;
        cout << "1. Pizza\t" << pPizza << endl;
        cout << "2. Pasta\t" << pPasta << endl;
        cout << "3. Lasagna\t" << pLasagna << endl; 
        cout << "0. Cancelar" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 0)
            break;
        
        aux--;
        rOrder.houseInfo.pDish.push_back(mainDish(aux));
        aux++;
    }while(aux != 0);

    do{
        cout << "\nBebida" << endl;
        cout << "1. Cerveza\t" << pBeer << endl;
        cout << "2. Soda\t\t" << pSoda << endl;
        cout << "3. Te Helado\t" << pTea << endl; 
        cout << "0. Cancelar" << endl;
        cout << "Su opcion: "; cin >> aux;
        cin.ignore();

        if(aux == 0) //Se puede validar mas
            break;
        
        aux--;
        rOrder.houseInfo.pDrink.push_back(drink(aux));
        aux++;
        
    }while(aux != 0);

    rOrder.houseInfo.idOrder = idOrder++;

    cout << "\nTipo de pago" << endl;
    cout << "1. Tarjeta" << endl;
    cout << "2. Efectivo" << endl;
    cout << "Su opcion: "; cin >> aux;
    cin.ignore();    

    if (aux == 1){
        rOrder.houseInfo.pay = card;
    }

    else if (aux == 2){
        rOrder.houseInfo.pay = cash;
    }

    else{
        cout << "Opcion de pago no valida!" << endl;
        return;
    }
    aux--;

    cout << "Monto: "; cin >> rOrder.houseInfo.total;
    cin.ignore();

    rOrder.houseInfo.time = (rOrder.houseInfo.pDish.size() * 1.5 + rOrder.houseInfo.pStarter.size() * 1.10 + rOrder.houseInfo.pDrink.size() * 1.35);
    cout << "\nTiempo estimado esta orden: " << rOrder.houseInfo.time << " minutos." <<endl;
    cout << "Orden en restaurante agregada exitosamente..." << endl;
    
    vRestaurant.push_back(rOrder);
}

void printHome(void){

}

void printRestaurant(void){

}

void dispatchHome(void){

}

void dispatchRestaurant(void){

}

void estimatedTime(vector<Home> vDelivery){

}

void estimatedTime(vector<Restaurant> vRestaurant){

}

void cancelOrder(void){

}

float totalHome(int pos){

}

float totalRestaurant(int pos){

}

float totalStarter(vector<starter> pStarter){

}

float totalDish(vector<mainDish> pDish){

}

float totalDrink(vector<drink> pDrink){

}


