//
//  main.cpp
//  Progetto
//
//  Created by Luigi Giugliano on 02/01/14.
//  Copyright (c) 2014 Luigi Giugliano. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;



//stutture dati

struct BigNatural{
    char digit;
    BigNatural *next;
};

struct Variabili{
    string nome;
    BigNatural *valore;
    Variabili *next;
};



//funzioni Memorizzazione

BigNatural *crea_BigNatural();
BigNatural *crea_BigNaturalString(string valore);

void salva_su_file(Variabili *var);
Variabili *leggi_da_file(Variabili *p);
Variabili *add(Variabili *last,string nome,BigNatural *p);

Variabili *cercaNome(Variabili *p,string s);

void stampa_variabili(Variabili *p);
string return_lista_inverso(BigNatural *p);
void visualizza_lista(BigNatural *p);


//successore e predecessore
BigNatural *successore(BigNatural *p);
BigNatural *precedessore(BigNatural *p);

//confronto
double confronto(BigNatural *p,BigNatural *s);

//addizione e moltiplicazione
BigNatural *stessasize(BigNatural *p,BigNatural *s);
BigNatural *addizione(BigNatural *p,BigNatural *s);
BigNatural *moltiplicazione(BigNatural *p,BigNatural *s);


void menu();


void menu(){
    
    cout << "Scegliere una tra le seguenti opzioni :\n";
    cout << "\t\t 1)Aggiungere variabile\n";
    cout << "\t\t 2)Leggere da file\n";
    cout << "\t\t 3)Scrivere su file\n";
    cout << "\t\t 4)Stampare lista variabili\n";
    cout << "\t\t 5)Successore\n";
    cout << "\t\t 6)Predecessore\n";
    cout << "\t\t 7)Confronto\n";
    cout << "\t\t 8)Addizione\n";
    cout << "\t\t 9)Moltiplicazione\n";
    cout << "\t\t 0)Esci\n";
}


BigNatural *crea_BigNatural(){
    cout << "Inserisci il numero\n";
    BigNatural *p;
    string string ="";
    cin >> string;
    
    
    unsigned long n=string.length();
    
    if(n==1){
        p=new BigNatural;
        p->digit=string.at(n-1);
        p->next=0;
    }else{
    
        
        BigNatural *punt;
    
        p=new BigNatural;
        //primo elemento
        p->digit=string.at(n-1);
        punt=p;
    
        //elementi restanti
        for(unsigned i=n-2;i>0;i--){
            punt->next= new BigNatural;
            punt=punt->next;
            punt->digit=string.at(i);
        
        }
    
        //ultimo numero
        punt->next= new BigNatural;
        punt=punt->next;
        punt->digit=string.at(0);
        punt->next=0;
        
    }
    
    return p;
}

BigNatural *crea_BigNaturalString(string valore){
    BigNatural *p;
    string string=valore;
    
    unsigned long n=string.length();
    
    if(n==1){
        p=new BigNatural;
        p->digit=string.at(n-1);
        p->next=0;
        return p;
    }else{
        
        BigNatural *punt;
        
        p=new BigNatural;
        //primo elemento
        p->digit=string.at(n-1);
        punt=p;
        
        //elementi restanti
        for(unsigned i=n-2;i>0;i--){
            punt->next= new BigNatural;
            punt=punt->next;
            punt->digit=string.at(i);
            
        }
        
        //ultimo numero
        punt->next= new BigNatural;
        punt=punt->next;
        punt->digit=string.at(0);
        punt->next=0;
        
    }
    
    return p;
}

void stampa_variabili(Variabili *p){
    Variabili *punt;
    cout<< "List: " << "\n";
    punt=p;
    while(punt!=0){
        cout<<"Nome: "<<punt->nome;
        cout<<" Valore: "<<return_lista_inverso(punt->valore);
        cout << "\n";
        punt=punt->next;
        
    }
    
    cout<< endl;
    
}

string return_lista_inverso(BigNatural *p){
    string stringa;
    if(p==NULL)
        return "";
    stringa+=return_lista_inverso(p->next);
    stringa+= string(1,p->digit);
    
    return stringa;
    
}

