#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;
const int Seats = 40;
const int Max_Bus = 10;
const int Max_Tickets = 400;
class Bus{
    protected:
        string busNo;
        string route;
        double distanceKm;
        string departure;
        bool seatBooked[Seats];
        string passenger[Seats];
    public:
        void menu();
        void add_bus();
        void inputBus();
        virtual double farePerSeat() = 0;
        void list_buses();
        void seatmap();
        void viewseat_map();
        string getBusNo()
        {
            return busNo;
        }
        string getRoute()
        {
            return route;
        }
        double getDistance()
        {
            return distanceKm;
        }
        string getDeparture()
        {
            return departure;
        }
};
class NormalBus : public Bus
{
    private:
        double rate;
    public:
        NormalBus()
        {
            rate = 2.0;
        }
        double farePerSeat()
        {
            return 0;
        }
};
class DeluxeBus : public Bus
{
    private:
        double rate;
        double acCharge;
    public:
        DeluxeBus()
        {
            rate = 3.0;
            acCharge = 100;
        }
        double farePerSeat()
        {
            return 0;
        }
};
NormalBus normalBuses[Max_Bus];
DeluxeBus deluxeBuses[Max_Bus];
int normalCount = 0;
int deluxeCount = 0;
Bus :: Bus()
{
    busNo = "";
    route = "";
    distanceKm = 0;
    departure = "";
    for(int i = 0; i < Seats; i++)
    {
        seatBooked[i] = false;
        passenger[i] = "";
    }
}
void Bus :: list_buses()
{
    system("cls");
    cout<<"\n NORMAL BUSES \n";
    if(normalCount == 0)
    {
        cout<<"No Normal Bus available.\n";
    }
    else
    {
        for(int i = 0; i < normalCount; i++)
        {
            cout<<"\nBus No       : "<<normalBuses[i].getBusNo();
            cout<<"\nRoute        : "<<normalBuses[i].getRoute();
            cout<<"\nDistance     : "<<normalBuses[i].getDistance() << " KM";
            cout<<"\nDeparture    : "<<normalBuses[i].getDeparture();
            cout<<"\n";
        }
    }
    cout<<"\n DELUXE BUSES \n";
    if(deluxeCount == 0)
    {
        cout << "No Deluxe Bus available.\n";
    }
    else
    {
        for(int i = 0; i < deluxeCount; i++)
        {
            cout<<"\nBus No       : "<<deluxeBuses[i].getBusNo();
            cout<<"\nRoute        : "<<deluxeBuses[i].getRoute();
            cout<<"\nDistance     : "<<deluxeBuses[i].getDistance()<<" KM";
            cout<<"\nDeparture    : "<<deluxeBuses[i].getDeparture();
            cout<<"\n";
        }
    }
    system("pause");
}
void Bus :: add_bus()
{
    system("cls");
    int choice;
    cout<<"1. Normal Bus";
    cout<<"2. Deluxe Bus";
    cout<<"3. Exit";
    cout<<"Enter your Choice : ";
    cin>>choice;
    switch(choice)
    {
        case 1:
            if(normalCount >= Max_Bus)
            {
                cout<<"\nNormal Bus limit reached!\n";
                system("pause");
                return;
            }
            normalBuses[normalCount].inputBus();
            normalCount++;
            cout<<"\nNormal Bus added successfully!\n";
            system("pause");
            break;
        case 2:
            if(deluxeCount >= Max_Bus)
            {
                cout<<"\nDeluxe Bus limit reached!\n";
                system("pause");
                return;
            }
            deluxeBuses[deluxeCount].inputBus();
            deluxeCount++;
            cout<<"\nDeluxe Bus added successfully!\n";
            system("pause");
            break ;
        case 3:
            exit(0);
        default:
            cout<<"Invalid Choice! Please Try Again";
            system("pause");
    }
}
void Bus :: inputBus()
{
    while(true)
    {
        cout<<"\nEnter Bus Number: ";
        cin>>busNo;

        if(busNo.empty())
        {
            cout<<"Bus Number cannot be empty!\n";
        }
        else
        {
            break;
        }
    }
    cin.ignore();
    while(true)
    {
        cout<<"Enter Route: ";
        getline(cin, route);

        if(route.empty())
        {
            cout<<"Route cannot be empty!\n";
        }
        else
        {
            break;
        }
    }
    while(true)
    {
        cout<<"Enter Distance (KM): ";
        if(cin>>distanceKm && distanceKm > 0)
        {
            break;
        }
        cout<<"Invalid distance! Please enter a positive number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore();
    while(true)
    {
        cout<<"Enter Departure Time: ";
        getline(cin, departure);
        if(departure.empty())
        {
            cout<<"Departure time cannot be empty!\n";
        }
        else
        {
            break;
        }
    }
}
void Bus :: seat_map()
{
    system("cls");
    cout<<endl;
    cout<<"            BUS SEAT MAP\n";
    cout<<"       LEFT SIDE          RIGHT SIDE\n\n";
    for(int i = 0; i < Seats; i += 4)
    {
        if(seatBooked[i])
            cout<<"   [XX] ";
        else
            cout<<"   [" << setw(2) << setfill('0') << i + 1 << "] ";
        if(seatBooked[i + 1])
            cout<<"[XX] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 2 << "] ";
        cout << "      ";
        if(seatBooked[i + 2])
            cout<<"[" << "XX" << "] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 3 << "] ";
        if(seatBooked[i + 3])
            cout << "[" << "XX" << "] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 4 << "] ";
        cout<<endl;
        setfill(' ');
    }
    cout<<"XX = Booked\n";
    cout<<"Number = Available\n";
    system("pause");
}
void Bus :: viewseat_map()
{
    system("cls");
    if(normalCount == 0 && deluxeCount == 0)
    {
        cout<<"\nNo buses available!\n";
        system("pause");
        return;
    }
    int choice;
    cout<<"\n VIEW SEAT MAP \n";
    cout<<"1. Normal Bus\n";
    cout<<"2. Deluxe Bus\n";
    cout<<"3. Back\n";
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice == 1)
    {
        if(normalCount == 0)
        {
            cout<<"\nNo Normal Bus available!\n";
            system("pause");
            return;
        }
        cout<<"\nAvailable Normal Buses:\n";
        for(int i = 0; i < normalCount; i++)
        {
            cout<<i + 1 << ". "<< normalBuses[i].getBusNo()<< " - "<< normalBuses[i].getRoute()<< endl;
        }
        int busChoice;
        cout<<"\nSelect Bus: ";
        cin>>busChoice;
        if(busChoice < 1 || busChoice > normalCount)
        {
            cout<<"Invalid bus choice!\n";
            system("pause");
            return;
        }
        normalBuses[busChoice - 1].showSeatMap();
    }
    else if(choice == 2)
    {
        if(deluxeCount == 0)
        {
            cout<<"\nNo Deluxe Bus available!\n";
            system("pause");
            return;
        }
        cout<<"\nAvailable Deluxe Buses:\n";
        for(int i = 0; i < deluxeCount; i++)
        {
            cout<<i + 1 << ". "<< deluxeBuses[i].getBusNo()<< " - "<< deluxeBuses[i].getRoute()<< endl;
        }
        int busChoice;
        cout<<"\nSelect Bus: ";
        cin>>busChoice;
        if(busChoice < 1 || busChoice > deluxeCount)
        {
            cout<<"Invalid bus choice!\n";
            system("pause");
            return;
        }
        deluxeBuses[busChoice - 1].showSeatMap();
    }
    else if(choice == 3)
    {
        return;
    }
    else
    {
        cout<<"\nInvalid choice!\n";
        system("pause");
    }
}
void Bus ::menu()
{
    p:
    system("cls");
    int choice;
    cout<<"Menu";
    cout<<"1. Add Bus";
    cout<<"2. List Buses";
    cout<<"3. View Seat Map";
    cout<<"4. Book ticket";
    cout<<"5. Cancel Ticket";
    cout<<"6. Search Ticket";
    cout<<"7. Save & Exit";
    cout<<"Enter Your choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1:
            add_bus();
            break;
        case 2:
            list_buses();
            break;
        case 3:
            viewseat_map();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            exit(0);
        default:
            cout<<"Invalid Choice! Please Try Again";
    }
    goto p;
}
int main()
{
    Bus b;
    b.menu();
    return 0;
}