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

vector<Home> vDelivery, aux1, aux3;
vector<Restaurant> vRestaurant, aux2, aux4;
 
//Variables globales
bool isAdmin = false;
int hIdOrder = 1, rIdOrder = 1;
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
void cancelOrderH(void);
void cancelOrderR(void);
float totalHome(int pos);
float totalRestaurant(int pos);
float totalStarter(vector<starter> pStarter);
float totalDish(vector<mainDish> pDish);
float totalDrink(vector<drink> pDrink);


int main(void){
    int option = 0;
    int option1 = 0;
    int option2 = 0;

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
                        cout << "\nSolo los administradores pueden acceder a esta opcion" << endl;
                    } 
                    else{
                        cout << "\nIngrese una de las siguientes opciones" << endl;
                        cout << "1. Cancelar orden a domicilio" << endl;
                        cout << "2. Cancelar orden en restaurante" << endl;
                        cout << "Su opcion: ";
                        cin >> option2; cin.ignore();                        
                        if(option2 == 1){
                            cancelOrderH();
                        }
                        else if(option2 == 2){
                            cancelOrderR();
                        }
                        else{
                            cout << "\nOpcion ingresada no valida!" << endl;
                        }
                    }
                break;
                case 10:
                    cout << "\nIngrese una de las siguientes opciones: " <<endl;
                    cout << "1. Ver total de ventas a domicilio" << endl;
                    cout << "2. Ver total de ventas en restaurante" << endl;
                    cout << "Su opcion: ";
                    cin >> option1; cin.ignore();
                    if (option1 == 1){
                        cout << "\nTotal de ventas a domicilio: " << endl;
                        cout << "$" << (totalHome(0) + totalHome(0) * 0.13) << endl;
                    }
                    else{
                        cout << "\nTotal de ventas en restaurante: " << endl;
                        cout << "$" << (totalRestaurant(0) + totalRestaurant(0) * 0.13) << endl;
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
    cout << "\n***** SISTEMA DE DESPACHO PIZZERIA MEZA-PIZZA *****" << endl;
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

    hOrder.deliveryInfo.idOrder = hIdOrder++;

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

        if(aux == 0)
            break;
        
        aux--;
        rOrder.houseInfo.pDrink.push_back(drink(aux));
        aux++;
    }while(aux != 0);

    rOrder.houseInfo.idOrder = rIdOrder++;

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

    rOrder.houseInfo.time = (rOrder.houseInfo.pDish.size() * 1.5 + rOrder.houseInfo.pStarter.size() * 1.10 + rOrder.houseInfo.pDrink.size() * 1.35);
    cout << "\nTiempo estimado esta orden: " << rOrder.houseInfo.time << " minutos." <<endl;
    cout << "Orden en restaurante agregada exitosamente..." << endl;
    
    vRestaurant.push_back(rOrder);
}

void printHome(void){
    for(int i = 0; i < vDelivery.size(); i++){
        vDelivery[i].deliveryInfo.total = 0;
        cout << "\nNombre del cliente: " << vDelivery[i].deliveryInfo.name << endl;
        cout << "Direccion del cliente: ";
        cout << "No. casa: " << vDelivery[i].deliveryAddress.houseNumber;
        cout << ", Calle: " << vDelivery[i].deliveryAddress.settlement;
        cout << ", Municipio: " << vDelivery[i].deliveryAddress.municipality;
        cout << ", Departamento: " << vDelivery[i].deliveryAddress.department << endl;
        cout << "No. Telefono: " << vDelivery[i].cellphone << endl;
        cout << "\nEntrada(s): " << endl;
        for (int j = 0; j < vDelivery[i].deliveryInfo.pStarter.size(); j++){
            if(vDelivery[i].deliveryInfo.pStarter[j] == 0){
                cout << "Pan con ajo $" << pBread << endl;
                vDelivery[i].deliveryInfo.total += pBread;
            }
            else if(vDelivery[i].deliveryInfo.pStarter[j] == 1){
                cout << "Pizza Rolls $" << pRolls << endl;
                vDelivery[i].deliveryInfo.total += pRolls;
            }
            else if(vDelivery[i].deliveryInfo.pStarter[j] == 2){
                cout << "Cheese sticks $" << pSticks << endl;
                vDelivery[i].deliveryInfo.total += pSticks;
            }
        }
        cout << "Plato(s) principal(es): " << endl;
        for (int k = 0; k < vDelivery[i].deliveryInfo.pDish.size(); k++){
            if(vDelivery[i].deliveryInfo.pDish[k] == 0){
                cout << "Pizza $" << pPizza << endl;
                vDelivery[i].deliveryInfo.total += pPizza;
            }
            else if(vDelivery[i].deliveryInfo.pDish[k] == 1){
                cout << "Pasta $" << pPasta << endl;
                vDelivery[i].deliveryInfo.total += pPasta;
            }
            else if(vDelivery[i].deliveryInfo.pDish[k] == 2){
                cout << "Lasagna $" << pLasagna << endl;
                vDelivery[i].deliveryInfo.total += pLasagna;
            }            
        }
        cout << "Bebida(s): " << endl;
        for (int l = 0; l < vDelivery[i].deliveryInfo.pDrink.size(); l++){
            if(vDelivery[i].deliveryInfo.pDrink[l] == 0){
                cout << "Cerveza $" << pBeer << endl;
                vDelivery[i].deliveryInfo.total += pBeer;
            }
            else if(vDelivery[i].deliveryInfo.pDrink[l] == 1){
                cout << "Soda $" << pSoda << endl;
                vDelivery[i].deliveryInfo.total += pSoda;
            }
            else if(vDelivery[i].deliveryInfo.pDrink[l] == 2){
                cout << "Te Helado $" << pTea << endl;
                vDelivery[i].deliveryInfo.total += pTea;
            }            
        }

        cout << "\nTipo de pago: ";
        if(vDelivery[i].deliveryInfo.pay == 1){
            cout << "Tarjeta" << endl;
        }
        else if(vDelivery[i].deliveryInfo.pay == 0){
            cout << "Efectivo" <<endl;
        }
        cout << "Monto de esta orden: $" << vDelivery[i].deliveryInfo.total << endl;
        cout << "Tiempo de espera: " << vDelivery[i].deliveryInfo.time << " minutos." << endl;
        cout << "Numero de orden: " << vDelivery[i].deliveryInfo.idOrder << endl;
    }

}