void salva_su_file(Variabili *p){
    ofstream myfile ("A.txt", ios::trunc); //metti il tuo percorso del file
    if (myfile.is_open())
    {
         while(p!=0){
             myfile << p->nome;
             myfile << "=";
             myfile << return_lista_inverso(p->valore) << "\n";
             p=p->next;
         }
        
        myfile.close();
    }
}

Variabili *leggi_da_file(Variabili *p){
    
    Variabili *prev,*punt;
    string line="";
    char *vettore;
    
    if(p==0){
        p= new Variabili;
        punt=p;
    }else{
        
        punt=p;
        //cerca ultimo elemento
        while(punt->next!=0){
            punt=punt->next;
        }
        punt->next= new Variabili;
        punt=punt->next;
    }
    
    ifstream myfile ("A.txt");    //metti il tuo percorso del file
    if (myfile.is_open()){
        while ( getline (myfile,line) )
        {
            vettore = (char *)line.c_str();
            
            unsigned long i=line.find("=");
            string nome= line.substr(0,i);
            string valore= line.substr(i+1);
            
            punt->nome=nome;
            punt->valore=crea_BigNaturalString(valore);
            
            
            prev=punt;
            punt->next=new Variabili;
            punt=punt->next;
                
            }
    }
    
    prev->next=0;
    return p;
}

Variabili *add(Variabili *head,string nome,BigNatural *p){
    Variabili *punt,*temp;
    
    
    temp= new Variabili;
    temp->nome=nome;
    temp->valore=p;
    
    
    punt=head;
    
    //la lista è vuota
    if(punt==0){
        return temp;
    }
    //cerca ultimo elemento
    while(punt->next!=0){
        punt=punt->next;
    }
    punt->next=temp;
    return temp;
    
}

Variabili *cercaNome(Variabili *p,string s){
    Variabili *punt;
    punt=p;
    if(p==0)
        return NULL;
    else{
        while(punt!=0){
            
        if(punt->nome.compare(s)==0)
            return punt;
        
        punt=punt->next;
        }
    }
    return NULL;
}

BigNatural *successore(BigNatural *p){
    BigNatural *vol;
    BigNatural *temp=p;
    char digit;
    int var;
    
    while(temp!=0){
        digit=temp->digit;
        var=digit-'0';
        var++;
        if(var>=10){
            var= var % 10;
            temp->digit=(char)(((int)'0')+var);
            
            if(temp->next==0){
                vol=new BigNatural;
                vol->digit='0';
                temp->next=vol;
            }
            temp=temp->next;
            
        }
        else{
            
            temp->digit=(char)(((int)'0')+var);
            break;
        }
    }
    
    return p;
}

BigNatural *precedessore(BigNatural *p){
    BigNatural *temp=p;
    BigNatural *prev=p;
    bool flag=false;
    char digit;
    int var;
    
    if(temp->next==0 && temp->digit=='0'){
        return temp;
    }
    
    if(temp->next==0 && temp->digit=='1'){
        temp->digit='0';
        return temp;
    }
    
    while(temp!=0){
        digit=temp->digit;
        var=digit-'0';
        if(var==0){
            var=9;
            flag=true;
            temp->digit=(char)(((int)'0')+var);
        }
        else if(var==1 && temp->next==0){
            prev->next=0;
            break;
        }else{
            var--;
            temp->digit=(char)(((int)'0')+var);
            break;
        }
        if(flag){
            prev=temp;
            temp=temp->next;
        }
    }
    
    return p;
}

int size(BigNatural *p){
    BigNatural *punt=p;
    int i=0;
    while(punt!=0){
        i++;
        punt=punt->next;
    }
    return i;
}


double confronto(BigNatural *p,BigNatural *s){
    double i = 0;
    
    if(size(p)>size(s))
        return 1;
    else{
        if(size(p)<size(s))
            return -1;
    }
    
    if(p==0 || s==0)
        return 0;
    i+=(confronto(p->next, s->next));
    if(p->digit>s->digit){
        i+=1*pow(2,-size(p));
        //cout << i <<"\n";
    }
    else{
        if(p->digit==s->digit)
            i+=0;
        else{
            i+=-1*pow(2,-size(p));
        }
    }
    
    return i;
}

