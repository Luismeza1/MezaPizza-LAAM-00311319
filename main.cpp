#include <iostream>
#include <string>

#define PASSWORD "rand"

using namespace std;

enum mainDish {pizza, pasta, lasagna};
enum drink {beer, soda, tea};
enum starter {garlicBread, pizzaRolls, cheeseSticks};

enum paymentType{cash, card};

struct address{
    string settlement, municipality, department;
    int houseNumber;
};

struct mainInfo{
    string name;
    mainDish pDish;
    drink pDrink;
    starter pStarter;
    paymentType pay;
    int idOrder;
    float total;
};

struct delivery{
    address deliveryAddress;
    int cellphone;
    mainInfo deliveryInfo;
};

struct houseOrder{
    int pTable;
    mainInfo houseInfo;
};

//Variables globales
bool isAdmin = false;
int idOrder = 1;

//Prototipos
bool loginUser(void);

int main(void){
    int option = 0;
    delivery *Darray = NULL;
    houseOrder *Harray = NULL;

    if(loginUser() == false){
        return 0;
        do{
            printMenu(); cin >> option;
            cin.ignore();

            switch(option){
                case 1:
                    addOrder(Darray);
                break;
                case 2:
                    addOrder(Harray);
                break;
            }

        }while(option != 0);
    }

    return 0;
}

bool loginUser(void){
    string enterPass = " ";
    char option;
    cout << "INICIO DE SESION" <<endl;
    cout << "A - ADMINISTRADOR" << endl;
    cout << "E - EMPLEADO" << endl;
    cout << "Su opcion:\t"; cin >> option;

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
    }
    return false;
}

void printMenu(void){
    cout << "SISTEMA DE DESPACHO PIZZERIA PIZZA-MEZA" << endl;
    cout << "1. Agregar ordenes a domicilio" << endl;
    cout << "2. Agregar ordenes a restaurante" << endl;
    cout << "3. Ver ordenes a domicilio" << endl;
    cout << "4. Ver ordenes en restaurante" << endl;
    cout << "Su opcion:\t";
}

void addOrder(delivery* array){
    int size = 0;
    int aux = 0;
    cout << "Cantidad de pedidos a ingresar: "; cin >> size;
    cin.ignore();

    array = new delivery[size];

    for (int i = 0; i < size; i++){
        cout << "Nombre:\t"; getline(cin, array[i].deliveryInfo.name);
        cout << "Direccion:" << endl;
        cout << "Colonia\t"; getline(cin, array[i].deliveryAddress.settlement);
        cout << "Municipio:\t"; getline(cin, array[i].deliveryAddress.municipality);
        cout << "Departamento:\t"; getline(cin, array[i].deliveryAddress.department);
        cout << "No Casa:\t"; getline(cin, array[i].deliveryAddress.houseNumber);
        cin.ignore();
        
        cout << "Entrada:" << endl; 

        cout << "Plato principal:" << endl;
        cout << "1 - Pizza" << endl;
        cout << "2 - Pasta" << endl;
        cout << "3 - Lasagna" << endl; 
        cout << "Su opcion:\t"; cin >> aux;
        cin.ignore;

        if(aux == 1){
            array[i].deliveryInfo.pDish = pizza;
        }
        else if(aux == 2){
            array[i].deliveryInfo.pDish = pasta;
        }
        else if(aux == 3){
            array[i].deliveryInfo.pDish = lasagna;
        }

        cout << "Bebida" << endl;

        array[i].deliveryInfo.idOrder = idOrder++;

        cout << "Tipo de pago" << endl;
        cout << "1- Tarjeta" << endl;
        cout << "2- Efectivo" << endl;
        cout << "Su opcion:\t"; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].deliveryInfo.pay = card;
        }
        else{
            array[i].deliveryInfo.pay = cash;
        }

        cout << "Monto: "; cin >> array[i].deliveryInfo.total;
        cin.ignore();
        cout << "Telefono: "; cin >> array[i].cellphone;
        cin.ignore();
    }
}

void addOrder(houseOrder* array){

}

void searchByName(delivery* array, int size){
    bool userExists = false;
    string aux = " ";
    cout << "Nombre a buscar: "; getline(cin, aux);

    for (int i = 0; i < size; i++){
        if(aux.compare(array[i].deliveryInfo.name) == 0){
            //Imprimir datos
            userExists = true;
        }
    }

    (!userExists) ? cout << "No existe el usuario" : cout << "";

}

void searchByName(houseOrder* array, int size){

}