void printRestaurant(void){
    for(int i = 0; i < vRestaurant.size(); i++){
        vRestaurant[i].houseInfo.total = 0;
        cout << "\nNombre del cliente: " << vRestaurant[i].houseInfo.name << endl;
        cout << "Cantidad de personas: " << vRestaurant[i].pTable << endl;
        cout << "\nEntrada(s): "<< endl;
        for (int j = 0; j < vRestaurant[i].houseInfo.pStarter.size(); j++){            
            if(vRestaurant[i].houseInfo.pStarter[j] == 0){
                cout << "Pan con ajo $" << pBread << endl;
                vRestaurant[i].houseInfo.total += pBread;
            }
            else if(vRestaurant[i].houseInfo.pStarter[j] == 1){
                cout << "Pizza Rolls $" << pRolls << endl;
                vRestaurant[i].houseInfo.total += pRolls;
            }
            else if(vRestaurant[i].houseInfo.pStarter[j] == 2){
                cout << "Cheese sticks $" << pSticks << endl;
                vRestaurant[i].houseInfo.total += pSticks;
            }
        }
        cout << "Plato(s) principal(es): "<< endl;
        for (int k = 0; k < vRestaurant[i].houseInfo.pDish.size(); k++){            
            if(vRestaurant[i].houseInfo.pDish[k] == 0){
                cout << "Pizza $" << pPizza << endl;
                vRestaurant[i].houseInfo.total += pPizza;
            }
            else if(vRestaurant[i].houseInfo.pDish[k] == 1){
                cout << "Pasta $" << pPasta << endl;
                vRestaurant[i].houseInfo.total += pPasta;
            }
            else if(vRestaurant[i].houseInfo.pDish[k] == 2){
                cout << "Lasagna $" << pLasagna << endl;
                vRestaurant[i].houseInfo.total += pLasagna;
            }
        }
        cout << "Bebida(s): "<< endl;
        for (int l = 0; l < vRestaurant[i].houseInfo.pDrink.size(); l++){            
            if(vRestaurant[i].houseInfo.pDrink[l] == 0){
                cout << "Cerveza $" << pBeer << endl;
                vRestaurant[i].houseInfo.total += pBeer;
            }
            else if(vRestaurant[i].houseInfo.pDrink[l] == 1){
                cout << "Soda $" << pSoda << endl;
                vRestaurant[i].houseInfo.total += pSoda;
            }
            else if(vRestaurant[i].houseInfo.pDrink[l] == 2){
                cout << "Te Helado $" << pTea << endl;
                vRestaurant[i].houseInfo.total += pTea;
            }
        }

        cout << "\nTipo de pago: ";
        if(vRestaurant[i].houseInfo.pay == 1){
            cout << "Tarjeta" << endl;
        }
        else if(vRestaurant[i].houseInfo.pay == 0){
            cout << "Efectivo" <<endl;
        }
        cout << "Monto de esta orden: $" << vRestaurant[i].houseInfo.total << endl;
        cout << "Tiempo de espera: " << vRestaurant[i].houseInfo.time << " minutos." << endl;
        cout << "Numero de orden: " << vRestaurant[i].houseInfo.idOrder << endl;
    }

}