BigNatural *stessasize(BigNatural *p,BigNatural *s){
    
    
    
    if(size(p)>=size(s))
        return p;
    else{
        int j=size(s)-size(p);
        string stringa="";
        
        while(j>0){
            
            
            stringa+="0";
            j--;
            
        }
        
        stringa+=return_lista_inverso(p);
        BigNatural *appoggio= crea_BigNaturalString(stringa);
        //cout << return_lista_inverso(appoggio);
        return appoggio;
    }
    
        
}

BigNatural *addizione(BigNatural *p,BigNatural *s){
    BigNatural *vol;
    BigNatural *temp1=p;
    BigNatural *temp2=s;
    

    char digit1,digit2;
    int var1,var2=0;
    bool flag=false;
   
    if(size(p)>=size(s)){
   
        while(temp1!=0){
            var1=temp1->digit-'0';
            while(var1>10){
                var1=var1/10;
            }
            //cout << var1;
        
            
        
       if(temp2==0)
           var2=0;
       else{
           var2=temp2->digit-'0';
           while(var2>10){
               var2=var2/10;
           }
           //cout << var1;
           
       }
           
        //cout << "Var 1: "<< var1 <<" Var 2: "  << var2 ;
        
        var1+=var2;
        
        //cout << "somma: " << var1 << "\n";
        if(flag)
            var1++;
        
        if(var1>=10){
            var1=var1%10;
            flag=true;
            temp1->digit=(char)(((int)'0')+var1);
       
        
            //cout << temp1->digit << var1 << var2;
            
            
            if(temp1->next==0){
                vol=new BigNatural;
                vol->digit='0';
                temp1->next=vol;
            }
            temp1=temp1->next;
            
            if(!temp2==0)
                temp2=temp2->next;
        
        }else{
            
            temp1->digit=(char)(((int)'0')+var1);
            flag=false;
            temp1=temp1->next;
            
            if(!temp2==0)
                temp2=temp2->next;
            
        }
        
    }
    }/**else{
        while(temp2!=0){
        var1=temp1->digit-'0';
        var2=temp2->digit-'0';
    
        var1+=var2;
        if(flag)
            var1++;
        if(var1>=10){
            var1=var1%10;
            flag=true;
            temp1->digit= (char)(((int)'0')+var1);
            
            if(temp1->next==0){
                vol=new BigNatural;
                vol->digit='0';
                temp1->next=vol;
                if(temp2->next==0){
                    temp1->next->digit='1';
                    break;
                }
            }
            temp1=temp1->next;
            temp2=temp2->next;
        }else{
            temp1->digit= (char)(((int)'0')+var1);
            flag=false;
             if(temp1->next==0 && temp2->next!=0 ){
                 vol=new BigNatural;
                 vol->digit='0';
                 temp1->next=vol;
            }
            temp1=temp1->next;
            temp2=temp2->next;
        }
    }
    }*/
    
    return p;
}

