/*
BARRIOS RETANA LIZETH 372813
Es un programa de gestión de empleados que utiliza un arreglo de estructuras.
Ofrece funciones como agregar, editar, eliminar, buscar y ordenar registros.
Además, incluye operaciones de archivo y manejo de fechas.
El programa permite interactuar con datos de empleados mediante un menú de opciones.
BRL_RP13_PE
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "BRL.h"

typedef struct Datos_de_empleado
{
    int numeroEmpleado;
    int key;
    char fechaIngreso[11];
    char nombre[30];
    char apellidos[50];
    char fechaNacimiento[11];
    int numero_de_la_seguridad_social;
    char direccion[50];
    char telefono[12];
    int Status;
} Tdatos;

void DatosRandoms(Tdatos registros[], int *NumReg);
int Bisiesto(int year);
int DiaNacimiento(int mes, int bis);
void ImprimirTerminal(Tdatos registros[], int NumReg);
void ordenar(Tdatos registros[], int *NumReg);
int particion(Tdatos registros[], int ri, int rs);
void quicksort(Tdatos registros[], int ri, int rs);
void ordenarQuickSort(Tdatos registros[], int *NumReg);
void buscar(Tdatos registros[], int *NumReg);
void BuscarParaModificar(Tdatos registros[], int *NumReg);
void BajaReg(Tdatos registros[], int *NumReg, int registro_a_eliminaar);
int imprmirParaEliminar(Tdatos registros[], int *NumReg, int registro);
void ImprimirEliminadosBinarios(Tdatos registros[], int NumReg, FILE *fa);
void ImprimirEnArchivo(Tdatos registros[], int NumReg, FILE *fa, char *NombreDArchivo);
void ImprimirEnArchivoBinarioDeTexto(Tdatos registros[], int NumReg, FILE *fa, char *NombreDArchivo);
void CrearArchivoTemporal(FILE *fa);

int main()
{

    Tdatos registros[5000];
    FILE *archivo, *archivo_binario, *archivo_borrados = fopen("archivos_eliminados.dll", "ab");
    srand(time(NULL));
    char NombreDArchivo[20];
    int NumReg = 0, ordenado = 1, RegPEliminar, encontrado, PregEliminar;
    int inicializado = 0;

    int opc, menu;
    do
    {
        menu = 1;
        opc = validarnumeros("\n--MENU--\n1.- AGREGAR (AUTOM 100 REGISTROS)\n2.- EDITAR REGISTRO \n3.- ELIMINAR REGISTRO (logico)\n4.- Buscar\n5.- Ordenar\n6- IMPRIMIR\n7.- GENERAR ARCHIVO TEXTO\n8.- VER ARCHIVO TEXTO\n9.- CREAR ARCH BINARIO\n10.- CARGAR ARCH BINARIO\n11.- MOSTRAR ELIMINADOS\n0.-salir\n", 0, 11);
        switch (opc)
        {
        case 0:
            system("cls");
            printf("FIN DEL PROGRAMA");
            return 0;
            break;
        case 1:
            DatosRandoms(registros, &NumReg);
            break;
        case 2:
            BuscarParaModificar(registros, &NumReg);
            break;
        case 3:

            RegPEliminar = validarnumeros("INGRESE LA MATRICULA DEL REGISTRO PARA ELIMINAR SU REGISTRO\n", 200000, 400000);
            encontrado = imprmirParaEliminar(registros, &NumReg, RegPEliminar);
            if (encontrado == 1)
            {
                PregEliminar = validarnumeros("QUIERES ELIMINAR ESTE REGISTRO?\n1.-SI\n2.-NO\n", 1, 2);
                if (PregEliminar == 1)
                {
                    BajaReg(registros, &NumReg, RegPEliminar);
                    ImprimirEliminadosBinarios(registros, NumReg, archivo_borrados);
                    ordenado = 1;
                }
            }
            break;
        case 4:
            buscar(registros, &NumReg);
            break;
        case 5:
            if (NumReg > 0)
            {
                if (ordenado == 1)
                {
                    if (NumReg <= 500)
                    {
                        ordenar(registros, &NumReg);
                        printf("ORDENADO POR METODO DE BURBUJA\n");
                    }
                    else
                    {
                        ordenarQuickSort(registros, &NumReg);
                        printf("ORDENADO POR METODO QUICKSORT\n");
                    }
                    ordenado = 0;
                }
                else
                {
                    printf("YA ESTA ORDENADO\n");
                    getchar();
                }
            }
            else
            {
                printf("NO HAY REGISTROS\n");
            }
            break;

        case 6:
            ImprimirTerminal(registros, NumReg);

            break;
        case 7:
            printf("INGRESE EL NOMBRE DEL ARCHIVO\n");
            gets(NombreDArchivo);
            strcat(NombreDArchivo, ".txt");
            ImprimirEnArchivo(registros, NumReg, archivo, NombreDArchivo);
            break;
        case 8:
            printf("INGRESE EL NOMBRE DEL ARCHIVO\n");
            gets(NombreDArchivo);
            strcat(NombreDArchivo, ".txt");
            archivo = fopen(NombreDArchivo, "a");

            break;

        case 9:
            if (inicializado == 1)
            {
                CrearArchivoTemporal(archivo_binario);
                archivo_binario = fopen("datos.dll", "wb");
                ImprimirEnArchivoBinarioDeTexto(registros, NumReg, archivo_binario, "datos.dll");
            }
            else
            {
                printf("No se puede crear por falta de registros en el vector");
            }

            break;
        case 10:
            if (inicializado == 0)
            {
                archivo_binario = fopen("datos.dll", "a+b");
                inicializado = 1;
            }
            else
            {
                printf("Ya se cargo");
            }

            break;
        case 11:
            ImprimirEliminadosBinarios(registros, NumReg, archivo_borrados);
            break;
        }

    } while (menu == 1);
    fclose(archivo_borrados);
}
void DatosRandoms(Tdatos registros[], int *NumReg)
{
    char hombres[20][10] = {"JUAN", "PEDRO", "CARLOS", "LUIS", "JAVIER", "ANDRES", "ALEJANDRO", "MIGUEL", "JOSE", "ADAN", "JORGE", "GABRIEL", "ROBERTO", "DAVID", "FERNANDO", "RAUL", "EDUARDO", "SERGIO", "ANTONIO", "FRANCISCO"};
    char mujeres[20][10] = {"DANIELA", "LAURA", "ANA", "CARMEN", "SOFIA", "ISABEL", "MARTA", "PAULA", "ELENA", "PATRICIA", "LUCIA", "CLARA", "ROSA", "BEATRIZ", "CAROLINA", "JULIA", "TERESA", "SARA", "IRENE", "ADRIANA"};
    char apellidos_paternos[20][10] = {"BARRIOS", "RODRIGUEZ", "LOPEZ", "PEREZ", "MARTINEZ", "SANCHEZ", "FERNANDEZ", "GONZALEZ", "RAMIREZ", "TORRES", "MARTIN", "JIMENEZ", "RUIZ", "DIAZ", "SOTO", "GOMEZ", "LOZANO", "CASTRO", "HERRERA", "GARCIA"};
    char apellidos_maternos[20][10] = {"SUAREZ", "VILLEGAS", "GUERRERO", "PALACIOS", "FARIAS", "AVILA", "MOLINA", "SALAZAR", "DELGADO", "SANCHEZ", "FLORES", "MORALES", "ROMERO", "OROZCO", "RIVERA", "CASTILLO", "CHAVEZ", "SUAREZ", "VILLEGAS", "GUERRERO"};
    char direcciones[20][50] = {"Calle de los Pinos 132", "Avenida Principal 567", "Calle del Sol 754", "Calle de la Luna 567", "Avenida de las Flores 369", "Calle de las Rosas 987", "Avenida de los Robles 231", "Calle de los Girasoles 876", "Avenida del Bosque 543", "Calle de las Margaritas 210", "Avenida de las Palmas 345", "Calle de los Cerezos 678", "Avenida de los Almendros 901", "Calle de los Olivos 543", "Avenida de los Sauces 876", "Calle de los Abedules 129", "Avenida del Alamo 765", "Calle de los Fresnos 432", "Avenida de las Acacias 876", "Calle de los Nogales 543"};
    int k;
    int year, bis, mes, dia, year2, bis2, mes2, dia2;
    char fecha_ingreso[12], fecha_nacimiento[12];
    char numero_telefono[15];
    int numero_telefono1, numero_telefono2, numero_telefono3;
    int numsexo = 0, numero_de_de_empleado = 0, numero_social = 0;
    int numero_nombre2;

    for (k = 0; k < 10; k++)
    {
        Tdatos *registro = &registros[*NumReg];
        numero_de_de_empleado = numerorandomsinrepetir(200000, 400000);
        registro->numeroEmpleado = numero_de_de_empleado;
        registro->key = numero_de_de_empleado;
        numero_social = numerorandomsinrepetir(200000, 400000);
        registro->numero_de_la_seguridad_social = numero_social;
        numsexo = random(1, 2);

        if (numsexo == 1)
        {
            strcpy(registro->nombre, hombres[rand() % 20]);
            numero_nombre2 = rand() % 2;
            if (numero_nombre2 == 0)
            {
                strcat(registro->nombre, "_");
                strcat(registro->nombre, hombres[rand() % 20]);
            }
        }
        else
        {
            strcpy(registro->nombre, mujeres[rand() % 20]);
            if (numero_nombre2 == 0)
            {
                strcat(registro->nombre, "_");
                strcpy(registro->nombre, mujeres[rand() % 20]);
            }
        }
        strcpy(registro->apellidos, apellidos_paternos[rand() % 20]);
        strcat(registro->apellidos, " ");
        strcat(registro->apellidos, apellidos_maternos[rand() % 20]);
        year = random(2014, 2023);
        bis = Bisiesto(year);
        mes = random(1, 12);
        dia = DiaNacimiento(mes, bis);
        sprintf(fecha_ingreso, "%02d/%02d/%02d", dia, mes, year);
        strcpy(registro->fechaIngreso, fecha_ingreso);
        year2 = random(1980, 2004);
        bis2 = Bisiesto(year2);
        mes2 = random(1, 12);
        dia2 = DiaNacimiento(mes2, bis2);
        sprintf(fecha_nacimiento, "%02d/%02d/%02d", dia2, mes2, year2);
        strcpy(registro->fechaNacimiento, fecha_nacimiento);
        strcpy(registro->direccion, direcciones[rand() % 20]);
        numero_telefono1 = random(100, 999);
        numero_telefono2 = random(10, 99);
        numero_telefono3 = random(10, 99);
        sprintf(numero_telefono, "646-%d-%d-%d", numero_telefono1, numero_telefono2, numero_telefono3);
        strcpy(registro->telefono, numero_telefono);
        registro->Status = 1;
        (*NumReg)++;
        if (*NumReg > 5000)
        {
            printf("REGISTROS LLENOS");
            k = 100;
        }
    }
}
int Bisiesto(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int dia_nacimiento(int mes, int bis)
{
    int m, dia;
    int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    m = day[mes];
    if (bis == 1 && mes == 3)
    {
        m = 29;
    }
    if (bis == 0 && mes == 3)
    {
        m = 28;
    }
    dia = validarnumeros("INGRESE SU DIA DE ENTRADA\n", 1, m);
    return dia;
}
int DiaNacimiento(int mes, int bis)
{
    int diasPorMes[] = {0, 31, (bis == 1) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int maxDias = diasPorMes[mes];
    if (mes == 2 && bis == 1)
    {
        maxDias = 29;
    }

    int dia = random(1, maxDias);
    return dia;
}
void ImprimirTerminal(Tdatos registros[], int NumReg)
{
    int i, acu = 1;
    printf("Registros almacenados:\n");
    printf("===========================================================================================================================================================\n");
    printf("|Num.Empl| Fecha Ingreso |          Nombre         | Apellidos            | Fecha Nacimiento  | Num.Social | Direccion                    | Telefono      |\n");
    printf("===========================================================================================================================================================\n");

    for (i = 0; i <= NumReg; i++)
    {
        if (registros[i].Status == 1)
        {
            printf("| %4d | %-13s | %-23s | %-20s | %-17s | %-10d | %-28s | %-9s |\n", registros[i].numeroEmpleado, registros[i].fechaIngreso, registros[i].nombre, registros[i].apellidos, registros[i].fechaNacimiento, registros[i].numero_de_la_seguridad_social, registros[i].direccion, registros[i].telefono);
            printf("===========================================================================================================================================================\n");
        }

        if (acu == 40)
        {
            getchar();
            acu = 0;
        }
        acu++;
    }
}
void ordenar(Tdatos registros[], int *NumReg)
{
    Tdatos temp;
    int i, j;
    for (i = 0; i < *NumReg; i++)
    {
        for (j = 0; j < *NumReg - 1; j++)
        {
            if (registros[j].key > registros[j + 1].key)
            {
                temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
            }
        }
    }
}
int particion(Tdatos registros[], int ri, int rs)
{
    int tem2;
    int i, j;

    tem2 = registros[rs].key;
    i = (ri - 1);

    for (j = ri; j < rs; j++)
    {
        if (registros[j].key < tem2)
        {
            i++;
            Tdatos temp = registros[i];
            registros[i] = registros[j];
            registros[j] = temp;
        }
    }

    Tdatos temp = registros[i + 1];
    registros[i + 1] = registros[rs];
    registros[rs] = temp;

    return (i + 1);
}
void quicksort(Tdatos registros[], int ri, int rs)
{
    int pi;
    if (ri < rs)
    {
        pi = particion(registros, ri, rs);

        quicksort(registros, ri, pi - 1);
        quicksort(registros, pi + 1, rs);
    }
}
void ordenarQuickSort(Tdatos registros[], int *NumReg)
{
    quicksort(registros, 0, *NumReg - 1);
}
void buscar(Tdatos registros[], int *NumReg)
{
    int numero_a_encontrar, encontrado = 0;
    numero_a_encontrar = validarnumeros("Ingrese el Numero del Empleado\n", 200000, 400000);

    for (int i = 0; i < *NumReg; i++)
    {
        if (registros[i].key == numero_a_encontrar)
        {
            printf("============================================================================\n");
            printf("| Numero de Empleado: %d                                               |\n", registros[i].numeroEmpleado);
            printf("|--------------------------------------------------------------------------|\n");
            printf("| Fecha de Ingreso: %-12s                                           |\n", registros[i].fechaIngreso);
            printf("| Nombre: %-25s                                        |\n", registros[i].nombre);
            printf("| Apellidos: %-28s                                  |\n", registros[i].apellidos);
            printf("| Fecha de nacimiento: %-12s                                        |\n", registros[i].fechaNacimiento);
            printf("| Numero Social: %-11d                                               |\n", registros[i].numero_de_la_seguridad_social);
            printf("| Direccion: %-30s                                |\n", registros[i].direccion);
            printf("| Numero de Telefono: %-11s                                        |\n", registros[i].telefono);
            printf("============================================================================\n");
        }
        encontrado = 1;
    }
    if (encontrado == 0)
    {
        printf("NO SE ENCONTRO LA MATRICULA\n\n");
    }
}
void BuscarParaModificar(Tdatos registros[], int *NumReg)
{
    int numero_a_encontrar, encontrado = 0, opc;
    int i, numero_empleado = 0, numero_social = 0;
    int num_telefono, limite_maximo = 100000000, prefijo;
    int year, dia, mes, bis, year2, dia2, mes2, bis2, num;
    char fecha_ingreso[12], fecha_nacimiento[12], nom[20], nom2[20], AP[20], AM[20], direccion[30], numero_telefono[12], numero_telefono_estructurado[20];
    numero_a_encontrar = validarnumeros("Ingrese el Numero del Empleado\n", 200000, 400000);
    for (i = 0; i < *NumReg; i++)
    {
        if (registros[i].Status == 1)
        {
            if (registros[i].key == numero_a_encontrar)
            {
                printf("============================================================================\n");
                printf("| Numero de Empleado: %d                                               |\n", registros[i].numeroEmpleado);
                printf("|--------------------------------------------------------------------------|\n");
                printf("| Fecha de Ingreso: %-12s                                           |\n", registros[i].fechaIngreso);
                printf("| Nombre: %-25s                                        |\n", registros[i].nombre);
                printf("| Apellidos: %-28s                                  |\n", registros[i].apellidos);
                printf("| Fecha de nacimiento: %-12s                                        |\n", registros[i].fechaNacimiento);
                printf("| Numero Social: %-11d                                               |\n", registros[i].numero_de_la_seguridad_social);
                printf("| Direccion: %-30s                                |\n", registros[i].direccion);
                printf("| Numero de Telefono: %-11s                                        |\n", registros[i].telefono);
                printf("============================================================================\n");
                encontrado = 1;
                opc = validarnumeros("\n--MENU--\nCual area quieres modificar?\n1.-Numero de Empleado\n2.-Fecha de Ingreso\n3.-Nombre\n4.-Apellidos\n5.-Fecha de nacimiento\n6.-Numero Social\n7.-Direccion\n8.-Numero de Telefono\n0.-NINGUNO\n", 0, 8);
                switch (opc)
                {
                case 0:;
                    break;
                case 1:
                    numero_empleado = validarnumeros("El numero tiene que ser con rango de [200000,400000]", 200000, 400000);
                    registros[i].numeroEmpleado = numero_empleado;
                    registros[i].key = numero_empleado;
                    break;
                case 2:
                    year = validarnumeros("INGRESE SU AÑO DE ENTRADA\n", 1900, 2023);
                    bis = Bisiesto(year);
                    mes = validarnumeros("INGRESE SU MES DE ENTRADA\n", 0, 12);
                    dia = dia_nacimiento(mes, bis);
                    sprintf(fecha_ingreso, "%02d/%02d/%02d", dia, mes, year);
                    strcpy(registros[i].fechaIngreso, fecha_ingreso);
                    break;
                case 3:
                    validarletras("ESCRIBA SU NOMBRE: ", nom);
                    strcpy(registros[i].nombre, nom);
                    num = validarnumeros("TIENE SEGUNDO NOMBRE?\n1.-SI\n2.-NO\n", 1, 2);
                    if (num == 1)
                    {
                        validarletras("ESCRIBA SU NOMBRE: ", nom2);
                        strcpy(registros[i].nombre, nom2);
                    }
                    break;
                case 4:
                    validarletras("ESCRIBA SU PRIMER APELLIDO: ", AP);
                    strcpy(registros[i].apellidos, AP);
                    strcat(registros[i].apellidos, " ");
                    validarletras("ESCRIBA SU SEGUNDO APELLIDO: ", AM);
                    strcat(registros[i].apellidos, AM);
                    break;
                case 5:
                    year2 = validarnumeros("INGRESE SU AÑO DE ENTRADA\n", 1900, 2023);
                    bis2 = Bisiesto(year2);
                    mes2 = validarnumeros("INGRESE SU MES DE ENTRADA\n", 0, 12);
                    dia2 = dia_nacimiento(mes2, bis2);
                    sprintf(fecha_nacimiento, "%02d/%02d/%02d", dia2, mes2, year2);
                    strcpy(registros[i].fechaIngreso, fecha_nacimiento);
                    break;
                case 6:
                    numero_social = validarnumeros("El numero tiene que ser con rango de [200000,400000]", 200000, 400000);
                    registros[i].numeroEmpleado = numero_social;

                    break;
                case 7:

                    gets(direccion);
                    strcpy(registros[i].direccion, direccion);

                    break;
                case 8:
                    prefijo = validarnumeros("ESCRIBA SU PREFIJO EJEMPLO [646]: ", 0, 999);
                    num_telefono = validarnumeros("Ingrese su numero de telefono ejemplo [769-98-19]: ", 0, limite_maximo);
                    sprintf(numero_telefono, "%d%d", prefijo, num_telefono);
                    sprintf(numero_telefono_estructurado, "%c%c%c-%c%c%c-%c%c-%c%c", numero_telefono[0], numero_telefono[1], numero_telefono[2], numero_telefono[3], numero_telefono[4], numero_telefono[5], numero_telefono[6], numero_telefono[7], numero_telefono[8], numero_telefono[9]);
                    strcpy(registros[i].telefono, numero_telefono_estructurado);
                    break;
                }
            }
        }
        if (registros[i].Status == 2)
        {
            printf("EMPLEADO DADO DE BAJA\n");
            return;
        }
    }
    if (encontrado == 0)
    {
        printf("NO SE ENCONTRO LA MATRICULA\n\n");
        return;
    }
}
void BajaReg(Tdatos registros[], int *NumReg, int registro_a_eliminaar)
{
    int i;
    for (i = 0; i <= *NumReg; i++)
    {
        if (registros[i].key == registro_a_eliminaar)
        {
            if (registros[i].Status == 1)
            {
                registros[i].Status = 2;
                printf("REGISTRO DADO DE BAJA\n");

                (*NumReg)--;
            }
            else
            {
                printf("EL REGSITRO YA ESTA DADO DE BAJA");
            }
        }
    }
}
int imprmirParaEliminar(Tdatos registros[], int *NumReg, int registro)
{
    int i;
    for (i = 0; i <= *NumReg; i++)
    {
        if (registros[i].key == registro)
        {
            {
                printf("============================================================================\n");
                printf("| Numero de Empleado: %d                                               |\n", registros[i].numeroEmpleado);
                printf("|--------------------------------------------------------------------------|\n");
                printf("| Fecha de Ingreso: %-12s                                           |\n", registros[i].fechaIngreso);
                printf("| Nombre: %-25s                                        |\n", registros[i].nombre);
                printf("| Apellidos: %-28s                                  |\n", registros[i].apellidos);
                printf("| Fecha de nacimiento: %-12s                                        |\n", registros[i].fechaNacimiento);
                printf("| Numero Social: %-11d                                               |\n", registros[i].numero_de_la_seguridad_social);
                printf("| Direccion: %-30s                                |\n", registros[i].direccion);
                printf("| Numero de Telefono: %-11s                                        |\n", registros[i].telefono);
                printf("============================================================================\n");
            }
            return 1;
        }
    }

    printf("NO SE ENCONTRO LA MATRICULA\n\n");
    return 0;
}
void ImprimirEliminadosBinarios(Tdatos registros[], int NumReg, FILE *fa)
{
    int i, acu = 1;

    fa = fopen("archivos_eliminados.dll", "wb");
    for (i = 0; i < NumReg; i++)
    {
        if (!feof(fa))
        {
            fprintf(fa, " ");
        }
    }
    if (NumReg == 0)
    {
        fprintf(fa, "No hay registros para imprimir.\n");
        fclose(fa);
        return;
    }
    fprintf(fa, "\nRegistros ELIMINADOS:\n");
    fprintf(fa, " Num.Empl  Fecha Ingreso   Nombre                    Apellidos              Fecha Nacimiento    Num.Social   Direccion                      Telefono       \n");

    for (i = 0; i <= NumReg; i++)
    {
        if (registros[i].Status == 2)
        {
            fprintf(fa, " %-4d    %-13s   %-23s   %-20s   %-17s   %-10d   %-28s   %-9s  \n", registros[i].numeroEmpleado, registros[i].fechaIngreso, registros[i].nombre, registros[i].apellidos, registros[i].fechaNacimiento, registros[i].numero_de_la_seguridad_social, registros[i].direccion, registros[i].telefono);

            if (acu == 40)
            {
                getchar();
                acu = 0;
            }
            acu++;
        }
    }
    fclose(fa);
}
void ImprimirEnArchivo(Tdatos registros[], int NumReg, FILE *fa, char *NombreDArchivo)
{
    int i, acu = 1;
    fa = fopen(NombreDArchivo, "w");
    for (int i = 0; i < NumReg; i++)
    {
        if (!feof(fa))
        {
            fprintf(fa, " ");
        }
    }
    if (NumReg == 0)
    {
        fprintf(fa, "No hay registros para imprimir.\n");
        fclose(fa);
        return;
    }
    fprintf(fa, "\nRegistros almacenados:\n");
    fprintf(fa, " Num.Empl  Fecha Ingreso   Nombre                    Apellidos              Fecha Nacimiento    Num.Social   Direccion                      Telefono       \n");

    for (i = 0; i <= NumReg; i++)
    {
        if (registros[i].Status == 1)
        {
            fprintf(fa, " %-4d    %-13s   %-23s   %-20s   %-17s   %-10d   %-28s   %-9s  \n", registros[i].numeroEmpleado, registros[i].fechaIngreso, registros[i].nombre, registros[i].apellidos, registros[i].fechaNacimiento, registros[i].numero_de_la_seguridad_social, registros[i].direccion, registros[i].telefono);

            if (acu == 40)
            {
                getchar();
                acu = 0;
            }
            acu++;
        }
    }
    fclose(fa);
}
void ImprimirEnArchivoBinarioDeTexto(Tdatos registros[], int NumReg, FILE *fa, char *NombreDArchivo)
{
    int i, acu = 1;
    fa = fopen(NombreDArchivo, "wb");
    for (int i = 0; i < NumReg; i++)
    {
        if (!feof(fa))
        {
            fprintf(fa, " ");
        }
    }
    if (NumReg == 0)
    {
        fprintf(fa, "No hay registros para imprimir.\n");
        fclose(fa);
        return;
    }
    fprintf(fa, "\nRegistros almacenados:\n");
    fprintf(fa, " Num.Empl  Fecha Ingreso   Nombre                    Apellidos              Fecha Nacimiento    Num.Social   Direccion                      Telefono       \n");

    for (i = 0; i <= NumReg; i++)
    {
        if (registros[i].Status == 1)
        {
            fprintf(fa, " %-4d    %-13s   %-23s   %-20s   %-17s   %-10d   %-28s   %-9s  \n", registros[i].numeroEmpleado, registros[i].fechaIngreso, registros[i].nombre, registros[i].apellidos, registros[i].fechaNacimiento, registros[i].numero_de_la_seguridad_social, registros[i].direccion, registros[i].telefono);

            if (acu == 40)
            {
                getchar();
                acu = 0;
            }
            acu++;
        }
    }
    fclose(fa);
}
void CrearArchivoTemporal(FILE *fa)
{
    FILE *archivo_origen;
    char caracter;

    archivo_origen = fopen("datos.dll", "r");
    if (archivo_origen == NULL)
    {
        printf("No se pudo abrir el archivo externo.\n");
        return;
    }

    fa = fopen("datos.tmp", "w");
    if (fa == NULL)
    {
        printf("No se pudo crear o abrir el archivo.\n");
        fclose(archivo_origen);
        return;
    }

    while ((caracter = fgetc(archivo_origen)) != EOF)
    {
        fputc(caracter, fa);
    }

    fclose(archivo_origen);
    fclose(fa);
}