void dispatchHome(void){
    int dispatchId;

    cout << "\nIngrese el numero de la orden a despachar: ";
    cin >> dispatchId; cin.ignore();
    int i = 0;
    for (auto iter = vDelivery.begin(); iter != vDelivery.end(); ++iter)
    {
        if (iter->deliveryInfo.idOrder == dispatchId)
        {
            aux1.push_back(vDelivery.at(i));
            iter = vDelivery.erase(iter);
            cout << "Orden despachada exitosamente...\n";
            break;
        }
    }
}

void dispatchRestaurant(void){
    int dispatchId;

    cout << "\nIngrese el numero de la orden a despachar: ";
    cin >> dispatchId; cin.ignore();
    int i = 0;
    for (auto iter = vRestaurant.begin(); iter != vRestaurant.end(); ++iter)
    {
        if (iter->houseInfo.idOrder == dispatchId)
        {
            aux2.push_back(vRestaurant.at(i));
            iter = vRestaurant.erase(iter);
            cout << "Orden despachada exitosamente...\n";
            break;
        }
    }
}

void estimatedTime(vector<Home> vDelivery){
    float totalTime = 0;
    Home h1;
    for(Home h1 : vDelivery){
        totalTime += h1.deliveryInfo.time;
        ceil(totalTime);        
    }
    cout << "\nEl tiempo de espera total de las ordenes a domicilio es: " << totalTime << " minutos." <<endl;
}

void estimatedTime(vector<Restaurant> vRestaurant){
    float totalTime = 0;
    Restaurant r1;
    for(Restaurant r1 : vRestaurant){
        totalTime += r1.houseInfo.time;
        ceil(totalTime);        
    }
    cout << "\nEl tiempo de espera total de las ordenes en restaurante es: " << totalTime << " minutos." <<endl;
}

void cancelOrderH(void){
    int cancelId;

    cout << "\nIngrese el numero de la orden a cancelar: ";
    cin >> cancelId; cin.ignore();
    int i = 0;
    for (auto iter = vDelivery.begin(); iter != vDelivery.end(); ++iter)
    {
        if (iter->deliveryInfo.idOrder == cancelId)
        {
            aux3.push_back(vDelivery.at(i));
            iter = vDelivery.erase(iter);
            cout << "Orden cancelada exitosamente...\n";
            break;
        }
    }
}

void cancelOrderR(void){
    int cancelId;

    cout << "\nIngrese el numero de la orden a cancelar: ";
    cin >> cancelId; cin.ignore();
    int i = 0;
    for (auto iter = vRestaurant.begin(); iter != vRestaurant.end(); ++iter)
    {
        if (iter->houseInfo.idOrder == cancelId)
        {
            aux4.push_back(vRestaurant.at(i));
            iter = vRestaurant.erase(iter);
            cout << "Orden cancelada exitosamente...\n";
            break;
        }
    }

}

float totalStarter(vector<starter> pStarter){
    float total = 0;
    for (int i = 0; i < pStarter.size(); i++)
    {
        switch (pStarter.at(i))
        {
        case garlicBread:
            total += 3.99;
            break;
        case pizzaRolls:
            total += 4.99;
            break;
        case cheeseSticks:
            total += 3.75;
            break;
        }
    }
    return total;
}

float totalDish(vector<mainDish> pDish){
    float total = 0;
    for (int i = 0; i < pDish.size(); i++)
    {
        switch (pDish.at(i))
        {
        case pizza:
            total += 13.99;
            break;
        case pasta:
            total += 5.55;
            break;
        case lasagna:
            total += 6.25;
            break;
        }
    }
    return total;
}

float totalDrink(vector<drink> pDrink){
    float total = 0;
    for (int i = 0; i < pDrink.size(); i++)
    {
        switch (pDrink.at(i))
        {
        case beer:
            total += 1.99;
            break;
        case soda:
            total += 0.95;
            break;
        case tea:
            total += 1.15;
            break;
        }
    }
    return total;

}

float totalHome(int pos){
    if (pos == aux1.size())
        return 0;
    else
    {
        return totalStarter(aux1.at(pos).deliveryInfo.pStarter) + totalDish(aux1.at(pos).deliveryInfo.pDish) + totalDrink(aux1.at(pos).deliveryInfo.pDrink) + totalHome(pos + 1);
    }
    cout << endl;

}

float totalRestaurant(int pos){
    if (pos == aux2.size())
        return 0;
    else
    {   
        return totalStarter(aux2.at(pos).houseInfo.pStarter) + totalDish(aux2.at(pos).houseInfo.pDish) + totalDrink(aux2.at(pos).houseInfo.pDrink) + totalRestaurant(pos + 1);
    }
    cout << endl;
}