BigNatural *moltiplicazione(BigNatural *p,BigNatural *s){

    BigNatural *temp1=p;					//prima variabile 
    BigNatural *temp2=s;					//seconda variabile 
    BigNatural *appoggio=0,*punt=0,*temp3=0;	//variabili di appoggio di tipo big natural
    Variabili *temptot=0,*tot=0,*puntvar=0;		//variabili di appoggio di tipo big variabili
    string stringa;
    

    if(size(s)==1 && s->digit=='0')				//se la lunghezza è uguale a 1 e il digit è zero
        return crea_BigNaturalString("0");			//restituisco 0 (esempio 15x0)
    
    int i=-size(p);								//inserisco dentro i la dimensione di p però al negativo
    int molt,j,var1,var2,resto=0;				
    
    while(temp2!=0){							//finche temp2 è diverso da 0 (ci sono altri digit)
        var2=0;									//inizializzo var2
        var2=temp2->digit-'0';					//inserisco dentro var2 il digit di temp2
        
        //cout << "var2: " << var2 << "\n";
        
        j=size(p)+i;							//dentro j metto la size di p + i (che era la size di s però al negativo)
												//ovvero 153x22 i=-3 j=3-3 =0; (prima iterazione =0) (seconda uguale a 1)
        //cout << "variabile j: " << j << "\n";
        
        //cout << "inizializzazione zeri: " << return_lista_inverso(appoggio) << "\n";
        
        stringa="";							//inizializzo una stringa vuota
        while(j>0){							//questo while creerà una stringa del tipo "000" in base alla lunghezza di j
            
            
            stringa+="0";
            j--;
            
        }
        if(stringa.length()>0){						//se la lunghezza della stringa è maggiore di 0
            appoggio=crea_BigNaturalString(stringa);		//crea un big natural avente come numero quegli zeri
            
            temp3=appoggio;						 
            while(temp3->next!=0){					//cerca l'ultimo digit all'interno del big natural appena creato (dopo gli inserirà il numero ad esempio 02 sarà 20)
                temp3=temp3->next;
            }
            
        }
        
        
        punt=temp3;								//punt contiene il primo spazio vuoto dopo l'ultimo numero
        
        //cout << stringa << "\n";
        //cout << "inizializzazione zeri: " << return_lista_inverso(appoggio) << "\n";
        //cout << "size: " << size(appoggio) << "\n";
        
        while(temp1!=0){							//finche c'è un digit dentro il temp1
            var1=0;
            var1=temp1->digit-'0';					//dentro var1 metto il digit
            
            //cout << "var1: " << var1 << "\n";
            
            if(appoggio==0){						//se appogio è uguale a zero (ovvero non esiste)
                appoggio=new BigNatural;				//inizializza appoggio
                punt=appoggio;
                //cout << "creazione punt\n";
            }else{									//altrimenti vuol dire che la lista appoggio (quegli degli zeri) non è vuota
                temp3=new BigNatural;					//inserisce un nuovo elemento
                punt->next=temp3;						//glie lo fa puntare e va al sucessivo
                punt=punt->next;
            }
            molt=((var1*var2)+resto)%10;			//calcola la moltiplicazione
            resto=((var1*var2)+resto)/10;			//calcola il resto
            
            //cout << "moltiplicazione: " << molt << " resto: " << resto << "\n";
            
            punt->digit=(char)(((int)'0')+molt);	//nel digit di punt gli inserisce il risultato della moltiplicazione
            
            //cout << "digit" << punt->digit << "\n";
            
            
            
            if(temp1->next==0 && resto>0){			//se non ci sono più digit in temp1 e il resto è maggiore di zero
                
                temp3=new BigNatural;						//inserisco un nuovo elemento
                temp3->digit=(char)(((int)'0')+resto);		//gli metto dentro il resto
                punt->next=temp3;							//punto al successivo
                break;										//brekko perchè è finita la moltiplicazione
            }
            
				
            temp1=temp1->next;					//vado al prossimo temp1
        }
        molt=0;										//reinizializzo a zero moltiplicaizone e resto
        resto=0;
        
        temp2=temp2->next;							//vado al prossimo temp2
        
        
        if(tot==0){									//se tot è uguale a zero
            tot=new Variabili;							// lo inizializzo
            puntvar=tot;								//faccio puntare il puntatore a tot
            puntvar->valore=appoggio;					//in puntvar di valore  gli inserisco appoggio (ovvero il risultato di una moliplicazione, ad esempio 15x2)
        }else{										//se tot non è vuota (vuol dire che già dentro c'è un risultato parziale
            temptot=new Variabili;						//praticamente creo una nuova variabile dentro le metto il valore appoggio
            temptot->valore=appoggio;
            puntvar->next=temptot;
            puntvar=puntvar->next;
        }
        
        //cout << "moltiplicazione completa: " << return_lista_inverso(puntvar->valore) << "\n";
        //cout << "size: " << size(appoggio);
        
        appoggio=0,punt=0,temp3=0;				//risettto a zero tutto
        temptot=0;
        
        
        
        temp1=p;
        i++;								//incremento i così alle successive iterazioni cambierà il valore di j
        
        
    }
    
    
    
    BigNatural *add=crea_BigNaturalString("0");			//creo un big natural vuoto (ovvero di valore zero)
    while(tot!=0){										//mi scorro tutte le variabili dove la head è tot
        
        //cout << "valore add: " << return_lista_inverso(add) << " valore tot: "<< return_lista_inverso(tot->valore)<<"\n";
        
        add=addizione(add,tot->valore);					//aggiungo dentro add i vari valori contenuti in tot (esempio= tot= 153x2 e 153x20 faccio 0+306+3060)
        
        tot=tot->next;									//vado al successivo
    }

    delete temp3;										//cancello tutte le variabili usate (come chiede nella traccia)
    delete appoggio;
    delete punt;
    delete temptot;
    return add;											//restituisco il risultato
    
}


int main(int argc, const char * argv[]){
    int scelta = 0;
    //char valore;
    Variabili *head = 0,*temp,*temp1;
    string nome,nome1;
   
    do{
        menu();
        cout << ">>";
        cin >> scelta;
        
        //cout << scelta;
        
        switch (scelta) {
            
            case 1:{
                cout << "inserisci il nome della variabile che vuoi inserire\n";
                cin >> nome;
                cout << "inserisci il valore della variabile che vuoi inserire\n";
                string valore;
                cin >> valore;
                if(head==0)
                    head=add(head, nome, crea_BigNaturalString(valore));
                else
                    add(head, nome, crea_BigNaturalString(valore));
                cout << "Fatto! \n";
                break;
            }
            
            case 2:{
                head=leggi_da_file(head);
                cout << "Fatto! \n";
                break;
            }
                
            case 3:{
                salva_su_file(head);
                cout << "Fatto! \n";
                break;
            }
                
            case 4:{
                if(head==0){
                    cout << "Lista vuota, caricare da file \n";
                    break;
                }
                stampa_variabili(head);
                cout << "Fatto! \n";
                break;
            }
                
            case 5:{
                cout << "Inserire il valore della variabile di cui vuoi il sucecssore\n";
                cin >> nome;
                temp=cercaNome(head, nome);
                if(temp==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }
                temp->valore=successore(temp->valore);
                cout << "Fatto! \n";
                break;
            }
                
            case 6:{
                cout << "Inserire il valore della variabile di cui vuoi calcolare il predecessore\n";
                cin >> nome;
                temp=cercaNome(head, nome);
                if(temp==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }
                temp->valore=precedessore(temp->valore);
                cout << "Fatto! \n";
                break;
            }
                
            case 7:{
                cout << "Inserire il valore della prima variabile da confrontare\n";
                cin >> nome;
                temp=cercaNome(head, nome);
                if(temp==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }

                cout << "Inserire il valore della seconda variabile da confrontare\n";
                cin >> nome1;
                temp1=cercaNome(head, nome1);
                
                if(temp1==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }

                
                double val= confronto(temp->valore, temp1->valore);
                if(val>0)
                    cout << temp->nome << " è maggiore di: " << temp1->nome << "\n";
                else{
                    if(val<0)
                        cout << temp1->nome << " è maggiore di: " << temp->nome << "\n";
                    else
                        cout << "le due variabili sono uguali\n";
                }
                break;
            }
            
            case 8:{
                
                cout << "Inserire il valore della prima variabile da addizzionare\n";
                cin >> nome;
                temp=cercaNome(head, nome);
                if(temp==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }
                
                cout << "Inserire il valore della seconda variabile da addizzionare\n";
                cin >> nome1;
                temp1=cercaNome(head, nome1);
                
                if(temp1==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }
                
                temp->valore=stessasize(temp->valore, temp1->valore);
                //cout << return_lista_inverso(temp->valore);
                temp->valore=addizione(temp->valore, temp1->valore);
                cout << "Fatto! \n";
                //cout << "Addizzione: " << return_lista_inverso(temp->valore) <<"\n";
                break;

            }
            
            case 9:{
                
                cout << "Attenzione scegliere come prima variabile una maggiore-uguale della seconda\n";
                cout << "Inserire il valore della prima variabile da moltiplicare\n";
                cin >> nome;
                temp=cercaNome(head, nome);
                if(temp==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }
                
                cout << "Inserire il valore della seconda variabile da moltiplicare\n";
                cin >> nome1;
                temp1=cercaNome(head, nome1);
                
                if(temp1==NULL){
                    cout << "Variabile non trovata\n";
                    break;
                }
                if(size(temp1->valore)>size(temp->valore)){
                    cout << "Prima variabile minore della seconda scegliere una giusta combinazione\n";
                    break;
                }else{
                    temp->valore= moltiplicazione(temp->valore, temp1->valore);
                }
                
                cout << "Fatto! \n";
                break;
            }
            
            case 0:{
                cout << "Arrivederci \n";
                break;
            }
                
            default:
                
                cout << "Scegliere un valore valido \n";
                break;
        }
        
        
        
        
    }while(scelta!=0);
    
    
}

